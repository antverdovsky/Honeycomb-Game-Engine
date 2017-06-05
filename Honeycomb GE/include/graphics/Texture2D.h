#pragma once
#ifndef TEXTURE_2D
#define TEXTURE_2D

#include <string>

#include "../base/GLItem.h"
#include "../file/ImageIO.h"

namespace Honeycomb { namespace Graphics {
	/// <summary>
	/// Enumeration of the different types of Texture2D filtering modes.
	/// </summary>
	enum Texture2DFilterMode {
		LINEAR                             = 0x2601,
		NEAREST                            = 0x2600
	};

	/// <summary>
	/// Enumeration of the different types of Texture 2D wrapping modes.
	/// </summary>
	enum Texture2DWrapMode {
		CLAMP_TO_BORDER                    = 0x812D,
		CLAMP_TO_EDGE                      = 0x812F,
		MIRRORED_REPEAT                    = 0x8370,
		REPEAT                             = 0x2901
	};

	/// <summary>
	/// Enumeration of common Texture2D colors. These colors are initialized by
	/// default and can be shared across multiple texture instances.
	/// </summary>
	enum Texture2DCommonFillColor {
		BLACK,
		BLUE,
		GREEN,
		RED,
		WHITE
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

		/// Creates an empty Texture instance.
		Texture2D();

		/// Binds this texture to OpenGL at GL_TEXTURE0.
		void bind() const;

		/// Binds this texture to OpenGL at the specified location. 
		/// const int &loc : The location of the texture in memory. This is
		///					 treated as the displacement from GL_TEXTURE0.
		void bind(const int &loc) const;

		/// Generates a MipMap for the texture.
		void genMipMap();

		/// Returns the directory of this 2D Texture.
		/// return : The system directory.
		const std::string& getDirectory() const;

		/// Returns the texture ID of this 2D Texture.
		/// return : The Texture ID.
		const int& getTextureID() const;

		/// Initializes this 2D Texture instance by generating the appropriate
		/// texture buffer to store the texture data.
		void initialize();
		
		/// Destroys this 2D Texture instance by destroying the appropriate
		/// texture buffer.
		void destroy();

		/// <summary>
		/// Sets the texture filtering mode for the minifying and magnifying of
		/// the texture.
		/// </summary>
		/// <param name="filter">
		/// The filter mode to be used when minifying and magnifying the 
		/// texture.
		/// </param>
		void setFiltering(const Texture2DFilterMode &filter);

		/// <summary>
		/// Sets the texture filtering mode for the minifying and magnifying of
		/// the texture.
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
		/// pixel (1x1) and solid fills it with the specified RGBA color.
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
		/// Sets the wrapping mode for the S and T axes of the texture.
		/// </summary>
		/// <param name="wrap">
		/// The wrapping mode to be used on the S and T axes.
		/// </param>
		void setWrap(const Texture2DWrapMode &wrap);

		/// <summary>
		/// Sets the wrapping mode for the S and T axes of the texture.
		/// </summary>
		/// <param name="s">
		/// The wrapping mode to be used for the S axis.
		/// </param>
		/// <param name="t">
		/// The wrapping mode to be used for the T axis.
		/// </param>
		void setWrap(const Texture2DWrapMode &s, const Texture2DWrapMode &t);
	private:
		static int textureCount; // The number of GL initialized textures
		
		int textureID; // The texture "pointer"
		std::string directory; // The file from which the texture was loaded
	};
} }

#endif
