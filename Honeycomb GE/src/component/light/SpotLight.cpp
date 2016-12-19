#include "..\..\..\include\component\light\SpotLight.h"

#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\math\MathUtils.h"
#include "..\..\..\include\object\GameObject.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Utils::PI;
using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::ShaderProgram;

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
		this->position = &this->getAttached()->
			getComponentOfType<Transform>("Transform")->getTranslation();
		this->direction = &this->getAttached()->
			getComponentOfType<Transform>("Transform")->getLocalForward();
	}

	void SpotLight::toShader(ShaderProgram &shader, const std::string &uni) {
		BaseLight::toShader(shader, uni + ".base");
		this->attenuation.toShader(shader, uni + ".attenuation");

		shader.setUniform_vec3(uni + ".position", *this->position);
		shader.setUniform_vec3(uni + ".direction", *this->direction);
		shader.setUniform_f(uni + ".range", this->range);
		shader.setUniform_f(uni + ".cosAngle", cos(this->angle));
	}
}