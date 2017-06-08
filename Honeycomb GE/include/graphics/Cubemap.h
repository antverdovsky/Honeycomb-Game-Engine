#pragma once
#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <string>

#include "../base/GLItem.h"
#include "Texture2D.h"

namespace Honeycomb { namespace Graphics {
	/// <summary>
	/// Class representing a cubemap of six textures.
	/// </summary>
	class Cubemap : public Honeycomb::Base::GLItem {
	public:
		/// <summary>
		/// Enumeration of the different sides of the cubemap.
		/// </summary>
		enum CubemapTextureTarget {
			RIGHT   = 0,                   POSITIVE_X = 0,
			LEFT    = 1,                   NEGATIVE_X = 1,
			TOP     = 2,                   POSITIVE_Y = 2,
			BOTTOM  = 3,                   NEGATIVE_Y = 3,
			BACK    = 4,                   POSITIVE_Z = 4,
			FRONT   = 5,                   NEGATIVE_Z = 5
		};

		/// <summary>
		/// Creates an empty, uninitialized Cubemap instance.
		/// </summary>
		Cubemap();

		/// <summary>
		/// Binds this cubemap to OpenGL at GL_TEXTURE0. If the cubemap has not
		/// yet been initialized, a GLItemNotInitialized exception will be
		/// thrown.
		/// </summary>
		void bind() const;

		/// <summary>
		/// Binds this cubemap to OpenGL at the specified GL_TEXTURE position.
		/// If the cubemap has not yet been initialized, a GLItemNotInitialized
		/// exception will be thrown. If the parameter value is less than zero
		/// or greater than thirty-one, a GLError exception will be thrown.
		/// </summary>
		/// <param name="loc">
		/// The displacement from GL_TEXTURE0.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Cubemap has not yet been initialized.
		/// </exception>
		/// <exception cref="GLErrorException">
		/// Thrown if the location parameter is out of the [0, 31] bounds.
		/// </exception>
		void bind(const int &loc) const;

		/// <summary>
		/// Initializes the Cubemap to a new OpenGL texture. If the cubemap has
		/// already been initialized, a GLItemAlreadyInitialized exception will
		/// be thrown.
		/// </summary>
		/// <exception cref="GLItemAlreadyInitializedException">
		/// Thrown if the Cubemap has already been initialized.
		/// </exception>
		void initialize();

		/// <summary>
		/// Destroys this Cubemap from OpenGL. If the cubemap has not yet been
		/// initialized, a GLItemNotInitialized exception is thrown.
		/// </summary>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Cubemap has not yet been initialized.
		/// </exception>
		void destroy();

		/// Sets the texture of the specified face to the specified texture.
		/// const TextureTarget &face : The face of the Cubemap which is to be
		///								set.
		/// const string &tex : The directory of the texture file.
		void setFace(const CubemapTextureTarget &face, const std::string &tex);

		/// Sets the textures of all of the faces of the specified texture.
		/// The textures must be in the order of { RIGHT, LEFT, TOP, BOTTOM, 
		/// BACK, FRONT }.
		/// const string tex[6] : The array of the six texture directories
		///						  for the six sides of the cube.
		void setFaces(const std::string tex[6]);
	private:
		int textureID;		   // The texture "pointer"
		std::string faces[6];  // Stores the 6 fil directories for the sides
	};
} }

#endif
