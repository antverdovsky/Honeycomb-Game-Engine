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
using Honeycomb::Shader::Phong::PhongDirectionalShader;

namespace Honeycomb::Component::Light {
	DirectionalLight::DirectionalLight() : 
			DirectionalLight(BaseLight("DirectionalLight")){

	}

	DirectionalLight::DirectionalLight(const BaseLight &bL) : 
			DirectionalLight(bL.getName(), bL.getIntensity(), bL.getColor()) {

	}

	DirectionalLight::DirectionalLight(const std::string &nam, const float
			&inten, const Vector4f &col) : BaseLight(nam, inten, col) {
		this->shader = PhongDirectionalShader::getPhongDirectionalShader();
		this->shaderUniform = "directionalLight";
	}

	DirectionalLight::~DirectionalLight() {

	}

	DirectionalLight* DirectionalLight::clone() const {
		return new DirectionalLight(this->name, this->intensity, this->color);
	}

	const Vector3f& DirectionalLight::getDirection() const {
		return *this->direction;
	}

	void DirectionalLight::start() {
		// Get the direction from the Transform
		this->direction = &this->getAttached()->getComponent<Transform>()->
			getLocalForward();

		BaseLight::start();
	}

	void DirectionalLight::toShader() {
		BaseLight::toShader();

		this->shader->setUniform_vec3(this->shaderUniform + ".direction", 
			*this->direction);
	}
}