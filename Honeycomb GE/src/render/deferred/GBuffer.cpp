#include "..\..\..\include\render\deferred\GBuffer.h"

#include <GL/glew.h>

#include "..\..\..\include\base\GameWindow.h"
#include "..\..\..\include\debug\Logger.h"

using Honeycomb::Base::GameWindow;
using Honeycomb::Debug::Logger;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb::Render::Deferred {
	const std::string GBuffer::TEXTURE_SHADER_NAMES[] = {
		"gBufferPosition",
		"gBufferDiffuse",
		"gBufferNormal",
		"gBufferTexture",
		"gBufferSpecular",
		"gBufferDepth",
		"gBufferFinal"
	};

	GBuffer::GBuffer() {

	}

	GBuffer::~GBuffer() {

	}

	void GBuffer::bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, this->frameBufferObj);
	}

	void GBuffer::bindDraw() {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, this->frameBufferObj);
	}

	void GBuffer::bindDrawGeometry() {
		this->bindDraw();

		// Set the drawing buffers
		GLenum drawBuffers[] = {
			GL_COLOR_ATTACHMENT0 + GBufferTextureType::POSITION, 
			GL_COLOR_ATTACHMENT0 + GBufferTextureType::DIFFUSE, 
			GL_COLOR_ATTACHMENT0 + GBufferTextureType::NORMAL,
			GL_COLOR_ATTACHMENT0 + GBufferTextureType::TEXTURE,
			GL_COLOR_ATTACHMENT0 + GBufferTextureType::SPECULAR
		};
		glDrawBuffers(5, drawBuffers);
	}

	void GBuffer::bindDrawLight(ShaderProgram &shader) {
		glDrawBuffer(GL_COLOR_ATTACHMENT0 + GBufferTextureType::FINAL);
		
		this->bindColorTextures(shader);
	}

	void GBuffer::bindRead() {
		glBindFramebuffer(GL_READ_FRAMEBUFFER, this->frameBufferObj);
	}

	void GBuffer::bindTexture(const GBufferTextureType &type) {
		this->bufferTextures[type].bind();
	}

	void GBuffer::bindTexture(const GBufferTextureType &type, ShaderProgram
			&shader) {
		shader.setUniform_i(GBuffer::TEXTURE_SHADER_NAMES[type], type);
		this->bufferTextures[type].bind(type);
	}

	void GBuffer::bindColorTextures(ShaderProgram &shader) {
		this->bindTexture(GBufferTextureType::POSITION, shader);
		this->bindTexture(GBufferTextureType::DIFFUSE, shader);
		this->bindTexture(GBufferTextureType::NORMAL, shader);
		this->bindTexture(GBufferTextureType::SPECULAR, shader);
	}

	void GBuffer::bindStencil() {
		glDrawBuffer(GL_NONE); // Disable drawing to buffers in stencil pass
	}

	void GBuffer::destroy() {
		GLuint fbo = this->frameBufferObj;
		glDeleteFramebuffers(1, &fbo);
	}

	void GBuffer::frameBegin() {
		// Clear the final texture attached to this GBuffer
		this->bindDraw();
		glDrawBuffer(GL_COLOR_ATTACHMENT0 + GBufferTextureType::FINAL);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	const int& GBuffer::getFrameBuffer() const {
		return this->frameBufferObj;
	}

	bool GBuffer::initialize() {
		if (this->isInitialized) return false;

		GameWindow::getGameWindow()->getResizeEvent() += 
			this->windowResizeHandler;
		this->windowResizeHandler += std::bind(&GBuffer::resizeTextures, this);

		// Fetch the Height and Width of the Game Window
		this->textureHeight = GameWindow::getGameWindow()->getWindowHeight();
		this->textureWidth = GameWindow::getGameWindow()->getWindowWidth();

		// Generate the Frame Buffer Object for this G-Buffer
		GLuint fbo;
		glGenFramebuffers(1, &fbo);
		this->frameBufferObj = fbo;
		
		// Bind the Buffer so that it may be written to and modified in the
		// remaining initialization steps.
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		
		// Stores all of the color (non-depth) buffers, for a test to see if
		// everything was correctly initialized.
		GLenum colorBuffers[GBufferTextureType::DEPTH];

		// Generate the textures for everything but the Depth Buffer
		for (int i = 0; i < GBufferTextureType::DEPTH; i++) {
			// Create an empty texture
			this->bufferTextures[i].initialize();
			this->bufferTextures[i].bind();
			this->bufferTextures[i].setImageData(NULL, GL_FLOAT, GL_RGB32F, 
				GL_RGB, this->textureWidth, this->textureHeight);

			// Bind the texture to the Frame Buffer Object
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
				GL_TEXTURE_2D, this->bufferTextures[i].getTextureID(), 0);

			colorBuffers[i] = GL_COLOR_ATTACHMENT0 + i; // Add to Color Buffers
		}

		// Create the Depth Buffer Texture
		this->bufferTextures[GBufferTextureType::DEPTH].initialize();
		this->bufferTextures[GBufferTextureType::DEPTH].bind();
		this->bufferTextures[GBufferTextureType::DEPTH].setImageData(NULL, 
			GL_FLOAT_32_UNSIGNED_INT_24_8_REV, GL_DEPTH32F_STENCIL8, 
			GL_DEPTH_STENCIL, this->textureWidth, this->textureHeight);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
			GL_TEXTURE_2D, this->bufferTextures[GBufferTextureType::DEPTH].
			getTextureID(), 0);

		// Create the Final Image Texture
		this->bufferTextures[GBufferTextureType::FINAL].initialize();
		this->bufferTextures[GBufferTextureType::FINAL].bind();
		this->bufferTextures[GBufferTextureType::FINAL].setImageData(NULL,
			GL_FLOAT, GL_RGBA, GL_RGB, this->textureWidth, this->textureHeight
		);
		glFramebufferTexture2D(GL_FRAMEBUFFER, 
			GL_COLOR_ATTACHMENT0 + GBufferTextureType::FINAL,
			GL_TEXTURE_2D, this->bufferTextures[GBufferTextureType::FINAL].
			getTextureID(), 0);

		// Bind the 5 buffers as the color buffers which will be used when
		// drawing & check that all the color buffers were initialized properly
		glDrawBuffers(GBufferTextureType::DEPTH, colorBuffers);
		
		GLenum bufferStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		
		if (bufferStatus != GL_FRAMEBUFFER_COMPLETE) {
			Logger::getLogger().logError(__FUNCTION__, __LINE__,
				"Unable to Create Deferred GBuffer!");
		}

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // Bind Default FrameBuffer
		
		this->isInitialized = true;
		return true;
	}

	void GBuffer::unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void GBuffer::unbindDraw() {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	}

	void GBuffer::unbindRead() {
		glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	}

	void GBuffer::resizeTextures() {
		this->textureHeight = GameWindow::getGameWindow()->getWindowHeight();
		this->textureWidth = GameWindow::getGameWindow()->getWindowWidth();
		
		for (int i = 0; i < GBufferTextureType::DEPTH; i++) {
			this->bufferTextures[i].setImageData(NULL, GL_FLOAT, GL_RGB32F,
				GL_RGB, this->textureWidth, this->textureHeight);
		}

		this->bufferTextures[GBufferTextureType::DEPTH].setImageData(NULL,
			GL_FLOAT_32_UNSIGNED_INT_24_8_REV, GL_DEPTH32F_STENCIL8,
			GL_DEPTH_STENCIL, this->textureWidth, this->textureHeight);
		this->bufferTextures[GBufferTextureType::FINAL].setImageData(NULL,
			GL_FLOAT, GL_RGBA, GL_RGB, this->textureWidth, this->textureHeight
		);
	}
}