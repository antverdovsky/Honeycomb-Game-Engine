#include "..\..\..\include\component\light\PointLight.h"

#include <algorithm>

#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\scene\GameScene.h"
#include "..\..\..\include\shader\phong\PhongPointShader.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::Phong::PhongPointShader;

namespace Honeycomb::Component::Light {
	PointLight::PointLight() : 
			PointLight(BaseLight("PointLight"), BaseLight::Attenuation(), 
			10.0F) {

	}

	PointLight::PointLight(const BaseLight &bL, 
		const BaseLight::Attenuation &atten, const float &ran) : 
			PointLight(bL.getName(), bL.getIntensity(), bL.getColor(),
			atten.getAttenuationConstant(), atten.getAttenuationLinear(),
			atten.getAttenuationQuadratic(), ran) {
		
	}

	PointLight::PointLight(const std::string &nam, const float &inten, const
		Honeycomb::Math::Vector4f &col, const float &atC, const float &atL,
		const float &atQ, const float &ran) : 
			BaseLight(nam, inten, col), attenuation(atC, atL, atQ) {
		this->range = ran;

		this->shader = PhongPointShader::getPhongPointShader();
		this->shaderUniform = "pointLight";
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
	
		BaseLight::start();
	}

	void PointLight::toShader() {
		BaseLight::toShader();

		this->attenuation.toShader(*this->shader, 
			this->shaderUniform + ".attenuation");
		this->shader->setUniform_vec3(this->shaderUniform + ".position", 
			*this->position);
		this->shader->setUniform_f(this->shaderUniform + ".range", 
			this->range);
	}
}