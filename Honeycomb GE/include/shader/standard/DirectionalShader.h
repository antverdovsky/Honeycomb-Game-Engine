#pragma once
#ifndef DIRECTIONAL_LIGHT_SHADER_H
#define DIRECTIONAL_LIGHT_SHADER_H

#include "..\ShaderProgram.h"
#include "..\..\math\Matrix4f.h"
#include "..\..\component\light\BaseLight.h"
#include "..\..\component\light\DirectionalLight.h"

namespace Honeycomb::Shader::Standard {
	class DirectionalShader : public ShaderProgram {
	public:
		/// Returns the singleton instance of this Directional Light Shader
		/// class.
		/// return : The pointer to the singleton instance.
		static DirectionalShader* getDirectionalShader();

		/// Sets the projection matrix of the Directional Light Shader to the 
		/// specified matrix.
		/// const Matrix4f &proj : The projection matrix.
		void setProjection(const Honeycomb::Math::Matrix4f &proj);

		/// Sets the transformation matrix of the Directional Light Shader to 
		/// the specified matrix.
		/// const Matrix4f &trans : The transformation matrix.
		void setTransformation(const Honeycomb::Math::Matrix4f &trans);

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
	private:
		static DirectionalShader *directionalShader; // Singleton instance

		// Locations of the vertex & fragment shader files.
		const static std::string FRAG_FILE_LOC;
		const static std::string VERT_FILE_LOC;

		/// Initializes a new instance of the Directional Light Shader.
		DirectionalShader();

		/// Deletes this instance of the Directional Light Shader.
		~DirectionalShader();
	};
}

#endif