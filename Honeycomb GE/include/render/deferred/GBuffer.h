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
		DEPTH,		// Depth Buffer

		COUNT		// The total number of buffers
	};

	class GBuffer : 
			public Honeycomb::Base::GLItem,
			public Honeycomb::Render::Renderer {
	public:
		/// Instantiates a blank G Buffer structure.
		GBuffer();

		/// Deinstantiates this G Buffer structure.
		~GBuffer();

		/// Binds this G Buffer for drawing to it.
		void bindDraw();

		/// Binds this G Buffer for reading from it.
		void bindRead();

		/// Destroys this G Buffer structure, and its position, diffuse, normal
		/// and texture coordinate buffers.
		void destroy();

		/// Initializes this G Buffer structure with the position, diffuse,
		/// normal and texture coordinate buffers. The Buffer texture size will
		/// be set to the Game Window's size.
		bool initialize();

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