#pragma once
#ifndef SHADER_SOURCE_H
#define SHADER_SOURCE_H

#include <iostream>
#include <unordered_map>

namespace Honeycomb::Shader {
	class ShaderSourceProperties {
		friend class ShaderSource;

	public:
		/// Initializes a new set of Shader Source Properties with all 
		/// properties (detect structs, detect uniforms, include dependencies,
		/// and remove comments) being set to true.
		ShaderSourceProperties();

		/// Initializes a new set of Shader Source Properties with the
		/// specified properties.
		/// const bool &dC : Should comments be removed from the source?
		/// const bool &dS : Should structures be automatically detected?
		/// const bool &dU : Should uniforms be automatically detected?
		/// const bool &iD : Should external depedencies be automatically
		///					 imported into the shader code?
		ShaderSourceProperties(const bool &dC, const bool &dS, const bool &dU,
				const bool &iD);
	private:
		bool deleteComments; // Remove comments from the source?
		bool detectStructs; // Should structures be automatically detected?
		bool detectUniforms; // Should uniforms be automatically detected?
		bool includeDependencies; // Import external dependencies?
	};

	class ShaderSource {
	public:
		/// If the Shader Source has not been previously imported (or if it's
		/// import had been deleted), this will (re)import the Shader Source
		/// and return a pointer to it. The Shader Source pointer should not
		/// be deleted after it is used as it may be needed in the future, and
		/// that will result in a reimport of it. The Shader Source will be 
		/// imported with the default properties of the ShaderSourceProperties.
		/// If the file has been previously imported, a pointer to the existing
		/// instance will be returned instead. 
		/// const string &file : The file which is to be imported.
		static ShaderSource* getShaderSource(const std::string &file);

		/// If the Shader Source has not been previously imported (or if it's
		/// import had been deleted), this will (re)import the Shader Source
		/// and return a pointer to it. The Shader Source pointer should not
		/// be deleted after it is used as it may be needed in the future, and
		/// that will result in a reimport of it. The Shader Source will be 
		/// imported with the specified properties.If the file has been 
		/// previously imported, a pointer to the existing instance will be 
		/// returned instead. Do note that the file may have been imported with
		/// different properties.
		/// const string &file : The file which is to be imported.
		/// const ShaderSourceProperties &prop : The properties with which to
		///										 import the file. These are
		///										 ignored if the file has been
		///										 already imported.
		static ShaderSource* getShaderSource(const std::string &file, const 
				ShaderSourceProperties &prop);

		/// Gets the file directory from which this Shader Source was imported
		/// from.
		/// return : The directory to the file.
		const std::string& getFile() const;

		/// Gets the full source code of this Shader Source file.
		/// return : The full, processed source code of this file.
		const std::string& getSource() const;
	private:
		// Map of the file name of the shader source to the processed Shader
		// Source instance. This allows for fast fetching of already processed
		// Shader Source.
		static std::unordered_map<std::string, ShaderSource*> shaderSources;

		std::string file; // File which this Shader Source represents
		std::string source; // The source code of this Shader Source File

		// Map to the full variable names of variables detected in some named
		// struct; a list of all of the uniforms detected.
		std::unordered_map<std::string, std::vector<std::string>> detStructs;
		std::vector<std::string> detUniforms;

		/// Initializes a new instance of the Shader Source class for the
		/// specified source code file. The Shader Source from the specified
		/// file will be imported and be processed with specified properties.
		/// Afterwards, the instance will be added to the Shader Sources Map.
		/// const string &file : The file from which the source is being
		///						 imported.
		/// const ShaderSourceProperties &prop : The properties with which to
		///										 import the source code.
		ShaderSource(const std::string &file, const ShaderSourceProperties 
				&prop);
	};
}

#endif