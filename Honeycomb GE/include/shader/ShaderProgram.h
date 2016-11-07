#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <vector>
#include <unordered_map>

#include "..\math\Vector3f.h"
#include "..\math\Matrix4f.h"

namespace Honeycomb::Shader {
	class ShaderProgram {
	public:
		/// Initializes the Shader instance.
		ShaderProgram();

		/// Destroys the Shader from the GPU memory.
		~ShaderProgram();

		/// Links the Shader from the specified file to this Shader instance.
		/// string file : The file path from which to read in the shader code.
		/// int type : The type of shader to be added (GL_FRAGMENT_SHADER,
		///			   GL_GEOMETRY_SHADER, GL_VERTEX_SHADER).
		void addShader(std::string file, int type);

		/// Adds the specified shader uniform (GLSL variable) to this shader 
		/// program.
		/// std::string uni : The uniform variable to be added.
		void addUniform(std::string uni);

		/// Binds the shader program so that it may be used.
		void bindShaderProgram();

		/// After all of the shaders have been added and compiled, this links 
		/// the program and validates that everything was done correctly.
		void finalizeShaderProgram();

		/// Returns the pointer to the current active and bounded shader. If no
		/// shader is bounded, a nullptr will be returned instead.
		static ShaderProgram* getActiveShader();

		/// Gets the uniform location of the specified uniform variable.
		/// std::string uni : The name of the uniform variable.
		/// return : The pointer to the location.
		int getUniformLocation(std::string uni);

		/// Sets the specified uniform variable to the specified value.
		/// std::string uni : The name of the uniform variable to be set.
		/// float val : The new float value of the uniform.
		void setUniform_f(std::string uni, float val);

		/// Sets the specified uniform variable to the specified value.
		/// std::string uni : The name of the uniform variable to be set.
		/// int val : The new integer value of the uniform.
		void setUniform_i(std::string uni, int val);

		/// Sets the specified uniform variable to the specified value.
		/// std::string uni : The name of the uniform variable to be set.
		/// Vector3f val : The new Vector3f value of the uniform.
		void setUniform_vec3(std::string uni, Honeycomb::Math::Vector3f val);
		
		/// Sets the specified uniform variable to the specified value.
		/// std::string uni : The name of the uniform variable to be set.
		/// Matrix4f val : The new Matrix4f value of the uniform.
		void setUniform_mat4(std::string uni, Honeycomb::Math::Matrix4f val);

		/// Unbinds the shader program so that it may not be used anymore.
		void unbindShaderProgram();
	private:
		static ShaderProgram *active; // The current bounded shader, if any

		int programID; // "Pointer" ID to this shader program in the driver
		std::vector<int> shaders; // "Pointer" IDs to the individual shaders
		std::unordered_map<std::string, int> uniforms; // Hash Map of uniforms
	};
}

#endif