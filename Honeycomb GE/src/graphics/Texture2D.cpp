#include "..\..\include\graphics\Texture2D.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\file\FileIO.h"

using namespace Honeycomb::File;

namespace Honeycomb::Graphics {
	Texture2D::Texture2D() {
		GLuint texID;
		glGenTextures(1, &texID); // Initialize Texture using OpenGL

		this->textureID = texID;
	}

	Texture2D::~Texture2D() {
		GLuint texID = this->textureID;
		glDeleteTextures(1, &texID); // Delete Texture from OpenGL
	}

	void Texture2D::bind() {
		glBindTexture(GL_TEXTURE_2D, this->textureID);
	}

	void Texture2D::genMipMap() {
		this->bind();

		glGenerateMipmap(GL_TEXTURE_2D);

		this->unbind();
	}

	void Texture2D::setImageData(std::string file) {
		// Store the width, height and image data.
		int width, height;
		unsigned char *data = File::readImageToUChar(file, width, height);

		this->setImageData(data, GL_RGBA, GL_BGRA, width, height);
		delete data;
	}

	void Texture2D::setImageData(unsigned char *data, int inForm, int exForm,
			int w, int h) {
		this->bind();

		// Pass in the Image to OpenGL using the given parameters
		glTexImage2D(GL_TEXTURE_2D, 0, inForm, w, h, 0, exForm, 
			GL_UNSIGNED_BYTE, data);

		this->unbind();
	}

	void Texture2D::setTextureFiltering(int min, int mag) {
		this->bind();

		// Set the minifying and magnifying filter parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);

		this->unbind();
	}

	void Texture2D::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}