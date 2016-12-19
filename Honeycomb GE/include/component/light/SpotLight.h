#pragma once
#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "BaseLight.h"

#include "..\..\math\Vector3f.h"
#include "..\..\conjuncture\EventHandler.h"

namespace Honeycomb::Component::Light {
	class SpotLight : public BaseLight {
	public:
		/// Initializes a Point Light with the default base, and a default
		/// Attenuation, 10.0F for the Range, and PI / 6 radians (30.0 degrees)
		/// for the spot angle.
		SpotLight();

		/// Initializes a new Point Light with the specified base, range, spot
		/// angle and attenuation variables.
		/// const BaseLight &bL : The base light of this Spot Light.
		/// const Attenuation &atten : The attenuation of this Spot Light.
		/// const float &ran : The range of this Spot Light.
		/// const float &ang : The angle of this Spot Light, in radians.
		SpotLight(const BaseLight &bL, const BaseLight::Attenuation &atten,
				const float &ran, const float &ang);

		/// Destroys this Spot Light.
		~SpotLight();

		/// Clones this Point Light into a new, dynamically allocated, Spot 
		/// Light. This function should be used instead of the copy constructor
		/// to prevent object slicing.
		/// return : The cloned Spot Light.
		SpotLight* clone() const;

		/// Gets the spot angle of the Spot Light.
		/// return : The spot angle value.
		const float& getAngle() const;

		/// Gets the reference to the Attenuation of this Spot Light.
		/// return : The attenuation reference.
		const BaseLight::Attenuation& getAttenuation() const;

		/// Gets the Direction of this Spot Light.
		/// return : A vector representing the direction.
		const Honeycomb::Math::Vector3f& getDirection() const;

		/// Gets the Position of this Spot Light.
		/// return : A vector representing the position.
		const Honeycomb::Math::Vector3f& getPosition() const;

		/// Gets the range of this Spot Light.
		/// return : The range of this Spot Light.
		const float& getRange() const;

		/// Sets the spot angle of the Spot Light.
		/// const float &ang : The new angle of this Spot Light.
		void setAngle(const float &ang);

		/// Sets the attenuation of this Spot Light.
		/// const Attenuation &atten : The new attenuation of this Spot Light.
		void setAttenuation(const BaseLight::Attenuation &atten);

		/// Sets the range of this Spot Light.
		/// const float &ran : The new range of the Spot Light.
		void setRange(const float &ran);

		/// Starts this Spot Light.
		void start();
	private:
		const Honeycomb::Math::Vector3f *position; // Transform Position
		const Honeycomb::Math::Vector3f *direction; // Transform Direction

		BaseLight::Attenuation attenuation; // The attenuation of the Light
		float angle; // The spot angle of the Spot Light (entire light).
		float range; // The range of the Spot Light

		// Event handlers for the change in the transform and attenuation
		Honeycomb::Conjuncture::EventHandler transformChange;
		Honeycomb::Conjuncture::EventHandler attenuationChange;
	};
}

#endif