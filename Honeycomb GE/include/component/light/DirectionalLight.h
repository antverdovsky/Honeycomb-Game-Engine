#pragma once
#ifndef DIRECTIONAL_LIGHT
#define DIRECTIONAL_LIGHT

#include "BaseLight.h"
#include "..\..\math\Vector3f.h"

namespace Honeycomb::Component::Light {
	class DirectionalLight : public BaseLight {
	public:
		/// Creates a new Directional light with a default base.
		DirectionalLight();

		/// Creates a new Directional light with the given base.
		/// const BaseLight &bL : The base light to be used for this light.
		DirectionalLight(const BaseLight &bL);

		/// Creates a new Directional light with the given name, intensity and
		/// color.
		/// const string &nam : The name of this light.
		/// const float &inten : The intensity of this light.
		/// const Vector4f &col : The color of this light.
		DirectionalLight(const std::string &nam, const float &inten, const
			Honeycomb::Math::Vector4f &col);

		/// Destroys this Directional Light.
		~DirectionalLight();

		/// Clones this Directional Light into a new, dynamically allocated,
		/// Directional Light. This function should be used instead of the copy 
		/// constructor to prevent object slicing.
		/// return : The cloned Directional Light.
		DirectionalLight* clone() const;

		/// Gets the direction of this directional light. The reference which
		/// is returned is equivalent to the Transform's local forward vector.
		/// return : The direction.
		const Honeycomb::Math::Vector3f& getDirection() const;

		/// Starts this Directional Light.
		void start();

		/// Writes the parameters of this directional light into its preferred
		/// shader.
		void toShader();
	private:
		const Honeycomb::Math::Vector3f *direction; // Transform Direction
	};
}

#endif