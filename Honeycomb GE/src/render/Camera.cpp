#include "..\..\include\render\Camera.h"
#include "..\..\include\math\MathUtils.h"

#include <math.h>
#include <iostream>

using Honeycomb::Math::Matrix4f;
using Honeycomb::Object::Transform;
using namespace Honeycomb::Math::Utils;

namespace Honeycomb::Render {
	Camera::Camera(CameraType cT, float clF, float clN, float cTP, float projH,
			float projW) : Component("Camera") {
		this->type = cT;
		this->clipFar = clF;
		this->clipNear = clN;
		this->typeParameter = cTP;
		this->projectionHeight = projH;
		this->projectionWidth = projW;
	}

	Camera::~Camera() {

	}

	Camera::CameraType Camera::getCameraType() {
		return this->type;
	}

	float Camera::getClipFar() {
		return this->clipFar;
	}

	float Camera::getClipNear() {
		return this->clipNear;
	}

	float Camera::getTypeParameter() {
		return this->typeParameter;
	}

	Matrix4f Camera::getProjection() {
		return this->projection;
	}

	float Camera::getProjectionHeight() {
		return this->projectionHeight;
	}

	Honeycomb::Math::Matrix4f Camera::getProjectionOrientation() {
		return this->calcProjectionOrientation();
		// return this->projectionOrien; // TODO: Don't recalculate each time!!!
	}

	Honeycomb::Math::Matrix4f Camera::getProjectionTranslation() {
		return this->calcProjectionTranslation();
		// return this->projectionTrans; // TODO: Don't recalculate each time!!!
	}

	float Camera::getProjectionWidth() {
		return this->projectionWidth;
	}

	void Camera::setProjectionSize(int h, int w) {
		// Write the new values into the Camera instance
		this->projectionHeight = h;
		this->projectionWidth = w;
		
		this->calcProjection(); // Recalculate the Projection
	}

	void Camera::start() {
		this->calcProjection();
		this->calcProjectionOrientation();
		this->calcProjectionTranslation();
	}

	Matrix4f Camera::calcProjection() {
		// Call the appropriate matrix projection calculation method according
		// to the type of Camera.
		switch (this->type) {
		case CameraType::PERSPECTIVE:
			return this->calcProjectionPerspective();
		case CameraType::ORTHOGRAPHIC:
			return this->calcProjectionOrthographic();
		default:
			return this->getProjection();
		}
	}

	Matrix4f Camera::calcProjectionOrientation() {
		this->projectionOrien = this->getAttached()->
			getComponentOfType<Transform>("Transform")->getOrientationMatrix();

		// Negate the local forwards of the camera since the camera faces the
		// opposite direction as the objects when rendering them.
		this->projectionOrien.setAt(2, 0, -this->projectionOrien.getAt(2, 0));
		this->projectionOrien.setAt(2, 1, -this->projectionOrien.getAt(2, 1));
		this->projectionOrien.setAt(2, 2, -this->projectionOrien.getAt(2, 2));

		return this->projectionOrien;
	}

	Matrix4f Camera::calcProjectionOrthographic() {
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
		this->projection.setAt(3, 3, 1.0F);

		return this->projection;
	}

	Matrix4f Camera::calcProjectionPerspective() {
		// Mathematics Explanation From:
		// www.scratchapixel.com/lessons/3d-basic-rendering/
		// perspective-and-orthographic-projection-matrix

		float aR = projectionWidth / projectionHeight; // Aspect Ratio
		float tanHalfFOV = // Tangent of the Field of View Halved
			tan(degToRad(typeParameter / 2));
		
		// Calculate the "top" section of the projection. Since the projection
		// is symmetric (top == -bot, left == -right), there is no need for the
		// other sections of the projection.
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

	Matrix4f Camera::calcProjectionTranslation() {
		this->projectionTrans = this->getAttached()->
			getComponentOfType<Transform>("Transform")->getTranslationMatrix();

		// Negate the local forwards of the camera since the camera faces the
		// opposite direction as the objects when rendering them.
		this->projectionTrans.setAt(0, 3, -this->projectionTrans.getAt(0, 3));
		this->projectionTrans.setAt(1, 3, -this->projectionTrans.getAt(1, 3));
		this->projectionTrans.setAt(2, 3, -this->projectionTrans.getAt(2, 3));

		return this->projectionTrans;
	}
}