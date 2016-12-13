#pragma once
#ifndef PHONG_AMBIENT_SHADER
#define PHONG_AMBIENT_SHADER

#include <string.h>

#include "..\ShaderProgram.h"
#include "..\..\component\light\AmbientLight.h"

namespace Honeycomb::Shader::Phong {
	class PhongAmbientShader : public ShaderProgram {
	public:
		/// Returns the singleton instance of the Phong Ambient Light Shader.
		/// return : The pointer to the singleton instance.
		static PhongAmbientShader* getPhongAmbientShader();
	private:
		static PhongAmbientShader* phongAmbientShader; // Singleton Instance
		
		// Vertex and Fragment File Locations of the Shader
		const static std::string VERT_FILE_LOC;
		const static std::string FRAG_FILE_LOC;
		
		/// Initializes a new instance of the Phong Ambient Light Shader.
		PhongAmbientShader();

		/// Deletes this instance of the Phong Ambient Light Shader.
		~PhongAmbientShader();
	};
}

#endif