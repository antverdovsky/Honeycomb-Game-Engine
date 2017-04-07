#include "../../include/graphics/Texture2D.h"

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../include/file/FileIO.h"

using namespace Honeycomb::File;

namespace Honeycomb { namespace Graphics {
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

	bool Texture2D::initialize() {
		if (this->isInitialized) return false;
		
		GLuint texID;
		glGenTextures(1, &texID);
		this->textureID = texID;

		this->isInitialized = true;
		return true;
	}

	void Texture2D::destroy() {
		GLuint texID = this->textureID;
		glDeleteTextures(1, &texID); // Delete Texture from OpenGL
	}

	void Texture2D::setImageData(const int &r, const int &g, const int &b) {
		this->bind();

		GLubyte color[] = { (GLubyte)r, (GLubyte)g, (GLubyte)b };
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB,
			GL_UNSIGNED_BYTE, color);
	}

	void Texture2D::setImageData(const std::string &file, 
			const int &r, const int &g, const int &b) {
		this->setImageData(file, GL_RGB, GL_RGB, r, g, b);
	}

	void Texture2D::setImageData(const std::string &file, const int &in, 
			const int &ex, const int &r, const int &g, const int &b) {
		// Read in the data from the image file
		int w, h;
		auto data = File::readImageToUChar(file, w, h);

		if (data != nullptr) {	// Data was read in -> Send to texture
			this->setImageData(data, GL_UNSIGNED_BYTE, in, ex, w, h);
			this->directory = file;
		} else {				// Data was not read in -> Send RGB to texture
			this->setImageData(r, g, b);

			delete data;		// Delete the data
		}
	}

	void Texture2D::setImageData(unsigned char *data, const int &type, 
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
