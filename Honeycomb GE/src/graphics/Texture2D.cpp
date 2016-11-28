#include "..\..\include\graphics\Texture2D.h"

#include <iostream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\file\FileIO.h"

using namespace Honeycomb::File;

namespace Honeycomb::Graphics {
	std::unordered_map<std::string, int> Texture2D::dirToID;
	Texture2D *Texture2D::nonTexture = nullptr;

	int Texture2D::instanceCount[] = { };

	Texture2D::Texture2D()
			: Texture2D(*Texture2D::getNonTexture()) {
	
	}

	Texture2D::Texture2D(std::string file) {
		this->directory = file;

		int texIDfromDir = Texture2D::textureIdFromDirectory(file);
		if (texIDfromDir >= 0) {
			this->textureID = texIDfromDir;

			Texture2D::instanceCount[this->textureID - 1]++;
		} else {
			GLuint texID;
			glGenTextures(1, &texID); // Initialize Texture using OpenGL
			this->textureID = texID;

			this->setImageData(file, GL_RGB, GL_RGB);
			this->setTextureFiltering(GL_NEAREST, GL_NEAREST);
			this->setTextureWrap(GL_REPEAT, GL_REPEAT);
			this->genMipMap();

			Texture2D::instanceCount[this->textureID - 1] = 1;
			Texture2D::dirToID.insert({ this->directory, this->textureID });
		}
	}

	Texture2D::Texture2D(const Texture2D &tex) {
		if (this != &tex) {
			Texture2D::instanceCount[tex.textureID - 1]++;

			this->textureID = tex.textureID;
			this->directory = tex.directory;
		}
	}

	Texture2D::~Texture2D() {
		if (--Texture2D::instanceCount[this->textureID - 1] <= 0) {
			Texture2D::dirToID.erase(this->directory);			
			
			GLuint texID = this->textureID;
			glDeleteTextures(1, &texID); // Delete Texture from OpenGL
		}
	}

	void Texture2D::bind() const {
		glBindTexture(GL_TEXTURE_2D, this->textureID);
	}

	void Texture2D::genMipMap() {
		this->bind();

		glGenerateMipmap(GL_TEXTURE_2D);

		this->unbind();
	}

	void Texture2D::setImageData(std::string file) {
		this->setImageData(file, GL_RGB, GL_RGB);
	}

	void Texture2D::setImageData(std::string file, int inForm, int exForm) {
		// Store the width, height and image data.
		int width, height;
		unsigned char *data = File::readImageToUChar(file, width, height);

		this->setImageData(data, inForm, exForm, width, height);
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

	void Texture2D::setTextureWrap(int s, int t) {
		this->bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);

		this->unbind();
	}

	void Texture2D::unbind() {
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture2D& Texture2D::operator=(const Texture2D &tex) {
		if (this != &tex) {
			Texture2D::instanceCount[tex.textureID - 1]++;

			this->textureID = tex.textureID;
			this->directory = tex.directory;
		}

		std::cout << "created new tex with ID: " << this->textureID << std::endl;

		int j = 32;

		return *this;
	}

	Texture2D* Texture2D::getNonTexture() {
		if (Texture2D::nonTexture == nullptr) {
			Texture2D::nonTexture = new Texture2D(
				"..\\Honeycomb GE\\res\\textures\\default\\null.bmp");
		}

		return Texture2D::nonTexture;
	}

	int Texture2D::textureIdFromDirectory(std::string dir) {
		// Find the index of the texture with the specified directory
		std::unordered_map<std::string, int>::const_iterator texIt =
			Texture2D::dirToID.find(dir);

		if (texIt != Texture2D::dirToID.end()) 
			return texIt->second; // Return ID if found
		
		return -1; // Return negative if not found
	}
}