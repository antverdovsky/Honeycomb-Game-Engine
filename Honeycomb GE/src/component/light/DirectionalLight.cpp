#include "..\..\..\include\component\light\DirectionalLight.h"

#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\shader\phong\PhongShader.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::Phong::PhongShader;

namespace Honeycomb::Component::Light {
	DirectionalLight::DirectionalLight() 
			: DirectionalLight(BaseLight("directionalLight")){

	}

	DirectionalLight::DirectionalLight(const BaseLight &bL) 
			: BaseLight(bL) {

	}

	DirectionalLight::DirectionalLight(const std::string &nam, const float
			&inten, const Vector4f &col) : BaseLight(nam, inten, col) {

	}

	DirectionalLight::~DirectionalLight() {
		int j = 32;
	}

	DirectionalLight* DirectionalLight::clone() const {
		return new DirectionalLight(this->name, this->intensity, this->color);
	}

	const Vector3f& DirectionalLight::getDirection() const {
		return *this->direction;
	}

	void DirectionalLight::start() {
		if (this->isActive) return;
		this->isActive = true;

		// Get the direction from the Transform so that it may be sent to the
		// Phong Shader.
		this->direction = &this->getAttached()->
			getComponentOfType<Transform>("Transform")->getLocalForward();
	}
}