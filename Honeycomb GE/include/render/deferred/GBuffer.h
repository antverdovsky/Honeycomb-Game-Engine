#pragma once
#ifndef G_BUFFER_H
#define G_BUFFER_H

#include "../../base/GLItem.h"
#include "../../conjuncture/EventHandler.h"
#include "../../graphics/Texture2D.h"
#include "../../render/Renderer.h"

namespace Honeycomb { namespace Render { namespace Deferred {
	enum GBufferTextureType {
		// Uses GL_RGB16F
		POSITION,		// Position
		NORMAL,			// Normals

		// Uses GL_RGBA32UI
		MATERIAL,		// Albedo (x.rgb), Ambient (y.rgb), Diffuse (z.rgb), 
						// Specular (w.rgb) & Shininess (w.w)
		
		// Uses GL_DEPTH32F_STENCIL8
		DEPTH,			// Depth Buffer (== to # of color buffers)
		
		// When post processing, we cannot read from and write to the same
		// buffer, so we must read from one and write to the other, so we
		// require two final buffers.
		// Uses GL_RGB
		FINAL_1,		// Final Buffer 1
		FINAL_2,		// Final Buffer 2

		COUNT			// The total number of buffers
	};

	class GBuffer : public Honeycomb::Base::GLItem {
		friend class DeferredRenderer;
	public:
		// Event Handler for the Window Resize Event
		Honeycomb::Conjuncture::EventHandler windowResizeHandler;

		/// Instantiates a blank G Buffer structure.
		GBuffer();

		/// Deinstantiates this G Buffer structure.
		~GBuffer();

		/// Binds this G Buffer for both drawing to it, and reading from it.
		void bind();

		/// Binds this G Buffer for only drawing to it.
		void bindDraw();

		/// Binds this G Buffer for drawing Geometry to it from the Deferred
		/// Renderer.
		void bindDrawGeometry();

		/// Binds this G Buffer for drawing Light to it from the Deferred
		/// Renderer. All the color textures of this GBuffer will be binded
		/// to the shader provided.
		/// ShaderProgram &shader : The Shader Program with which the lights
		///							will be drawn.
		void bindDrawLight(Honeycomb::Shader::ShaderProgram &shader);

		/// Binds this G Buffer for drawing Light to it from the Deferred
		/// Renderer. If the light is of type Ambient Light, only the Diffuse
		/// texture will be binded, otherwise, all the color textures of this
		/// GBuffer will be binded to the shader provided.
		/// ShaderProgram &shader : The Shader Program with which the lights
		///							will be drawn.
		/// const LightType &type : The type of the light which will be drawn.
		void bindDrawLight(Honeycomb::Shader::ShaderProgram &shader, const
				Honeycomb::Component::Light::LightType &type);

		/// Binds this G Buffer for only reading from it.
		void bindRead();

		/// Binds this G Buffer for the Stencil Pass.
		void bindStencil();

		/// Binds the texture of the specified type of this G Buffer.
		/// const GBufferTextureType &type : The type of texture to be binded.
		void bindTexture(const GBufferTextureType &type);

		/// Binds the texture of the specified GBuffer type to the specified
		/// Shader.
		/// const GBufferTextureType &type : The type of the GBuffer texture.
		/// ShaderProgram &shader : The Shader Program for which the texture
		///							is to be binded.
		void bindTexture(const GBufferTextureType &type, Honeycomb::Shader::
				ShaderProgram &shader);

		/// Binds the texture of the specified GBuffer type to the specified
		/// Shader with the specified uniform anme.
		/// const GBufferTextureType &type : The type of the GBuffer texture.
		/// ShaderProgram &shader : The Shader Program for which the texture
		///							is to be binded.
		/// const string &uniform : The uniform name in the Shader.
		void bindTexture(const GBufferTextureType &type, Honeycomb::Shader::
			ShaderProgram &shader, const std::string &uniform);

		/// Binds all of the color attachment textures (with the exception of
		/// the texture coordinates texture) of this GBuffer to the specified 
		/// Shader.
		/// ShaderProgram &shader : The Shader Program for which the textures
		///							are to be binded.
		void bindColorTextures(Honeycomb::Shader::ShaderProgram &shader);

		/// Destroys this G Buffer structure, and its position, diffuse, normal
		/// and texture coordinate buffers.
		void destroy();

		/// Sets up the GBuffer for the beginning of a frame render.
		void frameBegin();

		/// Returns the frame buffer object index for this G Buffer.
		/// return : The FBO index.
		const int& getFrameBuffer() const;

		/// Initializes this G Buffer structure with the position, diffuse,
		/// normal and texture coordinate buffers. The Buffer texture size will
		/// be set to the Game Window's size.
		void initialize();

		/// Binds the default frame buffer object (0) for both drawing and
		/// reading.
		static void unbind();

		/// Binds the default frame buffer object (0) for drawing only.
		static void unbindDraw();

		/// Binds the default frame buffer object (0) for reading only.
		static void unbindRead();
	private:
		int frameBufferObj; // The frame buffer object for this G Buffer
		
		std::unique_ptr<Honeycomb::Graphics::Texture2D> bufferTextures
			[GBufferTextureType::COUNT];

		// Stores the Shader Uniform names of all of the GBuffer Textures of a
		// GBuffer.
		static const std::string 
			TEXTURE_SHADER_NAMES[GBufferTextureType::COUNT];

		// The width and height of the buffer textures, from the GameWindow
		int textureHeight;
		int textureWidth;

		/// Resizes all of the buffer textures of this GBuffer to match the
		/// current window screen size.
		void resizeTextures();
	};
} } }

#endif
