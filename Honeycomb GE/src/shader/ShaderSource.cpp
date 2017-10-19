#include "../../include/shader/ShaderSource.h"

#include <algorithm>
#include <regex>
#include <sstream>

#include "../../include/debug/Logger.h"
#include "../../include/file/FileIO.h"

using namespace Honeycomb::File;
using namespace Honeycomb::Debug;

namespace Honeycomb { namespace Shader {
	SourceVariable::SourceVariable(const std::string &name, const std::string
			&type) {
		this->name = name;
		this->type = type;
	}

	ShaderLoadException::ShaderLoadException(const std::string &path) :
			std::runtime_error("shader could not be loaded") {
		this->directory = path;
	}

	const char* ShaderLoadException::what() const noexcept {
		std::ostringstream oss("");
		oss << std::runtime_error::what() << " from directory " <<
			this->directory << ".";
		return oss.str().c_str();
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

	bool ShaderSourceProperties::operator==(
			const ShaderSourceProperties &rhs) const {
		return this->deleteComments == rhs.deleteComments &&
			this->detectStructs == rhs.detectStructs &&
			this->detectUniforms == rhs.detectUniforms &&
			this->includeDependencies == rhs.includeDependencies;
	}

	bool ShaderSourceProperties::operator!=(
			const ShaderSourceProperties &rhs) const {
		return !(*this == rhs);
	}

	ShaderSource& ShaderSource::getShaderSource(const std::string &file,
			const ShaderSourceProperties &prop) {
		auto it = std::find_if(
			ShaderSource::getShaderImports().begin(),
			ShaderSource::getShaderImports().end(),
			[&](const std::unique_ptr<ShaderSource>& imp) {
				return imp->getFile() == file && imp->getProperties() == prop;
		});

		if (it == ShaderSource::getShaderImports().end()) {
			return *(new ShaderSource(file, prop));
		} else {
			return *(it->get());
		}
	}

	const std::string& ShaderSource::getFile() const {
		return this->file;
	}

	const ShaderSourceProperties& ShaderSource::getProperties() const {
		return this->properties;
	}

	const std::string& ShaderSource::getSource() const {
		return this->source;
	}

	bool ShaderSource::operator==(const ShaderSource &rhs) const {
		return this->file == rhs.file && this->properties == rhs.properties;
	}

	bool ShaderSource::operator!=(const ShaderSource &rhs) const {
		return this->file != rhs.file || this->properties != rhs.properties;
	}

	std::vector<std::unique_ptr<ShaderSource>>& 
			ShaderSource::getShaderImports() {
		static std::vector<std::unique_ptr<ShaderSource>> shaders;
		return shaders;
	}

	ShaderSource::ShaderSource(const std::string &file, const
		ShaderSourceProperties &prop) {
		this->file = file;
		this->properties = prop;

		std::string *srcPtr = File::readFileToStr(file);
		if (srcPtr == nullptr) throw ShaderLoadException(file);

		this->source = *srcPtr;
		delete srcPtr;

		if (prop.deleteComments) this->deleteComments();
		if (prop.includeDependencies) this->includeDependencies();
		if (prop.detectStructs) this->detectStructs();
		if (prop.detectUniforms) this->detectUniforms();

		ShaderSource::getShaderImports().push_back(
				std::unique_ptr<ShaderSource>(this));
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
		std::string thisDir = this->file.substr(0, file.find_last_of("/"));

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
			while (rawDir.substr(0, 3) == "../") {
				rawDir = rawDir.substr(3);
				includeDir = includeDir.substr(0,
					includeDir.find_last_of("../"));
			}

			// The full include file path is the directory where the file
			// is located with the name of the file appended at the end.
			std::string includeFile = includeDir + "/" + rawDir;

			// Import the Shader Source code (process with the standard props)
			ShaderSource includeSrc = ShaderSource::getShaderSource(
					includeFile, this->getProperties());

			// Delete the entire include declaration and replace it with the
			// imported source code.
			source.replace(include->position(), include->length(),
				includeSrc.source.c_str());

			// Add any structs and uniforms which exist in the imported src
			this->detUniforms.insert(this->detUniforms.end(),
				includeSrc.detUniforms.begin(),
				includeSrc.detUniforms.end());
			this->detStructs.insert(includeSrc.detStructs.begin(),
				includeSrc.detStructs.end());

			// Since the iterator has been invalidated, rebuild it (but this
			// time, offset the iterator to begin after the included source
			// code, for obvious performance reasons).
			include = std::sregex_iterator(
				source.begin(), source.end(), regex);
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
		std::regex varRegex = std::regex("(\\w+)\\s+(\\w+)");

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

			// Iterator through all of the variables of this struct. Increment
			// said iterator because the first "variable" is this struct.
			std::sregex_iterator varDecl(structBegin, structEnd, varRegex);
			++varDecl;

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
		// uniform name), which is NOT followed by an open bracket (that
		// indicates an array).
		std::regex regexField = std::regex(
			"uniform\\s+(\\w+)\\s+(\\w+)\\s*(?!.*\\[)");

		std::sregex_iterator uniformFields(this->source.cbegin(),
			this->source.cend(), regexField); // Iterator through all uniforms
		std::sregex_iterator end; // End defined by Default Constructor

		// Go through all matched uniforms
		for (; uniformFields != end; uniformFields++) {
			// The first group represents the uniform type; the second the
			// uniform name (see regex description).
			std::string type = uniformFields->str(1);
			std::string name = uniformFields->str(2);

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

		// Regex for automatically detecting uniform array type, name and size.
		// The regex will identify any string containing the word uniform 
		// followed by at least one space, followed by a word (1st group: 
		// uniform type), followed by at least one space, followed by a word 
		// (2nd group: uniform name), followed by a number, surrounded by
		// brackets (3rd group: array size), which is followed by a semicolon.
		std::regex regexArray = std::regex(
			"uniform\\s+(\\w+)\\s+(\\w+)\\s*(?=\\[(\\d+)\\])");

		std::sregex_iterator uniformArrays(this->source.cbegin(),
			this->source.cend(), regexArray); // Iterator through all uniforms

		// Go through all matched uniforms
		for (; uniformArrays != end; uniformArrays++) {
			// The first group represents the uniform type; the second the
			// uniform name (see regex description); the third the size of the
			// array
			std::string type = uniformArrays->str(1);
			std::string name = uniformArrays->str(2);
			int size = atoi(uniformArrays->str(3).c_str());

			for (int i = 0; i < size; ++i) {
				// If the uniform type is a type of a user defined struct
				if (this->detStructs.count(type)) {
					// Get all of the variables of the struct
					std::vector<SourceVariable> structVars =
						this->detStructs[type];

					for (const SourceVariable& structVar : structVars) {
						// Add the full uniform name (uniform name + index + 
						// variable name) to detected uniforms.
						this->detUniforms.push_back(SourceVariable(name + "[" +
							std::to_string(i) + "]" + "." + structVar.name,
							structVar.type));
					}
				}
				else { // If the uniform type is not a user defined struct
					this->detUniforms.push_back(SourceVariable(name, type));
				}
			}
		}
	}
} }