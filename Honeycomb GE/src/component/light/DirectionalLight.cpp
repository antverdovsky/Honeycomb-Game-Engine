#include "..\..\..\include\component\light\DirectionalLight.h"

#include <algorithm>

#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\object\GameObject.h"
#include "..\..\..\include\scene\GameScene.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;

namespace Honeycomb::Component::Light {
	DirectionalLight::DirectionalLight() 
			: DirectionalLight(BaseLight("DirectionalLight")){

	}

	DirectionalLight::DirectionalLight(const BaseLight &bL) 
			: BaseLight(bL) {

	}

	DirectionalLight::DirectionalLight(const std::string &nam, const float
			&inten, const Vector4f &col) : BaseLight(nam, inten, col) {

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
		this->direction = &this->getAttached()->
			getComponentOfType<Transform>("Transform")->getLocalForward();

		this->getAttached()->getScene()->directionalLights.push_back(this);
	}

	void DirectionalLight::stop() {
		std::vector<DirectionalLight*> &dLs =
			this->getAttached()->getScene()->directionalLights;

		dLs.erase(std::remove(dLs.begin(), dLs.end(), this), dLs.end());
	}

	void DirectionalLight::toShader(ShaderProgram &shader, const std::string 
			&uni) {
		BaseLight::toShader(shader, uni + ".base");

		shader.setUniform_vec3(uni + ".direction", *this->direction);
	}
}