#include "../../../include/component/render/CameraController.h"

#include <math.h>
#include <iostream>

#include "../../../include/base/GameWindow.h"
#include "../../../include/math/MathUtils.h"
#include "../../../include/shader/ShaderProgram.h"
#include "../../../include/shader/ShaderSource.h"

using Honeycomb::Base::GameWindow;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Conjuncture::EventHandler;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::GenericStruct;
using Honeycomb::Shader::ShaderSource;

using namespace Honeycomb::Math::Utils;

namespace Honeycomb { namespace Component { namespace Render {
	CameraController *CameraController::activeCamera = nullptr;

	const std::string CameraController::PROJECTION_MAT4 = "projection";
	const std::string CameraController::VIEW_MAT4 = "view";
	const std::string CameraController::TRANSLATION_VEC3 = "translation";
	const std::string CameraController::WIDTH_F = "width";
	const std::string CameraController::HEIGHT_F = "height";

	const std::string CameraController::STRUCT_FILE = "../Honeycomb GE/"
		"res/shaders/standard/structs/stdCamera.glsl";
	const std::string CameraController::STRUCT_NAME = "Camera";

	CameraController::CameraController() : 
			CameraController(ProjectionType::PERSPECTIVE, 1.31F, 
			1000.0F, 0.30F, 
			(float)GameWindow::getGameWindow()->getWindowHeight(),
			(float)GameWindow::getGameWindow()->getWindowWidth()) {

	}

	CameraController::CameraController(
			const ProjectionType &cT, const float &cTP, 
			const float &clF, const float &clN, 
			const float &projH, const float &projW, const bool &fit) : 
			GenericStruct(ShaderSource::getShaderSource(STRUCT_FILE),
				STRUCT_NAME) {
		this->type = cT;
		this->typeParameter = cTP;

		this->clipFar = clF;
		this->clipNear = clN;

		this->setProjectionSize(projW, projH);
		this->fitToWindow = fit;
	}

	std::unique_ptr<CameraController> CameraController::clone() const {
		return std::unique_ptr<CameraController>(this->cloneInternal());
	}

	CameraController* CameraController::getActiveCamera() {
		return activeCamera;
	}

	const CameraController::ProjectionType& 
			CameraController::getProjectionType() const {
		return this->type;
	}

	const float& CameraController::getClipFar() const {
		return this->clipFar;
	}

	const float& CameraController::getClipNear() const {
		return this->clipNear;
	}

	const bool& CameraController::getFitToWindow() const {
		return this->fitToWindow;
	}

	GameComponentID CameraController::getGameComponentID() const noexcept {
		return GameComponent::getGameComponentTypeID<CameraController>();
	}

	bool CameraController::getIsActive() const {
		return this == CameraController::getActiveCamera();
	}

	const float& CameraController::getProjectionParameter() const {
		return this->typeParameter;
	}

	const Matrix4f& CameraController::getProjection() const {
		if (this->isProjectionDirty) 
			this->calcProjection();

		return this->projection;
	}

	const float& CameraController::getProjectionHeight() const {
		return this->projectionHeight;
	}

	const Matrix4f& CameraController::getProjectionOrientation() const {
		if (this->isProjectionOrienDirty)
			this->calcProjectionOrientation();

		return this->projectionOrien;
	}

	const Matrix4f& CameraController::getProjectionTranslation() const {
		if (this->isProjectionTransDirty)
			this->calcProjectionTranslation();

		return this->projectionTrans;
	}

	const Matrix4f& CameraController::getProjectionView() const {
		if (this->isProjectionViewDirty)
			this->calcProjectionView();

		return this->projectionView;
	}

	const float& CameraController::getProjectionWidth() const {
		return this->projectionWidth;
	}

	void CameraController::onAttach() {
		// Fetch the Transform of the Game Object to which we are now attached
		this->transform = &this->getAttached()->getComponent<Transform>();

		// Recalculate everything since the new Transform has different values
		this->isProjectionDirty = true;
		this->isProjectionOrienDirty = true;
		this->isProjectionTransDirty = true;
		this->isProjectionViewDirty = true;

		// Create an event for window resize; set the projection size and
		// recalculate the projection view and projection when it occurs.
		this->windowResizeHandler.addAction(
			std::bind(&CameraController::onWindowResize, this));
		GameWindow::getGameWindow()->getResizeEvent().addEventHandler(
			&this->windowResizeHandler);

		// Create an event for transform change; recalculate the orientation,
		// translation and projection when it occurs.
		this->transformChangeHandler.addAction(
			std::bind(&CameraController::onTransformChange, this));
		this->transform->getChangedEvent().addEventHandler(
			&this->transformChangeHandler);
	}

	void CameraController::onDetach() {
		// Remove the changed event handler from the Transform and set this
		// Transform pointer to NULL since we are not attached to anything.
		this->transform->getChangedEvent().removeEventHandler(
			&this->transformChangeHandler);
		this->transform = nullptr;
	}

	void CameraController::onDisable() {
		if (CameraController::activeCamera == this)
			CameraController::activeCamera = nullptr;
	}

	void CameraController::onEnable() {
		// If any other camera is already enabled, disable it
		if (CameraController::activeCamera != nullptr)
			CameraController::activeCamera->doDisable();

		CameraController::activeCamera = this;
	}

	void CameraController::setFitToWindow(const bool &fit) {
		this->fitToWindow = fit;
	}

	void CameraController::setProjectionSize(float w, float h) {
		// Write the new values into the Camera instance
		this->projectionWidth = w;
		this->projectionHeight = h;

		this->isProjectionViewDirty = true;
		this->isProjectionDirty = true;

		// Write new width and height to the GenericStruct
		this->glFloats.setValue(CameraController::WIDTH_F,
			this->projectionWidth);
		this->glFloats.setValue(CameraController::HEIGHT_F,
			this->projectionHeight);
	}

	void CameraController::setProjectionSizeToWindowSize() {
		this->setProjectionSize(
			(float)GameWindow::getGameWindow()->getWindowWidth(),
			(float)GameWindow::getGameWindow()->getWindowHeight());
	}

	const Matrix4f& CameraController::calcProjection() const {
		// Calculate the Projection using the View, Orientation and Translation
		// matrices.
		this->projection = 
			this->getProjectionView() *
			this->getProjectionOrientation() *
			this->getProjectionTranslation();

		// Write new projection and view matrices to the GenericStruct
		this->glMatrix4fs.setValue(CameraController::PROJECTION_MAT4,
			this->projection);
		this->glMatrix4fs.setValue(CameraController::VIEW_MAT4,
			this->projectionView * this->projectionOrien);

		this->isProjectionDirty = false;
		return this->projection;
	}

	const Matrix4f& CameraController::calcProjectionOrientation() const {
		this->projectionOrien = this->transform->getMatrixOrientation();

		// Negate the local forwards of the camera since the camera faces the
		// opposite direction as the objects when rendering them.
		this->projectionOrien.setAt(2, 0, -this->projectionOrien.getAt(2, 0));
		this->projectionOrien.setAt(2, 1, -this->projectionOrien.getAt(2, 1));
		this->projectionOrien.setAt(2, 2, -this->projectionOrien.getAt(2, 2));

		this->isProjectionOrienDirty = false;
		return this->projectionOrien;
	}

	const Matrix4f& CameraController::calcProjectionViewOrthographic() const {
		// Calculate the "top" and "right" sections of the projection. Since 
		// the viewport is divided into positive and negative sides, the top 
		// and right must be halfed. Additionally, left and bottom are not
		// needed since bot == -top and left == -right.
		float top = projectionHeight / projectionWidth * typeParameter;
		float right = projectionWidth / projectionHeight * typeParameter;

		this->projectionView = Matrix4f::getMatrixOrthographic(right, top,
				this->clipNear, this->clipFar);

		return this->projectionView;
	}

	const Matrix4f& CameraController::calcProjectionViewPerspective() const {
		float aR = this->projectionWidth / this->projectionHeight;

		this->projectionView = Matrix4f::getMatrixPerspective(
				this->typeParameter, aR, this->clipNear, this->clipFar);

		return this->projectionView;
	}

	const Matrix4f& CameraController::calcProjectionTranslation() const {
		this->projectionTrans = this->transform->getMatrixTranslation();

		// Negate the local forwards of the camera since the camera faces the
		// opposite direction as the objects when rendering them.
		this->projectionTrans.setAt(0, 3, -this->projectionTrans.getAt(0, 3));
		this->projectionTrans.setAt(1, 3, -this->projectionTrans.getAt(1, 3));
		this->projectionTrans.setAt(2, 3, -this->projectionTrans.getAt(2, 3));

		// Write new translation to GenericStruct
		this->glVector3fs.setValue(CameraController::TRANSLATION_VEC3,
			this->transform->getGlobalTranslation());

		this->isProjectionTransDirty = false;
		return this->projectionTrans;
	}

	const Matrix4f& CameraController::calcProjectionView() const {
		// Call the appropriate matrix projection calculation method according
		// to the type of Camera.
		switch (this->type) {
		case ProjectionType::PERSPECTIVE:
			this->projectionView = this->calcProjectionViewPerspective();
			break;
		case ProjectionType::ORTHOGRAPHIC:
			this->projectionView = this->calcProjectionViewOrthographic();
			break;
		}

		this->isProjectionViewDirty = false;
		return this->projectionView;
	}

	CameraController* CameraController::cloneInternal() const {
		auto clone = new CameraController(
			this->type, this->typeParameter,
			this->clipFar, this->clipNear, 
			this->projectionHeight, this->projectionWidth, fitToWindow);

		return clone;
	}

	void CameraController::onTransformChange() {
		this->isProjectionOrienDirty = true;
		this->isProjectionTransDirty = true;
		this->isProjectionDirty = true;

		this->getProjection(); // Trigger recalculation of all matrices
	}

	void CameraController::onWindowResize() {
		if (this->fitToWindow) this->setProjectionSizeToWindowSize();
	}
} } }
