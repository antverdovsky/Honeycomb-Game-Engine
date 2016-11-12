#pragma once
#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H

#include "..\ShaderProgram.h"
#include "..\..\light\AmbientLight.h"
#include "..\..\light\BaseLight.h"
#include "..\..\light\DirectionalLight.h"

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

		/// Sets the ambient light uniform of the name provided to the ambient
		/// light specified.
		/// string name : The name of the ambient light uniform.
		/// AmbientLight aL : The ambient light.
		void setUniform_AmbientLight(std::string name,
			Honeycomb::Light::AmbientLight aL);

		/// Sets the base light uniform of the name provided to the base light
		/// specified.
		/// string name : The name of the base light uniform.
		/// BaseLight bL : The base light.
		void setUniform_BaseLight(std::string name, 
			Honeycomb::Light::BaseLight bL);

		/// Sets the directional light uniform of the name provided to the
		/// directional light specified. The base component of the directional
		/// light will also be set.
		/// string name : The name of the direction light uniform.
		/// DirectionalLight dL : The directional light.
		void setUniform_DirectionalLight(std::string name, 
			Honeycomb::Light::DirectionalLight dL);
	private:
		static PhongShader *instance; // Singleton instance of the Shader

		/// TODO: Move some where
		Honeycomb::Light::DirectionalLight dirLight;
		Honeycomb::Light::AmbientLight ambLight;

		/// Initializes an instance of the Simple Shader singleton.
		PhongShader();
	};
}

#endif