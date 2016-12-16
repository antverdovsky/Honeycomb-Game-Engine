#include "..\..\..\include\component\light\BaseLight.h"

#include "..\..\..\include\shader\phong\PhongShader.h"

using Honeycomb::Conjuncture::Event;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::Phong::PhongShader;

namespace Honeycomb::Component::Light {
	BaseLight::Attenuation::Attenuation()
			: Attenuation(1.0F, 0.22F, 0.20F) {

	}

	BaseLight::Attenuation::Attenuation(const float &c, const float &l, 
			const float &q) {
		this->attenConstant = c;
		this->attenLinear = l;
		this->attenQuadratic = q;
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

	const Event& BaseLight::Attenuation::getChangedEvent() const {
		return this->attenuationChange;
	}

	void BaseLight::Attenuation::set(const float &c, const float &l, 
			const float &q) {
		this->attenConstant = c;
		this->attenLinear = l;
		this->attenQuadratic = q;

		this->attenuationChange();
	}

	void BaseLight::Attenuation::setAttenuationConstant(const float &c) {
		this->attenConstant = c;

		this->attenuationChange();
	}

	void BaseLight::Attenuation::setAttenuationLinear(const float &l) {
		this->attenLinear = l;

		this->attenuationChange();
	}

	void BaseLight::Attenuation::setAttenuationQuadratic(const float &q) {
		this->attenQuadratic = q;

		this->attenuationChange();
	}

	BaseLight::BaseLight() : BaseLight("light", 1.0F, 
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F)) {

	}

	BaseLight::BaseLight(const std::string &nam) : BaseLight(nam, 1.0F,
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F)) {

	}

	BaseLight::BaseLight(const std::string &nam, const float &inten, 
			const Vector4f &col) : GameComponent(nam) {
		this->intensity = inten;
		this->color = col;

		this->baseName = nam + ".base";
	}

	BaseLight::~BaseLight() {

	}

	BaseLight* BaseLight::clone() const {
		return new BaseLight(this->name, this->intensity, this->color);
	}

	const Vector4f& BaseLight::getColor() const {
		return this->color;
	}

	const float& BaseLight::getIntensity() const {
		return this->intensity;
	}

	void BaseLight::setColor(const Vector4f &c) {
		this->color = c;
	}

	void BaseLight::setIntensity(const float &i) {
		this->intensity = i;
	}
	
	void BaseLight::start() {
		
	}
}