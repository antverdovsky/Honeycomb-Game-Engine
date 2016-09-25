#include "..\..\include\shader\ShaderProgram.h"

#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\file\FileIO.h"
#include "..\..\include\math\Vector3f.h"
#include "..\..\include\math\Matrix4f.h"

using namespace Honeycomb::File;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Matrix4f;

namespace Honeycomb::Shader {
	ShaderProgram::ShaderProgram() {
		// Create a pointer to the program ID for the shader
		this->programID = glCreateProgram();
	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(this->programID);
	}

	void ShaderProgram::addShader(std::string file, int type) {
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
		this->shaders.push_back(shaderID);
	}

	void ShaderProgram::addUniform(std::string uni) {
		// Create the uniform on the GPU & get its location
		int uniformLoc = glGetUniformLocation(this->programID, uni.c_str());

		if (uniformLoc == -1) {
#if _DEBUG
			std::cout << "Unable to create uniform " << uni << std::endl;

			return;
#endif
		}
		
		// Bind the uniform name and its location to the HashMap so it can be
		// referenced for future use.
		uniforms.insert({ uni, uniformLoc });
	}

	void ShaderProgram::bindShaderProgram() {
		glUseProgram(this->programID);
	}

	void ShaderProgram::finalizeShaderProgram() {
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
		for (int shaderID : shaders) {
			glDetachShader(this->programID, shaderID);
			glDeleteShader(shaderID);
		}
	}

	int ShaderProgram::getUniformLocation(std::string uni) {
		return uniforms.at(uni);
	}

	void ShaderProgram::setUniform_f(std::string uni, float val) {
		int loc = getUniformLocation(uni); // Get uniform location
		glUniform1f(loc, val); // Write the value to the location
	}

	void ShaderProgram::setUniform_i(std::string uni, int val) {
		int loc = getUniformLocation(uni);
		glUniform1i(loc, val);
	}
	
	void ShaderProgram::setUniform_vec3(std::string uni, Vector3f val) {
		int loc = getUniformLocation(uni);
		glUniform3f(loc, val.getX(), val.getY(), val.getZ());
	}

	void ShaderProgram::setUniform_mat4(std::string uni, Matrix4f val) {
		int loc = getUniformLocation(uni);
		glUniformMatrix4fv(loc, 1, false, val.get());
	}
	
	void ShaderProgram::unbindShaderProgram() {
		glUseProgram(0);
	}
}