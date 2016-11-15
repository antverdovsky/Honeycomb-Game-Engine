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
	private:

	};
}

#endif