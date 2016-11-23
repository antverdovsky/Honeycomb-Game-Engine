#pragma once
#include "BaseLight.h"

#include "..\..\conjuncture\EventHandler.h"
#include "..\..\math\Vector3f.h"

namespace Honeycomb::Component::Light {
	class PointLight : public BaseLight {
	public:
		/// Initializes a new Point Light with a default base, 1.0F for the
		/// attenuation constant, 0.22F for the attenuation linear and 0.20F
		/// for the attentuation quadratic.
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

		/// Gets the constant term in the attenuation equation.
		/// return : The value of the constant term.
		float getAttenuationConstant();

		/// Gets the linear term in the attenuation equation.
		/// return : The value of the linear term.
		float getAttenuationLinear();

		/// Gets the quadratic term in the attenuation equation.
		/// return : The value of the quadratic term.
		float getAttenuationQuadratic();
		
		/// Gets the Position of this Point Light.
		/// return : A vector representing the position.
		Honeycomb::Math::Vector3f getPosition();

		/// Gets the sphere-like radius range of this Point Light.
		/// return : The range value.
		float getRange();
		
		/// Sets the constant term in the attenuation equation.
		/// float c : The new value of the constant term.
		void setAttenuationConstant(float c);

		/// Sets the linear term in the attenuation equation.
		/// float l : The new value of the linear term.
		void setAttenuationLinear(float l);

		/// Sets the quadratic term in the attenuation equation.
		/// float q : The new value of the quadratic term.
		void setAttenuationQuadratic(float q);

		/// Sets the range of this Point Light.
		/// float ran : The new range of the Point Light.
		void setRange(float ran);

		/// Starts this Point Light.
		void start();

		/// Writes this Point Light to the Phong Shader.
		void writeToShader();
	private:
		Honeycomb::Math::Vector3f *position; // The position (from Transform)

		/// Variables for the Attenuation calculation
		float attenConstant;
		float attenLinear;
		float attenQuadratic;

		float range; // The sphere-like radius range of the Point Light

		// Event handler for the change in the transform (for position)
		Honeycomb::Conjuncture::EventHandler transformChange;
	};
}