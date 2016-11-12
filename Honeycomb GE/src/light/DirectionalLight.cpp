#include "..\..\include\light\DirectionalLight.h"

using Honeycomb::Math::Vector3f;

namespace Honeycomb::Light {
	DirectionalLight::DirectionalLight() : 
		DirectionalLight(BaseLight(), -Vector3f::getGlobalUp()){

	}

	DirectionalLight::DirectionalLight(BaseLight bL, Vector3f dir) {
		this->base = bL;
		this->direction = dir.normalized();
	}

	DirectionalLight::~DirectionalLight() {

	}

	BaseLight DirectionalLight::getBase() {
		return this->base;
	}

	Vector3f& DirectionalLight::getDirection() {
		return this->direction;
	}
}