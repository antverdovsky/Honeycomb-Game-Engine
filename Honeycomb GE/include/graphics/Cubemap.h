#pragma once
#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <string>

#include "../base/GLItem.h"
#include "Texture2D.h"

namespace Honeycomb { namespace Graphics {
	class Cubemap : public Honeycomb::Base::GLItem {
	public:
		// Wrapper for the Texture Targets for each face of the Cubemap
		enum TextureTarget {
			RIGHT = 0,		POSITIVE_X = 0,
			LEFT = 1,		NEGATIVE_X = 1,

			TOP = 2,		POSITIVE_Y = 2,
			BOTTOM = 3,		NEGATIVE_Y = 3,

			BACK = 4,		POSITIVE_Z = 4,
			FRONT = 5,		NEGATIVE_Z = 5
		};

		/// Creates an empty Cubemap Instance.
		Cubemap();

		/// Binds this texture to OpenGL at GL_TEXTURE0.
		void bind() const;

		/// Binds this texture to OpenGL at the specified location. 
		/// const int &loc : The location of the texture in memory. This is
		///					 treated as the displacement from GL_TEXTURE0.
		void bind(const int &loc) const;

		/// Initializes this Cubemap instance by generating the appropriate
		/// texture buffer to store the texture data.
		void initialize();

		/// Destroys this Cubemap instance by destroying the texture buffer
		/// it used to store the texture data.
		void destroy();

		/// Sets the texture of the specified face to the specified texture.
		/// const TextureTarget &face : The face of the Cubemap which is to be
		///								set.
		/// const Texture2D &tex : The texture which is to be set to the face 
		///						   of the Cubemap.
		void setFace(const TextureTarget &face, const Texture2D &tex);

		/// Sets the texture of the specified face to the specified texture.
		/// const TextureTarget &face : The face of the Cubemap which is to be
		///								set.
		/// const string &tex : The directory of the texture file.
		void setFace(const TextureTarget &face, const std::string &tex);

		/// Sets the textures of all of the faces of the specified texture.
		/// The textures must be in the order of { RIGHT, LEFT, TOP, BOTTOM, 
		/// BACK, FRONT }.
		/// const Texture2D tex[6] : The array of the six textures for the six
		///							 sides of the cube.
		void setFaces(const Texture2D tex[6]);

		/// Sets the textures of all of the faces of the specified texture.
		/// The textures must be in the order of { RIGHT, LEFT, TOP, BOTTOM, 
		/// BACK, FRONT }.
		/// const string tex[6] : The array of the six texture directories
		///						  for the six sides of the cube.
		void setFaces(const std::string tex[6]);
	private:
		bool isInitialized;    // Has the cubemap been initialized?

		int textureID;		   // The texture "pointer"
		std::string faces[6];  // Stores the 6 fil directories for the sides
	};
} }

#endif
