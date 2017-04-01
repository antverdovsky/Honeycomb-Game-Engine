#include "../../../include/component/light/DirectionalLight.h"

#include <algorithm>

#include "../../../include/component/physics/Transform.h"
#include "../../../include/object/GameObject.h"
#include "../../../include/scene/GameScene.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderSource;

namespace Honeycomb { namespace Component { namespace Light {
	const std::string DirectionalLight::COLOR_VEC3 = "base.color";
	const std::string DirectionalLight::INTENSITY_F = "base.intensity";
	const std::string DirectionalLight::DIRECTION_VEC3 = "direction";

	const std::string DirectionalLight::structFile = "../Honeycomb GE/"
			"res/shaders/standard/include/light/stdDirectionalLight.glsl";
	const std::string DirectionalLight::structName = "DirectionalLight";

	DirectionalLight::DirectionalLight() : 
			DirectionalLight(1.0F, Vector3f(1.0F, 1.0F, 1.0F)) {

	}

	DirectionalLight::DirectionalLight(const float &inten, const
			Honeycomb::Math::Vector3f &col) : 
			BaseLight(*ShaderSource::getShaderSource(structFile), structName,
				LightType::LIGHT_TYPE_DIRECTIONAL) {
		this->glFloats.setValue(DirectionalLight::INTENSITY_F, inten);
		this->glVector3fs.setValue(DirectionalLight::COLOR_VEC3, col);
	}

	DirectionalLight* DirectionalLight::clone() const {
		return new DirectionalLight(
			this->glFloats.getValue(DirectionalLight::INTENSITY_F),
			this->glVector3fs.getValue(DirectionalLight::COLOR_VEC3)
		);
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

	void DirectionalLight::update() {
		this->glVector3fs.setValue(DirectionalLight::DIRECTION_VEC3, 
			*this->direction);
	}
} } }
