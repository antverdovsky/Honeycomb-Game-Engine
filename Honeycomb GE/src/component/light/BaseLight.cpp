#include "..\..\..\include\component\light\BaseLight.h"

#include "..\..\..\include\shader\phong\PhongShader.h"

using Honeycomb::Conjuncture::Event;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::Phong::PhongShader;

namespace Honeycomb::Component::Light {
	BaseLight::Attenuation::Attenuation()
			: Attenuation(1.0F, 0.22F, 0.20F) {

	}

	BaseLight::Attenuation::Attenuation(float c, float l, float q) {
		this->attenConstant = c;
		this->attenLinear = l;
		this->attenQuadratic = q;
	}

	BaseLight::Attenuation::~Attenuation() {

	}

	void BaseLight::Attenuation::get(float &c, float &l, float &q) const {
		c = this->attenConstant;
		l = this->attenLinear;
		q = this->attenQuadratic;
	}

	const float& BaseLight::Attenuation::getAttenuationConstant() const {
		return this->attenConstant;
	}

	const float& BaseLight::Attenuation::getAttenuationLinear() const {
		return this->attenLinear;
	}

	const float& BaseLight::Attenuation::getAttenuationQuadratic() const {
		return this->attenQuadratic;
	}

	Event& BaseLight::Attenuation::getChangedEvent() {
		return this->attenuationChange;
	}

	void BaseLight::Attenuation::set(float c, float l, float q) {
		this->attenConstant = c;
		this->attenLinear = l;
		this->attenQuadratic = q;
	}

	void BaseLight::Attenuation::setAttenuationConstant(float c) {
		this->attenConstant = c;

		this->attenuationChange();
	}

	void BaseLight::Attenuation::setAttenuationLinear(float l) {
		this->attenLinear = l;

		this->attenuationChange();
	}

	void BaseLight::Attenuation::setAttenuationQuadratic(float q) {
		this->attenQuadratic = q;

		this->attenuationChange();
	}

	BaseLight::BaseLight() : BaseLight("light", 1.0F, 
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F)) {

	}

	BaseLight::BaseLight(std::string nam, float inten, Vector4f col) 
			: GameComponent(nam) {
		this->intensity = inten;
		this->color = col;

		this->baseName = nam + ".base";
	}

	BaseLight::~BaseLight() {

	}

	BaseLight* BaseLight::clone() {
		return new BaseLight(*this);
	}

	const Vector4f& BaseLight::getColor() const {
		return this->color;
	}

	const float& BaseLight::getIntensity() const {
		return this->intensity;
	}

	void BaseLight::setColor(Vector4f c) {
		this->color = c;

		this->writeToShader();
	}

	void BaseLight::setIntensity(float i) {
		this->intensity = i;

		this->writeToShader();
	}
	
	void BaseLight::start() {
		PhongShader::getPhongShader()->addUniform_BaseLight(*this);

		this->writeToShader();
	}

	void BaseLight::writeToShader() {
		PhongShader::getPhongShader()->setUniform_BaseLight(*this);
	}
}