#include "..\..\..\include\component\light\DirectionalLight.h"

#include <algorithm>

#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\scene\GameScene.h"
#include "..\..\..\include\shader\phong\PhongDirectionalShader.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderSource;
using Honeycomb::Shader::Phong::PhongDirectionalShader;

namespace Honeycomb::Component::Light {
	const std::string DirectionalLight::COLOR_VEC4 = "base.color";
	const std::string DirectionalLight::INTENSITY_F = "base.intensity";
	const std::string DirectionalLight::DIRECTION_VEC3 = "direction";

	const ShaderSource *DirectionalLight::shaderSource =
		ShaderSource::getShaderSource("..\\Honeycomb GE\\res\\shaders\\"
			"standard\\source\\light\\stdDirectionalLight.glsl");
	const std::string DirectionalLight::structName = "DirectionalLight";

	DirectionalLight::DirectionalLight() : 
			DirectionalLight(1.0F, Vector4f(1.0F, 1.0F, 1.0F, 1.0F)) {

	}

	DirectionalLight::DirectionalLight(const float &inten, const
			Honeycomb::Math::Vector4f &col) : 
			BaseLight(*shaderSource, structName) {
		this->glFloats.setValue(DirectionalLight::INTENSITY_F, inten);
		this->glVector4fs.setValue(DirectionalLight::COLOR_VEC4, col);

		this->preferredShader = PhongDirectionalShader::
			getPhongDirectionalShader();
		this->uniformName = "directionalLight";
	}

	DirectionalLight* DirectionalLight::clone() const {
		return new DirectionalLight(
			this->glFloats.getValue(DirectionalLight::INTENSITY_F),
			this->glVector4fs.getValue(DirectionalLight::COLOR_VEC4)
		);
	}

	void DirectionalLight::start() {
		// Get the direction from the Transform
		this->direction = &this->getAttached()->getComponent<Transform>()->
			getLocalForward();

		BaseLight::start();
	}

	void DirectionalLight::update() {
		this->glVector3fs.setValue(DirectionalLight::DIRECTION_VEC3, 
			*this->direction);
	}
}