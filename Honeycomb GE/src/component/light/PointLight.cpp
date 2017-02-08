#include "..\..\..\include\component\light\PointLight.h"

#include <algorithm>

#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\scene\GameScene.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderSource;

namespace Honeycomb::Component::Light {
	const std::string PointLight::COLOR_VEC4 = "base.color";
	const std::string PointLight::INTENSITY_F = "base.intensity";
	const std::string PointLight::POSITION_VEC3 = "position";
	const std::string PointLight::RANGE_F = "range";

	const std::string PointLight::structFile = "..\\Honeycomb GE\\res\\shaders"
			"\\standard\\include\\light\\stdPointLight.glsl";
	const std::string PointLight::structName = "PointLight";

	PointLight::PointLight() : 
			PointLight(1.0F, Vector4f(1.0F, 1.0F, 1.0F, 1.0F), Attenuation(),
			10.0F) {

	}

	PointLight::PointLight(const float &inten, const Honeycomb::Math::Vector4f
			&col, const Attenuation &atten, const float &ran) : 
			BaseLight(*ShaderSource::getShaderSource(structFile), structName, 
				LightType::LIGHT_TYPE_POINT) {
		this->glFloats.setValue(PointLight::INTENSITY_F, inten);
		this->glVector4fs.setValue(PointLight::COLOR_VEC4, col);
		this->glFloats.setValue(PointLight::RANGE_F, ran);

		this->attenuation = atten;
	}

	PointLight* PointLight::clone() const {
		PointLight *pL = new PointLight();

		pL->setIntensity(this->getIntensity());
		pL->setColor(this->getColor());
		pL->attenuation = this->attenuation;
		pL->glFloats.setValue(PointLight::RANGE_F, 
			this->glFloats.getValue(PointLight::RANGE_F));

		return pL;
	}

	Attenuation& PointLight::getAttenuation() {
		return this->attenuation;
	}

	const Attenuation& PointLight::getAttenuation() const {
		return this->attenuation;
	}

	const Vector3f& PointLight::getPosition() const {
		return *this->position;
	}

	float& PointLight::getRange() {
		return this->glFloats.getValue(PointLight::RANGE_F);
	}

	const float& PointLight::getRange() const {
		return this->glFloats.getValue(PointLight::RANGE_F);
	}

	void PointLight::setAttenuation(const Attenuation &atten) {
		this->attenuation = atten;
	}

	void PointLight::setRange(const float &range) {
		this->getRange() = range;
	}
	
	void PointLight::start() {
		// Get the position from the Transform.
		this->position = &this->getAttached()->getComponent<Transform>()->
			getTranslation();

		BaseLight::start();
	}

	void PointLight::toShader(ShaderProgram &shader, const std::string &uni)
			const {
		GenericStruct::toShader(shader, uni);

		this->attenuation.toShader(shader, uni + ".attenuation");
	}

	void PointLight::update() {
		this->glVector3fs.setValue(PointLight::POSITION_VEC3, *this->position);
	}
}