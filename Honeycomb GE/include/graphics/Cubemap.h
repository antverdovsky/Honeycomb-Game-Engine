#pragma once
#ifndef CUBEMAP_H
#define CUBEMAP_H

#include <string>

#include "../base/GLItem.h"
#include "Texture2D.h"

namespace Honeycomb { namespace Graphics {
	/// <summary>
	/// Enumeration of the different sides of the cubemap.
	/// </summary>
	enum CubemapTextureTarget {
		RIGHT   = 0,                             POSITIVE_X = 0,
		LEFT    = 1,                             NEGATIVE_X = 1,

		TOP     = 2,                             POSITIVE_Y = 2,
		BOTTOM  = 3,                             NEGATIVE_Y = 3,
		
		BACK    = 4,                             POSITIVE_Z = 4,
		FRONT   = 5,                             NEGATIVE_Z = 5
	};

	/// <summary>
	/// Class representing a cubemap of six textures.
	/// </summary>
	class Cubemap : public Honeycomb::Base::GLItem {
	public:
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

		/// <summary>
		/// Creates a texture with a width of one pixel and a height of one
		/// pixel (1x1) and solid fills it with the specified RGBA color for
		/// the specified cubemap target. If the cubemap has not yet been 
		/// initialized, a GLItemNotInitialized exception is thrown. If this 
		/// cube has already had its data set for the specified texture target,
		/// the previous data will be lost and replaced with the new image 
		/// data.
		/// </summary>
		/// <param name="target">
		/// The side of the cubemap for which the texture data is to be set.
		/// </param>
		/// <param name="r">
		/// The red channel of the texture color, in range between 0 and 255.
		/// </param>
		/// <param name="g">
		/// The green channel of the texture color, in range between 0 and 255.
		/// </param>
		/// <param name="b">
		/// The blue channel of the texture color, in range between 0 and 255.
		/// </param>
		/// <param name="a">
		/// The alpha channel of the texture color, in range between 0 and 255.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		/// <exception cref="GLErrorException">
		/// Thrown if the RGBA data is invalid.
		/// </exception>
		void setFaceDataFill(const CubemapTextureTarget &target,
				const int &r, const int &g, const int &b, const int &a);

		/// <summary>
		/// Sets this texture data to the data of the specified IO image for
		/// the specified texture facec. If the cubemap has not yet been 
		/// initialized, a GLItemNotInitialized exception will be thrown. If 
		/// this cubemap has already had its data set for the specified target,
		/// the previous data will be lost and replaced with the new image 
		/// data.
		/// </summary>
		/// <param name="target">
		/// The side of the cubemap for which the texture data is to be set.
		/// </param>
		/// <param name="image">
		/// The image whose data is to be set for the cubemap target.
		/// </param>
		void setFaceDataIO(const CubemapTextureTarget &target,
				const Honeycomb::File::ImageIO &image);

		/// <summary>
		/// Sets the image data for the specified target of the Cubemap. If the
		/// cubemap has not yet been initialized, a GLItemNotInitialized 
		/// exception will be thrown. If this cubemap has already had its data
		/// set for the specified target, the previous data will be lost and 
		/// replaced with the new image data.
		/// </summary>
		/// <param name="target">
		/// The side of the cubemap for which the texture data is to be set.
		/// </param>
		/// <param name="data">
		/// The pointer to the image data to be written to the texture 
		/// instance.
		/// </param>
		/// <param name="type">
		/// The type of data which is to be passed to the texture. This should
		/// be the type of the void pointer passed in.
		/// </param>
		/// <param name="iformat">
		/// The internal format with which the data should be stored, this
		/// specifies the number of color components of the texture.
		/// </param>
		/// <param name="format">
		/// The format of the pixel data to be passed to the texture.
		/// </param>
		/// <param name="width">
		/// The width of the texture, in pixels.
		/// </param>
		/// <param name="height">
		/// The height of the texture, in pixels.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		/// <exception cref="GLErrorException">
		/// Thrown if any of the parameters are invalid.
		/// </exception>
		void setFaceDataManual(const CubemapTextureTarget &target,
				const void *data,
				const TextureDataType &type,
				const TextureDataInternalFormat &iformat,
				const TextureDataFormat &format,
				const int &width, const int &height);
	private:
		int textureID;		   // The texture "pointer"
	};
} }

#endif
