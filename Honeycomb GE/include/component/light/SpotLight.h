#pragma once
#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "BaseLight.h"

#include "..\..\math\Vector3f.h"

namespace Honeycomb::Component::Light {
	class SpotLight : public BaseLight {
	public:
		// Variables defining the color and intensity of the light.
		const static std::string COLOR_VEC3;
		const static std::string INTENSITY_F;
		const static std::string POSITION_VEC3;
		const static std::string DIRECTION_VEC3;
		const static std::string RANGE_F;
		const static std::string ANGLE_F;

		/// Initializes a new Spot Light with a white { 1.0F, 1.0F, 1.0F }
		/// color, 1.0F intensity, default attenuation, 10.0F range and
		/// PI / 4.0F angle. The position and direction will be set to the 
		/// default Vector3 values, until the Spot Light is started and the 
		/// Transform translation takes over.
		SpotLight();

		/// Initializes a new Spot Light with the specified name, intensity,
		/// color, attenuation variables, range and angle. The position and 
		/// direction will be set to the default Vector3 values, until the Spot
		/// Light is started and the Transform translation takes over.
		/// const float &inten : The intensity of this light.
		/// const Vector3f &col : The color of this light.
		/// const Attenuation &atten : The attenuation of this Light.
		/// const float &ran : The range of this light.
		/// const float &ang : The angle of this light.
		SpotLight(const float &inten, const Honeycomb::Math::Vector3f &col,
			const Honeycomb::Component::Light::Attenuation &atten, 
			const float &ran, const float &ang);

		/// Clones this Spot Light into a new, dynamically allocated, Spot 
		/// Light. This function should be used instead of the copy constructor
		/// to prevent object slicing.
		/// return : The cloned Spot Light.
		SpotLight* clone() const;

		/// Returns the angle of this Spot Light.
		/// return : The reference to the angle.
		float& getAngle();

		/// Returns the angle of this Spot Light.
		/// return : The constant reference to the angle.
		const float& getAngle() const;

		/// Returns the attenuation of this Point Light.
		/// return : The reference to the Attenuation.
		Honeycomb::Component::Light::Attenuation& getAttenuation();

		/// Returns the attenuation of this Point Light.
		/// return : The constant reference to the Attenuation.
		const Honeycomb::Component::Light::Attenuation& getAttenuation() const;

		/// Returns the direction of this Spot Light.
		/// return : The constant reference to the Direction.
		const Honeycomb::Math::Vector3f& getDirection() const;

		/// Returns the position of this Spot Light.
		/// return : The constant reference to the Position.
		const Honeycomb::Math::Vector3f& getPosition() const;

		/// Returns the range of this Point Light.
		/// return : The reference to the range.
		float& getRange();

		/// Returns the range of this Point Light.
		/// return : The constant reference to the range.
		const float& getRange() const;

		/// Writes the light and attenuation values of this Spot Light to the
		/// specified Shader.
		/// ShaderProgram &shader : The shader to which to write the values of
		///							this light.
		///	const string &uni : The uniform name of this Light in the Shader.
		void toShader(Honeycomb::Shader::ShaderProgram &shader, 
				const std::string &uni) const;

		/// Sets the attenuation of this Point Light.
		/// const Attenuation &atten : The new attenuation of this Point Light.
		void setAttenuation(const Honeycomb::Component::Light::Attenuation&
			atten);

		/// Starts this Spot Light.
		void start();

		/// Updates this Spot Light.
		void update();
	private:
		// The struct definition for the Spot Light.
		const static std::string structFile;
		const static std::string structName;

		Honeycomb::Component::Light::Attenuation attenuation; // Attenuation

		const Honeycomb::Math::Vector3f *position; // Transform Position
		const Honeycomb::Math::Vector3f *direction; // Transform Direction
	};
}

#endif