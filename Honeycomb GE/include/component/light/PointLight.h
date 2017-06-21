#pragma once
#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H

#include "BaseLight.h"

#include "../../math/Vector3f.h"

namespace Honeycomb { namespace Component { namespace Light {
	class PointLight : public BaseLight {
	public:
		// Variables defining the color and intensity of the light.
		const static std::string COLOR_VEC3;
		const static std::string INTENSITY_F;
		const static std::string POSITION_VEC3;
		const static std::string RANGE_F;

		/// Initializes a new Point Light with a white { 1.0F, 1.0F, 1.0F }
		/// color, 1.0F intensity, default attenuation, and 10.0F range.
		/// The position will be set to the default Vector3 until the Point 
		/// Light is started and the Transform translation takes over.
		PointLight();

		/// Initializes a new Point Light with the specified name, intensity,
		/// color, attenuation variables, and range. The position will be set 
		/// to the default Vector3 until the Point Light is started and the 
		/// Transform translation takes over.
		/// const float &inten : The intensity of this light.
		/// const Vector3f &col : The color of this light.
		/// const Attenuation &atten : The attenuation of this light.
		/// const float &ran : The range of this light.
		PointLight(const float &inten, const Honeycomb::Math::Vector3f &col, 
				const Honeycomb::Component::Light::Attenuation &atten, const 
				float &ran);

		/// Clones this Point Light into a new, dynamically allocated, Point 
		/// Light. This function should be used instead of the copy constructor
		/// to prevent object slicing.
		/// return : The cloned Point Light.
		std::unique_ptr<PointLight> clone() const;

		/// Returns the attenuation of this Point Light.
		/// return : The reference to the Attenuation.
		Honeycomb::Component::Light::Attenuation& getAttenuation();

		/// Returns the attenuation of this Point Light.
		/// return : The constant reference to the Attenuation.
		const Honeycomb::Component::Light::Attenuation& getAttenuation() const;

		/// <summary>
		/// Returns the Component ID integer representation of the Point Light.
		/// </summary>
		/// <returns>
		/// The Component ID of the Point Light Component.
		/// </returns>
		virtual GameComponentID getGameComponentID() const noexcept override;

		/// Returns the position of this Point Light.
		/// return : The constant reference to the Position.
		const Honeycomb::Math::Vector3f& getPosition() const;

		/// Returns the range of this Point Light.
		/// return : The reference to the range.
		float& getRange();

		/// Returns the range of this Point Light.
		/// return : The constant reference to the range.
		const float& getRange() const;

		/// Sets the attenuation of this Point Light.
		/// const Attenuation &atten : The new attenuation of this Point Light.
		void setAttenuation(const Honeycomb::Component::Light::Attenuation& 
				atten);

		/// Sets the range of this Point Light.
		/// const float &range : The new range of this Point Light.
		void setRange(const float &range);

		/// Starts this Point Light.
		void onAttach() override;

		void onDetach() override;

		/// Writes the light and attenuation values of this Point Light to the
		/// specified Shader.
		/// ShaderProgram &shader : The shader to which to write the values of
		///							this light.
		///	const string &uni : The uniform name of this Light in the Shader.
		void toShader(Honeycomb::Shader::ShaderProgram &shader,
				const std::string &uni) const;

		/// Updates this Point Light.
		void onUpdate() override;
	private:
		// The struct definition for the Point Light.
		const static std::string structFile;
		const static std::string structName;

		Honeycomb::Component::Light::Attenuation attenuation;

		const Honeycomb::Math::Vector3f *position; // Transform Position

		virtual PointLight* cloneInternal() const override;
	};
} } }

#endif
