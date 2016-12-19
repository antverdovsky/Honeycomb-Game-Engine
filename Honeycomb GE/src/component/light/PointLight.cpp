#include "..\..\..\include\component\light\PointLight.h"

#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\object\GameObject.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb::Component::Light {
	PointLight::PointLight() : 
			PointLight(BaseLight("PointLight"), BaseLight::Attenuation(), 
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
	}

	void PointLight::setRange(const float &ran) {
		this->range = ran;
	}

	void PointLight::start() {
		// Get the position from the Transform.
		this->position = &this->getAttached()->
			getComponentOfType<Transform>("Transform")->getTranslation();
	}

	void PointLight::toShader(ShaderProgram &shader, const std::string &uni) {
		BaseLight::toShader(shader, uni + ".base");
		this->attenuation.toShader(shader, uni + ".attenuation");

		shader.setUniform_vec3(uni + ".position", *this->position);
		shader.setUniform_f(uni + ".range", this->range);
	}
}