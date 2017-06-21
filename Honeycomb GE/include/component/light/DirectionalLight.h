#pragma once
#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include "BaseLight.h"
#include "../GameComponent.h"
#include "../physics/Transform.h"
#include "../../conjuncture/EventHandler.h"

namespace Honeycomb { namespace Component { namespace Light {
	class DirectionalLight : public BaseLight {
	public:
		// Variables defining the color and intensity of the light.
		const static std::string COLOR_VEC3;
		const static std::string INTENSITY_F;
		const static std::string DIRECTION_VEC3;

		/// Creates a new directional light with a white { 1.0F, 1.0F, 1.0F }
		/// color, and an intensity of 1.0F. The direction will be set
		/// to the default Vector3 until the Directional Light is started and
		/// the Transform direction takes over.
		DirectionalLight();

		/// Creates a new Directional Light with the given intensity and color.
		/// The direction will be set to the default Vector3 until the 
		/// Directional Light is started and the Transform direction takes 
		/// over.
		/// const float &inten : The intensity of this light.
		/// const Vector3f &col : The color of this light.
		/// const ShadowType &shdw : The shadow type.
		DirectionalLight(const float &inten, const Honeycomb::Math::Vector3f 
				&col, const ShadowType &shdw);

		/// Clones this Directional Light into a new, dynamically allocated,
		/// Directional Light. This function should be used instead of the copy 
		/// constructor to prevent object slicing.
		/// return : The cloned Directional Light.
		std::unique_ptr<DirectionalLight> clone() const;

		/// <summary>
		/// Returns the Component ID integer representation of the Directional
		/// Light.
		/// </summary>
		/// <returns>
		/// The Component ID of the Directional Light Component.
		/// </returns>
		virtual GameComponentID getGameComponentID() const noexcept override;

		/// Returns the direction of this Directional Light.
		/// return : The constant reference to the direction vector.
		const Honeycomb::Math::Vector3f& getDirection() const;

		/// Returns the shadow data of this Directional Light.
		/// return : The reference to the shadow.
		Shadow& getShadow();

		/// Returns the shadow data of this Directional Light.
		/// return : The constant reference to the shadow.
		const Shadow& getShadow() const;

		/// Starts this Directional Light.
		void onAttach() override;

		void onDetach() override;

		/// Writes the light and shadow values of this Directional Light to the
		/// specified Shader.
		/// ShaderProgram &shader : The shader to which to write the values of
		///							this light.
		///	const string &uni : The uniform name of this Light in the Shader.
		void toShader(Honeycomb::Shader::ShaderProgram &shader,
			const std::string &uni) const;
	private:
		// The struct definition for the Directional Light.
		const static std::string structFile;
		const static std::string structName;

		Honeycomb::Conjuncture::EventHandler
			transformChangeHandler; // Handles the transform change event

		Shadow shadow;
		Honeycomb::Component::Physics::Transform *transform;

		/// Calculates the light projection for the shadow map.
		Honeycomb::Math::Matrix4f calculateLightProjection();

		/// Event which is called when the transform of the Directional Light
		/// changes. Writes the direction data to the Generic Struct and 
		/// recalculates and writes the shadow matrix.
		void onTransformChange();

		virtual DirectionalLight* cloneInternal() const override;
	};
} } }

#endif
