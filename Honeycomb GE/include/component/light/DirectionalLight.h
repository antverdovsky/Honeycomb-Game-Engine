#pragma once
#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include "BaseLight.h"
#include "..\..\conjuncture\EventHandler.h"
#include "..\..\math\Vector3f.h"

namespace Honeycomb::Component::Light {
	class DirectionalLight : public BaseLight {
	public:
		/// Creates a new Directional light with a default base.
		DirectionalLight();

		/// Creates a new Directional light with the given base.
		/// BaseLight bL : The base light to be used for this light.
		DirectionalLight(BaseLight bL);

		/// Default Destructor.
		~DirectionalLight();

		/// Clones this Directional Light into a new, dynamically allocated,
		/// Directional Light. This function should be used instead of the copy 
		/// constructor to prevent object slicing.
		/// return : The cloned Directional Light.
		DirectionalLight* clone();

		/// Gets the direction of this directional light.
		/// return : The direction.
		Honeycomb::Math::Vector3f getDirection();

		/// Starts this Directional Light.
		void start();

		/// Writes this Directional Light to the Phong Shader.
		void writeToShader();
	private:
		Honeycomb::Math::Vector3f *direction; // The direction (from Transform)

		// Event handler for the change in the transform (for direction)
		Honeycomb::Conjuncture::EventHandler transformChange;
	};
}

#endif