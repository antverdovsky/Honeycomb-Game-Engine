#pragma once
#ifndef TEXTURE_ENUMS_H
#define TEXTURE_ENUMS_H

typedef int GLint;

namespace Honeycomb { namespace Graphics {
	/// <summary>
	/// Enumeration of the different types of Texture pixel data formats.
	/// </summary>
	enum TextureDataFormat {
		FORMAT_BGR,
		FORMAT_BGR_INTEGER,
		FORMAT_BGRA,
		FORMAT_BGRA_INTEGER,
		FORMAT_DEPTH_COMPONENT,
		FORMAT_DEPTH_STENCIL,
		FORMAT_RED,
		FORMAT_RED_INTEGER,
		FORMAT_RG,
		FORMAT_RG_INTEGER,
		FORMAT_RGB,
		FORMAT_RGB_INTEGER,
		FORMAT_RGBA,
		FORMAT_RGBA_INTEGER,
		FORMAT_STENCIL_INDEX
	};

	/// <summary>
	/// Enumeration of the different types of Texture pixel internal data
	/// formats.
	/// </summary>
	enum TextureDataInternalFormat {
		// Base Formats
		INTERNAL_FORMAT_DEPTH_COMPONENT,
		INTERNAL_FORMAT_DEPTH_STENCIL,
		INTERNAL_FORMAT_RED,
		INTERNAL_FORMAT_RG,
		INTERNAL_FORMAT_RGB,
		INTERNAL_FORMAT_RGBA,

		// Sized Formats
		INTERNAL_FORMAT_R8,
		INTERNAL_FORMAT_R8_SNORM,
		INTERNAL_FORMAT_R16,
		INTERNAL_FORMAT_R16_SNORM,
		INTERNAL_FORMAT_RG8,
		INTERNAL_FORMAT_RG8_SNORM,
		INTERNAL_FORMAT_RG16,
		INTERNAL_FORMAT_RG16_SNORM,
		INTERNAL_FORMAT_R3_G3_B2,
		INTERNAL_FORMAT_RGB4,
		INTERNAL_FORMAT_RGB5,
		INTERNAL_FORMAT_RGB8,
		INTERNAL_FORMAT_RGB8_SNORM,
		INTERNAL_FORMAT_RGB10,
		INTERNAL_FORMAT_RGB12,
		INTERNAL_FORMAT_RGB16_SNORM,
		INTERNAL_FORMAT_RGBA2,
		INTERNAL_FORMAT_RGBA4,
		INTERNAL_FORMAT_RGB5_A1,
		INTERNAL_FORMAT_RGBA8,
		INTERNAL_FORMAT_RGBA8_SNORM,
		INTERNAL_FORMAT_RGB10_A2,
		INTERNAL_FORMAT_RGB10_A2UI,
		INTERNAL_FORMAT_RGBA12,
		INTERNAL_FORMAT_RGBA16,
		INTERNAL_FORMAT_SRGB8,
		INTERNAL_FORMAT_SRGB8_ALPHA8,
		INTERNAL_FORMAT_R16F,
		INTERNAL_FORMAT_RG16F,
		INTERNAL_FORMAT_RGB16F,
		INTERNAL_FORMAT_RGBA16F,
		INTERNAL_FORMAT_R32F,
		INTERNAL_FORMAT_RG32F,
		INTERNAL_FORMAT_RGB32F,
		INTERNAL_FORMAT_RGBA32F,
		INTERNAL_FORMAT_R11F_G11F_B10F,
		INTERNAL_FORMAT_RGB9_E5,
		INTERNAL_FORMAT_R8I,
		INTERNAL_FORMAT_R8UI,
		INTERNAL_FORMAT_R16I,
		INTERNAL_FORMAT_R16UI,
		INTERNAL_FORMAT_R32I,
		INTERNAL_FORMAT_R32UI,
		INTERNAL_FORMAT_RG8I,
		INTERNAL_FORMAT_RG8UI,
		INTERNAL_FORMAT_RG16I,
		INTERNAL_FORMAT_RG16UI,
		INTERNAL_FORMAT_RG32I,
		INTERNAL_FORMAT_RG32UI,
		INTERNAL_FORMAT_RGB8I,
		INTERNAL_FORMAT_RGB8UI,
		INTERNAL_FORMAT_RGB16I,
		INTERNAL_FORMAT_RGB16UI,
		INTERNAL_FORMAT_RGB32I,
		INTERNAL_FORMAT_RGB32UI,
		INTERNAL_FORMAT_RGBA8I,
		INTERNAL_FORMAT_RGBA8UI,
		INTERNAL_FORMAT_RGBA16I,
		INTERNAL_FORMAT_RGBA16UI,
		INTERNAL_FORMAT_RGBA32I,
		INTERNAL_FORMAT_RGBA32UI,
		INTERNAL_FORMAT_DEPTH_COMPONENT16,
		INTERNAL_FORMAT_DEPTH_COMPONENT24,
		INTERNAL_FORMAT_DEPTH_COMPONENT32F,
		INTERNAL_FORMAT_DEPTH24_STENCIL8,
		INTERNAL_FORMAT_DEPTH32F_STENCIL8
	};

	/// <summary>
	/// Enumeration of the different types of Texture2D pixel data types.
	/// </summary>
	enum TextureDataType {
		DATA_BYTE,
		DATA_FLOAT,
		DATA_FLOAT_32_UNSIGNED_INT_24_8_REV,
		DATA_HALF_FLOAT,
		DATA_INT,
		DATA_SHORT,
		DATA_UNSIGNED_BYTE,
		DATA_UNSIGNED_INT,
		DATA_UNSIGNED_INT_2_10_10_10_REV,
		DATA_UNSIGNED_INT_10F_11F_11F_REV,
		DATA_UNSIGNED_INT_5_9_9_9_REV,
		DATA_UNSIGNED_INT_24_8,
		DATA_UNSIGNED_SHORT,
		DATA_UNSIGNED_SHORT_5_6_5,
		DATA_UNSIGNED_SHORT_4_4_4_4,
		DATA_UNSIGNED_SHORT_5_5_5_1
	};

	/// <summary>
	/// Enumeration of the different types of Texture2D filtering modes when
	/// magnifying the texture.
	/// </summary>
	enum TextureFilterMagMode {
		FILTER_MAG_LINEAR,
		FILTER_MAG_NEAREST
	};

	/// <summary>
	/// Enumeration of the different types of Texture2D filtering modes when
	/// minifying the texture.
	/// </summary>
	enum TextureFilterMinMode {
		FILTER_MIN_LINEAR,
		FILTER_MIN_LINEAR_MIPMAP_LINEAR,
		FILTER_MIN_LINEAR_MIPMAP_NEAREST,
		FILTER_MIN_NEAREST,
		FILTER_MIN_NEAREST_MIPMAP_LINEAR,
		FILTER_MIN_NEAREST_MIPMAP_NEAREST
	};

	/// <summary>
	/// Enumeration of the different types of Texture 2D wrapping modes.
	/// </summary>
	enum TextureWrapMode {
		WRAP_CLAMP_TO_BORDER,
		WRAP_CLAMP_TO_EDGE,
		WRAP_MIRRORED_REPEAT,
		WRAP_REPEAT
	};

	/// <summary>
	/// Converts the specified Texture2D Data Format enumeration to its
	/// GLint counterpart.
	/// </summary>
	/// <param name="format">
	/// The data format value.
	/// </param>
	/// <returns>
	/// The GLint value representation of the format value.
	/// </returns>
	GLint getGLintDataFormat(const TextureDataFormat &format);

	/// <summary>
	/// Converts the specified Texture2D Data Type enumeration to its
	/// GLint counterpart.
	/// </summary>
	/// <param name="type">
	/// The data type value.
	/// </param>
	/// <returns>
	/// The GLint value representation of the type value.
	/// </returns>
	GLint getGLintDataType(const TextureDataType &type);

	/// <summary>
	/// Converts the specified Texture2D Filter Magnifying Mode enumeration
	/// to its GLint counterpart.
	/// </summary>
	/// <param name="filter">
	/// The filter mode value.
	/// </param>
	/// <returns>
	/// The GLint value representation of the filter value.
	/// </returns>
	GLint getGLintFilterMagMode(const TextureFilterMagMode &filter);

	/// <summary>
	/// Converts the specified Texture2D Filter Minifying Mode enumeration
	/// to its GLint counterpart.
	/// </summary>
	/// <param name="filter">
	/// The filter mode value.
	/// </param>
	/// <returns>
	/// The GLint value representation of the filter value.
	/// </returns>
	GLint getGLintFilterMinMode(const TextureFilterMinMode &filter);

	/// <summary>
	/// Converts the specified Texture2D Internal Data Format enumeration 
	/// to its GLint counterpart.
	/// </summary>
	/// <param name="iformat">
	/// The internal data format value.
	/// </param>
	/// <returns>
	/// The GLint value representation of the internal format value.
	/// </returns>
	GLint getGLintInternalDataFormat(const TextureDataInternalFormat &iformat);

	/// <summary>
	/// Converts the specified Texture2D Wrap Mode enumeration to its
	/// GLint counterpart.
	/// </summary>
	/// <param name="wrap">
	/// The wrapping mode value.
	/// </param>
	/// <returns>
	/// The GLint value representation of the wrap value.
	/// </returns>
	GLint getGLintWrapMode(const TextureWrapMode &wrap);
} }

#endif