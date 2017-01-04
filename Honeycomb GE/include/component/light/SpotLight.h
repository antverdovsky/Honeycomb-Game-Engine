#pragma once
#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "BaseLight.h"

#include "..\..\math\Vector3f.h"

namespace Honeycomb::Component::Light {
	class SpotLight : public BaseLight {
	public:
		// Variables defining the color and intensity of the light.
		const static std::string ATTENUATION_CONSTANT_F;
		const static std::string ATTENUATION_LINEAR_F;
		const static std::string ATTENUATION_QUADRATIC_F;
		const static std::string COLOR_VEC4;
		const static std::string INTENSITY_F;
		const static std::string POSITION_VEC3;
		const static std::string DIRECTION_VEC3;
		const static std::string RANGE_F;
		const static std::string ANGLE_F;

		/// Initializes a new Spot Light with a white { 1.0F, 1.0F, 1.0F, 
		/// 1.0F } color, 1.0F intensity, 1.0F constant attenuation, 0.22
		/// linear attenuation, 0.20 quadratic attenuation, 10.0F range and
		/// PI / 4.0F angle. The position and direction will be set to the 
		/// default Vector3 values, until the Spot Light is started and the 
		/// Transform translation takes over.
		SpotLight();

		/// Initializes a new Spot Light with the specified name, intensity,
		/// color, attenuation variables, range and angle. The position and 
		/// direction will be set to the default Vector3 values, until the Spot
		/// Light is started and the Transform translation takes over.
		/// const float &inten : The intensity of this light.
		/// const Vector4f &col : The color of this light.
		/// const float &atC : The attenuation constant of this light.
		/// const float &atL : The attenuation linear of this light.
		/// const float &atQ : The attenuation quadratic of this light.
		/// const float &ran : The range of this light.
		/// const float &ang : The angle of this light.
		SpotLight(const float &inten, const Honeycomb::Math::Vector4f &col,
			const float &atC, const float &atL, const float &atQ, const
			float &ran, const float &ang);

		/// Clones this Spot Light into a new, dynamically allocated, Spot 
		/// Light. This function should be used instead of the copy constructor
		/// to prevent object slicing.
		/// return : The cloned Spot Light.
		SpotLight* clone() const;

		/// Starts this Spot Light.
		void start();

		/// Updates this Spot Light.
		void update();
	private:
		// The struct definition for the Spot Light.
		const static std::string structFile;
		const static std::string structName;

		const Honeycomb::Math::Vector3f *position; // Transform Position
		const Honeycomb::Math::Vector3f *direction; // Transform Direction
	};
}

#endif