#pragma once
#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "BaseLight.h"

#include "..\..\math\Vector3f.h"

namespace Honeycomb::Component::Light {
	class PointLight : public BaseLight {
	public:
		// Variables defining the color and intensity of the light.
		const static std::string ATTENUATION_CONSTANT_F;
		const static std::string ATTENUATION_LINEAR_F;
		const static std::string ATTENUATION_QUADRATIC_F;
		const static std::string COLOR_VEC4;
		const static std::string INTENSITY_F;
		const static std::string POSITION_VEC3;
		const static std::string RANGE_F;

		/// Initializes a new Point Light with a white { 1.0F, 1.0F, 1.0F, 
		/// 1.0F } color, 1.0F intensity, 1.0F constant attenuation, 0.22
		/// linear attenuation, 0.20 quadratic attenuation, and 10.0F range.
		/// The position will be set to the default Vector3 until the Point 
		/// Light is started and the Transform translation takes over.
		PointLight();

		/// Initializes a new Point Light with the specified name, intensity,
		/// color, attenuation variables, and range. The position will be set 
		/// to the default Vector3 until the Point Light is started and the 
		/// Transform translation takes over.
		/// const float &inten : The intensity of this light.
		/// const Vector4f &col : The color of this light.
		/// const float &atC : The attenuation constant of this light.
		/// const float &atL : The attenuation linear of this light.
		/// const float &atQ : The attenuation quadratic of this light.
		/// const float &ran : The range of this light.
		PointLight(const float &inten, const Honeycomb::Math::Vector4f &col, 
				const float &atC, const float &atL, const float &atQ, const 
				float &ran);

		/// Clones this Point Light into a new, dynamically allocated, Point 
		/// Light. This function should be used instead of the copy constructor
		/// to prevent object slicing.
		/// return : The cloned Point Light.
		PointLight* clone() const;

		/// Starts this Point Light.
		void start();

		/// Updates this Point Light.
		void update();
	private:
		// The struct definition for the Point Light.
		const static Honeycomb::Shader::ShaderSource* shaderSource;
		const static std::string structName;

		const Honeycomb::Math::Vector3f *position; // Transform Position
	};
}

#endif