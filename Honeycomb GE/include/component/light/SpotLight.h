#pragma once
#ifndef SPOT_LIGHT_H
#define SPOT_LIGHT_H

#include "BaseLight.h"
#include "../GameComponent.h"
#include "../physics/Transform.h"
#include "../../conjuncture/EventHandler.h"
#include "../../math/Vector3f.h"

namespace Honeycomb { namespace Component { namespace Light {
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
			const Attenuation &atten, const float &ran, const float &ang);

		/// Clones this Spot Light into a new, dynamically allocated, Spot 
		/// Light. This function should be used instead of the copy constructor
		/// to prevent object slicing.
		/// return : The cloned Spot Light.
		std::unique_ptr<SpotLight> clone() const;

		/// Returns the angle of this Spot Light.
		/// return : The reference to the angle.
		float& getAngle();

		/// Returns the angle of this Spot Light.
		/// return : The constant reference to the angle.
		const float& getAngle() const;

		/// Returns the attenuation of this Spot Light.
		/// return : The reference to the Attenuation.
		Attenuation& getAttenuation();

		/// Returns the attenuation of this Spot Light.
		/// return : The constant reference to the Attenuation.
		const Attenuation& getAttenuation() const;

		/// <summary>
		/// Returns the Component ID integer representation of the Spot Light.
		/// </summary>
		/// <returns>
		/// The Component ID of the Spot Light Component.
		/// </returns>
		virtual GameComponentID getGameComponentID() const noexcept override;

		/// Returns the direction of this Spot Light.
		/// return : The constant reference to the Direction.
		const Honeycomb::Math::Vector3f& getDirection() const;

		/// Returns the position of this Spot Light.
		/// return : The constant reference to the Position.
		const Honeycomb::Math::Vector3f& getPosition() const;

		/// Returns the range of this Spot Light.
		/// return : The reference to the range.
		float& getRange();

		/// Returns the range of this Spot Light.
		/// return : The constant reference to the range.
		const float& getRange() const;

		/// Returns the shadow data of this Spot Light.
		/// return : The reference to the shadow.
		Shadow& getShadow();

		/// Returns the shadow data of this Spot Light.
		/// return : The constant reference to the shadow.
		const Shadow& getShadow() const;

		/// Sets the attenuation of this Spot Light.
		/// const Attenuation &atten : The new attenuation of this Spot Light.
		void setAttenuation(const Attenuation &atten);

		/// Starts this Spot Light.
		void onAttach() override;

		void onDetach() override;

		/// Writes the light and attenuation values of this Spot Light to the
		/// specified Shader.
		/// ShaderProgram &shader : The shader to which to write the values of
		///							this light.
		///	const string &uni : The uniform name of this Light in the Shader.
		void toShader(Honeycomb::Shader::ShaderProgram &shader,
				const std::string &uni) const;
	private:
		// The struct definition for the Spot Light.
		const static std::string structFile;
		const static std::string structName;

		Honeycomb::Conjuncture::EventHandler
			transformChangeHandler; // Handles the transform change event

		Honeycomb::Component::Physics::Transform *transform;
		Attenuation attenuation;
		Shadow shadow;

		/// Calculates the light projection for the shadow map.
		Honeycomb::Math::Matrix4f calculateLightProjection();

		/// Event which is called when the transform of the Spot Light
		/// changes. Writes the direction and position data to the Generic 
		/// Struct and recalculates and writes the shadow matrix.
		void onTransformChange();

		virtual SpotLight* cloneInternal() const override;
	};
} } }

#endif
