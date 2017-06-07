#pragma once
#ifndef GL_ERROR
#define GL_ERROR

#include <stdexcept>
#include <string>

namespace Honeycomb { namespace Base {
	/// <summary>
	/// Enumeration of the different types of OpenGL errors possible.
	/// </summary>
	enum GLErrorType {
		TYPE_NONE,
		TYPE_INVALID_ENUM,
		TYPE_INVALID_VALUE,
		TYPE_INVALID_OPERATION,
		TYPE_STACK_OVERFLOW,
		TYPE_STACK_UNDERFLOW,
		TYPE_OUT_OF_MEMORY,
		TYPE_INVALID_FRAMEBUFFER_OPERATION,
		TYPE_OTHER
	};

	/// <summary>
	/// Class representing an exception for handling OpenGL errors.
	/// </summary>
	class GLErrorException : public std::runtime_error {
	public:
		/// <summary>
		/// Clears the OpenGL error stream.
		/// </summary>
		static void clear();

		/// <summary>
		/// Checks whether a GL error has occured since the last time this
		/// method was called. If so, a new GLErrorException is thrown with the
		/// details of the GL error.
		/// </summary>
		/// <param name="file">
		/// The C++ source file from which this method was called 
		/// (use: __FILE__).
		/// </param>
		/// <param name="line">
		/// The line of the C++ source file from which this method was called
		/// (use: __LINE__).
		/// </param>
		static void checkGLError(const char *file, const int &line);

		/// <summary>
		/// Initializes a new instance of the GLError Exception.
		/// </summary>
		/// <param name="file">
		/// The file in which the error occured (use: __FILE__).
		/// </param>
		/// <param name="line">
		/// The line of the file in which the error occured (use: __LINE__).
		/// </param>
		/// <param name="type">
		/// The type of GL Error which occured.
		/// </param>
		GLErrorException(const char *file, const int &line,
				const GLErrorType &type);

		/// <summary>
		/// Returns a constant character string containing the description of
		/// the exception.
		/// </summary>
		/// <returns>
		/// The constant character string exception info.
		/// </returns>
		virtual const char* what() const throw();
	private:
		/// <summary>
		/// Gets the string description of the passed in error.
		/// </summary>
		/// <param name="type">
		/// The type of the error.
		/// </param>
		/// <returns>
		/// A string representation of the error type.
		/// </returns>
		static std::string errorTypeString(const GLErrorType &type);

		GLErrorType type;
		std::string file;
		int line;
	};
} }

#endif