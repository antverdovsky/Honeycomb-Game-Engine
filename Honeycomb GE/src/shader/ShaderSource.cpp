#include "..\..\include\shader\ShaderSource.h"

#include <algorithm>
#include <regex>

#include "..\..\include\debug\Logger.h"
#include "..\..\include\file\FileIO.h"

using namespace Honeycomb::File;
using namespace Honeycomb::Debug;

namespace Honeycomb::Shader {
	SourceVariable::SourceVariable(const std::string &name, const std::string 
			&type) {
		this->name = name;
		this->type = type;
	}

	ShaderSourceProperties::ShaderSourceProperties() : 
			ShaderSourceProperties(true, true, true, true) {
		
	}

	ShaderSourceProperties::ShaderSourceProperties(const bool &dC, 
			const bool &dS, const bool &dU, const bool &iD) {
		this->deleteComments = dC;
		this->detectStructs = dS;
		this->detectUniforms = dU;
		this->includeDependencies = iD;
	}

	std::unordered_map<std::string, ShaderSource*> ShaderSource::shaderSources
		= std::unordered_map<std::string, ShaderSource*>();

	ShaderSource* ShaderSource::getShaderSource(const std::string &file) {
		return ShaderSource::getShaderSource(file, ShaderSourceProperties());
	}

	ShaderSource* ShaderSource::getShaderSource(const std::string &file,
			const ShaderSourceProperties &prop) {
		// Try to find the file in the already imported source files
		std::unordered_map<std::string, ShaderSource*>::iterator it =
			ShaderSource::shaderSources.find(file);

		// If the file has not yet been imported, import it and return the
		// pointer to the newly imported shader source. Otherwise, return a
		// pointer to the existing shader source.
		if (it == ShaderSource::shaderSources.end()) 
			return new ShaderSource(file, prop);
		else
			return it->second;
	}

	const std::string& ShaderSource::getFile() const {
		return this->file;
	}

	const std::string& ShaderSource::getSource() const {
		return this->source;
	}

	ShaderSource::ShaderSource(const std::string &file, const 
			ShaderSourceProperties &prop) {
		this->file = file;

		// Import the original source, copy into this instance, and clean up
		std::string *srcPtr = File::readFileToStr(file);
		this->source = *srcPtr;
		delete srcPtr;

		if (prop.deleteComments) this->deleteComments();
		if (prop.includeDependencies) this->includeDependencies();
		if (prop.detectStructs) this->detectStructs();
		if (prop.detectUniforms) this->detectUniforms();
		
		ShaderSource::shaderSources.insert({ file, this });
	}

	void ShaderSource::deleteComments() {
		// Regex for finding single line and multi line C-style comments
		// The first group deals with matching single line comments (//), and
		// the second group deals with matching multi line comments (/* */).
		std::regex regex = std::regex("(//.*)|(/\\*[^]*?\\*/)");

		// Search using the regex and remove any findings
		this->source = std::regex_replace(this->source, regex, "");
	}

	void ShaderSource::includeDependencies() {
		// Get the directory of this file, by trimming the file name off of the
		// full import directory.
		std::string thisDir = this->file.substr(0, file.find_last_of("\\"));

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

			// Import the Shader Source code (process with the standard props)
			ShaderSource* includeSrc = ShaderSource::getShaderSource(
				includeFile);

			// Delete the entire include declaration and replace it with the
			// imported source code.
			source.replace(include->position(), include->length(),
				includeSrc->source.c_str());

			// Add any structs and uniforms which exist in the imported src
			this->detUniforms.insert(this->detUniforms.end(),
				includeSrc->detUniforms.begin(),
				includeSrc->detUniforms.end());
			this->detStructs.insert(includeSrc->detStructs.begin(),
				includeSrc->detStructs.end());

			// Since the iterator has been invalidated, rebuild it (but this
			// time, offset the iterator to begin after the included source
			// code, for obvious performance reasons).
			include = std::sregex_iterator(
				source.begin() + includeSrc->source.size(), source.end(), 
				regex);
		}
	}

	void ShaderSource::detectStructs() {
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

		std::sregex_iterator structDecl(this->source.cbegin(), 
			this->source.cend(), structRegex); // Iterator through all structs
		std::sregex_iterator end; // Default End Iterator

		for (; structDecl != end; structDecl++) {
			// Get the name of the structure from the first group and define a
			// vector to store all of the variables.
			std::string sName = structDecl->str(1);
			std::vector<SourceVariable> vars;

			// If this struct has already been found -> Continue to next one
			if (detStructs.count(sName)) 
				continue;

			// Get the string iterator for the beginning and end of the struct
			// within the source code.
			auto structBegin = this->source.cbegin() + structDecl->position();
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
				if (this->detStructs.count(vType)) {
					std::vector<SourceVariable> detectedStructVars =
						this->detStructs[vType];
					
					// The variable's full name will be the name of the
					// variable plus the structure's variable. The variable
					// also takes on the type of the struct's variable.
					for (const SourceVariable &structVar : detectedStructVars) 
					{
						vars.push_back(SourceVariable(
							vName + "." + structVar.name,
							structVar.type));
					}
				}
				else { // Otherwise, just add the variable
					vars.push_back(SourceVariable(vName, vType));
				}
			}

			// Add the detected structure name with all of its detected vars
			this->detStructs.insert({ sName, vars });
		}
	}

	void ShaderSource::detectUniforms() {
		// Regex for automatically detecting uniform type and name. The regex
		// will identify any string containing the word uniform followed by at
		// least one space, followed by a word (1st group: uniform type),
		// followed by at least one space, followed by a word (2nd group:
		// uniform name).
		std::regex regex = std::regex("uniform\\s+(\\w+)\\s+(\\w+)");

		std::sregex_iterator uniform(this->source.cbegin(), 
			this->source.cend(), regex); // Iterator through all uniforms
		std::sregex_iterator end; // End defined by Default Constructor

		for (; uniform != end; uniform++) { // Go through all matched uniforms
			// The first group represents the uniform type; the second the
			// uniform name (see regex description).
			std::string type = uniform->str(1);
			std::string name = uniform->str(2);

			// If the uniform type is a type of a user defined struct
			if (this->detStructs.count(type)) {
				// Get all of the variables of the struct
				std::vector<SourceVariable> structVars = 
					this->detStructs[type];

				for (const SourceVariable& structVar : structVars) {
					// Add the full uniform name (uniform name + variable name)
					// to detected uniforms.
					this->detUniforms.push_back(SourceVariable(name + "." + 
						structVar.name, structVar.type));
				}
			}
			else { // If the uniform type is not a user defined struct
				this->detUniforms.push_back(SourceVariable(name, type));
			}
		}
	}
}