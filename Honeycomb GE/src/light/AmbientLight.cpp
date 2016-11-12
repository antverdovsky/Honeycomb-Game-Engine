#include "..\..\include\light\AmbientLight.h"

namespace Honeycomb::Light {
	AmbientLight::AmbientLight() : AmbientLight(BaseLight()) {

	}

	AmbientLight::AmbientLight(BaseLight bL) {
		this->base = bL;
	}

	AmbientLight::~AmbientLight() {

	}

	BaseLight AmbientLight::getBase() {
		return this->base;
	}
}