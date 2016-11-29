#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "..\GameComponent.h"
#include "..\..\..\include\component\physics\Transform.h"
#include "..\..\..\include\conjuncture\EventHandler.h"
#include "..\..\..\include\math\Matrix4f.h"
#include "..\..\..\include\object\GameObject.h"

namespace Honeycomb::Component::Render {
	class CameraController : public GameComponent {
	public:
		enum CameraType { // The type of camera (Orthographic or Perspective)
			ORTHOGRAPHIC,
			PERSPECTIVE
		};

		/// Initializes a new Perspective camera, with 100.0F and 0.03F for the
		/// far and near clipping planes, respectively; 75.0F degrees FOV;
		/// and the window size for the projection width and height.
		CameraController();

		/// Initializes a new Camera instance.
		/// CameraType cT : The camera type.
		/// float cTP : The camera type parameter. If the Camera Type is set to
		///				perspective, this is the FOV. If the Camera Type is set
		///				to orthographic, this is the orthographic size.
		/// float clF : The far clipping plane.
		/// float clN : The near clipping plane.
		/// float projH : The camera projection height.
		/// float projW : The camera projection width.
		CameraController(const CameraType &cT, const float &cTP, 
			const float &clF, const float &clN, const float &projH, 
			const float &projW);

		/// Destroys this Camera instance.
		~CameraController();

		/// Clones this Camera Controller into a new, dynamically allocated 
		/// Camera Controller. This function should be used instead of the copy
		/// constructor to prevent object slicing.
		/// return : The cloned Transform.
		CameraController* CameraController::clone() const;

		/// Gets the current active camera instance.
		static CameraController* getActiveCamera();

		/// Gets the camera type (Ortho / Persp).
		/// return : The camera type.
		const CameraType& getCameraType() const;

		/// Gets the far clipping plane for this camera.
		/// return : The far clipping plane.
		const float& getClipFar() const;

		/// Gets the near clipping plane for this camera.
		/// return : The near clipping plane.
		const float& getClipNear() const;

		/// Gets the type parameter for the camera. If this is a perspective
		/// camera, the parameter is equal to the FOV (in degrees). Otherwise,
		/// the parameter is equal to the orthographic size.
		/// return : The type parameter.
		const float& getTypeParameter() const;

		/// Gets the projection matrix for this camera. The projection matrix
		/// is comprised of the camera projection view matrix multiplied by the 
		/// camera orientation matrix multiplied by the camera translation
		/// matrix.
		/// return : The projection matrix.
		const Honeycomb::Math::Matrix4f& getProjection() const;

		/// Gets the projection height for this camera.
		/// return : The projection height.
		const float& getProjectionHeight() const;

		/// Gets the projection orientation matrix for this camera. This method
		/// should be used instead of the Transformation's orientation method
		/// for projection matricies, as this matrix is correctly negated.
		/// return : The projection orientation matrix.
		const Honeycomb::Math::Matrix4f& getProjectionOrientation() const;

		/// Gets the projection translation matrix for this camera. This method
		/// should be used instead of the Transformation's translation method
		/// for projection matricies, as this matrix is correctly negated.
		/// return : The projection translation matrix.
		const Honeycomb::Math::Matrix4f& getProjectionTranslation() const;

		/// Gets the projection matrix for this camera.
		/// return : The projection matrix.
		const Honeycomb::Math::Matrix4f& getProjectionView() const;

		/// Gets the projection width for this camera.
		/// return : The projection width.
		const float& getProjectionWidth() const;

		/// Sets this camera as the active world camera. There can only be one
		/// active world camera, so this camera will replace the existing
		/// active camera as the new active camera.
		void setActive();

		/// Sets the projection width and height for the Camera.
		/// int h : The new height of the projection size.
		/// int w : The new width of the projection size.
		void setProjectionSize(int h, int w);

		/// Sets the projection width and height for the Camera to the current
		/// window width and height.
		void setProjectionSizeToWindow();

		/// Starts this camera component. When started, this camera will become
		/// the active world camera.
		void start();

		/// Updates this camera instance.
		void update();
	private:
		static CameraController *activeCamera; // The active camera

		CameraType type = PERSPECTIVE; // The type of Camera (Persp / Ortho)
		float clipFar = 1000.0F; // The far clipping plane
		float clipNear = 0.1F; // The near clipping plane
		float typeParameter = 75.0F; // The Camera Type parameter (FOV / Ortho)
		float projectionHeight = 1.0F; // The projection height
		float projectionWidth = 1.0F; // The projection width

		Honeycomb::Conjuncture::EventHandler 
			windowResizeHandler; // Handles window resize event
		Honeycomb::Conjuncture::EventHandler
			transformChangeHandler; // Handles transform change event

		// Transform of the game object this camera is attached to
		Honeycomb::Component::Physics::Transform *transform;

		Honeycomb::Math::Matrix4f projection; // Stores the Projection

		Honeycomb::Math::Matrix4f projectionView; // Projection View (P / O)
		Honeycomb::Math::Matrix4f projectionOrien; // Orientation Projection
		Honeycomb::Math::Matrix4f projectionTrans; // Translation Projection

		/// Calculates (or recalculates) either the perspective or the
		/// orthographic projection matrix for this camera, depending on its
		/// type.
		/// return : The projection matrix.
		const Honeycomb::Math::Matrix4f& calcProjection();

		/// Calculates (or recalculates) the orientation projection for this
		/// camera. This corrects the transformation orientation projection
		/// matrix by negating quantities which cause the world to rotate 
		/// opposite of the camera, creating the illusion that the camera is
		/// rotating.
		const Honeycomb::Math::Matrix4f& calcProjectionOrientation();

		/// Calculates (or recalculates) the orthographic projection matrix for
		/// this camera and stores it into the projection view matrix variable.
		/// return : The projection view matrix.
		const Honeycomb::Math::Matrix4f& calcProjectionOrthographic();

		/// Calculates (or recalculates) the perspective projection matrix for 
		/// this camera and stores it into the projection view matrix variable.
		/// return : The projection view matrix.
		const Honeycomb::Math::Matrix4f& calcProjectionPerspective();

		/// Calculates (or recalculates) the translation projection for this
		/// camera. This corrects the transformation translation projection
		/// matrix by negating quantities which cause the world to move 
		/// opposite of the camera, creating the illusion that the camera is
		/// moving.
		const Honeycomb::Math::Matrix4f& calcProjectionTranslation();

		/// Calculates (or recalculates) the projection view for this camera,
		/// and stores it into the projection view matrix variable. The type
		/// of projection calculated depends on the type for which the camera 
		/// is configured.
		const Honeycomb::Math::Matrix4f& calcProjectionView();
	};
}

#endif