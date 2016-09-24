#include "..\..\include\file\FileIO.h"
#include "..\..\include\shader\Shader.h"

#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

using namespace Honeycomb::File;

namespace Honeycomb::Shader {
	Shader::Shader() {
		// Create a pointer to the program ID for the shader
		this->programID = glCreateProgram();
	}

	Shader::~Shader() {
		glDeleteProgram(this->programID);
	}

	void Shader::addShader(std::string file, int type) {
		// Read in the source from the file provided and get a pointer to it
		std::string src = readFileToStr(file);
		const char *srcPtr = src.c_str();

		GLuint shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &srcPtr, NULL);
		glCompileShader(shaderID);

		// Print all of the error / warning messages which the compiler has
		GLint logLen = 0;
		GLint success = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLen);
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (logLen > 0 && success == GL_FALSE) { // If something went wrong
#if _DEBUG
		// Get the message that OpenGL is trying to state, print it out and 
		// discard the temporarily stored message from memory.
			GLchar *logString = new char[logLen + 1];
			glGetShaderInfoLog(shaderID, logLen, NULL, logString);
			std::cout << "FAILED: " << std::endl << logString << std::endl;
			delete[] logString;

			glDeleteShader(shaderID);
			return;
#endif
		}

		// Attach the shader to this shader program & store its ID for later
		glAttachShader(this->programID, shaderID);
		this->shaderIDs.push_back(shaderID);
	}

	void Shader::bindProgram() {
		glUseProgram(this->programID);
	}

	void Shader::finalizeProgram() {
		glLinkProgram(this->programID); // Link the Program

		// Check to the make sure that the link was done correctly
		GLint logLen = 0;
		GLint success = 0;
		glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &logLen);
		glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
		if (logLen > 0 && success == 0) {
#if _DEBUG
			GLchar *logString = new char[logLen + 1];
			glGetProgramInfoLog(this->programID, logLen, NULL, logString);
			std::cout << "FAILED: " << std::endl << logString << std::endl;
			delete[] logString;
			return;
#endif
		}

		glValidateProgram(this->programID); // Validate the Program

		// Check to make sure that the validation returned no errors
		GLint isValidated;
		glGetProgramiv(this->programID, GL_VALIDATE_STATUS, &isValidated);

		if (!isValidated) {
#if _DEBUG
			std::cout << "UNABLE TO VALIDATE PROGRAM: " << this->programID <<
				std::endl;

			return;
#endif
		}

		// Detach and delete each individual shader, as its no longer needed
		for (int shaderID : shaderIDs) {
			glDetachShader(this->programID, shaderID);
			glDeleteShader(shaderID);
		}
	}

	void Shader::unbindProgram() {
		glUseProgram(0);
	}
}