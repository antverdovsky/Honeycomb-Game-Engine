#include "..\..\..\include\component\render\CameraController.h"

#include <math.h>
#include <iostream>

#include "..\..\..\include\base\GameWindow.h"
#include "..\..\..\include\math\MathUtils.h"
#include "..\..\..\include\shader\ShaderProgram.h"
#include "..\..\..\include\shader\ShaderSource.h"

using Honeycomb::Base::GameWindow;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Conjuncture::EventHandler;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Shader::ShaderProgram;
using Honeycomb::Shader::GenericStruct;
using Honeycomb::Shader::ShaderSource;

using namespace Honeycomb::Math::Utils;

namespace Honeycomb::Component::Render {
	CameraController *CameraController::activeCamera = nullptr;

	const std::string CameraController::PROJECTION_MAT4 = "projection";
	const std::string CameraController::TRANSLATION_VEC3 = "translation";
	const std::string CameraController::WIDTH_F = "width";
	const std::string CameraController::HEIGHT_F = "height";

	const std::string CameraController::STRUCT_FILE = "..\\Honeycomb GE\\"
		"res\\shaders\\standard\\include\\stdCamera.glsl";
	const std::string CameraController::STRUCT_NAME = "Camera";

	CameraController::CameraController() : 
			CameraController(CameraType::PERSPECTIVE, 75.0F, 1000.0F, 0.30F,
			(float)GameWindow::getGameWindow()->getWindowHeight(),
			(float)GameWindow::getGameWindow()->getWindowWidth()) {

	}

	CameraController::CameraController(const CameraType &cT, const float &cTP,
			const float &clF, const float &clN, const float &projH,
			const float &projW) : 
			GameComponent("CameraController"), GenericStruct(*ShaderSource::
				getShaderSource(STRUCT_FILE), STRUCT_NAME) {
		this->type = cT;
		this->typeParameter = cTP;

		this->clipFar = clF;
		this->clipNear = clN;

		this->projectionHeight = projH;
		this->projectionWidth = projW;
	}

	CameraController::~CameraController() {

	}

	CameraController* CameraController::clone() const {
		return new CameraController(*this);
	}

	CameraController* CameraController::getActiveCamera() {
		return activeCamera;
	}

	const CameraController::CameraType& CameraController::getCameraType() 
			const {
		return this->type;
	}

	const float& CameraController::getClipFar() const {
		return this->clipFar;
	}

	const float& CameraController::getClipNear() const {
		return this->clipNear;
	}

	const float& CameraController::getTypeParameter() const {
		return this->typeParameter;
	}

	const Matrix4f& CameraController::getProjection() const {
		return this->projection;
	}

	const float& CameraController::getProjectionHeight() const {
		return this->projectionHeight;
	}

	const Matrix4f& CameraController::getProjectionOrientation() const {
		return this->projectionOrien;
	}

	const Matrix4f& CameraController::getProjectionTranslation() const {
		return this->projectionTrans;
	}

	const Matrix4f& CameraController::getProjectionView() const {
		return this->projectionView;
	}

	const float& CameraController::getProjectionWidth() const {
		return this->projectionWidth;
	}

	void CameraController::setActive() {
		this->isActive = true;

		if (CameraController::activeCamera != nullptr)
			CameraController::activeCamera->stop();
		CameraController::activeCamera = this;
	}

	void CameraController::setProjectionSize(float h, float w) {
		// Write the new values into the Camera instance
		this->projectionHeight = h;
		this->projectionWidth = w;

		this->calcProjection(); // Recalculate the Projection
	}

	void CameraController::setProjectionSizeToWindow() {
		this->setProjectionSize(
			(float)GameWindow::getGameWindow()->getWindowHeight(),
			(float)GameWindow::getGameWindow()->getWindowWidth());
	}

	void CameraController::start() {
		this->transform = this->getAttached()->getComponent<Transform>();

		// Calculate the initial projection orientation, translation and view
		// matricies; use the matricies to calculate the projection matrix.
		this->calcProjectionOrientation();
		this->calcProjectionTranslation();
		this->calcProjectionView();
		this->calcProjection();

		// Create an event for window resize; set the projection size and
		// recalculate the projection view and projection when it occurs.
		this->windowResizeHandler.addAction(
			std::bind(&CameraController::setProjectionSizeToWindow, this));
		GameWindow::getGameWindow()->getResizeEvent().addEventHandler(
			this->windowResizeHandler);
		this->windowResizeHandler.addAction(
			std::bind(&CameraController::calcProjectionView, this));
		this->windowResizeHandler.addAction(
			std::bind(&CameraController::calcProjection, this));

		// Create an event for transform change; recalculate the orientation,
		// translation and projection when it occurs.
		this->transformChangeHandler.addAction(
			std::bind(&CameraController::calcProjectionOrientation, this));
		this->transformChangeHandler.addAction(
			std::bind(&CameraController::calcProjectionTranslation, this));
		this->transformChangeHandler.addAction(
			std::bind(&CameraController::calcProjection, this));
		this->transform->getChangedEvent().addEventHandler(
			this->transformChangeHandler);

		this->setActive();
	}

	void CameraController::update() {
		
	}

	const Matrix4f& CameraController::calcProjection() {
		this->projection = this->getProjectionView() *
			this->getProjectionOrientation() *
			this->getProjectionTranslation();

		this->glFloats.setValue(CameraController::WIDTH_F,
			this->projectionWidth);
		this->glFloats.setValue(CameraController::HEIGHT_F,
			this->projectionHeight);
		this->glMatrix4fs.setValue(CameraController::PROJECTION_MAT4,
			this->projection);
		this->glVector3fs.setValue(CameraController::TRANSLATION_VEC3,
			this->transform->getTranslation());

		return this->getProjection();
	}

	const Matrix4f& CameraController::calcProjectionOrientation() {
		this->projectionOrien = this->transform->getOrientationMatrix();

		// Negate the local forwards of the camera since the camera faces the
		// opposite direction as the objects when rendering them.
		this->projectionOrien.setAt(2, 0, -this->projectionOrien.getAt(2, 0));
		this->projectionOrien.setAt(2, 1, -this->projectionOrien.getAt(2, 1));
		this->projectionOrien.setAt(2, 2, -this->projectionOrien.getAt(2, 2));

		return this->projectionOrien;
	}

	const Matrix4f& CameraController::calcProjectionViewOrthographic() {
		// Mathematics Explanation From:
		// www.scratchapixel.com/lessons/3d-basic-rendering/
		// perspective-and-orthographic-projection-matrix

		// Calculate the "top" and "right" sections of the projection. Since 
		// the viewport is divided into positive and negative sides, the top 
		// and right must be halfed. Additionally, left and bottom are not
		// needed since bot == -top and left == -right.
		float top = projectionHeight / projectionWidth * typeParameter;
		float right = projectionWidth / projectionHeight * typeParameter;

		// Variables which will go inside of the Camera Projection Matrix.
		float pmA = 1 / right;
		float pmB = 1 / top;
		float pmC = -2 / (clipFar - clipNear);
		float pmD = -(clipFar + clipNear) / (clipFar - clipNear);

		// Construct the Projection Matrix:
		this->projectionView = Matrix4f::identity();
		this->projectionView.setAt(0, 0, pmA);		// [ A  0  0  0 ]
		this->projectionView.setAt(1, 1, pmB);		// [ 0  B  0  0 ]
		this->projectionView.setAt(2, 2, pmC);		// [ 0  0  C  D ]
		this->projectionView.setAt(2, 3, pmD);		// [ 0  0  0  1 ]

		return this->projectionView;
	}

	const Matrix4f& CameraController::calcProjectionViewPerspective() {
		// Mathematics Explanation From:
		// www.scratchapixel.com/lessons/3d-basic-rendering/
		// perspective-and-orthographic-projection-matrix

		float aR = projectionWidth / projectionHeight; // Aspect Ratio
		float tanHalfFOV = // Tangent of the Field of View Halved
			tan(degToRad(typeParameter / 2));

		// Calculate the "top" section of the projection. Since the projection
		// is symmetric (top == -bot), there is no need for the other sections 
		// of the projection.
		float top = tanHalfFOV * clipNear;

		// Variables which will go inside of the Camera Projection Matrix.
		float pmA = clipNear / (top * aR);
		float pmB = clipNear / top;
		float pmC = -(clipFar + clipNear) / (clipFar - clipNear);
		float pmD = -2 * clipNear * clipFar / (clipFar - clipNear);

		// Construct the Projection Matrix:
		this->projectionView = Matrix4f::identity();
		this->projectionView.setAt(0, 0, pmA);		// [ A  0  0  0 ]
		this->projectionView.setAt(1, 1, pmB);		// [ 0  B  0  0 ]
		this->projectionView.setAt(2, 2, pmC);		// [ 0  0  C  D ]
		this->projectionView.setAt(2, 3, pmD);		// [ 0  0 -1  0 ]
		this->projectionView.setAt(3, 2, -1.0F);
		this->projectionView.setAt(3, 3, 0.0F);

		return this->projectionView;
	}

	const Matrix4f& CameraController::calcProjectionTranslation() {
		this->projectionTrans = this->transform->getTranslationMatrix();

		// Negate the local forwards of the camera since the camera faces the
		// opposite direction as the objects when rendering them.
		this->projectionTrans.setAt(0, 3, -this->projectionTrans.getAt(0, 3));
		this->projectionTrans.setAt(1, 3, -this->projectionTrans.getAt(1, 3));
		this->projectionTrans.setAt(2, 3, -this->projectionTrans.getAt(2, 3));

		return this->projectionTrans;
	}

	const Matrix4f& CameraController::calcProjectionView() {
		// Call the appropriate matrix projection calculation method according
		// to the type of Camera.
		switch (this->type) {
		case CameraType::PERSPECTIVE:
			this->projectionView = this->calcProjectionViewPerspective();
			break;
		case CameraType::ORTHOGRAPHIC:
			this->projectionView = this->calcProjectionViewOrthographic();
			break;
		}

		return this->projectionView;
	}
}
