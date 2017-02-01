#include "..\..\..\include\component\light\BaseLight.h"

#include <algorithm>

#include "..\..\..\include\debug\Logger.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\scene\GameScene.h"

using Honeycomb::Debug::Logger;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::GenericStruct;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderSource;

namespace Honeycomb::Component::Light {
	const std::string BaseLight::COLOR_VEC4 = "base.color";
	const std::string BaseLight::INTENSITY_F = "base.intensity";

	BaseLight::BaseLight(const Honeycomb::Shader::ShaderSource &src, const
			std::string &name) : 
			GenericStruct(src, name), GameComponent(name) {

	}

	BaseLight* BaseLight::clone() const {
		return new BaseLight(*GenericStruct::SHADER_SOURCE, 
			GenericStruct::structName);
	}

	Vector4f& BaseLight::getColor() {
		return this->glVector4fs.getValue(BaseLight::COLOR_VEC4);
	}

	const Vector4f& BaseLight::getColor() const {
		return this->glVector4fs.getValue(BaseLight::COLOR_VEC4);
	}

	float& BaseLight::getIntensity() {
		return this->glFloats.getValue(BaseLight::INTENSITY_F);
	}

	const float& BaseLight::getIntensity() const {
		return this->glFloats.getValue(BaseLight::INTENSITY_F);
	}

	void BaseLight::setColor(const Honeycomb::Math::Vector4f &col) {
		this->getColor() = col;
	}

	void BaseLight::setIntensity(const float &inten) {
		this->getIntensity() = inten;
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

	const std::string Attenuation::STRUCT_FILE = "..\\Honeycomb GE\\res\\"
		"shaders\\standard\\include\\light\\stdBaseLight.glsl";
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
}