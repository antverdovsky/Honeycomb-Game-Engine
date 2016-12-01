#include "..\..\..\include\component\light\PointLight.h"

#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\shader\phong\PhongShader.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::Phong::PhongShader;

namespace Honeycomb::Component::Light {
	PointLight::PointLight() : 
			PointLight(BaseLight("pointLight"), BaseLight::Attenuation(), 
			10.0F) {

	}

	PointLight::PointLight(const BaseLight &bL, 
			const BaseLight::Attenuation &atten, const float &ran) : 
			BaseLight(bL), attenuation(atten) {
		this->range = ran;
	}

	PointLight::PointLight(const std::string &nam, const float &inten, const
			Honeycomb::Math::Vector4f &col, const float &atC, const float &atL,
			const float &atQ, const float &ran) : 
			BaseLight(nam, inten, col), attenuation(atC, atL, atQ) {
		this->range = ran;
	}

	PointLight::~PointLight() {

	}

	PointLight* PointLight::clone() const {
		return new PointLight(*this, this->attenuation, this->range);
	}

	const BaseLight::Attenuation& PointLight::getAttenuation() const {
		return this->attenuation;
	}

	const Vector3f& PointLight::getPosition() const {
		return *this->position;
	}

	const float& PointLight::getRange() const {
		return this->range;
	}

	void PointLight::setAttenuation(const BaseLight::Attenuation &atten) {
		this->attenuation = atten;

		this->writeToShader();
	}

	void PointLight::setRange(const float &ran) {
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
			getChangedEvent().addEventHandler(this->transformChange);

		// Subscribe to the Attenuation change event, so that the attenuation
		// may be written to the shader each time it is changed.
		this->attenuationChange.addAction(
			std::bind(&PointLight::writeToShader, this));
		this->attenuation.getChangedEvent().
			addEventHandler(this->attenuationChange);

		// Get the position from the Transform so that it may be sent to the
		// Phong Shader.
		this->position = &this->getAttached()->
			getComponentOfType<Transform>("Transform")->getTranslation();

		writeToShader(); // Write the default Transform direction to Shader
	}

	void PointLight::writeToShader() {
		PhongShader::getPhongShader()->setUniform_PointLight(*this);
	}
}