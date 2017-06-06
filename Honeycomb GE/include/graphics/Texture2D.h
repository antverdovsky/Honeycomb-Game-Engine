#pragma once
#ifndef TEXTURE_2D
#define TEXTURE_2D

#include <string>

#include "../base/GLItem.h"
#include "../file/ImageIO.h"

typedef int GLint;

namespace Honeycomb { namespace Graphics {
	/// <summary>
	/// Enumeration of the different types of Texture2D filtering modes.
	/// </summary>
	enum Texture2DFilterMode {
		FILTER_LINEAR,
		FILTER_NEAREST
	};

	/// <summary>
	/// Enumeration of the different types of Texture 2D wrapping modes.
	/// </summary>
	enum Texture2DWrapMode {
		WRAP_CLAMP_TO_BORDER,
		WRAP_CLAMP_TO_EDGE,
		WRAP_MIRRORED_REPEAT,
		WRAP_REPEAT
	};

	/// <summary>
	/// Enumeration of common Texture2D colors. These colors are initialized by
	/// default and can be shared across multiple texture instances.
	/// </summary>
	enum Texture2DCommonFillColor {
		COLOR_BLACK,
		COLOR_BLUE,
		COLOR_GREEN,
		COLOR_RED,
		COLOR_WHITE
	};

	/// <summary>
	/// Object oriented representation of GL_TEXTURE2D.
	/// </summary>
	class Texture2D : public Honeycomb::Base::GLItem {
	public:
		/// <summary>
		/// Returns the number of textures which have been initialized. This
		/// does not relate to the total number of texture instances, but
		/// rather the amount of textures that have been created on the GPU
		/// through OpenGL.
		/// </summary>
		/// <returns>
		/// The total number of initialized textures.
		/// </returns>
		static const int& getInitializedTexturesCount();

		/// <summary>
		/// Returns a texture whose image data is a 1x1 pixel with the black
		/// color (RGBA = { 0, 0, 0, 255 }).
		/// </summary>
		/// <returns>
		/// The constant reference to the black texture.
		/// </returns>
		static const Texture2D& getTextureBlack();

		/// <summary>
		/// Returns a texture whose image data is a 1x1 pixel with the blue
		/// color (RGBA = { 0, 0, 255, 255 }).
		/// </summary>
		/// <returns>
		/// The constant reference to the blue texture.
		/// </returns>
		static const Texture2D& getTextureBlue();

		/// <summary>
		/// Returns a texture whose image data is a 1x1 pixel and is of the
		/// specified fill color.
		/// </summary>
		/// <param name="c">
		/// The fill color of the texture.
		/// </param>
		/// <returns>
		/// The constant reference to the texture of the specified fill color.
		/// </returns>
		static const Texture2D& getTextureCommonFill(const 
				Texture2DCommonFillColor &c);

		/// <summary>
		/// Returns a texture whose image data is a 1x1 pixel with the green
		/// color (RGBA = { 0, 255, 0, 255 }).
		/// </summary>
		/// <returns>
		/// The constant reference to the green texture.
		/// </returns>
		static const Texture2D& getTextureGreen();

		/// <summary>
		/// Returns a texture whose image data is a 1x1 pixel with the red
		/// color (RGBA = { 255, 0, 0, 255 }).
		/// </summary>
		/// <returns>
		/// The constant reference to the red texture.
		/// </returns>
		static const Texture2D& getTextureRed();

		/// <summary>
		/// Returns a texture whose image data is a 1x1 pixel with the white
		/// color (RGBA = { 255, 255, 255, 255 }).
		/// </summary>
		/// <returns>
		/// The constant reference to the white texture.
		/// </returns>
		static const Texture2D& getTextureWhite();

		/// <summary>
		/// Creates an empty, uninitialized texture instance.
		/// </summary>
		Texture2D();

		/// <summary>
		/// Binds this texture to OpenGL at GL_TEXTURE0. If the texture has not
		/// yet been initialized, a GLItemNotInitialized exception will be
		/// thrown.
		/// </summary>
		void bind() const;

		/// <summary>
		/// Binds this texture to OpenGL at the specified GL_TEXTURE position.
		/// If the texture has not yet been initialized, a GLItemNotInitialized
		/// exception will be thrown.
		/// </summary>
		/// <param name="loc">
		/// The displacement from GL_TEXTURE0.
		/// </param>
		void bind(const int &loc) const;

		/// Generates a MipMap for the texture.
		void genMipMap();

		/// <summary>
		/// Returns the raw OpenGL pointer of the texture. If the texture has
		/// not yet been initialized, the texture ID will be negative.
		/// </summary>
		/// <returns>
		/// The OpenGL pointer.
		/// </returns>
		const int& getTextureID() const;

		/// <summary>
		/// Initializes the Texture to a new OpenGL texture. If the texture has
		/// already been initialized, a GLItemAlreadyInitialized exception will
		/// be thrown.
		/// </summary>
		void initialize();
		
		/// <summary>
		/// Destroys this Texture from OpenGL. If the texture has not yet been
		/// initialized, a GLItemNotInitialized exception is thrown.
		/// </summary>
		void destroy();

		/// <summary>
		/// Sets the texture filtering mode for the minifying and magnifying of
		/// the texture. If the texture has not yet been initialized, a
		/// GLItemNotInitialized exception is thrown.
		/// </summary>
		/// <param name="filter">
		/// The filter mode to be used when minifying and magnifying the 
		/// texture.
		/// </param>
		void setFiltering(const Texture2DFilterMode &filter);

		/// <summary>
		/// Sets the texture filtering mode for the minifying and magnifying of
		/// the texture. If the texture has not yet been initialized, a
		/// GLItemNotInitialized exception is thrown.
		/// </summary>
		/// <param name="min">
		/// The filter mode to be used when minifying the texture.
		/// </param>
		/// <param name="mag">
		/// The filter mode to be used when magnifying the texture.
		/// </param>
		void setFiltering(const Texture2DFilterMode &min,
			const Texture2DFilterMode &mag);

		/// <summary>
		/// Creates a texture with a width of one pixel and a height of one
		/// pixel (1x1) and solid fills it with the specified RGBA color. If 
		/// the texture has not yet been initialized, a 
		/// GLItemNotInitialized exception is thrown. If this image has already
		/// had its data set, the previous data will be lost and replaced with 
		/// the new image data.
		/// </summary>
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
		void setImageDataFill(
				const int &r, const int &g, const int &b, const int &a);
		
		/// <summary>
		/// Sets this texture data to the data of the specified IO image. If
		/// the image has not yet been initialized, a GLItemNotInitialized
		/// exception will be thrown. If this image has already had its data
		/// set, the previous data will be lost and replaced with the new image
		/// data.
		/// </summary>
		/// <param name="image">
		/// The image which is to be stored in this Texture.
		/// </param>
		void setImageDataIO(const Honeycomb::File::ImageIO &image);

		/// <summary>
		/// TODO
		/// </summary>
		/// Passes the specified image data to OpenGL.
		/// unsigned char *data : The image data to be sent to OpenGL.
		/// const int &type : The type of data being passed in.
		/// const int &in : The internal format with which to store the image.
		/// const int &ex : The external format of the data passed in.
		/// const int &w : The width of the image.
		/// const int &h : The height of the image.
		void setImageDataManual(const unsigned char *data, const int &type, 
			const int &in, const int &ex, const int &w, const int &h);

		/// <summary>
		/// Sets the wrapping mode for the S and T axes of the texture. If the
		/// texture has not yet been initialized, a GLItemNotInitialized
		/// exception will be thrown.
		/// </summary>
		/// <param name="wrap">
		/// The wrapping mode to be used on the S and T axes.
		/// </param>
		void setWrap(const Texture2DWrapMode &wrap);

		/// <summary>
		/// Sets the wrapping mode for the S and T axes of the texture. If the
		/// texture has not yet been initialized, a GLItemNotInitialized
		/// exception will be thrown.
		/// </summary>
		/// <param name="s">
		/// The wrapping mode to be used for the S axis.
		/// </param>
		/// <param name="t">
		/// The wrapping mode to be used for the T axis.
		/// </param>
		void setWrap(const Texture2DWrapMode &s, const Texture2DWrapMode &t);
	private:
		/// <summary>
		/// Converts the specified Texture2D Filter Mode enumeration to its
		/// GLint counterpart.
		/// </summary>
		/// <param name="filter">
		/// The filter mode value.
		/// </param>
		/// <returns>
		/// The GLint value representation of the filter value.
		/// </returns>
		static GLint getGLintFilterMode(const Texture2DFilterMode &filter);

		/// <summary>
		/// Converts the specified Texture2D Wrap Mode eneumeration to its
		/// GLint counterpart.
		/// </summary>
		/// <param name="wrap">
		/// The wrapping mode value.
		/// </param>
		/// <returns>
		/// The GLint value representation of the wrap value.
		/// </returns>
		static GLint getGLintWrapMode(const Texture2DWrapMode &wrap);

		static int textureCount; // The number of GL initialized textures
		
		int textureID;           // The texture "pointer"
	};
} }

#endif
