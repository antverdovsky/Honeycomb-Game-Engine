#include "..\..\..\include\component\render\CameraController.h";

#include <math.h>
#include <iostream>

#include "..\..\..\include\base\GameWindow.h"
#include "..\..\..\include\math\MathUtils.h"
#include "..\..\..\include\shader\ShaderProgram.h"

using Honeycomb::Base::GameWindow;
using Honeycomb::Component::Physics::Transform;
using Honeycomb::Conjuncture::EventHandler;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Shader::ShaderProgram;

using namespace Honeycomb::Math::Utils;

namespace Honeycomb::Component::Render {
	CameraController *CameraController::activeCamera = nullptr;

	CameraController::CameraController(CameraType cT, float clF, float clN,
			float cTP, float projH, float projW) : GameComponent("Camera") {
		this->type = cT;
		this->clipFar = clF;
		this->clipNear = clN;
		this->typeParameter = cTP;
		this->projectionHeight = projH;
		this->projectionWidth = projW;
	}

	CameraController::~CameraController() {

	}

	CameraController* CameraController::clone() {
		return new CameraController(*this);
	}

	CameraController* CameraController::getActiveCamera() {
		return activeCamera;
	}

	CameraController::CameraType CameraController::getCameraType() {
		return this->type;
	}

	float CameraController::getClipFar() {
		return this->clipFar;
	}

	float CameraController::getClipNear() {
		return this->clipNear;
	}

	float CameraController::getTypeParameter() {
		return this->typeParameter;
	}

	Matrix4f CameraController::getProjection() {
		return this->projection;
	}

	float CameraController::getProjectionHeight() {
		return this->projectionHeight;
	}

	Honeycomb::Math::Matrix4f CameraController::getProjectionOrientation() {
		return this->projectionOrien;
	}

	Honeycomb::Math::Matrix4f CameraController::getProjectionTranslation() {
		return this->projectionTrans;
	}

	float CameraController::getProjectionWidth() {
		return this->projectionWidth;
	}

	void CameraController::setActive() {
		this->isActive = true;

		if (CameraController::activeCamera != nullptr)
			CameraController::activeCamera->stop();
		CameraController::activeCamera = this;
	}

	void CameraController::setProjectionSize(int h, int w) {
		// Write the new values into the Camera instance
		this->projectionHeight = h;
		this->projectionWidth = w;

		this->calcProjection(); // Recalculate the Projection
	}

	void CameraController::setProjectionSizeToWindow() {
		this->setProjectionSize(GameWindow::getGameWindow()->getWindowHeight(),
			GameWindow::getGameWindow()->getWindowWidth());
	}

	void CameraController::start() {
		this->transform = this->getAttached()->
			getComponentOfType<Transform>("Transform");

		this->calcProjection();
		this->calcProjectionOrientation();
		this->calcProjectionTranslation();

		this->windowResizeHandler.addAction(
			std::bind(&CameraController::setProjectionSizeToWindow, this));
		GameWindow::getGameWindow()->getResizeEvent().addEventHandler(
			&this->windowResizeHandler);

		this->transformChangeHandler.addAction(
			std::bind(&CameraController::calcProjectionOrientation, this));
		this->transformChangeHandler.addAction(
			std::bind(&CameraController::calcProjectionTranslation, this));
		this->transform->getChangedEvent().addEventHandler(
			&this->transformChangeHandler);

		this->setActive();
	}

	void CameraController::update() {
		if (!this->isActive) return;
	}

	Matrix4f CameraController::calcProjection() {
		// Call the appropriate matrix projection calculation method according
		// to the type of Camera.
		switch (this->type) {
		case CameraType::PERSPECTIVE:
			this->calcProjectionPerspective();
			break;
		case CameraType::ORTHOGRAPHIC:
			this->calcProjectionOrthographic();
			break;
		}

		ShaderProgram::getActiveShader()->setUniform_mat4("camProjection",
			this->getProjection());

		return this->getProjection();
	}

	Matrix4f CameraController::calcProjectionOrientation() {
		this->projectionOrien = this->transform->getOrientationMatrix();

		// Negate the local forwards of the camera since the camera faces the
		// opposite direction as the objects when rendering them.
		this->projectionOrien.setAt(2, 0, -this->projectionOrien.getAt(2, 0));
		this->projectionOrien.setAt(2, 1, -this->projectionOrien.getAt(2, 1));
		this->projectionOrien.setAt(2, 2, -this->projectionOrien.getAt(2, 2));
		
		ShaderProgram::getActiveShader()->setUniform_mat4("camOrientation",
			this->getProjectionOrientation());

		return this->projectionOrien;
	}

	Matrix4f CameraController::calcProjectionOrthographic() {
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
		this->projection = Matrix4f::identity();
		this->projection.setAt(0, 0, pmA);		// [ A  0  0  0 ]
		this->projection.setAt(1, 1, pmB);		// [ 0  B  0  0 ]
		this->projection.setAt(2, 2, pmC);		// [ 0  0  C  D ]
		this->projection.setAt(2, 3, pmD);		// [ 0  0  0  1 ]

		return this->projection;
	}

	Matrix4f CameraController::calcProjectionPerspective() {
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
		this->projection = Matrix4f::identity();
		this->projection.setAt(0, 0, pmA);		// [ A  0  0  0 ]
		this->projection.setAt(1, 1, pmB);		// [ 0  B  0  0 ]
		this->projection.setAt(2, 2, pmC);		// [ 0  0  C  D ]
		this->projection.setAt(2, 3, pmD);		// [ 0  0 -1  0 ]
		this->projection.setAt(3, 2, -1.0F);
		this->projection.setAt(3, 3, 0.0F);

		return this->projection;
	}

	Matrix4f CameraController::calcProjectionTranslation() {
		this->projectionTrans = this->transform->getTranslationMatrix();

		// Negate the local forwards of the camera since the camera faces the
		// opposite direction as the objects when rendering them.
		this->projectionTrans.setAt(0, 3, -this->projectionTrans.getAt(0, 3));
		this->projectionTrans.setAt(1, 3, -this->projectionTrans.getAt(1, 3));
		this->projectionTrans.setAt(2, 3, -this->projectionTrans.getAt(2, 3));

		ShaderProgram::getActiveShader()->setUniform_mat4("camTranslation",
			this->getProjectionTranslation());
		ShaderProgram::getActiveShader()->setUniform_vec3("cameraPos",
			this->transform->getTranslation());

		return this->projectionTrans;
	}
}
