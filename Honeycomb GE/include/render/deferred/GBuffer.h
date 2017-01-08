#pragma once
#ifndef G_BUFFER_H
#define G_BUFFER_H

#include "..\..\base\GLItem.h"
#include "..\..\graphics\Texture2D.h"
#include "..\..\render\Renderer.h"

namespace Honeycomb::Render::Deferred {
	enum GBufferTextureType {
		POSITION,	// Position Buffer
		DIFFUSE,	// Diffuse Buffer
		NORMAL,		// Normals Buffer
		TEXTURE,	// Texture Coordinates Buffer
		DEPTH,		// Depth Buffer (also equal to the number of color buffers)

		COUNT		// The total number of buffers
	};

	class GBuffer : public Honeycomb::Base::GLItem {
		friend class DeferredRenderer;

	public:
		/// Instantiates a blank G Buffer structure.
		GBuffer();

		/// Deinstantiates this G Buffer structure.
		~GBuffer();

		/// Binds this G Buffer for both drawing to it, and reading from it.
		void bind();

		/// Binds this G Buffer for only drawing to it.
		void bindDraw();

		/// Binds this G Buffer for only reading from it.
		void bindRead();

		/// Binds the texture of the specified type of this G Buffer.
		/// const GBufferTextureType &type : The type of texture to be binded.
		void bindTexture(const GBufferTextureType &type);

		/// Destroys this G Buffer structure, and its position, diffuse, normal
		/// and texture coordinate buffers.
		void destroy();

		/// Returns the frame buffer object index for this G Buffer.
		/// return : The FBO index.
		const int& getFrameBuffer() const;

		/// Initializes this G Buffer structure with the position, diffuse,
		/// normal and texture coordinate buffers. The Buffer texture size will
		/// be set to the Game Window's size.
		bool initialize();

		/// Binds the default frame buffer object (0) for both drawing and
		/// reading.
		static void unbind();

		/// Binds the default frame buffer object (0) for drawing only.
		static void unbindDraw();

		/// Binds the default frame buffer object (0) for reading only.
		static void unbindRead();
	private:
		int frameBufferObj; // The frame buffer object for this G Buffer
		
		Honeycomb::Graphics::Texture2D bufferTextures // All of the Buffer
			[GBufferTextureType::COUNT];			  // Textures (from Enum)

		// The width and height of the buffer textures, from the GameWindow
		int textureHeight;
		int textureWidth;
	};
}

#endif