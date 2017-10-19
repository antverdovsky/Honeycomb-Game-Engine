#pragma once
#ifndef SHADER_SOURCE_H
#define SHADER_SOURCE_H

#include <iostream>
#include <memory>
#include <regex>
#include <string>
#include <unordered_map>

namespace Honeycomb { namespace Shader {
	/// <summary>
	/// Represents any variable in a GLSL Shader Structure.
	/// </summary>
	struct SourceVariable {
		std::string name; // The name of the variable
		std::string type; // The type of the variable

		/// <summary>
		/// Initializes a new struct variable with the specified name and type.
		/// </summary>
		/// <param name="name">
		/// The name of the variable.
		/// </param>
		/// <param name="type">
		/// The type of the variable.
		/// </param>
		SourceVariable(const std::string &name, const std::string &type);
	};

	/// <summary>
	/// Represents an exception which is thrown when a Shader cannot be loaded
	/// from the system directory.
	/// </summary>
	class ShaderLoadException : public std::runtime_error {
	public:
		/// <summary>
		/// Creates a new Model Load Exception for the shader which could not 
		/// be loaded from the specified path.
		/// </summary>
		/// <param name="path">
		/// The path from which the shader could not be loaded.
		/// </param>
		ShaderLoadException(const std::string &path);

		/// <summary>
		/// Returns a constant character string containing the description of
		/// the exception.
		/// </summary>
		/// <returns>
		/// The constant character string exception info containing the
		/// directory of the shader.
		/// </returns>
		virtual const char* what() const noexcept;
	private:
		std::string directory;
	};

	/// <summary>
	/// Represents the properties, using which, a GLSL Shader is to be parsed.
	/// </summary>
	class ShaderSourceProperties {
		friend class ShaderSource;
	public:
		/// <summary>
		/// Initializes a new Shader Source Properties instance with all of the
		/// properties being set to true.
		/// </summary>
		ShaderSourceProperties();

		/// <summary>
		/// Initializes a new Shader Source Properties instance with the
		/// specified properties.
		/// </summary>
		/// <param name="dC">
		/// Should comments be removed from the source? It is highly 
		/// recommended that this is true, so that the parser does not attempt
		/// to parse commented out/disabled code.
		/// </param>
		/// <param name="dS">
		/// Should structures be automatically detected? It is recommended that
		/// this is true so that the parser may detect and parse any user
		/// created structures.
		/// </param>
		/// <param name="dU">
		/// Should uniforms be automatically detected? It is recommended that
		/// this is true, so that the parser may detect and automatically bind
		/// to OpenGL any user created uniforms.
		/// </param>
		/// <param name="iD">
		/// Should external files be automatically included if the include
		/// preprocessor directive is encountered? It is recommended that this
		/// is true since GLSL does not support the include preprocessor
		/// directive by default. Note that importing with this setting may 
		/// throw a ShaderNotFound exception, if any of the include directives 
		/// attempt to include a non-existant file.
		/// </param>
		ShaderSourceProperties(const bool &dC, const bool &dS, const bool &dU,
				const bool &iD);

		/// <summary>
		/// Compares this set of properties to the specified set for equality.
		/// </summary>
		/// <param name="rhs">
		/// The other shader properties set.
		/// </param>
		/// <returns>
		/// True if this is equal to <paramref name="rhs"/>, false otherwise.
		/// </returns>
		bool operator==(const ShaderSourceProperties &rhs) const;

		/// <summary>
		/// Compares this set of properties to the specified set for 
		/// inequality.
		/// </summary>
		/// <param name="rhs">
		/// The other shader properties set.
		/// </param>
		/// <returns>
		/// True if this is not equal to <paramref name="rhs"/>, false 
		/// otherwise.
		/// </returns>
		bool operator!=(const ShaderSourceProperties &rhs) const;
	private:
		bool deleteComments;      // Remove comments from the source?
		bool detectStructs;       // Should structures be detected and parsed?
		bool detectUniforms;      // Should uniforms be detected?
		bool includeDependencies; // Import external dependencies?
	};

	class ShaderSource {
		friend class GenericStruct;
		friend class ShaderProgram;
	public:
		/// <summary>
		/// Imports the shader source from the specified file and processes it
		/// using the specified properties. If the shader has previously been
		/// imported with those properties, it is not re-imported again, and
		/// the previously processed instance is returned instead.
		/// 
		/// If the source could not be processed, or if any of its dependencies
		/// could not be processed, this throws a Shader Load exception.
		/// </summary>
		/// <param name="file">
		/// The system path to the shader file.
		/// </param>
		/// <param name="prop">
		/// The properties using which the shader source is to be imported and
		/// processed.
		/// </param>
		/// <exception cref="ShaderLoadException">
		/// Thrown if the shader or any of its dependencies could not be 
		/// loaded.
		/// </exception>
		static ShaderSource& getShaderSource(const std::string &file,
				const ShaderSourceProperties &prop = ShaderSourceProperties());

		/// <summary>
		/// Gets the system path to the shader file.
		/// </summary>
		/// <returns>
		/// The system path string.
		/// </returns>
		const std::string& getFile() const;

		/// <summary>
		/// Gets the properties used to process this shader file.
		/// </summary>
		/// <returns>
		/// The properties set.
		/// </returns>
		const ShaderSourceProperties& getProperties() const;

		/// <summary>
		/// Gets the source contents of the shader file, post processing.
		/// </summary>
		/// <returns>
		/// The source contents string.
		/// </returns>
		const std::string& getSource() const;

		/// <summary>
		/// Compares this set of shader source to the shader source for 
		/// equality.
		/// </summary>
		/// <param name="rhs">
		/// The other shader source.
		/// </param>
		/// <returns>
		/// True if this is equal to <paramref name="rhs"/>, false otherwise.
		/// </returns>
		bool operator==(const ShaderSource &rhs) const;

		/// <summary>
		/// Compares this set of shader source to the shader source for 
		/// inequality.
		/// </summary>
		/// <param name="rhs">
		/// The other shader source.
		/// </param>
		/// <returns>
		/// True if this is not equal to <paramref name="rhs"/>, false 
		/// otherwise.
		/// </returns>
		bool operator!=(const ShaderSource &rhs) const;
	private:
		/// <summary>
		/// Returns a vector of unique pointers to all of the thus far imported
		/// shader sources.
		/// </summary>
		/// <returns>
		/// All of the Shader Sources which have been imported.
		/// </returns>
		static std::vector<std::unique_ptr<ShaderSource>>& getShaderImports();

		std::string file;                  // System path and file name of this
		std::string source;                // Source code of this
		ShaderSourceProperties properties; // Properties used to process this

		// Map of the name of the struct to a list of the variable names in the
		// struct. If the type of the variable in the struct is actually 
		// another user defined struct, then for each variable in that struct,
		// the name of the variable preceded by a period will be added instead.
		std::unordered_map<std::string, std::vector<SourceVariable>> 
				detStructs;
		
		// List of all of the uniforms detected in the shader source code. For
		// uniforms with a user defined struct type, for each variable in that 
		// struct, the name of the variable preceded by a period will be added 
		// instead. 
		std::vector<SourceVariable> detUniforms;

		/// <summary>
		/// Initializes a new instance of the Shader Source class with the
		/// specified source code file. The source code from the specified file
		/// will be imported and processed with the given properties. 
		/// 
		/// If the source could not be processed, or if any of its dependencies
		/// could not be processed, this throws a Shader Load exception.
		/// </summary>
		/// <param name="file">
		/// The system path to the shader file.
		/// </param>
		/// <param name="prop">
		/// The properties using which the shader source is to be imported and
		/// processed.
		/// </param>
		/// <exception cref="ShaderLoadException">
		/// Thrown if the shader or any of its dependencies could not be 
		/// loaded.
		/// </exception>
		ShaderSource(const std::string &file,
				const ShaderSourceProperties &prop);

		/// <summary>
		/// Removes any C style comments from the current shader source.
		/// </summary>
		void deleteComments();

		/// <summary>
		/// Detects structs in the current shader source and adds them to the
		/// detected structs map.
		/// </summary>
		void detectStructs();

		/// <summary>
		/// Detects uniforms in the current shader source and adds them to the
		/// detected uniforms vector.
		/// </summary>
		void detectUniforms();

		/// <summary>
		/// Finds and replaces any include directives with the source code of
		/// the include file. Each dependency is imported with the same 
		/// properties as the file which is dependent on it.
		/// </summary>
		/// <exception cref="ShaderLoadException">
		/// Thrown if any include directive fails.
		/// </exception>
		void includeDependencies();
	};
} }

#endif
