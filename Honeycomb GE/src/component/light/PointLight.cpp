#include "..\..\..\include\component\light\PointLight.h"

#include <algorithm>

#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\scene\GameScene.h"
#include "..\..\..\include\shader\phong\PhongPointShader.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderSource;
using Honeycomb::Shader::Phong::PhongPointShader;

namespace Honeycomb::Component::Light {
	const std::string PointLight::ATTENUATION_CONSTANT_F = 
			"attenuation.constant";
	const std::string PointLight::ATTENUATION_LINEAR_F = "attenuation.linear";
	const std::string PointLight::ATTENUATION_QUADRATIC_F = 
			"attenuation.quadratic";
	const std::string PointLight::COLOR_VEC4 = "base.color";
	const std::string PointLight::INTENSITY_F = "base.intensity";
	const std::string PointLight::POSITION_VEC3 = "position";
	const std::string PointLight::RANGE_F = "range";

	const std::string PointLight::structFile = "..\\Honeycomb GE\\res\\shaders"
			"\\standard\\source\\light\\stdPointLight.glsl";
	const std::string PointLight::structName = "PointLight";

	PointLight::PointLight() : 
			PointLight(1.0F, Vector4f(1.0F, 1.0F, 1.0F, 1.0F), 1.0F, 0.22F,
			0.20F, 10.0F) {

	}

	PointLight::PointLight(const float &inten, const Honeycomb::Math::Vector4f
			&col, const float &atC, const float &atL, const float &atQ, const
			float &ran) : 
			BaseLight(*ShaderSource::getShaderSource(structFile), structName) {
		this->glFloats.setValue(PointLight::INTENSITY_F, inten);
		this->glVector4fs.setValue(PointLight::COLOR_VEC4, col);
		this->glFloats.setValue(PointLight::ATTENUATION_CONSTANT_F, atC);
		this->glFloats.setValue(PointLight::ATTENUATION_LINEAR_F, atL);
		this->glFloats.setValue(PointLight::ATTENUATION_QUADRATIC_F, atQ);
		this->glFloats.setValue(PointLight::RANGE_F, ran);

		this->preferredShader = PhongPointShader::getPhongPointShader();
		this->uniformName = "pointLight";
	}

	PointLight* PointLight::clone() const {
		return new PointLight(
			this->glFloats.getValue(PointLight::INTENSITY_F),
			this->glVector4fs.getValue(PointLight::COLOR_VEC4),
			this->glFloats.getValue(PointLight::ATTENUATION_CONSTANT_F),
			this->glFloats.getValue(PointLight::ATTENUATION_LINEAR_F),
			this->glFloats.getValue(PointLight::ATTENUATION_QUADRATIC_F),
			this->glFloats.getValue(PointLight::RANGE_F));
	}
	
	void PointLight::start() {
		// Get the position from the Transform.
		this->position = &this->getAttached()->getComponent<Transform>()->
			getTranslation();

		BaseLight::start();
	}

	void PointLight::update() {
		this->glVector3fs.setValue(PointLight::POSITION_VEC3, *this->position);
	}
}