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
		this->directory = "";
		this->textureID = -1;
	}

	void Texture2D::bind() const {
		this->bind(0);
	}

	void Texture2D::bind(const int &loc) const {
		glActiveTexture(GL_TEXTURE0 + loc);
		glBindTexture(GL_TEXTURE_2D, this->textureID);
	}

	void Texture2D::genMipMap() {
		this->bind();

		glGenerateMipmap(GL_TEXTURE_2D);
	}

	const std::string& Texture2D::getDirectory() const {
		return this->directory;
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

		std::cout << "Init new, " << (Texture2D::textureCount) << std::endl;
	}

	void Texture2D::destroy() {
		GLuint texID = this->textureID;
		glDeleteTextures(1, &texID); // Delete Texture from OpenGL

		--(Texture2D::textureCount);

		std::cout << "Dest old, " << (Texture2D::textureCount) << std::endl;
	}

	void Texture2D::setImageDataFill(
			const int &r, const int &g, const int &b, const int &a) {
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
		this->bind();

		// Pass in the Image to OpenGL using the given parameters
		glTexImage2D(GL_TEXTURE_2D, 0, in, w, h, 0, ex, type, data);

		// Default Texture2D settings
		this->setTextureFiltering(GL_NEAREST, GL_NEAREST);
		this->setTextureWrap(GL_REPEAT, GL_REPEAT);
		this->genMipMap();
	}

	void Texture2D::setTextureFiltering(const int &min, const int &mag) {
		this->bind();

		// Set the minifying and magnifying filter parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
	}

	void Texture2D::setTextureWrap(const int &s, const int &t) {
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
	}

	void Texture2D::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
} }
