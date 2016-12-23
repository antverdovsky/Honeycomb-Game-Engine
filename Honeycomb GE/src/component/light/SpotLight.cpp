#include "..\..\..\include\component\light\SpotLight.h"

#include <algorithm>

#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\math\MathUtils.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\scene\GameScene.h"
#include "..\..\..\include\shader\phong\PhongSpotShader.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Utils::PI;
using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::Phong::PhongSpotShader;

namespace Honeycomb::Component::Light {
	SpotLight::SpotLight() : 
			SpotLight(BaseLight("SpotLight"), BaseLight::Attenuation(), 
			10.0F, PI / 6.0F) {

	}

	SpotLight::SpotLight(const BaseLight &bL, const BaseLight::Attenuation 
		&atten, const float &ran, const float &ang) : 
			BaseLight(bL), attenuation(atten) {
		this->range = ran;
		this->angle = ang;

		this->shader = PhongSpotShader::getPhongSpotShader();
		this->shaderUniform = "spotLight";
	}

	SpotLight::~SpotLight() {

	}

	SpotLight* SpotLight::clone() const {
		return new SpotLight(*this, this->attenuation, this->range, 
			this->angle);
	}

	const float& SpotLight::getAngle() const {
		return this->angle;
	}

	const BaseLight::Attenuation& SpotLight::getAttenuation() const {
		return this->attenuation;
	}

	const Vector3f& SpotLight::getDirection() const {
		return *this->direction;
	}

	const Vector3f& SpotLight::getPosition() const {
		return *this->position;
	}

	const float& SpotLight::getRange() const {
		return this->range;
	}

	void SpotLight::setAngle(const float &ang) {
		this->angle = ang;
	}

	void SpotLight::setAttenuation(const BaseLight::Attenuation &atten) {
		this->attenuation = atten;
	}

	void SpotLight::setRange(const float &ran) {
		this->range = ran;
	}

	void SpotLight::start() {
		// Get the position and direction.
		this->position = &this->getAttached()->getComponent<Transform>()->
			getTranslation();
		this->direction = &this->getAttached()->getComponent<Transform>()->
			getLocalForward();

		BaseLight::start();
	}

	void SpotLight::toShader() {
		BaseLight::toShader();
		this->attenuation.toShader(*this->shader, 
			this->shaderUniform + ".attenuation");

		this->shader->setUniform_vec3(this->shaderUniform + ".position", 
			*this->position);
		this->shader->setUniform_vec3(this->shaderUniform + ".direction", 
			*this->direction);
		this->shader->setUniform_f(this->shaderUniform + ".range",
			this->range);
		this->shader->setUniform_f(this->shaderUniform + ".cosAngle",
			cos(this->angle));
	}
}