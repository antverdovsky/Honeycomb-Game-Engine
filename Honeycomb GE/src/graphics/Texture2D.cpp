#include "..\..\include\graphics\Texture2D.h"

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\file\FileIO.h"

using namespace Honeycomb::File;

namespace Honeycomb::Graphics {
	Texture2D *Texture2D::nonTexture = nullptr;

	Texture2D::Texture2D(const std::string &file) {
		this->directory = file;

		// Initialize Texture using OpenGL
		GLuint texID;
		glGenTextures(1, &texID);
		this->textureID = texID;

		// Default Texture2D settings
		this->setImageData(file, GL_RGB, GL_RGB);
		this->setTextureFiltering(GL_NEAREST, GL_NEAREST);
		this->setTextureWrap(GL_REPEAT, GL_REPEAT);
		this->genMipMap();
	}

	Texture2D::~Texture2D() {
		GLuint texID = this->textureID;
		glDeleteTextures(1, &texID); // Delete Texture from OpenGL
	}

	void Texture2D::bind() const {
		glBindTexture(GL_TEXTURE_2D, this->textureID);
	}

	void Texture2D::genMipMap() {
		this->bind();

		glGenerateMipmap(GL_TEXTURE_2D);

		this->unbind();
	}

	const Texture2D& Texture2D::getNonTexture() {
		if (Texture2D::nonTexture == nullptr) Texture2D::nonTexture = new 
			Texture2D("..\\Honeycomb GE\\res\\textures\\default\\null.bmp");

		return *Texture2D::nonTexture;
	}

	void Texture2D::setImageData(const std::string &file) {
		this->setImageData(file, GL_RGB, GL_RGB);
	}

	void Texture2D::setImageData(const std::string &file, const int &in, 
			const int &ex) {
		// Store the width, height and image data.
		int width, height;
		unsigned char *data = File::readImageToUChar(file, width, height);

		this->setImageData(data, in, ex, width, height);
		delete data;
	}

	void Texture2D::setImageData(unsigned char *data, const int &in, 
			const int &ex, const int &w, const int &h) {
		this->bind();

		// Pass in the Image to OpenGL using the given parameters
		glTexImage2D(GL_TEXTURE_2D, 0, in, w, h, 0, ex, GL_UNSIGNED_BYTE, 
			data);

		this->unbind();
	}

	void Texture2D::setTextureFiltering(const int &min, const int &mag) {
		this->bind();

		// Set the minifying and magnifying filter parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);

		this->unbind();
	}

	void Texture2D::setTextureWrap(const int &s, const int &t) {
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);

		this->unbind();
	}

	void Texture2D::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}