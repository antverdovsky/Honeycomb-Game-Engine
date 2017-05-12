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

	const std::string DirectionalLight::structFile = "../Honeycomb GE/res/"
		"shaders/standard/structs/light/stdDirectionalLight.glsl";
	const std::string DirectionalLight::structName = "DirectionalLight";

	DirectionalLight::DirectionalLight() : 
			DirectionalLight(1.0F, Vector3f(1.0F, 1.0F, 1.0F), 
			ShadowType::SHADOW_PCF) {

	}

	DirectionalLight::DirectionalLight(const float &inten, const
			Honeycomb::Math::Vector3f &col, const ShadowType &shdw) : 
			BaseLight(*ShaderSource::getShaderSource(structFile), structName,
				LightType::LIGHT_TYPE_DIRECTIONAL) {
		this->glFloats.setValue(DirectionalLight::INTENSITY_F, inten);
		this->glVector3fs.setValue(DirectionalLight::COLOR_VEC3, col);
		this->shadow.setShadowType(shdw);
	}

	DirectionalLight* DirectionalLight::clone() const {
		return new DirectionalLight(
			this->glFloats.getValue(DirectionalLight::INTENSITY_F),
			this->glVector3fs.getValue(DirectionalLight::COLOR_VEC3),
			this->shadow.getShadowType()
		);
	}

	const Vector3f& DirectionalLight::getDirection() const {
		return this->transform->getLocalForward();
	}

	Shadow& DirectionalLight::getShadow() {
		return this->shadow;
	}

	const Shadow& DirectionalLight::getShadow() const {
		return this->shadow;
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
			Matrix4f::orthographic(21, 21, -20.0F, 20.0F);				// csm is going to be needed for this

		// Fetch the orientation matrix and reverse its forward components (see
		// the CameraController calculate projection code).
		Matrix4f orientationMat = this->transform->getOrientationMatrix();
		orientationMat.setAt(2, 0, -orientationMat.getAt(2, 0));
		orientationMat.setAt(2, 1, -orientationMat.getAt(2, 1));
		orientationMat.setAt(2, 2, -orientationMat.getAt(2, 2));

		// Calculate the Light Projection Matrix for Shadow Mapping
		Matrix4f lightMatrix = PROJECTION * orientationMat;
		this->shadow.setProjection(lightMatrix);
		
		return lightMatrix;
	}

	void DirectionalLight::onTransformChange() {
		this->calculateLightProjection();
		this->glVector3fs.setValue(DirectionalLight::DIRECTION_VEC3,
			this->transform->getLocalForward());
	}

	void DirectionalLight::toShader(
			ShaderProgram &shader, const std::string &uni) const {
		GenericStruct::toShader(shader, uni);

		this->shadow.toShader(shader, uni + ".shadow");
	}
} } }
