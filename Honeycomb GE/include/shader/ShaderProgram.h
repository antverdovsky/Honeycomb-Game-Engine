#pragma once
#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <vector>
#include <unordered_map>

#include "ShaderSource.h"
#include "../base/GLItem.h"
#include "../file/FileIO.h"
#include "../file/LineOperation.h"
#include "../math/Vector3f.h"
#include "../math/Vector4f.h"
#include "../math/Matrix4f.h"

namespace Honeycomb { namespace Shader {
	enum ShaderType {
		FRAGMENT_SHADER				= 0x8B30,	// from GL_FRAGMENT_SHADER
		GEOMETRY_SHADER				= 0x8DD9,	// from GL_GEOMETRY_SHADER
		VERTEX_SHADER				= 0x8B31,	// from GL_VERTEX_SHADER
	};

	class ShaderProgram : public Honeycomb::Base::GLItem {
	public:
		/// Instantiates this Shader instance with the specified name, or the
		/// name "ShaderProgram" is the argument is not passed in.
		/// const string &name : The name of the Shader Program.
		ShaderProgram(const std::string &name = "ShaderProgram");

		/// Links the Shader from the specified file to this Shader instance.
		/// const string &file : The file path from which to read in the shader
		///						 code.
		/// const ShaderType &type : The type of shader to be added.
		void addShader(const std::string &file, const ShaderType &type);

		/// Adds the specified shader uniform (GLSL variable) to this shader 
		/// program.
		/// const string &uni : The uniform variable to be added.
		void addUniform(const std::string &uni);

		/// Binds the shader program so that it may be used.
		void bindShaderProgram();

		/// Destroys this Shader Program instance by destroying the program
		/// from the GPU.
		void destroy();

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

		/// Initializes this Shader Program by creating the program on the GPU.
		void initialize();

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
		/// const Vector2f &val : The new Vector2f value of the uniform.
		void setUniform_vec2(const std::string &uni,
				const Honeycomb::Math::Vector2f &val);

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
		std::string name; // The name of this Shader
		std::vector<ShaderSource*> sources; // Source Files of this Shader

		int programID; // "Pointer" ID to this shader program in the driver
		std::vector<int> shaders; // "Pointer" IDs to the individual shaders
		
		// HashMap of the Uniform's name to the Uniform's ID in OpenGL
		std::unordered_map<std::string, int> uniforms;
	};
} }

#endif
