#pragma once
#ifndef PHONG_POINT_SHADER
#define PHONG_POINT_SHADER

#include <string.h>

#include "..\ShaderProgram.h"
#include "..\..\component\light\AmbientLight.h"

namespace Honeycomb::Shader::Phong {
	class PhongPointShader : public ShaderProgram {
	public:
		/// Returns the singleton instance of the Phong Point Light Shader.
		/// return : The pointer to the singleton instance.
		static PhongPointShader* getPhongPointShader();
	private:
		static PhongPointShader* phongPointShader; // Singleton

		// Vertex and Fragment File Locations of the Shader
		const static std::string VERT_FILE_LOC;
		const static std::string FRAG_FILE_LOC;

		/// Initializes a new instance of the Phong Point Light Shader.
		PhongPointShader();

		/// Deletes this instance of the Phong Point Light Shader.
		~PhongPointShader();
	};
}

#endif