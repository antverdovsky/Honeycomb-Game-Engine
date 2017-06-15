#include "../../include/base/GLErrorException.h"

#include <sstream>

#include <GL/glew.h>

namespace Honeycomb { namespace Base {
	void GLErrorException::clear() {
		glGetError();
	}

	void GLErrorException::checkGLError(const char *file, const int &line) {
		GLenum error = glGetError();

		switch (error) {
		case GL_NO_ERROR: 
			return;
		case GL_INVALID_ENUM: 
			throw GLErrorException(file, line, TYPE_INVALID_ENUM);
		case GL_INVALID_VALUE:
			throw GLErrorException(file, line, TYPE_INVALID_VALUE);
		case GL_INVALID_OPERATION:
			throw GLErrorException(file, line, TYPE_INVALID_OPERATION);
		case GL_STACK_OVERFLOW:
			throw GLErrorException(file, line, TYPE_STACK_OVERFLOW);
		case GL_STACK_UNDERFLOW:
			throw GLErrorException(file, line, TYPE_STACK_UNDERFLOW);
		case GL_OUT_OF_MEMORY:
			throw GLErrorException(file, line, TYPE_OUT_OF_MEMORY);
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			throw GLErrorException(file, line, 
				TYPE_INVALID_FRAMEBUFFER_OPERATION);
		default:
			throw GLErrorException(file, line, TYPE_OTHER);
		}
	}

	GLErrorException::GLErrorException(const char *file, const int &line,
			const GLErrorType &type) :
			std::runtime_error("An OpenGL error has occured") {
		this->file = std::string(file);
		this->line = line;
		this->type = type;
	}

	const char* GLErrorException::what() const throw() {
		std::ostringstream oss("");
		oss << std::runtime_error::what() << "; error type: \"" <<
			errorTypeString(this->type) << "\" in file " << this->file <<
			", line " << this->line << ".";
		return oss.str().c_str();
	}
	
	std::string GLErrorException::errorTypeString(const GLErrorType &type) {
		switch (type) {
		case TYPE_INVALID_ENUM: return "invalid enumeration parameter";
		case TYPE_INVALID_VALUE: return "invalid value parameter";
		case TYPE_INVALID_OPERATION: return "invalid GL operation";
		case TYPE_STACK_OVERFLOW: return "stack overflow";
		case TYPE_STACK_UNDERFLOW: return "stack underflow";
		case TYPE_OUT_OF_MEMORY: return "out of memory";
		case TYPE_INVALID_FRAMEBUFFER_OPERATION: 
			return "invalid framebuffer operation";
		default: return "unknown";
		}
	}
} }