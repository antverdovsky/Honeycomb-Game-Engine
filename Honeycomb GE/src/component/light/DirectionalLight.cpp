#include "../../../include/component/light/DirectionalLight.h"

#include <algorithm>

#include "../../../include/component/physics/Transform.h"
#include "../../../include/object/GameObject.h"
#include "../../../include/scene/GameScene.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderSource;

namespace Honeycomb { namespace Component { namespace Light {
	const std::string DirectionalLight::COLOR_VEC3 = "base.color";
	const std::string DirectionalLight::INTENSITY_F = "base.intensity";
	const std::string DirectionalLight::DIRECTION_VEC3 = "direction";

	const std::string DirectionalLight::structFile = "../Honeycomb GE/"
			"res/shaders/standard/light/stdDirectionalLight.glsl";
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
		return this->transform->getLocalForward();
	}

	const Matrix4f& DirectionalLight::getLightProjection() const {
		return this->lightProjection;
	}

	void DirectionalLight::start() {
		this->transform = this->getAttached()->getComponent<Transform>();

		// Add event handler to the Transform
		this->transformChangeHandler.addAction(
			std::bind(&DirectionalLight::onTransformChange, this));
		this->transform->getChangedEvent().addEventHandler(
			this->transformChangeHandler);

		BaseLight::start();
	}

	Matrix4f DirectionalLight::calculateLightProjection() {
		// Standard Orthographic Projection
		const static Matrix4f PROJECTION =
			Matrix4f::orthographic(30, 30, -25.0F, 25.0F);

		// Fetch the orientation matrix and reverse its forward components (see
		// the CameraController calculate projection code).
		Matrix4f orientationMat = this->transform->getOrientationMatrix();
		orientationMat.setAt(2, 0, -orientationMat.getAt(2, 0));
		orientationMat.setAt(2, 1, -orientationMat.getAt(2, 1));
		orientationMat.setAt(2, 2, -orientationMat.getAt(2, 2));

		// Calculate the Light Projection Matrix for Shadow Mapping
		this->lightProjection = PROJECTION * orientationMat;
		return this->lightProjection;
	}

	void DirectionalLight::onTransformChange() {
		this->calculateLightProjection();
		this->glVector3fs.setValue(DirectionalLight::DIRECTION_VEC3,
			this->transform->getLocalForward());
	}
} } }
