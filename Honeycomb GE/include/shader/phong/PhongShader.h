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

// [TODO: Make an interface for attenuation to make adding the attenuation
// or modifying it easier]

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
		/// const AmbientLight &aL : The ambient light to be added.
		void addUniform_AmbientLight(
				const Honeycomb::Component::Light::AmbientLight &aL);

		/// Adds the attenuation variables for the specified base light as
		/// uniforms for this shader.
		/// const BaseLight &bL : The light for which the attenuation is to be
		///						  added.
		void addUniform_Attenuation(
				const Honeycomb::Component::Light::BaseLight &bL);

		/// Adds the specified base light as a uniform for this shader
		/// (provided that the Phong Shader file contains a uniform with the
		/// same name as the specified base light).
		/// const BaseLight &bL : The base light to be added.
		void addUniform_BaseLight(
				const Honeycomb::Component::Light::BaseLight &bL);

		/// Adds the specified directional light as a uniform for this shader
		/// (provided that the Phong Shader file contains a uniform with the
		/// same name as the specified directional light).
		/// const DirectionalLight &dL : The directional light to be added.
		void addUniform_DirectionalLight(
				const Honeycomb::Component::Light::DirectionalLight &dL);

		/// Adds the specified Material as a uniform for this shader
		/// (provided that the Phong Shader file contains a uniform with the
		/// same name as the specified material).
		/// const Material &mat : The material to be added.
		void addUniform_Material(
				const Honeycomb::Graphics::Material &mat);

		/// Adds the specified Point Light as a uniform for this shader.
		/// (provided that the Phong Shader file contains a uniform with the
		/// same name as the specified point light).
		/// coonst PointLight &pL : The Point Light to be added.
		void addUniform_PointLight(
				const Honeycomb::Component::Light::PointLight &pL);

		/// Adds the specified Spot Light as a uniform for this shader.
		/// (provided that the Phong Shader file contains a uniform with the
		/// same name as the specified point light).
		/// const SpotLight &pL : The Spot Light to be added.
		void addUniform_SpotLight(
				const Honeycomb::Component::Light::SpotLight &sL);

		/// Sets the ambient light specified to its ambient light uniform in 
		/// the Phong Shader.
		/// const AmbientLight &aL : The ambient light.
		void setUniform_AmbientLight(
				const Honeycomb::Component::Light::AmbientLight &aL);

		/// Sets the attenuation light uniform in the Phong Shader for the
		/// specified base light.
		/// const BaseLight &bL : The base light.
		/// const Attenuation &atten : The attenuation of the base light.
		void setUniform_Attenuation(
				const Honeycomb::Component::Light::BaseLight &bL,
				const Honeycomb::Component::Light::BaseLight::Attenuation 
				&atten);

		/// Sets the base light specified to its base light uniform in 
		/// the Phong Shader.
		/// const BaseLight &bL : The base light.
		void setUniform_BaseLight( 
			const Honeycomb::Component::Light::BaseLight &bL);

		/// Sets the directional light specified to its directional light 
		/// uniform in the Phong Shader.
		/// const DirectionalLight &dL : The directional light.
		void setUniform_DirectionalLight(
			const Honeycomb::Component::Light::DirectionalLight &dL);

		/// Sets the material specified to its material uniform in the Phong 
		/// Shader.
		/// Material mat : The material.
		void setUniform_Material(const Honeycomb::Graphics::Material &mat);

		/// Sets the point light light specified to its point light uniform in 
		/// the Phong Shader.
		/// const PointLight &pL : The point light.
		void setUniform_PointLight(
			const Honeycomb::Component::Light::PointLight &pL);

		/// Sets the spot light specified to its spot light uniform in the 
		/// Phong Shader.
		/// const SpotLight &sL : The spot light.
		void setUniform_SpotLight(
			const Honeycomb::Component::Light::SpotLight &sL);
	private:
		static PhongShader *instance; // Singleton instance of the Shader

		/// Initializes an instance of the Simple Shader singleton.
		PhongShader();
	};
}

#endif