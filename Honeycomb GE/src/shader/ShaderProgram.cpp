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
	const std::string ShaderProgram::SINGLE_LINE_COMMENT_BEGIN = "//";
	const std::string ShaderProgram::SINGLE_LINE_COMMENT_END = "\n";
	const std::string ShaderProgram::MULTI_LINE_COMMENT_BEGIN = "/*";
	const std::string ShaderProgram::MULTI_LINE_COMMENT_END = "*/";

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
		std::string *src = this->processSource(file);
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

	void ShaderProgram::deleteComments(std::string &source) {
		// Indices at which a comment begins and ends
		int startIndex = 0;
		int endIndex = 0;

		while (true) { // Will keep going until start index becomes invalid
			// Find the starting index and ending index by searching starting
			// from the last comment's starting index (do not use the last
			// comment's ending index as the file length has changed after the
			// last comment's deletion).
			startIndex = source.find(SINGLE_LINE_COMMENT_BEGIN, startIndex);
			endIndex = source.find(SINGLE_LINE_COMMENT_END, startIndex);
			
			if (startIndex == source.npos) break;
			else source.erase(startIndex, endIndex - startIndex + 
				SINGLE_LINE_COMMENT_END.size());
		}

		// Reset back to the start of the file for Multi Line Comment Search
		startIndex = 0;
		endIndex = 0;

		while (true) { // See Above
			startIndex = source.find(MULTI_LINE_COMMENT_BEGIN, startIndex);
			endIndex = source.find(MULTI_LINE_COMMENT_END, startIndex);

			if (startIndex == source.npos) break;
			else source.erase(startIndex, endIndex - startIndex + 
				MULTI_LINE_COMMENT_END.size());
		}
	}

	void ShaderProgram::includeDependencies(const std::string &file,
		std::string &source) {
		// Variables defining the position of the last found include directive
		// and the offset from the beginning of the source code at which the
		// search should begin the next iteration.
		int pos = 0;
		int offset = 0;

		// While an include directive has been found at some valid position
		while ((pos = source.find(INCLUDE_DIRECTIVE, offset)) != source.npos) {
			// Find the two angle brackets which indicate the beginning and
			// end of the file of the shader to be imported.
			int fileBegin = source.find("<", pos) + 1; // Starting Index
			int fileEnd = source.find(">", fileBegin); // Ending Index
			int fileLen = fileEnd - fileBegin; // File Length

			// Get the directory of file as it appears in the include statement
			std::string importFileLocal = source.substr(fileBegin, fileLen);

			// Get the directory in which this file (not the import) is located
			std::string importFileGlobal = file.substr(0,
				file.find_last_of("\\"));

			// While there are "..\" symbols in the local file directory, move 
			// the directory back one folder (like standard C imports).
			while (importFileLocal.substr(0, 3) == "..\\") {
				// Remove the "..\" symbols from the local file directory
				importFileLocal = importFileLocal.substr(3);

				// Delete the the last folder directory from the full directory
				// (like "cd ..\")
				importFileGlobal = importFileGlobal.substr(0,
					importFileGlobal.find_last_of("\\"));
			}

			// Append the name of the file once the final folder has been
			// reached. This is the global directory of the file which is to be
			// imported.
			importFileGlobal += "\\" + importFileLocal;

			// Import the source code from the full system path and process it
			std::string *importSrc = this->processSource(
				importFileGlobal);

			// Replace the include directive with the imported source code &
			// delete the imported source code.
			source.replace(pos, fileEnd + 1 - pos, importSrc->c_str());
			delete importSrc;

			// Set the new position from which to look for the next include
			// directive as the end of this include directive.
			offset = fileLen + 1;
		}
	}

	void ShaderProgram::detectUniforms(const std::string &source) {
		// Variables defining the position of the last found uniform directive
		// and the offset from the beginning of the source code at which the
		// search should begin the next iteration.
		int pos = 0;
		int offset = 0;

		// While a uniform directive has been found at some valid position
		while ((pos = source.find(UNIFORM_DIRECTIVE, offset)) != source.npos) {
			// Declare variables for the indices of the beginning and end of
			// the uniform declaration statements. Use them to find the length
			// for substrings.
			int declBegin = pos;
			int declEnd = source.find(";", pos);
			int declLen = declEnd - declBegin;

			// Get the entire declaration substring and feed it to the string
			// stream to be split up and processed.
			std::string declaration = source.substr(declBegin, declLen);
			std::stringstream sS(declaration);
			std::string token = "";

			std::string type; // The type of uniform this is

			int tokenNumber = -1; // The token number in the declaration
			while (std::getline(sS, token, ' ')) { // Split declaration by ' '
				tokenNumber++; // New Token -> Increment Token Number

				switch (tokenNumber) {
				case 0:	// The first token should be the word uniform; skip it
					continue;
				case 1: // The second token should be the uniform type
					type = token;
					break;
				case 2: // The third token is the uniform name; add it
					this->detectedUniforms.push_back(token);
					break;
				}
			}

			offset = declEnd + 1;
		}
	}

	std::string* ShaderProgram::processSource(const std::string &file) {
		std::string *importSrc = File::readFileToStr(file); // Import Source
		
		// Process the imported source code
		this->deleteComments(*importSrc);
		this->includeDependencies(file, *importSrc);
		this->detectUniforms(*importSrc);

		return importSrc;
	}
}