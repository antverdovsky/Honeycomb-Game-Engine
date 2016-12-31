#include "..\..\include\shader\ShaderSource.h"

#include "..\..\include\debug\Logger.h"
#include "..\..\include\file\FileIO.h"

using namespace Honeycomb::File;
using namespace Honeycomb::Debug;

namespace Honeycomb::Shader {
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

		// todo, import & process source...
		
		ShaderSource::shaderSources.insert({ file, this });
	}
}