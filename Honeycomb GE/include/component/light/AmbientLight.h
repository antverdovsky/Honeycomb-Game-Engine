#pragma once
#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "BaseLight.h"
#include "../GameComponent.h"

namespace Honeycomb::Component::Light {
	class AmbientLight : public BaseLight {
	public:
		// Variables defining the color and intensity of the light.
		const static std::string COLOR_VEC3;
		const static std::string INTENSITY_F;

		/// Creates a new ambient light with a white { 1.0F, 1.0F, 1.0F }
		/// color, and an intensity of 1.0F.
		AmbientLight();

		/// Creates a new Ambient Light with the given intensity and color.
		/// const float &inten : The intensity of this light.
		/// const Vector3f &col : The color of this light.
		AmbientLight(const float &inten, const Honeycomb::Math::Vector3f &col);

		/// Clones this Ambient Light into a new, dynamically allocated,
		/// Ambient Light. This function should be used instead of the copy 
		/// constructor to prevent object slicing.
		/// return : The cloned Ambient Light.
		AmbientLight* clone() const;

		/// Starts this Ambient Light.
		void start();
	private:
		// The struct definition for the Ambient Light.
		const static std::string structFile;
		const static std::string structName;
	};
}

#endif