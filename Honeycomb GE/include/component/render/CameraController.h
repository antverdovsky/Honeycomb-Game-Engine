#pragma once
#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "../GameComponent.h"
#include "../../../include/component/physics/Transform.h"
#include "../../../include/conjuncture/EventHandler.h"
#include "../../../include/math/Matrix4f.h"
#include "../../../include/object/GameObject.h"
#include "../../shader/GenericStruct.h"

namespace Honeycomb { namespace Component { namespace Render {
	class CameraController : 
			public GameComponent,
			public Honeycomb::Shader::GenericStruct {
	public:
		const static std::string PROJECTION_MAT4;
		const static std::string VIEW_MAT4;
		const static std::string TRANSLATION_VEC3;
		const static std::string WIDTH_F;
		const static std::string HEIGHT_F;

		enum CameraType { // The type of camera (Orthographic or Perspective)
			ORTHOGRAPHIC,
			PERSPECTIVE
		};

		/// Initializes a new Perspective camera, with 1000.0F and 0.03F for 
		/// the far and near clipping planes, respectively; 1.31F radians FOV,
		/// and the window size for the projection width and height.
		CameraController();

		/// Initializes a new Camera instance.
		/// cosnt CameraType &cT : The camera type.
		/// const float &cTP : The camera type parameter. If the Camera Type is
		///					   set to perspective, this is the FOV. If the 
		///					   Camera Type is set to orthographic, this is the 
		///					   orthographic size.
		/// const float &clF : The far clipping plane.
		/// const float &clN : The near clipping plane.
		/// const float &projH : The camera projection height.
		/// const float &projW : The camera projection width.
		CameraController(const CameraType &cT, const float &cTP, 
			const float &clF, const float &clN, const float &projH, 
			const float &projW);

		/// Destroys this Camera instance.
		~CameraController() override;

		/// Clones this Camera Controller into a new, dynamically allocated 
		/// Camera Controller. This function should be used instead of the copy
		/// constructor to prevent object slicing.
		/// return : The cloned Transform.
		std::unique_ptr<CameraController> clone() const;

		/// Gets the current active camera instance.
		static CameraController* getActiveCamera();

		/// Gets the camera type (Orthographic / Perspective).
		/// return : The constant reference to the camera type.
		const CameraType& getCameraType() const;

		/// Gets the far clipping plane for this camera.
		/// return : The constant reference to the far clipping plane.
		const float& getClipFar() const;

		/// Gets the near clipping plane for this camera.
		/// return : The constant reference to the near clipping plane.
		const float& getClipNear() const;

		/// <summary>
		/// Returns the Component ID integer representation of the Camera
		/// Controller.
		/// </summary>
		/// <returns>
		/// The Component ID of the Camera Controller Component.
		/// </returns>
		virtual GameComponentID getGameComponentID() const noexcept override;

		/// Gets the type parameter for the camera. If this is a perspective
		/// camera, the parameter is equal to the FOV (in degrees). Otherwise,
		/// the parameter is equal to the orthographic size.
		/// return : The constant reference to the type parameter.
		const float& getTypeParameter() const;

		/// Gets the projection matrix for this camera. The projection matrix
		/// is comprised of the camera projection view matrix multiplied by the 
		/// camera orientation matrix multiplied by the camera translation
		/// matrix.
		/// return : The constant reference to the projection matrix.
		const Honeycomb::Math::Matrix4f& getProjection() const;

		/// Gets the projection height for this camera.
		/// return : The constant reference to the projection height.
		const float& getProjectionHeight() const;

		/// Gets the projection orientation matrix for this camera. This method
		/// should be used instead of the Transformation's orientation method
		/// for projection matricies, as this matrix is correctly negated.
		/// return : The constant reference to the projection orientation 
		///			 matrix.
		const Honeycomb::Math::Matrix4f& getProjectionOrientation() const;

		/// Gets the projection translation matrix for this camera. This method
		/// should be used instead of the Transformation's translation method
		/// for projection matricies, as this matrix is correctly negated.
		/// return : The constant reference to the projection translation 
		///			 matrix.
		const Honeycomb::Math::Matrix4f& getProjectionTranslation() const;

		/// Gets the projection matrix for this camera.
		/// return : The constant reference to the projection matrix.
		const Honeycomb::Math::Matrix4f& getProjectionView() const;

		/// Gets the projection width for this camera.
		/// return : The constant reference to the projection width.
		const float& getProjectionWidth() const;

		/// <summary>
		/// When the Camera Controller is attached to a Game Object, it creates
		/// a reference to the Transform of the Game Object.
		/// </summary>
		void onAttach() override;

		/// <summary>
		/// When the Camera Controller is detached from a Game Object, it loses
		/// the reference to the Transform of the Game Object.
		/// </summary>
		void onDetach() override;

		/// Sets the projection width and height for the Camera. The projection
		/// matrix will be automatically updated.
		/// float h : The new height of the projection size.
		/// float w : The new width of the projection size.
		void setProjectionSize(float h, float w);

		/// Sets the projection width and height for the Camera to the current
		/// game window width and height. The projection matrix will be 
		/// automatically updated.
		void setProjectionSizeToWindow();
	private:
		static CameraController *activeCamera; // The active camera

		const static std::string STRUCT_FILE;
		const static std::string STRUCT_NAME;

		CameraType type;			// The type of Camera (Persp / Ortho)
		float clipFar;				// The far clipping plane
		float clipNear;				// The near clipping plane
		float typeParameter;		// The Camera Type parameter (FOV / Ortho)
		float projectionHeight;		// The projection height
		float projectionWidth;		// The projection width

		Honeycomb::Conjuncture::EventHandler 
			windowResizeHandler; // Handles the window resize event
		Honeycomb::Conjuncture::EventHandler
			transformChangeHandler; // Handles the transform change event

		// Transform of the game object this camera is attached to
		Honeycomb::Component::Physics::Transform *transform;

		Honeycomb::Math::Matrix4f projection; // Stores the Projection

		Honeycomb::Math::Matrix4f projectionView; // Projection View (P / O)
		Honeycomb::Math::Matrix4f projectionOrien; // Orientation Projection
		Honeycomb::Math::Matrix4f projectionTrans; // Translation Projection

		/// Calculates (or recalculates) either the perspective or the
		/// orthographic projection matrix for this camera, depending on its
		/// type.
		/// return : The constant reference to the projection matrix.
		const Honeycomb::Math::Matrix4f& calcProjection();

		/// Calculates (or recalculates) the orientation projection for this
		/// camera. This corrects the transformation orientation projection
		/// matrix by negating quantities which cause the world to rotate 
		/// opposite of the camera, creating the illusion that the camera is
		/// rotating.
		/// return : The constant reference to the projection orientation
		///			 matrix.
		const Honeycomb::Math::Matrix4f& calcProjectionOrientation();

		/// Calculates (or recalculates) the orthographic projection matrix for
		/// this camera and stores it into the projection view matrix variable.
		/// return : The constant reference to the orthographic view projection
		///			 matrix.
		const Honeycomb::Math::Matrix4f& calcProjectionViewOrthographic();

		/// Calculates (or recalculates) the perspective projection matrix for 
		/// this camera and stores it into the projection view matrix variable.
		/// return : The constant reference to the perspective view projection
		///			 matrix.
		const Honeycomb::Math::Matrix4f& calcProjectionViewPerspective();

		/// Calculates (or recalculates) the translation projection for this
		/// camera. This corrects the transformation translation projection
		/// matrix by negating quantities which cause the world to move 
		/// opposite of the camera, creating the illusion that the camera is
		/// moving.
		/// return : The constant reference to the projection translation 
		///			 matrix.
		const Honeycomb::Math::Matrix4f& calcProjectionTranslation();

		/// Calculates (or recalculates) the projection view for this camera,
		/// and stores it into the projection view matrix variable. The type
		/// of projection calculated depends on the type for which the camera 
		/// is configured.
		/// return : The constant reference to the view projection matrix.
		const Honeycomb::Math::Matrix4f& calcProjectionView();

		virtual CameraController* cloneInternal() const override;
	};
} } }

#endif
