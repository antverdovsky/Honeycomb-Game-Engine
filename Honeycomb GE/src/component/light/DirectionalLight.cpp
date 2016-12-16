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
			: DirectionalLight(BaseLight("DirectionalLight")){

	}

	DirectionalLight::DirectionalLight(const BaseLight &bL) 
			: BaseLight(bL) {

	}

	DirectionalLight::DirectionalLight(const std::string &nam, const float
			&inten, const Vector4f &col) : BaseLight(nam, inten, col) {

	}

	DirectionalLight::~DirectionalLight() {

	}

	DirectionalLight* DirectionalLight::clone() const {
		return new DirectionalLight(this->name, this->intensity, this->color);
	}

	const Vector3f& DirectionalLight::getDirection() const {
		return *this->direction;
	}

	void DirectionalLight::start() {
		// Add the Directional Light to the Phong Shader
		PhongShader::getPhongShader()->addUniform_DirectionalLight(*this);

		// Subscribe to the Transform change event, so that the direction of
		// the light may be written to the shader each time the transform
		// changes.
//		this->transformChange.addAction(
//			std::bind(&DirectionalLight::writeToShader, this));
//		this->getAttached()->getComponentOfType<Transform>("Transform")->
//			getChangedEvent().addEventHandler(this->transformChange);

		// Get the direction from the Transform so that it may be sent to the
		// Phong Shader.
		this->direction = &this->getAttached()->
			getComponentOfType<Transform>("Transform")->getLocalForward();
	}
}