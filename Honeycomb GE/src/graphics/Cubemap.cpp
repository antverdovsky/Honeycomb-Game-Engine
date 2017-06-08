#include "../../include/graphics/Cubemap.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../include/base/GLErrorException.h"
#include "../../include/file/FileIO.h"

using Honeycomb::Base::GLErrorException;
using Honeycomb::Base::GLItemAlreadyInitializedException;
using Honeycomb::Base::GLItemNotInitializedException;
using Honeycomb::File::ImageIO;

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

	void Cubemap::setFaceDataFill(const CubemapTextureTarget &target,
			const int &r, const int &g, const int &b, const int &a) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		GLubyte color[] = { (GLubyte)r, (GLubyte)g, (GLubyte)b, (GLubyte)a };
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + target,
			0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, color);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}

	void Cubemap::setFaceDataIO(const CubemapTextureTarget &target,
			const ImageIO &image) {
		this->setFaceDataManual(
			target, image.getData(),
			TextureDataType::DATA_UNSIGNED_BYTE,
			TextureDataInternalFormat::INTERNAL_FORMAT_RGB,
			TextureDataFormat::FORMAT_RGB,
			image.getWidth(), image.getHeight());
	}

	void Cubemap::setFaceDataManual(const CubemapTextureTarget &target,
			const void *data, const TextureDataType &type,
			const TextureDataInternalFormat &iformat,
			const TextureDataFormat &format,
			const int &width, const int &height) {
		GLErrorException::clear();
		if (!this->isInitialized) throw GLItemNotInitializedException(this);
		this->bind();

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + target,
			0, getGLintInternalDataFormat(iformat),
			width, height, 0,
			getGLintDataFormat(format), getGLintDataType(type), data);

		GLErrorException::checkGLError(__FILE__, __LINE__);
	}
} }
