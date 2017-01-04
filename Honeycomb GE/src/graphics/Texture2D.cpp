#include "..\..\include\graphics\Texture2D.h"

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\file\FileIO.h"

using namespace Honeycomb::File;

namespace Honeycomb::Graphics {
	Texture2D::Texture2D() {
		this->isInitialized = false;
		this->directory = "";
		this->textureID = -1;
	}

	void Texture2D::bind() const {
		glBindTexture(GL_TEXTURE_2D, this->textureID);
	}

	void Texture2D::genMipMap() {
		this->bind();

		glGenerateMipmap(GL_TEXTURE_2D);

		this->unbind();
	}

	bool Texture2D::initialize(const std::string &file) {
		if (this->isInitialized) return false;
		
		this->directory = file;
		GLuint texID;
		glGenTextures(1, &texID);
		this->textureID = texID;

		if (file.empty()) { // If empty file -> Create a 1x1 white RGBA texture
			GLubyte white[] = { 255, 255, 255, 255 };

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA,
				GL_UNSIGNED_BYTE, white);
		} else { // Otherwise, import the texture from file
			this->setImageData(file, GL_RGB, GL_RGB);
		}

		// Default Texture2D settings
		this->setTextureFiltering(GL_NEAREST, GL_NEAREST);
		this->setTextureWrap(GL_REPEAT, GL_REPEAT);
		this->genMipMap();
	}

	void Texture2D::destroy() {
		GLuint texID = this->textureID;
		glDeleteTextures(1, &texID); // Delete Texture from OpenGL
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