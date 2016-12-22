#pragma once
#ifndef AMBIENT_LIGHT_H
#define AMBIENT_LIGHT_H

#include "BaseLight.h"

namespace Honeycomb::Component::Light {
	class AmbientLight : public BaseLight {
	public:
		/// Creates a new ambient light with a default base.
		AmbientLight();

		/// Creates a new ambient light with the specified base light.
		/// BaseLight bL : The base light to be used for this light.
		AmbientLight(BaseLight bL);

		/// Creates a new Ambient Light with the given name, intensity and
		/// color.
		/// const string &nam : The name of this light.
		/// const float &inten : The intensity of this light.
		/// const Vector4f &col : The color of this light.
		AmbientLight(const std::string &nam, const float &inten, const
			Honeycomb::Math::Vector4f &col);

		/// Default Destructor.
		~AmbientLight();

		/// Clones this Ambient Light into a new, dynamically allocated,
		/// Ambient Light. This function should be used instead of the copy 
		/// constructor to prevent object slicing.
		/// return : The cloned Ambient Light.
		AmbientLight* clone() const;

		/// Writes the parameters of this ambient light into its preferred
		/// shader.
		void toShader();
	};
}

#endif