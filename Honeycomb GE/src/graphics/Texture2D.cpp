#include "../../include/graphics/Texture2D.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../include/base/GLErrorException.h"

using Honeycomb::Base::GLErrorException;
using Honeycomb::Base::GLItemNotInitializedException;
using namespace Honeycomb::File;

namespace Honeycomb { namespace Graphics {
	int Texture2D::textureCount = 0;

	const int& Texture2D::getInitializedTexturesCount() {
		return Texture2D::textureCount;
	}

	const Texture2D& Texture2D::getTextureBlack() {
		static Texture2D blackTexture;

		if (!blackTexture.isInitialized) {
			blackTexture.initialize();
			blackTexture.setImageDataFill(0, 0, 0, 255);
		}

		return blackTexture;
	}

	const Texture2D& Texture2D::getTextureBlue() {
		static Texture2D blueTexture;

		if (!blueTexture.isInitialized) {
			blueTexture.initialize();
			blueTexture.setImageDataFill(0, 0, 255, 255);
		}

		return blueTexture;
	}

	const Texture2D& Texture2D::getTextureCommonFill(
			const Texture2DCommonFillColor &c) {
		switch (c) {
		case Texture2DCommonFillColor::COLOR_BLACK:
			return Texture2D::getTextureBlack();
		case Texture2DCommonFillColor::COLOR_BLUE:
			return Texture2D::getTextureBlue();
		case Texture2DCommonFillColor::COLOR_GREEN:
			return Texture2D::getTextureGreen();
		case Texture2DCommonFillColor::COLOR_RED:
			return Texture2D::getTextureRed();
		case Texture2DCommonFillColor::COLOR_WHITE:
			return Texture2D::getTextureWhite();
		}
	}

	const Texture2D& Texture2D::getTextureGreen() {
		static Texture2D greenTexture;

		if (!greenTexture.isInitialized) {
			greenTexture.initialize();
			greenTexture.setImageDataFill(0, 255, 0, 255);
		}

		return greenTexture;
	}

	const Texture2D& Texture2D::getTextureRed() {
		static Texture2D redTexture;

		if (!redTexture.isInitialized) {
			redTexture.initialize();
			redTexture.setImageDataFill(255, 0, 0, 255);
		}

		return redTexture;
	}

	const Texture2D& Texture2D::getTextureWhite() {
		static Texture2D whiteTexture;

		if (!whiteTexture.isInitialized) {
			whiteTexture.initialize();
			whiteTexture.setImageDataFill(255, 255, 255, 255);
		}

		return whiteTexture;
	}

	Texture2D::Texture2D() {
		this->isInitialized = false;
		this->textureID = -1;
		
		this->usesMipMap = false;
		this->height = -1;
		this->width = -1;
	}

	void Texture2D::bind() const {
		this->bind(0);
	}

	void Texture2D::bind(const int &loc) const {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		glActiveTexture(GL_TEXTURE0 + loc);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	const int& Texture2D::getHeight() const {
		return this->height;
	}

	const int& Texture2D::getTextureID() const {
		return this->textureID;
	}

	const int& Texture2D::getWidth() const {
		return this->width;
	}

	void Texture2D::initialize() {
		GLErrorException::clear();
		GLItem::initialize();
		
		GLuint texID;
		glGenTextures(1, &texID);
		this->textureID = texID;
		
		++(Texture2D::textureCount);
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Texture2D::destroy() {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		GLuint texID = this->textureID;
		glDeleteTextures(1, &texID); // Delete Texture from OpenGL

		--(Texture2D::textureCount);
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Texture2D::setAnisotropicFiltering(const int &aniso) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		this->anisoFiltering = aniso;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT,
			this->anisoFiltering);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Texture2D::setFiltering(const TextureFilterMagMode &filter) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			Texture2D::getGLintFilterMagMode(filter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			Texture2D::getGLintFilterMagMode(filter));
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Texture2D::setFiltering(const TextureFilterMinMode &min,
			const TextureFilterMagMode &mag) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			Texture2D::getGLintFilterMinMode(min));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			Texture2D::getGLintFilterMagMode(mag));
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Texture2D::setImageDataFill(
			const int &r, const int &g, const int &b, const int &a) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		GLubyte color[] = { (GLubyte)r, (GLubyte)g, (GLubyte)b, (GLubyte)a };
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, color);

		this->width = this->height = 1;
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Texture2D::setImageDataIO(const ImageIO &image, const bool &mipmap) {
		this->setImageDataManual<unsigned char>(
			image.getData(),
			TextureDataType::DATA_UNSIGNED_BYTE,
			TextureDataInternalFormat::INTERNAL_FORMAT_RGB,
			TextureDataFormat::FORMAT_RGB,
			image.getWidth(), image.getHeight(), mipmap);
	}

	template <typename T>
	void Texture2D::setImageDataManual(const T *data,
			const TextureDataType &type,
			const TextureDataInternalFormat &iformat,
			const TextureDataFormat &format,
			const int &width, const int &height, const bool &mipmap) {
		// If not initialized, throw exception; bind texture for change
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		// Write the data to the texture
		this->width = width;
		this->height = height;
		this->usesMipMap = mipmap;
		glTexImage2D(GL_TEXTURE_2D, 0,
			Texture2D::getGLintInternalDataFormat(iformat),
			width, height, 0,
			Texture2D::getGLintDataFormat(format),
			Texture2D::getGLintDataType(type),
			data);

		// Set the default Texture2D Settings
		this->setWrap(WRAP_REPEAT);
		this->setAnisotropicFiltering(1.0F);
		if (this->usesMipMap) {
			this->setFiltering(FILTER_MIN_LINEAR_MIPMAP_LINEAR, 
				FILTER_MAG_LINEAR);

			glGenerateMipmap(GL_TEXTURE_2D);
		} else {
			this->setFiltering(FILTER_MAG_LINEAR);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		}
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Texture2D::setWrap(const TextureWrapMode &wrap) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 
			Texture2D::getGLintWrapMode(wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
			Texture2D::getGLintWrapMode(wrap));
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Texture2D::setWrap(const TextureWrapMode &s, 
			const TextureWrapMode &t) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 
			Texture2D::getGLintWrapMode(s));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 
			Texture2D::getGLintWrapMode(t));
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	GLint Texture2D::getGLintFilterMagMode(const TextureFilterMagMode 
			&filter) {
		switch (filter) {
		case FILTER_MAG_LINEAR:                      return GL_LINEAR;
		case FILTER_MAG_NEAREST:                     return GL_NEAREST;
		default:                                     return -1;
		}
	}

	GLint Texture2D::getGLintFilterMinMode(const TextureFilterMinMode 
			&filter) {
		switch (filter) {
		case FILTER_MAG_LINEAR:                      return GL_LINEAR;
		case FILTER_MIN_LINEAR_MIPMAP_LINEAR:
			return GL_LINEAR_MIPMAP_LINEAR;
		case FILTER_MIN_LINEAR_MIPMAP_NEAREST:
			return GL_LINEAR_MIPMAP_NEAREST;
		case FILTER_MIN_NEAREST:                     return GL_NEAREST;
		case FILTER_MIN_NEAREST_MIPMAP_LINEAR:
			return GL_NEAREST_MIPMAP_LINEAR;
		case FILTER_MIN_NEAREST_MIPMAP_NEAREST:
			return GL_NEAREST_MIPMAP_NEAREST;
		}
	}

	GLint Texture2D::getGLintDataFormat(const TextureDataFormat &format) {
		switch (format) {
		case FORMAT_BGR:                             return GL_BGR;
		case FORMAT_BGRA:                            return GL_BGRA;
		case FORMAT_BGRA_INTEGER:                    return GL_BGRA_INTEGER;
		case FORMAT_BGR_INTEGER:                     return GL_BGR_INTEGER;
		case FORMAT_DEPTH_COMPONENT:                 return GL_DEPTH_COMPONENT;
		case FORMAT_DEPTH_STENCIL:                   return GL_DEPTH_STENCIL;
		case FORMAT_RED:                             return GL_RED;
		case FORMAT_RED_INTEGER:                     return GL_RED_INTEGER;
		case FORMAT_RG:                              return GL_RG;
		case FORMAT_RGB:                             return GL_RGB;
		case FORMAT_RGBA:                            return GL_RGBA;
		case FORMAT_RGBA_INTEGER:                    return GL_RGBA_INTEGER;
		case FORMAT_RGB_INTEGER:                     return GL_RGB_INTEGER;
		case FORMAT_RG_INTEGER:                      return GL_RG_INTEGER;
		case FORMAT_STENCIL_INDEX:                   return GL_STENCIL_INDEX;
		default:                                     return -1;
		}
	}

	GLint Texture2D::getGLintDataType(const TextureDataType &type) {
		switch (type) {
		case DATA_BYTE:                              return GL_BYTE;
		case DATA_FLOAT:                             return GL_FLOAT;
		case DATA_FLOAT_32_UNSIGNED_INT_24_8_REV:
			return GL_FLOAT_32_UNSIGNED_INT_24_8_REV;
		case DATA_HALF_FLOAT:                        return GL_HALF_FLOAT;
		case DATA_INT:                               return GL_INT;
		case DATA_SHORT:                             return GL_SHORT;
		case DATA_UNSIGNED_BYTE:                     return GL_UNSIGNED_BYTE;
		case DATA_UNSIGNED_INT:                      return GL_UNSIGNED_INT;
		case DATA_UNSIGNED_INT_2_10_10_10_REV:
			return GL_UNSIGNED_INT_2_10_10_10_REV;
		case DATA_UNSIGNED_INT_10F_11F_11F_REV:
			return GL_UNSIGNED_INT_10F_11F_11F_REV;
		case DATA_UNSIGNED_INT_5_9_9_9_REV:
			return GL_UNSIGNED_INT_5_9_9_9_REV;
		case DATA_UNSIGNED_INT_24_8:
			return GL_UNSIGNED_INT_24_8;
		case DATA_UNSIGNED_SHORT:                    return GL_UNSIGNED_SHORT;
		case DATA_UNSIGNED_SHORT_5_6_5:
			return GL_UNSIGNED_SHORT_5_6_5;
		case DATA_UNSIGNED_SHORT_4_4_4_4:
			return GL_UNSIGNED_SHORT_4_4_4_4;
		case DATA_UNSIGNED_SHORT_5_5_5_1:
			return GL_UNSIGNED_SHORT_5_5_5_1;
		default:                                     return -1;
		}
	}

	GLint Texture2D::getGLintInternalDataFormat(
			const TextureDataInternalFormat &iformat) {
		switch (iformat) {
		case INTERNAL_FORMAT_DEPTH_COMPONENT:        return GL_DEPTH_COMPONENT;
		case INTERNAL_FORMAT_DEPTH_STENCIL:          return GL_DEPTH_STENCIL;
		case INTERNAL_FORMAT_RED:                    return GL_RED;
		case INTERNAL_FORMAT_RG:                     return GL_RG;
		case INTERNAL_FORMAT_RGB:                    return GL_RGB;
		case INTERNAL_FORMAT_RGBA:                   return GL_RGBA;
		case INTERNAL_FORMAT_R8:                     return GL_R8;
		case INTERNAL_FORMAT_R8_SNORM:               return GL_R8_SNORM;
		case INTERNAL_FORMAT_R16:                    return GL_R16;
		case INTERNAL_FORMAT_R16_SNORM:              return GL_R16_SNORM;
		case INTERNAL_FORMAT_RG8:                    return GL_RG8;
		case INTERNAL_FORMAT_RG8_SNORM:              return GL_RG8_SNORM;
		case INTERNAL_FORMAT_RG16:                   return GL_RG16;
		case INTERNAL_FORMAT_RG16_SNORM:             return GL_RG16_SNORM;
		case INTERNAL_FORMAT_R3_G3_B2:               return GL_R3_G3_B2;
		case INTERNAL_FORMAT_RGB4:                   return GL_RGB4;
		case INTERNAL_FORMAT_RGB5:                   return GL_RGB5;
		case INTERNAL_FORMAT_RGB8:                   return GL_RGB8;
		case INTERNAL_FORMAT_RGB8_SNORM:             return GL_RGB8_SNORM;
		case INTERNAL_FORMAT_RGB10:                  return GL_RGB10;
		case INTERNAL_FORMAT_RGB12:                  return GL_RGB12;
		case INTERNAL_FORMAT_RGB16_SNORM:            return GL_RGB16_SNORM;
		case INTERNAL_FORMAT_RGBA2:                  return GL_RGBA2;
		case INTERNAL_FORMAT_RGBA4:                  return GL_RGBA4;
		case INTERNAL_FORMAT_RGB5_A1:                return GL_RGB5_A1;
		case INTERNAL_FORMAT_RGBA8:                  return GL_RGBA8;
		case INTERNAL_FORMAT_RGBA8_SNORM:            return GL_RGBA8_SNORM;
		case INTERNAL_FORMAT_RGB10_A2:               return GL_RGB10_A2;
		case INTERNAL_FORMAT_RGB10_A2UI:             return GL_RGB10_A2UI;
		case INTERNAL_FORMAT_RGBA12:                 return GL_RGBA12;
		case INTERNAL_FORMAT_RGBA16:                 return GL_RGBA16;
		case INTERNAL_FORMAT_SRGB8:                  return GL_SRGB8;
		case INTERNAL_FORMAT_SRGB8_ALPHA8:           return GL_SRGB8_ALPHA8;
		case INTERNAL_FORMAT_R16F:                   return GL_R16F;
		case INTERNAL_FORMAT_RG16F:                  return GL_RG16F;
		case INTERNAL_FORMAT_RGB16F:                 return GL_RGB16F;
		case INTERNAL_FORMAT_RGBA16F:                return GL_RGBA16F;
		case INTERNAL_FORMAT_R32F:                   return GL_R32F;
		case INTERNAL_FORMAT_RG32F:                  return GL_RG32F;
		case INTERNAL_FORMAT_RGB32F:                 return GL_RGB32F;
		case INTERNAL_FORMAT_RGBA32F:                return GL_RGBA32F;
		case INTERNAL_FORMAT_R11F_G11F_B10F:         return GL_R11F_G11F_B10F;
		case INTERNAL_FORMAT_RGB9_E5:                return GL_RGB9_E5;
		case INTERNAL_FORMAT_R8I:                    return GL_R8I;
		case INTERNAL_FORMAT_R8UI:                   return GL_R8UI;
		case INTERNAL_FORMAT_R16I:                   return GL_R16I;
		case INTERNAL_FORMAT_R16UI:                  return GL_R16UI;
		case INTERNAL_FORMAT_R32I:                   return GL_R32I;
		case INTERNAL_FORMAT_R32UI:                  return GL_R32UI;
		case INTERNAL_FORMAT_RG8I:                   return GL_RG8I;
		case INTERNAL_FORMAT_RG8UI:                  return GL_RG8UI;
		case INTERNAL_FORMAT_RG16I:                  return GL_RG16I;
		case INTERNAL_FORMAT_RG16UI:                 return GL_RG16UI;
		case INTERNAL_FORMAT_RG32I:                  return GL_RG32I;
		case INTERNAL_FORMAT_RG32UI:                 return GL_RG32UI;
		case INTERNAL_FORMAT_RGB8I:                  return GL_RGB8I;
		case INTERNAL_FORMAT_RGB8UI:                 return GL_RGB8UI;
		case INTERNAL_FORMAT_RGB16I:                 return GL_RGB16I;
		case INTERNAL_FORMAT_RGB16UI:                return GL_RGB16UI;
		case INTERNAL_FORMAT_RGB32I:                 return GL_RGB32I;
		case INTERNAL_FORMAT_RGB32UI:                return GL_RGB32UI;
		case INTERNAL_FORMAT_RGBA8I:                 return GL_RGBA8I;
		case INTERNAL_FORMAT_RGBA8UI:                return GL_RGBA8UI;
		case INTERNAL_FORMAT_RGBA16I:                return GL_RGBA16I;
		case INTERNAL_FORMAT_RGBA16UI:               return GL_RGBA16UI;
		case INTERNAL_FORMAT_RGBA32I:                return GL_RGBA32I;
		case INTERNAL_FORMAT_RGBA32UI:               return GL_RGBA32UI;
		case INTERNAL_FORMAT_DEPTH_COMPONENT16:
			return GL_DEPTH_COMPONENT16;
		case INTERNAL_FORMAT_DEPTH_COMPONENT24:
			return GL_DEPTH_COMPONENT24;
		case INTERNAL_FORMAT_DEPTH_COMPONENT32F:
			return GL_DEPTH_COMPONENT32F;
		case INTERNAL_FORMAT_DEPTH24_STENCIL8:
			return GL_DEPTH24_STENCIL8;
		case INTERNAL_FORMAT_DEPTH32F_STENCIL8:
			return GL_DEPTH32F_STENCIL8;
		default:                                     return -1;
		}
	}

	GLint Texture2D::getGLintWrapMode(const TextureWrapMode &wrap) {
		switch (wrap) {
		case WRAP_CLAMP_TO_BORDER:                   return GL_CLAMP_TO_BORDER;
		case WRAP_CLAMP_TO_EDGE:                     return GL_CLAMP_TO_EDGE;
		case WRAP_MIRRORED_REPEAT:                   return GL_MIRRORED_REPEAT;
		case WRAP_REPEAT:                            return GL_REPEAT;
		default:                                     return -1;
		}
	}

	/// <summary>
	/// Forward Declarations for the setImageDataManual function.
	/// </summary>
	template void Texture2D::setImageDataManual<signed char>(
			const signed char *data,
			const TextureDataType &type,
			const TextureDataInternalFormat &iformat,
			const TextureDataFormat &format,
			const int &width, const int &height, const bool &mipmap);
	template void Texture2D::setImageDataManual<float>(
			const float *data,
			const TextureDataType &type,
			const TextureDataInternalFormat &iformat,
			const TextureDataFormat &format,
			const int &width, const int &height, const bool &mipmap);
	template void Texture2D::setImageDataManual<int>(
			const int *data,
			const TextureDataType &type,
			const TextureDataInternalFormat &iformat,
			const TextureDataFormat &format,
			const int &width, const int &height, const bool &mipmap);
	template void Texture2D::setImageDataManual<short>(
			const short *data,
			const TextureDataType &type,
			const TextureDataInternalFormat &iformat,
			const TextureDataFormat &format,
			const int &width, const int &height, const bool &mipmap);
	template void Texture2D::setImageDataManual<unsigned char>(
			const unsigned char *data,
			const TextureDataType &type,
			const TextureDataInternalFormat &iformat,
			const TextureDataFormat &format,
			const int &width, const int &height, const bool &mipmap);
	template void Texture2D::setImageDataManual<unsigned int>(
			const unsigned int *data,
			const TextureDataType &type,
			const TextureDataInternalFormat &iformat,
			const TextureDataFormat &format,
			const int &width, const int &height, const bool &mipmap);
	template void Texture2D::setImageDataManual<unsigned short>(
			const unsigned short *data,
			const TextureDataType &type,
			const TextureDataInternalFormat &iformat,
			const TextureDataFormat &format,
			const int &width, const int &height, const bool &mipmap);
} }
