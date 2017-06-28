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

	std::shared_ptr<const Texture2D> Texture2D::getTextureBlack() {
		static std::shared_ptr<Texture2D> blackTexture = 
			std::shared_ptr<Texture2D>(new Texture2D());

		if (!blackTexture->isInitialized) {
			blackTexture->initialize();
			blackTexture->setImageDataFill(0, 0, 0, 255);
		}

		return blackTexture;
	}

	std::shared_ptr<const Texture2D> Texture2D::getTextureBlue() {
		static std::shared_ptr<Texture2D> blueTexture =
			std::shared_ptr<Texture2D>(new Texture2D());

		if (!blueTexture->isInitialized) {
			blueTexture->initialize();
			blueTexture->setImageDataFill(0, 0, 255, 255);
		}

		return blueTexture;
	}

	std::shared_ptr<const Texture2D> Texture2D::getTextureCommonFill(
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
		default:
			return Texture2D::getTextureBlack();
		}
	}

	std::shared_ptr<const Texture2D> Texture2D::getTextureGreen() {
		static std::shared_ptr<Texture2D> greenTexture =
			std::shared_ptr<Texture2D>(new Texture2D());

		if (!greenTexture->isInitialized) {
			greenTexture->initialize();
			greenTexture->setImageDataFill(0, 255, 0, 255);
		}

		return greenTexture;
	}

	std::shared_ptr<const Texture2D> Texture2D::getTextureRed() {
		static std::shared_ptr<Texture2D> redTexture =
			std::shared_ptr<Texture2D>(new Texture2D());

		if (!redTexture->isInitialized) {
			redTexture->initialize();
			redTexture->setImageDataFill(255, 0, 0, 255);
		}

		return redTexture;
	}

	std::shared_ptr<const Texture2D> Texture2D::getTextureWhite() {
		static std::shared_ptr<Texture2D> whiteTexture =
			std::shared_ptr<Texture2D>(new Texture2D());

		if (!whiteTexture->isInitialized) {
			whiteTexture->initialize();
			whiteTexture->setImageDataFill(255, 255, 255, 255);
		}

		return whiteTexture;
	}

	std::shared_ptr<Texture2D> Texture2D::newTexture2DShared() {
		auto ptr = std::shared_ptr<Texture2D>(new Texture2D());
		ptr->initialize();

		return ptr;
	}

	std::unique_ptr<Texture2D> Texture2D::newTexture2DUnique() {
		auto ptr = std::unique_ptr<Texture2D>(new Texture2D());
		ptr->initialize();

		return ptr;
	}

	Texture2D::~Texture2D() {
		if (this->isInitialized)
			this->destroy();
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

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Texture2D::setFiltering(const TextureFilterMagMode &filter) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			getGLintFilterMagMode(filter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			getGLintFilterMagMode(filter));
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Texture2D::setFiltering(const TextureFilterMinMode &min,
			const TextureFilterMagMode &mag) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
			getGLintFilterMinMode(min));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
			getGLintFilterMagMode(mag));
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Texture2D::setImageDataFill(
			const int &r, const int &g, const int &b, const int &a) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		this->width = 1;
		this->height = 1;
		GLubyte color[] = { (GLubyte)r, (GLubyte)g, (GLubyte)b, (GLubyte)a };
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, color);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Texture2D::setImageDataIO(const ImageIO &image, const bool &mipmap) {
		this->setImageDataManual(
			image.getData(),
			TextureDataType::DATA_UNSIGNED_BYTE,
			TextureDataInternalFormat::INTERNAL_FORMAT_RGB,
			TextureDataFormat::FORMAT_RGB,
			image.getWidth(), image.getHeight(), mipmap);
	}

	void Texture2D::setImageDataManual(const void *data,
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
		glTexImage2D(GL_TEXTURE_2D, 0,
			getGLintInternalDataFormat(iformat),
			width, height, 0,
			getGLintDataFormat(format),
			getGLintDataType(type),
			data);

		// Set the default Texture2D Settings
		this->setWrap(WRAP_REPEAT);
		this->setAnisotropicFiltering(1);
		if (mipmap) {
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
			getGLintWrapMode(wrap));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
			getGLintWrapMode(wrap));
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Texture2D::setWrap(const TextureWrapMode &s, 
			const TextureWrapMode &t) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 
			getGLintWrapMode(s));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 
			getGLintWrapMode(t));
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	bool Texture2D::operator==(const Texture2D &that) const {
		return this->textureID == that.textureID;
	}

	bool Texture2D::operator!=(const Texture2D &that) const {
		return this->textureID != that.textureID;
	}

	Texture2D::Texture2D() {
		this->isInitialized = false;
		this->textureID = -1;

		this->width = 0;
		this->height = 0;
	}
} }
