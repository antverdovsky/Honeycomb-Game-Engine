#pragma once
#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include "BaseLight.h"
#include "..\GameComponent.h"

namespace Honeycomb::Component::Light {
	class DirectionalLight : public BaseLight {
	public:
		// Variables defining the color and intensity of the light.
		const static std::string COLOR_VEC4;
		const static std::string INTENSITY_F;
		const static std::string DIRECTION_VEC3;

		/// Creates a new directional light with a white { 1.0F, 1.0F, 1.0F, 
		/// 1.0F } color, and an intensity of 1.0F. The direction will be set
		/// to the default Vector3 until the Directional Light is started and
		/// the Transform direction takes over.
		DirectionalLight();

		/// Creates a new Directional Light with the given intensity and color.
		/// The direction will be set to the default Vector3 until the 
		/// Directional Light is started and the Transform direction takes 
		/// over.
		/// const float &inten : The intensity of this light.
		/// const Vector4f &col : The color of this light.
		DirectionalLight(const float &inten, const Honeycomb::Math::Vector4f 
				&col);

		/// Clones this Directional Light into a new, dynamically allocated,
		/// Directional Light. This function should be used instead of the copy 
		/// constructor to prevent object slicing.
		/// return : The cloned Directional Light.
		DirectionalLight* clone() const;

		/// Starts this Directional Light.
		void start();

		/// Updates this Directional Light.
		void update();
	private:
		// The struct definition for the Directional Light.
		const static Honeycomb::Shader::ShaderSource* shaderSource;
		const static std::string structName;

		const Honeycomb::Math::Vector3f *direction; // Transform Direction
	};
}

#endif