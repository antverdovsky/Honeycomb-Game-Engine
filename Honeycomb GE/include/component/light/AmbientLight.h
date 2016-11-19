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

		/// Default Destructor.
		~AmbientLight();

		/// Clones this Ambient Light into a new, dynamically allocated,
		/// Ambient Light. This function should be used instead of the copy 
		/// constructor to prevent object slicing.
		/// return : The cloned Ambient Light.
		AmbientLight* clone();
	private:

	};
}

#endif