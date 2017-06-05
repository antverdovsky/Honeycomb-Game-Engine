#include "../../include/graphics/Texture2D.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../include/file/FileIO.h"

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
		case Texture2DCommonFillColor::BLACK:
			return Texture2D::getTextureBlack();
		case Texture2DCommonFillColor::BLUE:
			return Texture2D::getTextureBlue();
		case Texture2DCommonFillColor::GREEN:
			return Texture2D::getTextureGreen();
		case Texture2DCommonFillColor::RED:
			return Texture2D::getTextureRed();
		case Texture2DCommonFillColor::WHITE:
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
	}

	void Texture2D::bind() const {
		this->bind(0);
	}

	void Texture2D::bind(const int &loc) const {
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		glActiveTexture(GL_TEXTURE0 + loc);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
	}

	void Texture2D::genMipMap() {
		this->bind();

		glGenerateMipmap(GL_TEXTURE_2D);
	}

	const int& Texture2D::getTextureID() const {
		return this->textureID;
	}

	void Texture2D::initialize() {
		GLItem::initialize();
		
		GLuint texID;
		glGenTextures(1, &texID);
		this->textureID = texID;
		
		++(Texture2D::textureCount);
	}

	void Texture2D::destroy() {
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		GLuint texID = this->textureID;
		glDeleteTextures(1, &texID); // Delete Texture from OpenGL

		--(Texture2D::textureCount);
	}

	void Texture2D::setFiltering(const Texture2DFilterMode &filter) {
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	}

	void Texture2D::setFiltering(const Texture2DFilterMode &min,
			const Texture2DFilterMode &mag) {
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
	}

	void Texture2D::setImageDataFill(
			const int &r, const int &g, const int &b, const int &a) {
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		GLubyte color[] = { (GLubyte)r, (GLubyte)g, (GLubyte)b, (GLubyte)a };
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, color);
	}

	void Texture2D::setImageDataIO(const ImageIO &image) {
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		this->setImageDataManual(
			image.getData(), GL_UNSIGNED_BYTE, GL_RGB, GL_RGB,
			image.getWidth(), image.getHeight());
	}

	void Texture2D::setImageDataManual(const unsigned char *data, const int &type, 
			const int &in, const int &ex, const int &w, const int &h) {
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		// Pass in the Image to OpenGL using the given parameters
		glTexImage2D(GL_TEXTURE_2D, 0, in, w, h, 0, ex, type, data);

		// Default Texture2D settings
		this->setFiltering(Texture2DFilterMode::NEAREST, 
			Texture2DFilterMode::NEAREST);
		this->setWrap(Texture2DWrapMode::REPEAT, Texture2DWrapMode::REPEAT);
		this->genMipMap();
	}

	void Texture2D::setWrap(const Texture2DWrapMode &wrap) {
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
	}

	void Texture2D::setWrap(const Texture2DWrapMode &s, 
			const Texture2DWrapMode &t) {
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, t);
	}
} }
