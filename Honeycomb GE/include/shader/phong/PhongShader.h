#pragma once
#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H

#include "..\ShaderProgram.h"
#include "..\..\component\light\AmbientLight.h"
#include "..\..\component\light\BaseLight.h"
#include "..\..\component\light\DirectionalLight.h"
#include "..\..\component\light\PointLight.h"
#include "..\..\component\light\SpotLight.h"
#include "..\..\graphics\Material.h"

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

		/// Adds the specified ambient light as a uniform for this shader
		/// (provided that the Phong Shader file contains a uniform with the
		/// same name as the specified ambient light).
		/// AmbientLight aL : The ambient light to be added.
		void addUniform_AmbientLight(
			Honeycomb::Component::Light::AmbientLight aL);

		/// Adds the attenuation variables for the specified base light as
		/// uniforms for this shader.
		/// BaseLight bL : The light for which the attenuation is to be added.
		void addUniform_Attenuation(Honeycomb::Component::Light::BaseLight bL);

		/// Adds the specified base light as a uniform for this shader
		/// (provided that the Phong Shader file contains a uniform with the
		/// same name as the specified base light).
		/// BaseLight bL : The base light to be added.
		void addUniform_BaseLight(Honeycomb::Component::Light::BaseLight bL);

		/// Adds the specified directional light as a uniform for this shader
		/// (provided that the Phong Shader file contains a uniform with the
		/// same name as the specified directional light).
		/// DirectionalLight dL : The directional light to be added.
		void addUniform_DirectionalLight(
			Honeycomb::Component::Light::DirectionalLight dL);

		/// Adds the specified Material as a uniform for this shader
		/// (provided that the Phong Shader file contains a uniform with the
		/// same name as the specified material).
		/// Material mat : The material to be added.
		void addUniform_Material(Honeycomb::Graphics::Material mat);

		/// Adds the specified Point Light as a uniform for this shader.
		/// (provided that the Phong Shader file contains a uniform with the
		/// same name as the specified point light).
		/// PointLight pL : The Point Light to be added.
		void addUniform_PointLight(Honeycomb::Component::Light::PointLight pL);

		/// Adds the specified Spot Light as a uniform for this shader.
		/// (provided that the Phong Shader file contains a uniform with the
		/// same name as the specified point light).
		/// SpotLight pL : The Spot Light to be added.
		void addUniform_SpotLight(Honeycomb::Component::Light::SpotLight sL);

		/// Sets the ambient light uniform of the name provided to the ambient
		/// light specified.
		/// string name : The name of the ambient light uniform.
		/// AmbientLight aL : The ambient light.
		void setUniform_AmbientLight(std::string name,
			Honeycomb::Component::Light::AmbientLight aL);

		/// Sets the attenuation uniforms for the light of the specified name.
		/// std::string name : The name of the light for which the attenuation
		///					   is to be set.
		/// Attenuation atten : The attenuation of the light.
		void setUniform_Attenuation(std::string name,
			Honeycomb::Component::Light::BaseLight::Attenuation atten);

		/// Sets the base light uniform of the name provided to the base light
		/// specified.
		/// string name : The name of the base light uniform.
		/// BaseLight bL : The base light.
		void setUniform_BaseLight(std::string name, 
			Honeycomb::Component::Light::BaseLight bL);

		/// Sets the directional light uniform of the name provided to the
		/// directional light specified. The base component of the directional
		/// light will also be set.
		/// string name : The name of the direction light uniform.
		/// DirectionalLight dL : The directional light.
		void setUniform_DirectionalLight(std::string name, 
			Honeycomb::Component::Light::DirectionalLight dL);

		/// Sets the material uniform of the name provided to the material 
		/// specified.
		/// string name : The name of the material uniform.
		/// Material mat : The material.
		void setUniform_Material(std::string name, 
			Honeycomb::Graphics::Material mat);

		/// Sets the point light uniform of the name provided to the point
		/// light specified.
		/// string name : The name of the Point Light uniform.
		/// PointLight pL :  The Point Light.
		void setUniform_PointLight(std::string name, 
			Honeycomb::Component::Light::PointLight pL);

		/// Sets the spot light uniform of the name provided to the spot light
		/// specified.
		/// string name : The name of the Spot Light uniform.
		/// SpotLight sL : The Spot Light.
		void setUniform_SpotLight(std::string name, 
			Honeycomb::Component::Light::SpotLight sL);
	private:
		static PhongShader *instance; // Singleton instance of the Shader

		/// Initializes an instance of the Simple Shader singleton.
		PhongShader();
	};
}

#endif