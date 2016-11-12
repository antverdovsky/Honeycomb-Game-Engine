#pragma once
#ifndef BASE_LIGHT_H
#define BASE_LIGHT_H

#include "..\math\Vector3f.h"

namespace Honeycomb::Light {
	struct BaseLight {
	public:
		/// Initializes a new base light with an intensity of 1.0F and a white
		/// (1, 1, 1) color.
		BaseLight();

		/// Initializes a new base light with the given intensity and color.
		/// float inten : The intensity of the light [0, 1].
		/// Vector3f col : The color of the light ([0, 1], [0, 1], [0, 1]).
		BaseLight(float inten, Honeycomb::Math::Vector3f col);

		/// Default Destructor.
		~BaseLight();
		
		/// Gets the reference to the color of the base light.
		/// return : The reference to the color.
		Honeycomb::Math::Vector3f& getColor();

		/// Gets the reference to the intensity of this base light.
		/// return : The reference to the intensity.
		float& getIntensity();
	private:
		float intensity; // The intensity of the light
		Honeycomb::Math::Vector3f color; // The color of the light
	};
}

#endif