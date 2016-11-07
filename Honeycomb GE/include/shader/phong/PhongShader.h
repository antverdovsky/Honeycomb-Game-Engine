#pragma once
#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H

#include "..\ShaderProgram.h"

namespace Honeycomb::Shader::Phong {
	// File locations of the vertex and fragment shaders.
	extern std::string VERTEX_SHADER_LOC;
	extern std::string FRAGMENT_SHADER_LOC;

	class PhongShader : public Honeycomb::Shader::ShaderProgram {
	public:
		/// Deletes the simple shader.
		~PhongShader();

		/// Returns the singleton instance of the Shader.
		/// return : A pointer to the singleton instance.
		static PhongShader* getPhongShader();
	private:
		static PhongShader *instance; // Singleton instance of the Shader

		/// Initializes an instance of the Simple Shader singleton.
		PhongShader();
	};
}

#endif