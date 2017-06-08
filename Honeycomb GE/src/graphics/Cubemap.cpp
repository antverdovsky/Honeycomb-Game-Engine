#include "../../include/graphics/Cubemap.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../include/base/GLErrorException.h"
#include "../../include/file/FileIO.h"

using Honeycomb::Base::GLErrorException;
using Honeycomb::Base::GLItemAlreadyInitializedException;
using Honeycomb::Base::GLItemNotInitializedException;
using Honeycomb::File::readImageToUChar;

namespace Honeycomb { namespace Graphics {
	Cubemap::Cubemap() {
		this->isInitialized = false;
		this->textureID = -1;
	}

	void Cubemap::bind() const {
		this->bind(0);
	}

	void Cubemap::bind(const int &loc) const {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		glActiveTexture(GL_TEXTURE0 + loc);
		glBindTexture(GL_TEXTURE_CUBE_MAP, this->textureID);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Cubemap::initialize() {
		GLErrorException::clear();
		GLItem::initialize();

		GLuint texID;
		glGenTextures(1, &texID);
		this->textureID = texID;
		
		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Cubemap::destroy() {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);

		GLuint texID = this->textureID;
		glDeleteTextures(1, &texID);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Cubemap::setFace(const CubemapTextureTarget &face, const std::string &tex) {
		this->bind(); // Bind the texture before modifying its faces

		// Read in the image data from the file of the texture
		int width, height;
		auto image = readImageToUChar(tex, width, height);

		// Write the image data to the Cubemap (see Texture2D for explanation)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face,
			0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

		// Store the directory, just in case, for the future
		this->faces[face] = tex;

		// Set the minification and magnification filtering of the cubemap to
		// Linear
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		// Set the S, T, R (3D) wrapping of the cubemap 
		glTexParameteri(GL_TEXTURE_CUBE_MAP,
			GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,
			GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP,
			GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	void Cubemap::setFaces(const std::string tex[6]) {
		for (int i = 0; i < 6; ++i)
			this->setFace((CubemapTextureTarget)(CubemapTextureTarget::RIGHT + i), tex[i]);
	}
} }
