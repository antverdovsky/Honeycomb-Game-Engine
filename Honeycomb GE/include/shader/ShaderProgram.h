#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <vector>
#include <unordered_map>

#include "..\file\FileIO.h"
#include "..\file\LineOperation.h"
#include "..\math\Vector3f.h"
#include "..\math\Vector4f.h"
#include "..\math\Matrix4f.h"

namespace Honeycomb::Shader {
	class ShaderProgram {
	public:
		/// Initializes the Shader instance.
		ShaderProgram();

		/// Destroys the Shader from the GPU memory.
		~ShaderProgram();

		/// Links the Shader from the specified file to this Shader instance.
		/// const string &file : The file path from which to read in the shader
		///						 code.
		/// const int &type : The type of shader to be added 
		///					  (GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER, 
		///					  GL_VERTEX_SHADER).
		void addShader(const std::string &file, const int &type);

		/// Adds the specified shader uniform (GLSL variable) to this shader 
		/// program.
		/// const string &uni : The uniform variable to be added.
		void addUniform(const std::string &uni);

		/// Binds the shader program so that it may be used.
		void bindShaderProgram();

		/// After all of the shaders have been added and compiled, this links 
		/// the program and validates that everything was done correctly.
		void finalizeShaderProgram();

		/// Gets the uniform location of the specified uniform variable. If the
		/// uniform does not exist in this shader, a negative value will be
		/// returned instead.
		/// const string &uni : The name of the uniform variable.
		/// return : The uniform location in the shader; or a negative value if
		///			 the uniform does not exist.
		int getUniformLocation(const std::string &uni);

		/// Sets the specified uniform variable to the specified value. If the
		/// uniform does not exist, no changes will be made.
		/// const string &uni : The name of the uniform variable to be set.
		/// const float &val : The new float value of the uniform.
		void setUniform_f(const std::string &uni, const float &val);

		/// Sets the specified uniform variable to the specified value. If the
		/// uniform does not exist, no changes will be made.
		/// const string &uni : The name of the uniform variable to be set.
		/// const int &val : The new integer value of the uniform.
		void setUniform_i(const std::string &uni, const int &val);

		/// Sets the specified uniform variable to the specified value. If the
		/// uniform does not exist, no changes will be made.
		/// const string &uni : The name of the uniform variable to be set.
		/// const Vector3f &val : The new Vector3f value of the uniform.
		void setUniform_vec3(const std::string &uni, 
				const Honeycomb::Math::Vector3f &val);
		
		/// Sets the specified uniform variable to the specified value. If the
		/// uniform does not exist, no changes will be made.
		/// const string &uni : The name of the uniform variable to be set.
		/// const Vector4f &val : The new Vector4f value of the uniform.
		void setUniform_vec4(const std::string &uni, 
				const Honeycomb::Math::Vector4f &val);

		/// Sets the specified uniform variable to the specified value. If the
		/// uniform does not exist, no changes will be made.
		/// const string &uni : The name of the uniform variable to be set.
		/// const Matrix4f &val : The new Matrix4f value of the uniform.
		void setUniform_mat4(const std::string &uni, 
				const Honeycomb::Math::Matrix4f &val);

		/// Unbinds the shader program so that it may not be used anymore.
		void unbindShaderProgram();
	protected:
		// Command in a Shader Program for including other Shader Programs
		const static std::string INCLUDE_DIRECTIVE;

		// Command in a Shader Program for initializing a uniform
		const static std::string UNIFORM_DIRECTIVE;

		// Command in a Shader Program for defining a struct(ure)
		const static std::string STRUCT_DIRECTIVE;

		// Strings which indicate the beginning and end of a single line 
		// comment in a Shader Program.
		const static std::string SINGLE_LINE_COMMENT_BEGIN;
		const static std::string SINGLE_LINE_COMMENT_END;

		// Strings which indicate the beginning and end of a multi line comment
		// in a Shader Program.
		const static std::string MULTI_LINE_COMMENT_BEGIN;
		const static std::string MULTI_LINE_COMMENT_END;

		std::string name; // The name of this Shader

		int programID; // "Pointer" ID to this shader program in the driver
		std::vector<int> shaders; // "Pointer" IDs to the individual shaders
		std::unordered_map<std::string, int> uniforms; // Hash Map of uniforms

		std::vector<std::string> detectedUniforms; // Detected Uniforms List
		std::unordered_map<std::string, std::vector<std::string>> 
			detectedStructs; // Detected Struct's Name & their variables

		/// Removes C-style (//, /* */) comments from the specified source 
		/// code. It is strongly advised that this method be run before
		/// uniforms are detected or dependencies are imported as any comments
		/// containing uniform or include directives may be seen as actual
		/// directives!
		/// string &source : The source from which comments are to be removed
		///					 from.
		void deleteComments(std::string &source);

		/// Detects any structs defined in the specified source code and adds
		/// the name of the struct to the detected structs vector list as the
		/// key, and  adds the names of the variables of the struct to the 
		/// detected structs vector list as the value of the key.
		/// const string &source : The source code of the Shader.
		void detectStructs(const std::string &source);

		/// Detects any uniforms in the specified source code and adds them to
		/// the detected uniforms vector list.
		/// const string &source : The source code for which uniforms are to be
		///						   detected.
		void detectUniforms(const std::string &source);

		/// Finds any include directives in the specified source code and
		/// replaces the directive with the included source code.
		/// const string &file : The directory of the file for which the source
		///						 was passed in.
		/// string &source : The source code for which the dependencies are to
		///					 be included.
		void includeDependencies(const std::string &file, std::string &source);

		/// Processes the Shader source code imported from the specified file.
		/// Any include directives will be replaced with imported source code
		/// and any uniforms found will automatically be added to this Shader
		/// Program. The imported source code is dynamically allocated and
		/// should be removed after use.
		/// const string &file : The directory from which to import the source.
		std::string* processSource(const std::string &file);
	};
}

#endif