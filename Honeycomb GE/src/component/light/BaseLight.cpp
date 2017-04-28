#include "../../../include/component/light/BaseLight.h"

#include <algorithm>
#include <cmath>

#include "../../../include/debug/Logger.h"
#include "../../../include/object/GameObject.h"
#include "../../../include/scene/GameScene.h"

using Honeycomb::Debug::Logger;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Shader::GenericStruct;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderSource;

namespace Honeycomb { namespace Component { namespace Light {
	const std::string BaseLight::COLOR_VEC3 = "base.color";
	const std::string BaseLight::INTENSITY_F = "base.intensity";

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

	const LightType& BaseLight::getType() const {
		return this->type;
	}

	void BaseLight::setColor(const Honeycomb::Math::Vector3f &col) {
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

	const std::string Attenuation::STRUCT_FILE = "../Honeycomb GE/res/"
		"shaders/standard/structs/light/stdBaseLight.glsl";
	const std::string Attenuation::STRUCT_NAME = "Attenuation";

	const std::string Attenuation::ATTENUATION_CONSTANT_F = "constant";
	const std::string Attenuation::ATTENUATION_LINEAR_F = "linear";
	const std::string Attenuation::ATTENUATION_QUADRATIC_F = "quadratic";

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

	const std::string Shadow::STRUCT_FILE = "../Honeycomb GE/res/"
		"shaders/standard/structs/light/stdBaseLight.glsl";
	const std::string Shadow::STRUCT_NAME = "Shadow";

	const std::string Shadow::INTENSITY_F = "intensity";
	const std::string Shadow::MAX_BIAS_F = "maxBias";
	const std::string Shadow::MIN_BIAS_F = "minBias";
	const std::string Shadow::PROJECTION_MAT4 = "projection";
	const std::string Shadow::SHADOW_TYPE_I = "shadowType";

	bool Shadow::isClassicShadow(const ShadowType &shdw) {
		return shdw == ShadowType::SHADOW_HARD ||
			   shdw == ShadowType::SHADOW_PCF ||
			   shdw == ShadowType::SHADOW_INTERPOLATED ||
			   shdw == ShadowType::SHADOW_PCF_INTERPOLATED;
	}

	bool Shadow::isVarianceShadow(const ShadowType &shdw) {
		return shdw == ShadowType::SHADOW_VARIANCE;
	}

	Shadow::Shadow() : Shadow(ShadowType::SHADOW_VARIANCE) {

	}

	Shadow::Shadow(const ShadowType &shdw) :
			GenericStruct(*ShaderSource::getShaderSource(STRUCT_FILE),
			STRUCT_NAME) {
		this->setShadowType(shdw);
		this->setProjection(Matrix4f::identity());
		this->setMinimumBias(0.005F);
		this->setMaximumBias(0.050F);
		this->setIntensity(0.75F);
	}

	const float& Shadow::getIntensity() const {
		return this->glFloats.getValue(Shadow::INTENSITY_F);
	}

	const float& Shadow::getMaximumBias() const {
		return this->glFloats.getValue(Shadow::MAX_BIAS_F);
	}

	const float& Shadow::getMinimumBias() const {
		return this->glFloats.getValue(Shadow::MIN_BIAS_F);
	}

	const Matrix4f& Shadow::getProjection() const {
		return this->glMatrix4fs.getValue(Shadow::PROJECTION_MAT4);
	}

	ShadowType Shadow::getShadowType() const {
		return (ShadowType)(this->glInts.getValue(Shadow::SHADOW_TYPE_I));
	}

	void Shadow::setIntensity(const float &i) {
		this->glFloats.setValue(Shadow::INTENSITY_F, i);
	}

	void Shadow::setMaximumBias(const float &bias) {
		this->glFloats.setValue(Shadow::MAX_BIAS_F, bias);
	}

	void Shadow::setMinimumBias(const float &bias) {
		this->glFloats.setValue(Shadow::MIN_BIAS_F, bias);
	}

	void Shadow::setProjection(const Matrix4f &proj) {
		this->glMatrix4fs.setValue(Shadow::PROJECTION_MAT4, proj);
	}

	void Shadow::setShadowType(const ShadowType &shdw) {
		this->glInts.setValue(Shadow::SHADOW_TYPE_I, (int)(shdw));
	}
} } }
