#pragma once
#ifndef PHONG_SPOT_SHADER
#define PHONG_SPOT_SHADER

#include <string.h>

#include "..\ShaderProgram.h"
#include "..\..\component\light\AmbientLight.h"

namespace Honeycomb::Shader::Phong {
	class PhongSpotShader : public ShaderProgram {
	public:
		/// Returns the singleton instance of the Phong Spot Light Shader.
		/// return : The pointer to the singleton instance.
		static PhongSpotShader* getPhongSpotShader();
	private:
		static PhongSpotShader* phongSpotShader; // Singleton

		// Vertex and Fragment File Locations of the Shader
		const static std::string VERT_FILE_LOC;
		const static std::string FRAG_FILE_LOC;

		/// Initializes a new instance of the Phong Spot Light Shader.
		PhongSpotShader();

		/// Deletes this instance of the Phong Spot Light Shader.
		~PhongSpotShader();
	};
}

#endif