#include "..\..\..\include\component\light\PointLight.h"

#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\shader\phong\PhongShader.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::Phong::PhongShader;

namespace Honeycomb::Component::Light {
	PointLight::PointLight() 
			: PointLight(BaseLight(), 5.0F, 1.0F, 0.22F, 0.20F) {

	}

	PointLight::PointLight(BaseLight bL, float ran, float c, float l, float q) 
			: BaseLight(bL) {
		this->range = ran;

		this->attenConstant = c;
		this->attenLinear = l;
		this->attenQuadratic = q;
	}

	PointLight::~PointLight() {

	}

	PointLight* PointLight::clone() {
		return new PointLight(*this);
	}

	float PointLight::getAttenuationConstant() {
		return this->attenConstant;
	}

	float PointLight::getAttenuationLinear() {
		return this->attenLinear;
	}

	float PointLight::getAttenuationQuadratic() {
		return this->attenQuadratic;
	}

	Vector3f PointLight::getPosition() {
		return *this->position;
	}

	float PointLight::getRange() {
		return this->range;
	}

	void PointLight::setAttenuationConstant(float c) {
		this->attenConstant = c;

		this->writeToShader();
	}

	void PointLight::setAttenuationLinear(float l) {
		this->attenLinear = l;
	
		this->writeToShader();
	}

	void PointLight::setAttenuationQuadratic(float q) {
		this->attenQuadratic = q;

		this->writeToShader();
	}

	void PointLight::setRange(float ran) {
		this->range = ran;

		this->writeToShader();
	}

	void PointLight::start() {
		// Add the Point Light to the Phong Shader
		PhongShader::getPhongShader()->addUniform_PointLight(*this);

		// Subscribe to the Transform change event, so that the position of
		// the light may be written to the shader each time the transform
		// changes.
		this->transformChange.addAction(
			std::bind(&PointLight::writeToShader, this));
		this->getAttached()->getComponentOfType<Transform>("Transform")->
			getChangedEvent().addEventHandler(&this->transformChange);

		// Get the position from the Transform so that it may be sent to the
		// Phong Shader.
		this->position = &this->getAttached()->
			getComponentOfType<Transform>("Transform")->getTranslation();

		writeToShader(); // Write the default Transform direction to Shader
	}

	void PointLight::writeToShader() {
		PhongShader::getPhongShader()->setUniform_PointLight(this->name,
			*this);
	}
}