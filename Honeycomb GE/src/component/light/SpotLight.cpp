#include "..\..\..\include\component\light\SpotLight.h"

#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\shader\phong\PhongShader.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::Phong::PhongShader;

namespace Honeycomb::Component::Light {
	SpotLight::SpotLight()
			: SpotLight(BaseLight(), 10.0F, 45.0F, 1.0F, 0.22F, 0.20F) {

	}

	SpotLight::SpotLight(BaseLight bL, float ran, float ang, float c, float l,
			float q) : BaseLight(bL) {
		this->range = ran;
		this->angle = ang;

		this->attenConstant = c;
		this->attenLinear = l;
		this->attenQuadratic = q;
	}

	SpotLight::~SpotLight() {

	}

	SpotLight* SpotLight::clone() {
		return new SpotLight(*this);
	}

	float SpotLight::getAngle() {
		return this->angle;
	}

	float SpotLight::getAttenuationConstant() {
		return this->attenConstant;
	}

	float SpotLight::getAttenuationLinear() {
		return this->attenLinear;
	}

	float SpotLight::getAttenuationQuadratic() {
		return this->attenQuadratic;
	}

	Vector3f SpotLight::getDirection() {
		return *this->direction;
	}

	Vector3f SpotLight::getPosition() {
		return *this->position;
	}

	float SpotLight::getRange() {
		return this->range;
	}

	void SpotLight::setAngle(float ang) {
		this->angle = ang;

		this->writeToShader();
	}

	void SpotLight::setAttenuationConstant(float c) {
		this->attenConstant = c;

		this->writeToShader();
	}

	void SpotLight::setAttenuationLinear(float l) {
		this->attenLinear = l;

		this->writeToShader();
	}

	void SpotLight::setAttenuationQuadratic(float q) {
		this->attenQuadratic = q;

		this->writeToShader();
	}

	void SpotLight::setRange(float ran) {
		this->range = ran;

		this->writeToShader();
	}

	void SpotLight::start() {
		// Add the Spot Light to the Phong Shader
		PhongShader::getPhongShader()->addUniform_SpotLight(*this);

		// Subscribe to the Transform change event, so that the position and 
		// direction of the light may be written to the shader each time the 
		// transform changes.
		this->transformChange.addAction(
			std::bind(&SpotLight::writeToShader, this));
		this->getAttached()->getComponentOfType<Transform>("Transform")->
			getChangedEvent().addEventHandler(&this->transformChange);

		// Get the position and direction from the Transform so that it may be 
		// sent to the Phong Shader.
		this->position = &this->getAttached()->
			getComponentOfType<Transform>("Transform")->getTranslation();
		this->direction = &this->getAttached()->
			getComponentOfType<Transform>("Transform")->getLocalForward();

		writeToShader(); // Write the default Transform direction to Shader
	}

	void SpotLight::writeToShader() {
		PhongShader::getPhongShader()->setUniform_SpotLight(this->name,
			*this);
	}
}