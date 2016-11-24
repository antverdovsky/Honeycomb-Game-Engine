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
			: BaseLight(bL), attenuation(c, l, q) {
		this->range = ran;
	}

	PointLight::~PointLight() {

	}

	PointLight* PointLight::clone() {
		// TODO, for all lights which use a transform pointer, the clone needs
		// to get a new pointer.
		return new PointLight(*this);
	}

	BaseLight::Attenuation& PointLight::getAttenuation() {
		return this->attenuation;
	}

	Vector3f PointLight::getPosition() {
		return *this->position;
	}

	float PointLight::getRange() {
		return this->range;
	}

	void PointLight::setAttenuation(BaseLight::Attenuation atten) {
		this->attenuation = atten;

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

		// Subscribe to the Attenuation change event, so that the attenuation
		// may be written to the shader each time it is changed.
		this->attenuationChange.addAction(
			std::bind(&PointLight::writeToShader, this));
		this->attenuation.getChangedEvent().
			addEventHandler(&this->attenuationChange);

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