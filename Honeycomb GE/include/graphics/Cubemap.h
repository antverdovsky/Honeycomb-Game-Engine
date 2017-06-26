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
		/// Returns the number of initialized Cubemaps.
		/// </summary>
		/// <returns>
		/// The number of cubemaps.
		/// </returns>
		static const int& getInitializedCubemapCount();

		/// <summary>
		/// Creates a new, initialized Cubemap.
		/// </summary>
		/// <returns>
		/// The shared pointer to the new cubemap.
		/// </returns>
		static std::shared_ptr<Cubemap> newCubemapShared();

		/// <summary>
		/// Creates a new, initialized Cubemap.
		/// </summary>
		/// <returns>
		/// The unique pointer to the new cubemap.
		/// </returns>
		static std::unique_ptr<Cubemap> newCubemapUnique();

		/// <summary>
		/// De-initializes and destroys this Cubemap.
		/// </summary>
		~Cubemap();
		
		/// <summary>
		/// Cubemaps cannot be copied.
		/// </summary>
		Cubemap(const Cubemap&) = delete;

		/// <summary>
		/// Binds this cubemap to OpenGL at GL_TEXTURE0. If the cubemap has not
		/// yet been initialized, a GLItemNotInitialized exception will be
		/// thrown.
		/// </summary>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
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
		/// the specified texture face. If the cubemap has not yet been 
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
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		/// <exception cref="GLErrorException">
		/// Thrown if any of the parameters are invalid.
		/// </exception>
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

		/// <summary>
		/// Sets the texture data of each face of this Cubemap to the specified
		/// RGBA fill color with a width of one and height of one (1x1). If the
		/// cubemap has not yet been initialized, a GLItemNotInitialized 
		/// exception is thrown. If this cube has already had its data set for 
		/// any texture target, the previous data will be lost and replaced 
		/// with the new image data.
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
		/// Thrown if any of the parameters are invalid.
		/// </exception>
		void setFacesDataFill(const int &r, const int &g, const int &b,
				const int &a);

		/// <summary>
		/// Sets the texture data of each face of this Cubemap in the targets
		/// array to the specified RGBA fill color with a width of one and a
		/// height of one (1x1). If the cubemap has not yet been initialized, 
		/// a GLItemNotInitialized exception is thrown. If this cube has 
		/// already had its data set for the specified texture target, the 
		/// previous data will be lost and replaced with the new image data.
		/// </summary>
		/// <param name="numTargets">
		/// The number of texture targets. This should be the size of each of
		/// the arrays passed in.
		/// </param>
		/// <param name="targets">
		/// The targets for which the image data is to be set.
		/// </param>
		/// <param name="r">
		/// The array of the red channels of the texture colors, in ranges
		/// between 0 and 255.
		/// </param>
		/// <param name="g">
		/// The array of the green channels of the texture colors, in ranges
		/// between 0 and 255.
		/// </param>
		/// <param name="b">
		/// The array of the blue channels of the texture colors, in ranges
		/// between 0 and 255.
		/// </param>
		/// <param name="a">
		/// The array of the alpha channels of the texture colors, in ranges
		/// between 0 and 255.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		/// <exception cref="GLErrorException">
		/// Thrown if any of the parameters are invalid.
		/// </exception>
		void setFacesDataFill(const unsigned int &numTargets, 
				const CubemapTextureTarget targets[], 
				const int r[], const int g[], const int b[], const int a[]);

		/// <summary>
		/// Sets the texture data of each face of the Cubemap to the specified
		/// ImageIO's data. If the cubemap has not yet been initialized, a 
		/// GLItemNotInitialized exception will be thrown. If this cubemap has
		/// already had its data set for the any target, the previous data will
		/// be lost and replaced with the new image data. For this method, the
		/// filtering mode is set to LINEAR and the wrap to CLAMP_TO_EDGE.
		/// </summary>
		/// <param name="image">
		/// The inputted image whose data is to be set to the faces of the
		/// cubemap.
		/// </param>
		void setFacesDataIO(const Honeycomb::File::ImageIO &image);

		/// <summary>
		/// Sets the texture data for each face of the Cubemap which is
		/// specified in the targets array to the specified ImageIOs' datas.
		/// If the cubemap has not yet been initialized, a GLItemNotInitialized
		/// exception will be thrown. If this cubemap has already had its data 
		/// set for the specified target, the previous data will be lost and 
		/// replaced with the new image data. For this method, the filtering
		/// mode is set to LINEAR and the wrap to CLAMP_TO_EDGE.
		/// </summary>
		/// <param name="numTargets">
		/// The number of targets (sizes of the targets and images arrays).
		/// </param>
		/// <param name="targets">
		/// The targets for which the image data is to be set.
		/// </param>
		/// <param name="images">
		/// The inputted images whose data is to be set for the faces of the
		/// cubemap.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		/// <exception cref="GLErrorException">
		/// Thrown if any of the parameters are invalid.
		/// </exception>
		void setFacesDataIO(const unsigned int &numTargets,
				const CubemapTextureTarget targets[],
				const Honeycomb::File::ImageIO images[]);

		/// <summary>
		/// Sets the image data for each face of the cubemap. If the cubemap 
		/// has not yet been initialized, a GLItemNotInitialized exception will
		/// be thrown. If this cubemap has already had its data set for any 
		/// target, the previous data will be lost and replaced with the new 
		/// image data. For this method, the filtering mode is set to LINEAR 
		/// and the wrap to CLAMP_TO_EDGE.
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
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Texture has not yet been initialized.
		/// </exception>
		/// <exception cref="GLErrorException">
		/// Thrown if any of the parameters are invalid.
		/// </exception>
		void setFacesDataManual(
				const void *data,
				const TextureDataType &type,
				const TextureDataInternalFormat &iformat,
				const TextureDataFormat &format,
				const int &width, const int &height);

		/// <summary>
		/// Sets the image data for each of the faces of the cubemap in the
		/// targets array. If the cubemap has not yet been initialized, a 
		/// GLItemNotInitialized exception will be thrown. If this cubemap has 
		/// already had its data set for any target, the previous data will be 
		/// lost and replaced with the new image data. For this method, the
		/// filtering mode is set to LINEAR and the wrap to CLAMP_TO_EDGE.
		/// </summary>
		/// <param name="numTargets">
		/// The number of targets (sizes of the targets and images arrays).
		/// </param>
		/// <param name="targets">
		/// The targets for which the image data is to be set.
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
		void setFacesDataManual(const unsigned int &numTargets,
				const CubemapTextureTarget targets[],
				const void *data[],
				const TextureDataType type[],
				const TextureDataInternalFormat iformat[],
				const TextureDataFormat format[],
				const int width[], const int height[]);

		/// <summary>
		/// Sets the texture filtering mode for both the minifying and 
		/// magnifying of the texture. If the cubemap has not yet been 
		/// initialized, a GLItemNotInitialized exception is thrown.
		/// </summary>
		/// <param name="filter">
		/// The filter mode to be used when minifying and magnifying the
		/// cubemap.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Cubemap has not yet been initialized.
		/// </exception>
		void setFiltering(const TextureFilterMagMode &filter);

		/// <summary>
		/// Sets the texture filtering mode for the minifying and magnifying of
		/// the texture. If the cubemap has not yet been initialized, a
		/// GLItemNotInitialized exception is thrown.
		/// </summary>
		/// <param name="min">
		/// The filter mode to be used when minifying the cubemap.
		/// </param>
		/// <param name="mag">
		/// The filter mode to be used when magnifying the cubemap.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Cubemap has not yet been initialized.
		/// </exception>
		void setFiltering(const TextureFilterMagMode &min,
				const TextureFilterMagMode &mag);

		/// <summary>
		/// Sets the texture wrapping mode for the R, S, and T coordinates of
		/// the cubemap. If the cubemap has not yet been initialized, a
		/// GLItemNotInitialized exception is thrown.
		/// </summary>
		/// <param name="wrap">
		/// The wrap mode to be used for all cubemap coordinates.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Cubemap has not yet been initialized.
		/// </exception>
		void setWrap(const TextureWrapMode &wrap);

		/// <summary>
		/// Sets the texture wrapping mode for the R, S, and T coordinates of
		/// the cubemap. If the cubemap has not yet been initialized, a
		/// GLItemNotInitialized exception is thrown.
		/// </summary>
		/// <param name="r">
		/// The wrap mode to be used for the R coordinate.
		/// </param>
		/// <param name="s">
		/// The wrap mode to be used for the S coordinate.
		/// </param>
		/// <param name="t">
		/// The wrap mode to be used for the T coordinate.
		/// </param>
		/// <exception cref="GLItemNotInitializedException">
		/// Thrown if the Cubemap has not yet been initialized.
		/// </exception>
		void setWrap(const TextureWrapMode &r, const TextureWrapMode &s,
				const TextureWrapMode &t);

		/// <summary>
		/// Compares this Cubemap for equality with the other cubemap. This
		/// will return true only if the texture pointer of this cubemap is
		/// equivalent to the texture pointer of the other cubemap.
		/// </summary>
		/// <param name="other">
		/// The other cubemap, to be compared to this.
		/// </param>
		/// <returns>
		/// True if the texture pointers of this and the other cubemap are
		/// equal, false otherwise.
		/// </returns>
		bool operator==(const Cubemap &that) const;

		/// <summary>
		/// Compares this Cubemap for inequality with the other cubemap. This
		/// will return true only if the texture pointer of this cubemap is
		/// not equivalent to the texture pointer of the other cubemap.
		/// </summary>
		/// <param name="other">
		/// The other cubemap, to be compared to this.
		/// </param>
		/// <returns>
		/// True if the texture pointers of this and the other cubemap are
		/// not equal, false otherwise.
		/// </returns>
		bool operator!=(const Cubemap &that) const;

		/// <summary>
		/// Cubemaps cannot be re-assigned.
		/// </summary>
		Cubemap& operator=(const Cubemap&) = delete;
	private:
		static int cubemapCount;                 // Number of initialized maps
		int textureID;                           // The texture "pointer"

		/// <summary>
		/// Creates an empty, uninitialized Cubemap instance.
		/// </summary>
		Cubemap();
	};
} }

#endif
