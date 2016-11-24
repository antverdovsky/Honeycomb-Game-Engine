#pragma once
#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "BaseLight.h"

#include "..\..\conjuncture\EventHandler.h"
#include "..\..\math\Vector3f.h"

namespace Honeycomb::Component::Light {
	class PointLight : public BaseLight {
	public:
		/// Initializes a new Point Light with a default base, 10.0F for the
		/// range, 1.0F for the attenuation constant, 0.22F for the attenuation
		/// linear and 0.20F for the attentuation quadratic.
		PointLight();

		/// Initializes a new Point Light with the specified base, range, and 
		/// attenuation variables.
		/// BaseLight bL : The base light of this Point Light.
		/// float ran : The range of the Point Light.
		/// float c : The Attenuation constant factor.
		/// float l : The Attenuation linear factor.
		/// float q : The Attenuation quadratic factor.
		PointLight(BaseLight bL, float ran, float c, float l, float q);

		/// Destroys this Point Light.
		~PointLight();

		/// Clones this Point Light into a new, dynamically allocated, Point 
		/// Light. This function should be used instead of the copy constructor
		/// to prevent object slicing.
		/// return : The cloned Point Light.
		PointLight* clone();

		/// Gets the Position of this Point Light.
		/// return : A vector representing the position.
		Honeycomb::Math::Vector3f getPosition();

		/// Gets the reference to the Attenuation of this Point Light.
		/// return : The attenuation reference.
		BaseLight::Attenuation& getAttenuation();
		
		/// Gets the sphere-like radius range of this Point Light.
		/// return : The range value.
		float getRange();

		/// Sets the attenuation of this Point Light.
		/// Attenuation atten : The new attenuation of this Point Light.
		void setAttenuation(BaseLight::Attenuation atten);

		/// Sets the range of this Point Light.
		/// float ran : The new range of the Point Light.
		void setRange(float ran);

		/// Starts this Point Light.
		void start();

		/// Writes this Point Light to the Phong Shader.
		void writeToShader();
	private:
		Honeycomb::Math::Vector3f *position; // The position (from Transform)

		BaseLight::Attenuation attenuation; // The attenuation of the Light
		float range; // The sphere-like radius range of the Point Light

		// Event handlers for the change in the transform & attenuation
		Honeycomb::Conjuncture::EventHandler transformChange;
		Honeycomb::Conjuncture::EventHandler attenuationChange;
	};
}

#endif