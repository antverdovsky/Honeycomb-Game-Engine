#include "../../include/shader/ShaderProgram.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <locale>
#include <regex>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../include/debug/Logger.h"
#include "../../include/file/FileIO.h"

using namespace Honeycomb::File;
using Honeycomb::Math::Vector2f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Debug::Logger;

namespace Honeycomb { namespace Shader {
	ShaderProgram::ShaderProgram(const std::string &name) {
		this->name = name;
	}
	
	void ShaderProgram::addShader(const std::string &file, 
			const ShaderType &type) {
		this->bindShaderProgram();

		// Read in & process the source code from the file specified, and get
		// its raw source code string.
		ShaderSource &source = ShaderSource::getShaderSource(file);
		this->sources.push_back(&source);
		const char *srcPtr = source.getSource().c_str();

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

	void ShaderProgram::destroy() {
		glDeleteProgram(this->programID);
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

		for (ShaderSource *src : this->sources) {
			for (const SourceVariable &var : src->detUniforms) {
				this->addUniform(var.name);
			}
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

	void ShaderProgram::initialize() {
		GLItem::initialize();

		this->programID = glCreateProgram();
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

	void ShaderProgram::setUniform_vec2(const std::string &uni,
			const Vector2f &val) {
		this->bindShaderProgram();

		int loc = getUniformLocation(uni);
		if (loc >= 0) glUniform2f(loc, val.getX(), val.getY());
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
	}

	void ShaderProgram::unbindShaderProgram() {
		glUseProgram(0);
	}
} }
