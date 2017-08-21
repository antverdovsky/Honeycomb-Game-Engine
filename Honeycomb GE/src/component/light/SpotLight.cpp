#include "../../../include/component/light/SpotLight.h"

#include <algorithm>

#include "../../../include/component/physics/Transform.h"
#include "../../../include/math/MathUtils.h"
#include "../../../include/math/Matrix4f.h"
#include "../../../include/object/GameObject.h"
#include "../../../include/scene/GameScene.h"
#include "../../../include/render/Renderer.h"

using Honeycomb::Component::Physics::Transform;
using Honeycomb::Math::Utils::PI;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Vector4f;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::ShaderSource;
using Honeycomb::Render::Renderer;

namespace Honeycomb { namespace Component { namespace Light {
	const std::string SpotLight::COLOR_VEC3 = "base.color";
	const std::string SpotLight::INTENSITY_F = "base.intensity";
	const std::string SpotLight::DIRECTION_VEC3 = "direction";
	const std::string SpotLight::POSITION_VEC3 = "position";
	const std::string SpotLight::RANGE_F = "range";
	const std::string SpotLight::ANGLE_F = "angle";

	const std::string SpotLight::structFile = "../Honeycomb GE/res/"
		"shaders/standard/structs/light/stdSpotLight.glsl";
	const std::string SpotLight::structName = "SpotLight";

	SpotLight::SpotLight() : SpotLight(1.0F, Vector3f(1.0F, 1.0F, 1.0F),
			Attenuation(), 10.0F, PI / 4.0F) {

	}

	SpotLight::SpotLight(const float &inten, const Honeycomb::Math::Vector3f
			&col, const Attenuation &atten, const float &ran, 
			const float &ang) : 
			BaseLight(ShaderSource::getShaderSource(structFile), structName, 
				LightType::LIGHT_TYPE_SPOT) {
		this->glFloats.setValue(SpotLight::INTENSITY_F, inten);
		this->glVector3fs.setValue(SpotLight::COLOR_VEC3, col);
		this->glFloats.setValue(SpotLight::RANGE_F, ran);
		this->glFloats.setValue(SpotLight::ANGLE_F, ang);

		this->attenuation = atten;
	}

	std::unique_ptr<SpotLight> SpotLight::clone() const {
		return std::unique_ptr<SpotLight>(this->cloneInternal());
	}

	float& SpotLight::getAngle() {
		return this->glFloats.getValue(SpotLight::ANGLE_F);
	}

	const float& SpotLight::getAngle() const {
		return this->glFloats.getValue(SpotLight::ANGLE_F);
	}

	Attenuation& SpotLight::getAttenuation() {
		return this->attenuation;
	}

	const Attenuation& SpotLight::getAttenuation() const {
		return this->attenuation;
	}

	GameComponentID SpotLight::getGameComponentID() const noexcept {
		return GameComponent::getGameComponentTypeID<SpotLight>();
	}

	const Vector3f& SpotLight::getDirection() const {
		return this->transform->getLocalForward();
	}

	const Vector3f& SpotLight::getPosition() const {
		return this->transform->getGlobalTranslation();
	}

	const float& SpotLight::getRange() const {
		return this->glFloats.getValue(SpotLight::RANGE_F);
	}

	float& SpotLight::getRange() {
		return this->glFloats.getValue(SpotLight::RANGE_F);
	}

	Shadow& SpotLight::getShadow() {
		return this->shadow;
	}

	const Shadow& SpotLight::getShadow() const {
		return this->shadow;
	}

	void SpotLight::setAttenuation(const Attenuation &atten) {
		this->attenuation = atten;
	}

	void SpotLight::onAttach() {
		this->transform = &this->getAttached()->getComponent<Transform>();

		// Add event handler to the Transform
		this->transformChangeHandler.addAction(
			std::bind(&SpotLight::onTransformChange, this));
		this->transform->getChangedEvent().addEventHandler(
			&this->transformChangeHandler);

		BaseLight::onAttach();
	}

	void SpotLight::onDetach() {
		this->transform->getChangedEvent().removeEventHandler(
			&this->transformChangeHandler);
		this->transform = nullptr;

		BaseLight::onDetach();
	}

	void SpotLight::toShader(ShaderProgram &shader, const std::string &uni)
			const {
		GenericStruct::toShader(shader, uni);

		this->attenuation.toShader(shader, uni + ".attenuation");
		this->shadow.toShader(shader, uni + ".shadow");
	}

	Matrix4f SpotLight::calculateLightProjection() {
		// Perspective Projection Matrix based on the angle of the spot light
		int aR = Renderer::getRenderer()->getShadowMapWidth() / 
			Renderer::getRenderer()->getShadowMapHeight();
		Matrix4f persp = Matrix4f::getMatrixPerspective(this->getAngle(), aR, 
				0.1F, this->getRange());

		// Fetch the orientation matrix and reverse its forward components (see
		// the CameraController calculate projection code).
		Matrix4f orientationMat = this->transform->getMatrixOrientation();
		orientationMat.setAt(2, 0, -orientationMat.getAt(2, 0));
		orientationMat.setAt(2, 1, -orientationMat.getAt(2, 1));
		orientationMat.setAt(2, 2, -orientationMat.getAt(2, 2));

		// Fetch the translation matrix from the transform and reverse its
		// forward components (again, see the CameraController for reasoning).
		Matrix4f translationMat = this->transform->getMatrixTranslation();
		translationMat.setAt(0, 3, -translationMat.getAt(0, 3));
		translationMat.setAt(1, 3, -translationMat.getAt(1, 3));
		translationMat.setAt(2, 3, -translationMat.getAt(2, 3));

		// Calculate the Light Projection Matrix for Shadow Mapping
		Matrix4f lightMatrix = persp * orientationMat * translationMat;
		this->shadow.setProjection(lightMatrix);

		return lightMatrix;
	}

	void SpotLight::onTransformChange() {
		this->calculateLightProjection();
		this->glVector3fs.setValue(SpotLight::DIRECTION_VEC3,
			this->transform->getLocalForward());
		this->glVector3fs.setValue(SpotLight::POSITION_VEC3,
			this->transform->getGlobalTranslation());
	}

	SpotLight* SpotLight::cloneInternal() const {
		SpotLight *sL = new SpotLight();

		sL->setIntensity(this->getIntensity());
		sL->setColor(this->getColor());
		sL->attenuation = this->attenuation;
		sL->glFloats.setValue(PointLight::RANGE_F,
			this->glFloats.getValue(PointLight::RANGE_F));
		sL->glFloats.setValue(SpotLight::ANGLE_F,
			this->glFloats.getValue(SpotLight::ANGLE_F));

		return sL;
	}
} } }
