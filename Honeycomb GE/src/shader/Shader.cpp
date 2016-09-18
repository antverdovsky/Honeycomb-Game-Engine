#include "..\..\include\io\FileIO.h"
#include "..\..\include\shader\Shader.h"

#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

Shader::Shader() {
	// Create a pointer to the program ID for the shader
	this->programID = glCreateProgram();
}

Shader::~Shader() {

}

void Shader::addShader(std::string file, int type) {
	// Read in all of the source from the file provided and get a pointer to it
	std::string src = FileIO::readFileToStr(file);
	const char *srcPtr = src.c_str();

	// Create the shader and compile it
	GLuint shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &srcPtr, NULL);
	glCompileShader(shaderID);

	// Get and print all of the error / warning messages which the compiler has
	GLint logLen = 0;
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLen);
	if (logLen > 0) { // If there is anything in the log to print
#if _DEBUG
		// Get the message that OpenGL is trying to state, print it out and 
		// discard the temporarily stored message from memory.
		GLchar *logString = new char[logLen + 1];
		glGetShaderInfoLog(shaderID, logLen, NULL, logString);
		std::cout << logString << std::endl; // TODO
		delete[] logString;
#endif
	}

	// Attach the shader to this shader program
	glAttachShader(this->programID, shaderID);
}

void Shader::bindProgram() {
	glUseProgram(this->programID);
}

void Shader::finalizeProgram() {
	glLinkProgram(this->programID); // Link the Program

	// Check to the make sure that the link was done correctly
	GLint logLen = 0;
	glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &logLen);
	if (logLen > 0) {
#if _DEBUG
		GLchar *logString = new char[logLen + 1];
		glGetProgramInfoLog(this->programID, logLen, NULL, logString);
		std::cout << logString << std::endl; // TODO
		delete[] logString;
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
#endif
	}
}