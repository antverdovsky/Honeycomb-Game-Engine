#include "..\..\include\render\Camera.h"

#include <math.h>
#include <iostream>

using Honeycomb::Math::Matrix4f;

namespace Honeycomb::Render {
	Camera::Camera(float clF, float clN, float fov, float projH, float projW)
		: projection() {
		this->clipFar = clF;
		this->clipNear = clN;
		this->fieldOfView = fov;
		this->projectionHeight = projH;
		this->projectionWidth = projW;

		this->calcProjectionPerspective();
	}

	Camera::~Camera() {
		//delete this->projection;
	}

	float Camera::getClipFar() {
		return this->clipFar;
	}

	float Camera::getClipNear() {
		return this->clipNear;
	}

	float Camera::getFieldOfView() {
		return this->fieldOfView;
	}

	Matrix4f Camera::getProjection() {
		return this->projection;
	}

	float Camera::getProjectionHeight() {
		return this->projectionHeight;
	}

	float Camera::getProjectionWidth() {
		return this->projectionWidth;
	}

	Matrix4f Camera::calcProjectionPerspective() {
		// Mathematics Explanation From:
		// www.scratchapixel.com/lessons/3d-basic-rendering/
		// perspective-and-orthographic-projection-matrix

		float aR = projectionWidth / projectionHeight; // Aspect Ratio
		float tanHalfFOV = // Tangent of the Field of View Halved
			tan(fieldOfView * (atan(1) * 4) / 180 / 2); // (atan(1) * 4) = pi
		
		// Variables which will go inside of the Camera Projection Matrix.
		float pmB = 1 / tanHalfFOV;
		float pmA = pmB / aR;
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
}