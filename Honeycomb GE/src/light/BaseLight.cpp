#include "..\..\include\light\BaseLight.h"

using Honeycomb::Math::Vector3f;

namespace Honeycomb::Light {
	BaseLight::BaseLight() : BaseLight(1.0F, Vector3f(1.0F, 1.0F, 1.0F)) {

	}

	BaseLight::BaseLight(float inten, Vector3f col) {
		this->intensity = inten;
		this->color = col;
	}

	BaseLight::~BaseLight() {

	}

	Vector3f& BaseLight::getColor() {
		return this->color;
	}

	float& BaseLight::getIntensity() {
		return this->intensity;
	}
}