#pragma once
#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include "BaseLight.h"
#include "..\math\Vector3f.h"

namespace Honeycomb::Light {
	struct DirectionalLight {
	public:
		/// Creates a new Directional light with a default base and a direction
		/// of global down.
		DirectionalLight();

		/// Creates a new Directional light with the given base and direction.
		/// BaseLight bL : The base light to be used for this light.
		/// Vector3f dir : The direction to be used for this light.
		DirectionalLight(BaseLight bL, Honeycomb::Math::Vector3f dir);

		/// Default Destructor.
		~DirectionalLight();

		/// Gets the base light component of this directional light.
		/// return : The base light component.
		BaseLight getBase();

		/// Gets the direction of this directional light.
		/// return : The direction.
		Honeycomb::Math::Vector3f& getDirection();
	private:
		BaseLight base; // The base light
		Honeycomb::Math::Vector3f direction; // Direction of the light
	};
}

#endif