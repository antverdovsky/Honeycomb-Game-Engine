#pragma once
#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "BaseLight.h"

#include "..\..\math\Vector3f.h"

namespace Honeycomb::Component::Light {
	class PointLight : public BaseLight {
	public:
		/// Initializes a new Point Light with a default base and a default
		/// Attenuation, and 10.0F for the range.
		PointLight();

		/// Initializes a new Point Light with the specified base, range, and 
		/// attenuation.
		/// const BaseLight &bL : The base light of this Point Light.
		/// const Attenuation &atten : The attenuation of this Point Light.
		/// const float &ran : The range of the Point Light.
		PointLight(const BaseLight &bL, const BaseLight::Attenuation &atten,
				const float &ran);

		/// Initializes a new Point Light with the specified name, intensity,
		/// color, attenuation variables, and range.
		/// const string &nam : The name of this light.
		/// const float &inten : The intensity of this light.
		/// const Vector4f &col : The color of this light.
		/// const float &atC : The attenuation constant of this light.
		/// const float &atL : The attenuation linear of this light.
		/// const float &atQ : The attenuation quadratic of this light.
		/// const float &ran : The range of this light.
		PointLight(const std::string &nam, const float &inten, const
				Honeycomb::Math::Vector4f &col, const float &atC,
				const float &atL, const float &atQ, const float &ran);

		/// Destroys this Point Light.
		~PointLight();

		/// Clones this Point Light into a new, dynamically allocated, Point 
		/// Light. This function should be used instead of the copy constructor
		/// to prevent object slicing.
		/// return : The cloned Point Light.
		PointLight* clone() const;

		/// Gets the Position of this Point Light.
		/// return : A vector representing the position.
		const Honeycomb::Math::Vector3f& getPosition() const;

		/// Gets the reference to the Attenuation of this Point Light.
		/// return : The attenuation reference.
		const BaseLight::Attenuation& getAttenuation() const;
		
		/// Gets the sphere-like radius range of this Point Light.
		/// return : The range value.
		const float& getRange() const;

		/// Sets the attenuation of this Point Light.
		/// const Attenuation &atten : The new attenuation of this Point Light.
		void setAttenuation(const BaseLight::Attenuation &atten);

		/// Sets the range of this Point Light.
		/// const float &ran : The new range of the Point Light.
		void setRange(const float &ran);

		/// Starts this Point Light.
		void start();

		/// Writes the parameters of this point light into the specified 
		/// shader.
		/// ShaderProgram &shader : Reference to the shader to which the light
		///							is to be written to.
		/// const string &uni : Name of the light uniform in the shader.
		void toShader(Honeycomb::Shader::ShaderProgram &shader,
			const std::string &uni);
	private:
		const Honeycomb::Math::Vector3f *position; // Transform Position

		BaseLight::Attenuation attenuation; // The attenuation of the Light
		float range; // The sphere-like radius range of the Point Light
	};
}

#endif