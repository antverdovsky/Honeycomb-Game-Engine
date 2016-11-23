#pragma once
#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "BaseLight.h"

#include "..\..\math\Vector3f.h"
#include "..\..\conjuncture\EventHandler.h"

namespace Honeycomb::Component::Light {
	class SpotLight : public BaseLight {
	public:
		/// Initializes a Point Light with the default base, 1.0F for the
		/// attenuation constant, 0.22F for the attenuation linear, 0.20F for
		/// the attenuation quadratic, 10.0F for the range, and 45.0F degrees 
		/// for the spot angle.
		SpotLight();

		/// Initializes a new Point Light with the specified base, range, spot
		/// angle and attenuation variables.
		/// BaseLight bL : The base light of this Spot Light.
		/// float ran : The range of the Spot Light.
		/// float ang : The angle of the Spot Light in radians.
		/// float c : The Attenuation constant factor.
		/// float l : The Attenuation linear factor.
		/// float q : The Attenuation quadratic factor.
		SpotLight(BaseLight bL, float ran, float ang, float c, float l, 
			float q);

		/// Destroys this Spot Light.
		~SpotLight();

		/// Clones this Point Light into a new, dynamically allocated, Spot 
		/// Light. This function should be used instead of the copy constructor
		/// to prevent object slicing.
		/// return : The cloned Spot Light.
		SpotLight* clone();

		/// Gets the spot angle of the Spot Light.
		/// return : The spot angle value.
		float getAngle();

		/// Gets the constant term in the attenuation equation.
		/// return : The value of the constant term.
		float getAttenuationConstant();

		/// Gets the linear term in the attenuation equation.
		/// return : The value of the linear term.
		float getAttenuationLinear();

		/// Gets the quadratic term in the attenuation equation.
		/// return : The value of the quadratic term.
		float getAttenuationQuadratic();

		/// Gets the Direction of this Spot Light.
		/// return : A vector representing the direction.
		Honeycomb::Math::Vector3f getDirection();

		/// Gets the Position of this Spot Light.
		/// return : A vector representing the position.
		Honeycomb::Math::Vector3f getPosition();

		/// Gets the range of this Spot Light.
		/// return : The range of this Spot Light.
		float getRange();

		/// Sets the spot angle of the Spot Light.
		/// return : The value of the spot angle.
		void setAngle(float ang);

		/// Sets the constant term in the attenuation equation.
		/// float c : The new value of the constant term.
		void setAttenuationConstant(float c);

		/// Sets the linear term in the attenuation equation.
		/// float l : The new value of the linear term.
		void setAttenuationLinear(float l);

		/// Sets the quadratic term in the attenuation equation.
		/// float q : The new value of the quadratic term.
		void setAttenuationQuadratic(float q);

		/// Sets the range of this Spot Light.
		/// float ran : The new range of the Spot Light.
		void setRange(float ran);

		/// Starts this Spot Light.
		void start();

		/// Writes this Spot Light to the Phong Shader.
		void writeToShader();
	private:
		Honeycomb::Math::Vector3f *position; // The position (from Transform)
		Honeycomb::Math::Vector3f *direction; // The direction (from Transform)

		/// Variables for the Attenuation calculation
		float attenConstant;
		float attenLinear;
		float attenQuadratic;

		float angle; // The spot angle of the Spot Light (entire light).
		float range; // The range of the Spot Light

		// Event handler for the change in the transform
		Honeycomb::Conjuncture::EventHandler transformChange;
	};
}

#endif