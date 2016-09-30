#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "..\..\include\math\Matrix4f.h"

namespace Honeycomb::Math { class Matrix4f; }

namespace Honeycomb::Render {
	class Camera {
	public:
		/// Initializes a new Camera instance.
		/// float clF : The far clipping plane.
		/// float clN : The near clipping plane.
		/// float fov : The field of view (in degrees).
		/// float projH : The camera projection height.
		/// float projW : The camera projection width.
		Camera(float clF, float clN, float fov, float projH, float projW);

		/// Destroys this Camera instance.
		~Camera();

		/// Gets the far clipping plane for this camera.
		/// return : The far clipping plane.
		float getClipFar();

		/// Gets the near clipping plane for this camera.
		/// return : The near clipping plane.
		float getClipNear();

		/// Gets the field of view for this camera.
		/// return : The field of view (in degrees).
		float getFieldOfView();

		/// Gets the projection matrix for this camera.
		/// return : The projection matrix.
		Honeycomb::Math::Matrix4f getProjection();

		/// Gets the projection height for this camera.
		/// return : The projection height.
		float getProjectionHeight();

		/// Gets the projection width for this camera.
		/// return : The projection width.
		float getProjectionWidth();
	private:
		float clipFar = 1000.0F; // The far clipping plane
		float clipNear = 0.1F; // The near clipping plane
		float fieldOfView = 75.0F; // The field of view (in degrees)
		float projectionHeight = 1.0F; // The projection height
		float projectionWidth = 1.0F; // The projection width

		Honeycomb::Math::Matrix4f projection; // Stores the projection

		/// Calculates (or recalculates) the perspective projection matrix for 
		/// this camera, and stores it into the projection matrix variable.
		/// return : The projection matrix.
		Honeycomb::Math::Matrix4f calcProjectionPerspective();
	};
}

#endif