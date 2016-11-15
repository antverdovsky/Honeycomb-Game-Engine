#include "..\..\..\include\component\light\AmbientLight.h"

namespace Honeycomb::Component::Light {
	AmbientLight::AmbientLight() : AmbientLight(BaseLight()) {

	}

	AmbientLight::AmbientLight(BaseLight bL) : BaseLight(bL) {

	}

	AmbientLight::~AmbientLight() {

	}
}