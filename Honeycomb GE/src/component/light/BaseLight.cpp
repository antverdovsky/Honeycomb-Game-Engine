#include "../../../include/component/light/BaseLight.h"

#include <algorithm>
#include <cmath>

#include "../../../include/debug/Logger.h"
#include "../../../include/object/GameObject.h"
#include "../../../include/scene/GameScene.h"

using Honeycomb::Debug::Logger;
using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::GenericStruct;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderSource;

namespace Honeycomb { namespace Component { namespace Light {
	const std::string BaseLight::COLOR_VEC3 = "base.color";
	const std::string BaseLight::INTENSITY_F = "base.intensity";
	const std::string BaseLight::SHADOW_TYPE_I = "base.shadowType";

	BaseLight::BaseLight(const Honeycomb::Shader::ShaderSource &src, const
			std::string &name, const LightType &type) : 
			GenericStruct(src, name), GameComponent(name) {
		this->type = type;
	}

	BaseLight* BaseLight::clone() const {
		return new BaseLight(*GenericStruct::SHADER_SOURCE, 
			GenericStruct::structName, this->type);
	}

	Vector3f& BaseLight::getColor() {
		return this->glVector3fs.getValue(BaseLight::COLOR_VEC3);
	}

	const Vector3f& BaseLight::getColor() const {
		return this->glVector3fs.getValue(BaseLight::COLOR_VEC3);
	}

	float& BaseLight::getIntensity() {
		return this->glFloats.getValue(BaseLight::INTENSITY_F);
	}

	const float& BaseLight::getIntensity() const {
		return this->glFloats.getValue(BaseLight::INTENSITY_F);
	}

	ShadowType BaseLight::getShadowType() const {
		return (ShadowType)(this->glInts.getValue(BaseLight::SHADOW_TYPE_I));
	}

	const LightType& BaseLight::getType() const {
		return this->type;
	}

	void BaseLight::setColor(const Honeycomb::Math::Vector3f &col) {
		this->getColor() = col;
	}

	void BaseLight::setIntensity(const float &inten) {
		this->getIntensity() = inten;
	}

	void BaseLight::setShadowType(const ShadowType &shdw) {
		this->glInts.setValue(BaseLight::SHADOW_TYPE_I, (int)(shdw));
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

	const std::string Attenuation::STRUCT_FILE = "../Honeycomb GE/res/"
		"shaders/standard/light/blinn-phong/stdBaseLight.glsl";
	const std::string Attenuation::STRUCT_NAME = "Attenuation";

	const std::string Attenuation::ATTENUATION_CONSTANT_F = 
		"constant";
	const std::string Attenuation::ATTENUATION_LINEAR_F =
		"linear";
	const std::string Attenuation::ATTENUATION_QUADRATIC_F =
		"quadratic";

	Attenuation::Attenuation() : Attenuation(1.0F, 0.22F, 0.20F) {

	}

	Attenuation::Attenuation(const float &atC, const float &atL, 
			const float &atQ) : 
			GenericStruct(*ShaderSource::getShaderSource(STRUCT_FILE), 
				STRUCT_NAME) {
		this->setConstantTerm(atC);
		this->setLinearTerm(atL);
		this->setQuadraticTerm(atQ);
	}

	float Attenuation::calculateRange(const BaseLight &bL, const Attenuation
			&atten, const float &minI) {
		// Retrieve the RGBA color of the Light and get the maximum RGB 
		// component of the color.
		Vector3f rgb = bL.glVector3fs.getValue(PointLight::COLOR_VEC3);
		float kM = fmaxf(rgb.getX(), fmaxf(rgb.getY(), rgb.getZ()));

		// Constant representing the inverse of the brightness at the radius of
		// the sphere.
		float kK = 1.0F / minI;

		// Retrieve all of the attenuation constants
		float kC = atten.getConstantTerm();
		float kL = atten.getLinearTerm();
		float kQ = atten.getQuadraticTerm();

		// Get the range and return
		return (-kL + sqrt(kL * kL - 4 * kQ * (kC - kK * kM))) / (2 * kQ);
	}

	float& Attenuation::getConstantTerm() {
		return this->glFloats.getValue(ATTENUATION_CONSTANT_F);
	}

	const float& Attenuation::getConstantTerm() const {
		return this->glFloats.getValue(ATTENUATION_CONSTANT_F);
	}

	float& Attenuation::getLinearTerm() {
		return this->glFloats.getValue(ATTENUATION_LINEAR_F);
	}

	const float& Attenuation::getLinearTerm() const {
		return this->glFloats.getValue(ATTENUATION_LINEAR_F);
	}

	float& Attenuation::getQuadraticTerm() {
		return this->glFloats.getValue(ATTENUATION_QUADRATIC_F);
	}

	const float& Attenuation::getQuadraticTerm() const {
		return this->glFloats.getValue(ATTENUATION_QUADRATIC_F);
	}

	void Attenuation::setConstantTerm(const float &atC) {
		this->getConstantTerm() = atC;
	}

	void Attenuation::setLinearTerm(const float &atL) {
		this->getLinearTerm() = atL;
	}

	void Attenuation::setQuadraticTerm(const float &atQ) {
		this->getQuadraticTerm() = atQ;
	}
} } }
