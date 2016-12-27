#include "..\..\include\shader\ShaderProgram.h"

#include <algorithm>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>

#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include "..\..\include\debug\Logger.h"
#include "..\..\include\file\FileIO.h"

using namespace Honeycomb::File;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Debug::Logger;

namespace Honeycomb::Shader {
	const std::string ShaderProgram::INCLUDE_DIRECTIVE = "#include ";
	const std::string ShaderProgram::UNIFORM_DIRECTIVE = "uniform ";

	ShaderProgram::ShaderProgram() {
		this->name = "ShaderProgram";

		// Create a pointer to the program ID for the shader
		this->programID = glCreateProgram();

		this->bindShaderProgram();
	}

	ShaderProgram::~ShaderProgram() {
		glDeleteProgram(this->programID);

		this->unbindShaderProgram();
	}

	void ShaderProgram::addShader(const std::string &file, const int &type) {
		this->bindShaderProgram();

		// Read in the source from the file provided and get a pointer to it
		std::string *src = File::readFileToStr(file, *this);
		const char *srcPtr = src->c_str();

		GLuint shaderID = glCreateShader(type);
		glShaderSource(shaderID, 1, &srcPtr, NULL);
		glCompileShader(shaderID);

		// Print all of the error / warning messages which the compiler has
		GLint logLen = 0;
		GLint success = 0;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logLen);
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (logLen > 0 && success == GL_FALSE) { // If something went wrong
			// Print the error, if any, and delete the shader
			GLchar *logString = new char[logLen + 1];
			glGetShaderInfoLog(shaderID, logLen, NULL, logString);

			Logger::getLogger().logError(__FUNCTION__, __LINE__,
				"Shader Program " + std::to_string(this->programID) +
				" failed to add shader " + "\"" + file + "\"" + "\n\t" +
				std::string(logString));

			delete[] logString;
			glDeleteShader(shaderID);
			return;
		}

		// Attach the shader to this shader program & store its ID for later
		glAttachShader(this->programID, shaderID);
		this->shaders.push_back(shaderID);

		delete src; // Done using the imported contents
	}

	void ShaderProgram::addUniform(const std::string &uni) {
		this->bindShaderProgram();

		// Create the uniform on the GPU & get its location
		int uniformLoc = glGetUniformLocation(this->programID, uni.c_str());

		if (uniformLoc < 0) {
			// Notify the user that the uniform was NOT added
			Logger::getLogger().logError(__FUNCTION__, __LINE__,
				"Shader Program " + std::to_string(this->programID) +
				" failed to add uniform " + "\"" + uni + "\"");

			return;
		}

		// Bind the uniform name and its location to the HashMap so it can be
		// referenced for future use.
		uniforms.insert({ uni, uniformLoc });
	}

	void ShaderProgram::bindShaderProgram() {
		glUseProgram(this->programID);
	}

	void ShaderProgram::finalizeShaderProgram() {
		this->bindShaderProgram();

		glLinkProgram(this->programID); // Link the Program

		// Check to the make sure that the link was done correctly
		GLint logLen = 0;
		GLint success = 0;
		glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &logLen);
		glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
		if (logLen > 0 && success == 0) {
#if _DEBUG
			// Print the error, if any
			GLchar *logString = new char[logLen + 1];
			glGetProgramInfoLog(this->programID, logLen, NULL, logString);

			Logger::getLogger().logError(__FUNCTION__, __LINE__,
				"Shader Program " + std::to_string(this->programID) +
				" failed to finalize!" + "\n\t" + std::string(logString));

			delete[] logString;
			return;
#endif
		}

		glValidateProgram(this->programID); // Validate the Program

		// Check to make sure that the validation returned no errors
		GLint isValidated;
		glGetProgramiv(this->programID, GL_VALIDATE_STATUS, &isValidated);

		if (!isValidated) {
			Logger::getLogger().logWarning(__FUNCTION__, __LINE__,
				"Shader Program " + std::to_string(this->programID) +
				" failed to validate!");
		}

		// Detach and delete each individual shader, as its no longer needed
		for (int shaderID : shaders) {
			glDetachShader(this->programID, shaderID);
			glDeleteShader(shaderID);
		}

		/// temporary probably;
		// Add all of the detected uniforms after the shader is finalized.
		for (std::string uniform : this->detectedUniforms) {
			this->addUniform(uniform);
		}
	}

	int ShaderProgram::getUniformLocation(const std::string &uni) {
		std::unordered_map<std::string, int>::const_iterator it =
			this->uniforms.find(uni);
		
		if (it == this->uniforms.end()) {
			Logger::getLogger().logWarning(__FUNCTION__, __LINE__,
				"Unable to find uniform " + uni + " in Shader Program " +
				std::to_string(this->programID));

			return -1;
		}
		else return it->second;
	}

	void ShaderProgram::lineOperation(const std::string &file, std::string
			&line) {
		this->autoAddUniform(file, line);
		this->importDependency(file, line);
	}

	void ShaderProgram::setUniform_f(const std::string &uni,
		const float &val) {
		this->bindShaderProgram();

		int loc = getUniformLocation(uni); // Get uniform location
		if (loc >= 0) glUniform1f(loc, val); // Write the value to the location
	}

	void ShaderProgram::setUniform_i(const std::string &uni, const int &val) {
		this->bindShaderProgram();

		int loc = getUniformLocation(uni);
		if (loc >= 0) glUniform1i(loc, val);
	}

	void ShaderProgram::setUniform_vec3(const std::string &uni,
		const Vector3f &val) {
		this->bindShaderProgram();

		int loc = getUniformLocation(uni);
		if (loc >= 0) glUniform3f(loc, val.getX(), val.getY(), val.getZ());
	}

	void ShaderProgram::setUniform_vec4(const std::string &uni,
		const Vector4f &val) {
		this->bindShaderProgram();

		int loc = getUniformLocation(uni);
		if (loc >= 0) glUniform4f(loc, val.getX(), val.getY(), val.getZ(),
			val.getW());
	}

	void ShaderProgram::setUniform_mat4(const std::string &uni,
		const Matrix4f &val) {
		this->bindShaderProgram();
		int loc = getUniformLocation(uni);

		float *matPtr = &val.get()[0];
		if (loc >= 0) glUniformMatrix4fv(loc, 1, true, matPtr);
		delete matPtr;
	}

	void ShaderProgram::unbindShaderProgram() {
		glUseProgram(0);
	}

	void ShaderProgram::importDependency(const std::string &file, std::string 
			&line) {
		// If the line does not begin with the include directive -> return
		if (line.substr(0, INCLUDE_DIRECTIVE.size()) != INCLUDE_DIRECTIVE)
			return;

		// Find the two angle brackets which indicate the beginning and
		// end of the file of the shader to be imported.
		int fileBegin = line.find("<") + 1;
		int fileLen = line.find(">") - fileBegin;

		// If the angle brackets are messed up for some reason -> return
		if (fileBegin >= fileLen)
			return;

		// Get the directory of file as it appears in the include statement.
		std::string importFileLocal = line.substr(fileBegin, fileLen);

		// Get the folder in which this file was located.
		std::string importFileGlobal = file.substr(0,
			file.find_last_of("\\"));

		// While there are "..\" symbols in the string, move the
		// directory back one folder.
		while (importFileLocal.substr(0, 3) == "..\\") {
			importFileLocal = importFileLocal.substr(3);
			importFileGlobal = importFileGlobal.substr(0,
				importFileGlobal.find_last_of("\\"));
		}

		// Append the name of the file once the final folder has been
		// reached. This is the global name of the file to be imported.
		importFileGlobal += "\\" + importFileLocal;

		// Import the source code from the full system path.
		std::string *importSrc = File::readFileToStr(importFileGlobal,
			*this);

		// If the source code could not be imported -> return
		if (importSrc == nullptr)
			return;

		// Copy the import source into the current line (so that it may
		// be appended regularly) and remove the imported source code
		// string pointer.
		line = *importSrc;
		delete importSrc;
	}

	void ShaderProgram::autoAddUniform(const std::string &file, 
			std::string &line) {
		// If the line does not contain a uniform initialized -> return
		if (line.substr(0, UNIFORM_DIRECTIVE.size()) != UNIFORM_DIRECTIVE)
			return;

		// Get the indices at which the type of the uniform and the name of the
		// uniform start in the passed in line.
		size_t typeIndex = line.find(' ', UNIFORM_DIRECTIVE.size() - 1) + 1;
		size_t nameIndex = line.find(' ', typeIndex) + 1;

		// Use the type and name indices to retrieve the type and name 
		// substrings from the passed in line.
		std::string type = line.substr(typeIndex, nameIndex - typeIndex - 1);
		std::string name = line.substr(nameIndex);

		// Parse the name string to retain only what is part of the name
		// (trim semicolon, comments, initial value, etc).
		for (int i = 0; i < name.size(); i++) {
			// Variables cannot contain alphanumeric letters, therefore the
			// variable name must end here.
			if (!isalnum(name.at(i))) {
				name = name.substr(0, i);

				break;
			}
		}

		this->detectedUniforms.push_back(name);
	}
}