#include "..\..\..\include\component\light\DirectionalLight.h"

#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\shader\phong\PhongShader.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::Phong::PhongShader;

namespace Honeycomb::Component::Light {
	DirectionalLight::DirectionalLight() : 
		DirectionalLight(BaseLight()){

	}

	DirectionalLight::DirectionalLight(BaseLight bL) 
			: BaseLight(bL) {

	}

	DirectionalLight::~DirectionalLight() {

	}

	DirectionalLight* DirectionalLight::clone() {
		return new DirectionalLight(*this);
	}

	Vector3f DirectionalLight::getDirection() {
		return *this->direction;
	}

	void DirectionalLight::start() {
		PhongShader::getPhongShader()->addUniform_DirectionalLight(*this);

		this->transformChange.addAction(
			std::bind(&DirectionalLight::writeToShader, this));
		this->getAttached()->getComponentOfType<Transform>("Transform")->
			getChangedEvent().addEventHandler(&this->transformChange);

		this->direction = &this->getAttached()->
			getComponentOfType<Transform>("Transform")->getLocalForward();

		writeToShader();
	}

	void DirectionalLight::writeToShader() {
		PhongShader::getPhongShader()->setUniform_DirectionalLight(this->name,
			*this);
	}
}