#pragma once
#ifndef SIMPLE_SHADER_H
#define SIMPLE_SHADER_H

#include "..\ShaderProgram.h"

namespace Honeycomb::Shader::Default {
	// File locations of the vertex and fragment shaders.
	extern std::string VERTEX_SHADER_LOC;
	extern std::string FRAGMENT_SHADER_LOC;

	class SimpleShader : public Honeycomb::Shader::ShaderProgram {
	public:
		/// Deletes the simple shader.
		~SimpleShader();

		/// Returns the singleton instance of the Shader.
		/// return : A pointer to the singleton instance.
		static SimpleShader* getSimpleShader();
	private:
		static SimpleShader *instance; // Singleton instance of the Shader

		/// Initializes an instance of the Simple Shader singleton.
		SimpleShader();
	};
}

#endif