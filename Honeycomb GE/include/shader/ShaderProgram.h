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
	class ShaderProgram : Honeycomb::File::LineOperation {
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

		/// Processes the specified line of shader source code. This method
		/// will call the importDependencies method to replace the given line
		/// with the imported source code.
		/// const string &file : The file which contains the import dependency.
		/// string &line : The line with the import dependency.
		void lineOperation(const std::string &file, std::string &line);

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

		std::string name; // The name of this Shader

		int programID; // "Pointer" ID to this shader program in the driver
		std::vector<int> shaders; // "Pointer" IDs to the individual shaders
		std::unordered_map<std::string, int> uniforms; // Hash Map of uniforms

		/// Imports a dependent file found in the specified line. The line
		/// must be written in the format of INCLUDE_DIRECTIVE <FILE>, in order
		/// for the import to occur. If the import is successful, the line will
		/// be replaced with the imported source code. If the import is not
		/// succesful, the line will not be modified.
		/// const string &file : The file which contains the import dependency.
		/// string &line : The line with the import dependency.
		void importDependency(const std::string &file, std::string &line);
	};
}

#endif