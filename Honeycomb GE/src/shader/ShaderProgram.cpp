#include "..\..\include\shader\ShaderProgram.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <locale>
#include <regex>
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
	const std::string ShaderProgram::STRUCT_DIRECTIVE = "struct ";

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
		// Regex for finding single line and multi line C-style comments
		// The first group deals with matching single line comments (//), and
		// the second group deals with matching multi line comments (/* */).
		std::regex regex = std::regex("(//.*)|(/\\*[^]*?\\*/)");

		// Search using the regex and remove any findings
		source = std::regex_replace(source, regex, "");
	}
	
	void ShaderProgram::includeDependencies(const std::string &file,
			std::string &source) {
		// Get the directory of this file, by trimming the file name off of the
		// full import directory.
		std::string thisDir = file.substr(0, file.find_last_of("\\"));
		
		// Regex for automatically detecting the file directory which is to be 
		// included. The regex will identify any string containing the word
		// #include, followed by at least one space, followed by the directory
		// of the file (1st group) surrounded by matching angle brackets.
		std::regex regex = std::regex("#include\\s+<(.*)>");

		std::sregex_iterator include(source.cbegin(), source.cend(),
			regex); // Iterator through all the includes in the source
		std::sregex_iterator end; // End defined by Default Constructor

		while (include != end) { // Go through all matched includes
			// Get the raw directory, as it appears between the angle brackets
			std::string rawDir = include->str(1);
											
			// By default, assume that the file which is going to be included
			// is located in the same folder as this file (like with C).
			std::string includeDir = thisDir;

			// If the raw directory contains any back trace symbols (..\), move
			// one directory back (by trimming the back trace symbol, and
			// removing the last folder from the include directory), for each 
			// back trace symbol.
			while (rawDir.substr(0, 3) == "..\\") {
				rawDir = rawDir.substr(3);
				includeDir = includeDir.substr(0, 
					includeDir.find_last_of("..\\"));
			}

			// The full include file path is the directory where the file
			// is located with the name of the file appended at the end.
			std::string includeFile = includeDir + "\\" + rawDir;

			// Import the source and process it.
			std::string* includeSrc = this->processSource(includeFile);

			// Delete the entire include declaration and replace it with the
			// imported source code.
			source.replace(include->position(), include->length(), 
				includeSrc->c_str());

			// Since the iterator has been invalidated, rebuild it (but this
			// time, offset the iterator to begin after the included source
			// code, for obvious performance reasons).
			include = std::sregex_iterator(
				source.begin() + includeSrc->size(), source.end(), regex);

			delete includeSrc; // Clean up the included source
		}
	}

	void ShaderProgram::detectStructs(const std::string &source) {
		// Regex for detecting an entire struct declaration (from the struct
		// keyword to the closing brace and semicolon which ends the struct).
		// The regex will detect any string containing the word struct followed
		// by at least one space, followed by the name of the struct (1st
		// group), followed by some text until the struct end (}) is found.
		std::regex structRegex = std::regex("struct\\s+(\\w+)[^]*?\\}");

		// Regex for detecting variables inside of a struct. The regex will
		// detect any string containing a word defining the type of variable
		// (1st group), followed by at least one space, followed by another
		// word defining the name of the variable (2nd group).
		std::regex varRegex = std::regex("(\\w+)\\s+(\\w+);");

		std::sregex_iterator structDecl(source.cbegin(), source.cend(), 
			structRegex); // Iterator through all of the structs of the source
		std::sregex_iterator end; // Default End Iterator

		for (; structDecl != end; structDecl++) {
			// Get the name of the structure from the first group and define a
			// vector to store all of the variables.
			std::string sName = structDecl->str(1);
			std::vector<std::string> vars;

			// Get the string iterator for the beginning and end of the struct
			// within the source code.
			auto structBegin = source.cbegin() + structDecl->position();
			auto structEnd = structBegin + structDecl->length();

			// Iterator through all of the variables of this struct
			std::sregex_iterator varDecl(structBegin, structEnd, varRegex);
			
			for (; varDecl != end; varDecl++) {
				// Get the type of the variable (first group) and the name of
				// the variable (second group).
				std::string vType = varDecl->str(1);
				std::string vName = varDecl->str(2);

				// If the variable has the type of a previously defined struct
				// then append each of the variables from that struct to this
				// variable (due to how GLSL works).
				if (this->detectedStructs.count(vType)) {
					std::vector<std::string> detectedStructVars =
						this->detectedStructs[vType];

					for (int i = 0; i < detectedStructVars.size(); i++)
						vars.push_back(vName + "." + detectedStructVars.at(i));
				} else { // Otherwise, just add the variable
					vars.push_back(vName);
				}
			}
			
			// Add the detected structure name with all of its detected vars
			this->detectedStructs.insert({ sName, vars });
		}
	}

	void ShaderProgram::detectUniforms(const std::string &source) {
		// Regex for automatically detecting uniform type and name. The regex
		// will identify any string containing the word uniform followed by at
		// least one space, followed by a word (1st group: uniform type),
		// followed by at least one space, followed by a word (2nd group:
		// uniform name).
		std::regex regex = std::regex("uniform\\s+(\\w+)\\s+(\\w+)");
		
		std::sregex_iterator uniform(source.cbegin(), source.cend(),
			regex); // Iterator through all the uniforms in the source
		std::sregex_iterator end; // End defined by Default Constructor

		for (; uniform != end; uniform++) { // Go through all matched uniforms
			// The first group represents the uniform type; the second the
			// uniform name (see regex description).
			std::string type = uniform->str(1);
			std::string name = uniform->str(2);

			// If the uniform type is a type of a user defined struct
			if (this->detectedStructs.count(type)) {
				// Get all of the variables of the struct
				std::vector<std::string> vars = this->detectedStructs[type];

				for (int i = 0; i < vars.size(); i++) {
					// Add the full uniform name (uniform name + variable name)
					// to detected uniforms.
					this->detectedUniforms.push_back(name + "." + vars.at(i));
				}
			} else { // If the uniform type is not a user defined struct
				this->detectedUniforms.push_back(name);
			}
		}
	}

	std::string* ShaderProgram::processSource(const std::string &file) {
		std::string *importSrc = File::readFileToStr(file); // Import Source
		
		// Process the imported source code
		this->deleteComments(*importSrc);
		this->includeDependencies(file, *importSrc);
		this->detectStructs(*importSrc);
		this->detectUniforms(*importSrc);

		return importSrc;
	}
}