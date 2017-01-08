#include "..\..\..\include\render\deferred\GBuffer.h"

#include <GL/glew.h>

#include "..\..\..\include\base\GameWindow.h"
#include "..\..\..\include\debug\Logger.h"

using Honeycomb::Base::GameWindow;
using Honeycomb::Debug::Logger;

namespace Honeycomb::Render::Deferred {
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

	void GBuffer::bindRead() {
		glBindFramebuffer(GL_READ_FRAMEBUFFER, this->frameBufferObj);
	}

	void GBuffer::bindTexture(const GBufferTextureType &type) {
		glBindTexture(GL_TEXTURE_2D, 
			this->bufferTextures[type].getTextureID());
	}

	void GBuffer::destroy() {
		GLuint fbo = this->frameBufferObj;
		glDeleteFramebuffers(1, &fbo);
	}

	const int& GBuffer::getFrameBuffer() const {
		return this->frameBufferObj;
	}

	bool GBuffer::initialize() {
		if (this->isInitialized) return false;

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

		// Create a specific Depth Texture for the Depth Buffer
		this->bufferTextures[GBufferTextureType::DEPTH].initialize();
		this->bufferTextures[GBufferTextureType::DEPTH].bind();
		this->bufferTextures[GBufferTextureType::DEPTH].setImageData(NULL, 
			GL_FLOAT, GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, 
			this->textureWidth, this->textureHeight);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
				GL_TEXTURE_2D, this->bufferTextures[GBufferTextureType::DEPTH].
				getTextureID(), 0);

		// Bind the 4 buffers as the color buffers which will be used when
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
}