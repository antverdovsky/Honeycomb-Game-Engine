#pragma once
#ifndef TEXTURE_2D
#define TEXTURE_2D

#include <memory>
#include <string>

#include "TextureEnums.h"
#include "../base/GLItem.h"
#include "../file/ImageIO.h"

namespace Honeycomb { namespace Graphics {
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
		/// The shared pointer to the black texture.
		/// </returns>
		static std::shared_ptr<const Texture2D> getTextureBlack();

		/// <summary>
		/// Returns a texture whose image data is a 1x1 pixel with the blue
		/// color (RGBA = { 0, 0, 255, 255 }).
		/// </summary>
		/// <returns>
		/// The shared pointer to the blue texture.
		/// </returns>
		static std::shared_ptr<const Texture2D> getTextureBlue();

		/// <summary>
		/// Returns a texture whose image data is a 1x1 pixel and is of the
		/// specified fill color.
		/// </summary>
		/// <param name="c">
		/// The fill color of the texture.
		/// </param>
		/// <returns>
		/// The shared pointer to the texture of the specified fill color.
		/// </returns>
		static std::shared_ptr<const Texture2D> getTextureCommonFill(
				const Texture2DCommonFillColor &c);

		/// <summary>
		/// Returns a texture whose image data is a 1x1 pixel with the green
		/// color (RGBA = { 0, 255, 0, 255 }).
		/// </summary>
		/// <returns>
		/// The shared pointer to the green texture.
		/// </returns>
		static std::shared_ptr<const Texture2D> getTextureGreen();

		/// <summary>
		/// Returns a texture whose image data is a 1x1 pixel with the red
		/// color (RGBA = { 255, 0, 0, 255 }).
		/// </summary>
		/// <returns>
		/// The shared pointer to the red texture.
		/// </returns>
		static std::shared_ptr<const Texture2D> getTextureRed();

		/// <summary>
		/// Returns a texture whose image data is a 1x1 pixel with the white
		/// color (RGBA = { 255, 255, 255, 255 }).
		/// </summary>
		/// <returns>
		/// The shared pointer to the white texture.
		/// </returns>
		static std::shared_ptr<const Texture2D> getTextureWhite();

		/// <summary>
		/// Creates a new, initialized Texture2D instance.
		/// </summary>
		/// <returns>
		/// The shared pointer to the Texture2D instance.
		/// </returns>
		static std::shared_ptr<Texture2D> newTexture2DShared();

		/// <summary>
		/// Creates a new, initialized Texture2D instance.
		/// </summary>
		/// <returns>
		/// The unique pointer to the Texture2D instance.
		/// </returns>
		static std::unique_ptr<Texture2D> newTexture2DUnique();

		/// <summary>
		/// Copying of Texture2D instances is forbidden.
		/// </summary>
		Texture2D(const Texture2D &) = delete;

		/// <summary>
		/// Destroys and de-initializes this Texture2D.
		/// </summary>
		~Texture2D();

		/// <summary>
		/// Binds this texture to OpenGL at GL_TEXTURE0. If the texture has not
		/// yet been initialized, a GLItemNotInitialized exception will be
		/// thrown.
		/// </summary> 
		/// <exception cref="GLItemNotInitialized">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void bind() const;

		/// <summary>
		/// Binds this texture to OpenGL at the specified GL_TEXTURE position.
		/// If the texture has not yet been initialized, a GLItemNotInitialized
		/// exception will be thrown. If the parameter value is less than zero
		/// or greater than thirty-one, a GLError exception will be thrown.
		/// </summary>
		/// <param name="loc">
		/// The displacement from GL_TEXTURE0.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		/// <exception cref="GLErrorException">
		/// Thrown if the location parameter is out of the [0, 31] bounds.
		/// </exception>
		void bind(const int &loc) const;

		/// <summary>
		/// Returns the height of the texture, in pixels.
		/// </summary>
		/// <returns>
		/// The height of the texture.
		/// </returns>
		const int& getHeight() const;

		/// <summary>
		/// Returns the raw OpenGL pointer of the texture. If the texture has
		/// not yet been initialized, the texture ID will be negative.
		/// </summary>
		/// <returns>
		/// The OpenGL pointer.
		/// </returns>
		const int& getTextureID() const;

		/// <summary>
		/// Returns the width of texture, in pixels.
		/// </summary>
		/// <returns>
		/// The width of the texture.
		/// </returns>
		const int& getWidth() const;

		/// <summary>
		/// Initializes the Texture to a new OpenGL texture. If the texture has
		/// already been initialized, a GLItemAlreadyInitialized exception will
		/// be thrown.
		/// </summary>
		/// <exception cref="GLItemAlreadyInitializedException">
		/// Thrown if the Texture has already been initialized.
		/// </exception>
		void initialize();
		
		/// <summary>
		/// Destroys this Texture from OpenGL. If the texture has not yet been
		/// initialized, a GLItemNotInitialized exception is thrown.
		/// </summary>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void destroy();

		/// <summary>
		/// Sets the maximum anisotropic filtering value for this texture. If
		/// the texture has not yet been initialized, a GLItemNotInitialized 
		/// exception is thrown. If the aniso parameter value is negative, a
		/// GLError exception may also be thrown.
		/// </summary>
		/// <param name="aniso">
		/// The maximum anisotropic filtering value.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		/// <exception cref="GLErrorException">
		/// Thrown if the Anisotropic value is negative or is invalid.
		/// </exception>
		void setAnisotropicFiltering(const int &aniso);

		/// <summary>
		/// Sets the texture filtering mode for both the minifying and 
		/// magnifying of the texture. If the texture has not yet been 
		/// initialized, a GLItemNotInitialized exception is thrown.
		/// </summary>
		/// <param name="filter">
		/// The filter mode to be used when minifying and magnifying the
		/// texture.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void setFiltering(const TextureFilterMagMode &filter);

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
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void setFiltering(const TextureFilterMinMode &min,
				const TextureFilterMagMode &mag);

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
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		/// <exception cref="GLErrorException">
		/// Thrown if the RGBA data is invalid.
		/// </exception>
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
		/// <param name="mipmap">
		/// Should mip maps be generated for the texture? True by default.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void setImageDataIO(const Honeycomb::File::ImageIO &image, 
				const bool &mipmap = true);

		/// <summary>
		/// Sets this texture data to the specified custom pixel data. If the
		/// image has not yet been initialized, a GLItemNotInitialized 
		/// exception will be thrown. If this image has already had its data
		/// set, the previous data will be lost and replaced with the new image
		/// data.
		/// </summary>
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
		/// <param name="mipmap">
		/// Should mip maps be generated for the texture? True by default.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		/// <exception cref="GLErrorException">
		/// Thrown if any of the parameters are invalid.
		/// </exception>
		void setImageDataManual(const void *data, 
				const TextureDataType &type,
				const TextureDataInternalFormat &iformat,
				const TextureDataFormat &format,
				const int &width, const int &height, 
				const bool &mipmap = true);

		/// <summary>
		/// Sets the wrapping mode for the S and T axes of the texture. If the
		/// texture has not yet been initialized, a GLItemNotInitialized
		/// exception will be thrown.
		/// </summary>
		/// <param name="wrap">
		/// The wrapping mode to be used on the S and T axes.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void setWrap(const TextureWrapMode &wrap);

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
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		void setWrap(const TextureWrapMode &s, const TextureWrapMode &t);

		/// <summary>
		/// Compares this Texture for equality with the other texture. This
		/// will return true only if the texture pointer of this texture is
		/// equivalent to the texture pointer of the other texture.
		/// </summary>
		/// <param name="other">
		/// The other texture, to be compared to this.
		/// </param>
		/// <returns>
		/// True if the texture pointers of this and the other texture are
		/// equal, false otherwise.
		/// </returns>
		bool operator==(const Texture2D &that) const;

		/// <summary>
		/// Compares this Texture for inequality with the other texture. This
		/// will return true only if the texture pointer of this texture is
		/// not equivalent to the texture pointer of the other texture.
		/// </summary>
		/// <param name="other">
		/// The other texture, to be compared to this.
		/// </param>
		/// <returns>
		/// True if the texture pointers of this and the other texture are
		/// not equal, false otherwise.
		/// </returns>
		bool operator!=(const Texture2D &that) const;

		/// <summary>
		/// Assignment of Texture2D instances is forbidden.
		/// </summary>
		Texture2D& operator=(const Texture2D &) = delete;
	private:
		static int textureCount;       // The number of GL initialized textures
		
		int textureID;                 // The texture "pointer"

		int width;                     // The width of the texture
		int height;                    // The height of the texture

		/// <summary>
		/// Creates an empty, uninitialized texture instance.
		/// </summary>
		Texture2D();
	};
} }

#endif
