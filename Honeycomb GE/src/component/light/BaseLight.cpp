#include "..\..\..\include\component\light\BaseLight.h"

#include <algorithm>

#include "..\..\..\include\debug\Logger.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\scene\GameScene.h"

using Honeycomb::Debug::Logger;
using Honeycomb::Conjuncture::Event;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;

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

	void BaseLight::Attenuation::toShader(ShaderProgram &shader, const 
			std::string &uni) {
		shader.setUniform_f(uni + ".constant", this->attenConstant);
		shader.setUniform_f(uni + ".linear", this->attenLinear);
		shader.setUniform_f(uni + ".quadratic", this->attenQuadratic);
	}

	BaseLight::BaseLight() : BaseLight("BaseLight", 1.0F, 
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F)) {

	}

	BaseLight::BaseLight(const std::string &nam) : BaseLight(nam, 1.0F,
			Vector4f(1.0F, 1.0F, 1.0F, 1.0F)) {

	}

	BaseLight::BaseLight(const std::string &nam, const float &inten, 
			const Vector4f &col) : GameComponent(nam) {
		this->intensity = inten;
		this->color = col;
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

	ShaderProgram* BaseLight::getShader() {
		return this->shader;
	}

	void BaseLight::setColor(const Vector4f &c) {
		this->color = c;
	}

	void BaseLight::setIntensity(const float &i) {
		this->intensity = i;
	}
	
	void BaseLight::start() {
		this->getAttached()->getScene()->activeLights.push_back(this);
	}

	void BaseLight::stop() {
		std::vector<BaseLight*> &lights =
			this->getAttached()->getScene()->activeLights;

		lights.erase(std::remove(lights.begin(), lights.end(), this),
			lights.end());
	}

	void BaseLight::toShader() {
		if (this->shader == nullptr) {
			Logger::getLogger().logError(__FUNCTION__, __LINE__, "Shader has "
				"not been initialized in light " + this->name);
		}

		this->shader->setUniform_f(this->shaderUniform + ".base.intensity", 
			this->intensity);
		this->shader->setUniform_vec4(this->shaderUniform + ".base.color",
			this->color);
	}
}