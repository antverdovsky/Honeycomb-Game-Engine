#pragma once
#ifndef PHONG_DIRECTIONAL_SHADER
#define PHONG_DIRECTIONAL_SHADER

#include <string.h>

#include "..\ShaderProgram.h"
#include "..\..\component\light\AmbientLight.h"

namespace Honeycomb::Shader::Phong {
	class PhongDirectionalShader : public ShaderProgram {
	public:
		/// Returns the singleton instance of the Phong Directional Light 
		///	Shader.
		/// return : The pointer to the singleton instance.
		static PhongDirectionalShader* getPhongDirectionalShader();
	private:
		static PhongDirectionalShader* phongDirectionalShader; // Singleton

		// Vertex and Fragment File Locations of the Shader
		const static std::string VERT_FILE_LOC;
		const static std::string FRAG_FILE_LOC;

		/// Initializes a new instance of the Phong Directional Light Shader.
		PhongDirectionalShader();

		/// Deletes this instance of the Phong Directional Light Shader.
		~PhongDirectionalShader();
	};
}

#endif