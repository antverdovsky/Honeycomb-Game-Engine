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

		/// <summary>
		/// Returns the pointer to the active camera.
		/// </summary>
		/// <returns>
		/// The pointer to the active camera, or null if there is no active
		/// camera.
		/// </returns>
		static CameraController* getActiveCamera();

		/// <summary>
		/// The enumeration of the different types of camera projections.
		/// </summary>
		enum ProjectionType {
			ORTHOGRAPHIC,
			PERSPECTIVE
		};

		/// <summary>
		/// Initializes a new perspective camera. The camera component is built
		/// with a 1000.0F far clipping plane, a 0.03F near clipping plane, 
		/// 1.31F radians field of view and the window size for the projection
		/// width and height. The camere's size will automatically adjust to
		/// fit any window resizes.
		/// </summary>
		CameraController();

		/// <summary>
		/// Initializes a new perspective camera using the specified values.
		/// </summary>
		/// <param name="cT">
		/// The camera projection type.
		/// </param>
		/// <param name="cTP">
		/// The projection parameter. If the camera is a perspective camera, 
		/// this is the field of view of the camera, in radians. If the camera
		/// is an orthographic camera, this is the orthographic size of the 
		/// camera.
		/// </param>
		/// <param name="clF">
		/// The far clipping plane value.
		/// </param>
		/// <param name="clN">
		/// The near clipping plane value.
		/// </param>
		/// <param name="projH">
		/// The initial camera projection height.
		/// </param>
		/// <param name="projW">
		/// The initial camera projection width.
		/// </param>
		/// <param name="fit">
		/// Should the projection width and height be equivalent to the window
		/// width and height always? Note that this will automatically resize
		/// the camera width and height each time the window is resized.
		/// </param>
		CameraController(const ProjectionType &cT, const float &cTP, 
			const float &clF, const float &clN, const float &projH, 
			const float &projW, const bool &fit = true);

		/// <summary>
		/// Clones this Camera Controller into a new, independent Camera
		/// Controller component.
		/// </summary>
		/// <returns>
		/// The unique pointer to the camera controller.
		/// </returns>
		std::unique_ptr<CameraController> clone() const;

		/// <summary>
		/// Returns the far clipping value of the camera.
		/// </summary>
		/// <returns>
		/// The far clipping value.
		/// </returns>
		const float& getClipFar() const;

		/// <summary>
		/// Returns the near clipping value of the camera.
		/// </summary>
		/// <returns>
		/// The near clipping value.
		/// </returns>
		const float& getClipNear() const;

		/// <summary>
		/// Gets a boolean representing whether or not this Camera 
		/// automatically resizes its size to fit the game window when the game
		/// window is resized.
		/// </summary>
		/// <returns>
		/// True if the Camera automatically resizes on a window resize event,
		/// false otherwise.
		/// </returns>
		const bool& getFitToWindow() const;

		/// <summary>
		/// Returns the Component ID integer representation of the Camera
		/// Controller.
		/// </summary>
		/// <returns>
		/// The Component ID of the Camera Controller Component.
		/// </returns>
		virtual GameComponentID getGameComponentID() const noexcept override;

		/// <summary>
		/// Checks if this Camera Controller is active.
		/// </summary>
		/// <returns>
		/// True if this is the active Camera Controller, false otherwise.
		/// </returns>
		bool getIsActive() const;

		/// <summary>
		/// Returns the projection parameter of this camera. If the projection 
		/// is orthographic, this is the orthographic size of the camera. If 
		/// the projection is perspective, this is the field of view of the
		/// camera.
		/// </summary>
		/// <returns>
		/// The projection parameter value.
		/// </returns>
		const float& getProjectionParameter() const;

		/// <summary>
		/// Returns the projection matrix of the camera.
		/// </summary>
		/// <returns></returns>
		const Honeycomb::Math::Matrix4f& getProjection() const;

		/// <summary>
		/// Returns the type of the camera projection.
		/// </summary>
		/// <returns>
		/// The projection of this camera, either a perspective or orthographic
		/// value.
		/// </returns>
		const ProjectionType& getProjectionType() const;

		/// <summary>
		/// Gets the height of the projection of this camera.
		/// </summary>
		/// <returns>
		/// The projection height.
		/// </returns>
		const float& getProjectionHeight() const;

		/// <summary>
		/// Gets the orientation projection matrix for this camera.
		/// </summary>
		/// <returns>
		/// The orientation projection matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& getProjectionOrientation() const;

		/// <summary>
		/// Gets the translation projection matrix for this camera.
		/// </summary>
		/// <returns>
		/// The translation projection matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& getProjectionTranslation() const;

		/// <summary>
		/// Gets the view projection matrix for this camera.
		/// </summary>
		/// <returns>
		/// The view projection matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& getProjectionView() const;

		/// <summary>
		/// Gets the width of the projection of this camera.
		/// </summary>
		/// <returns>
		/// The projection width.
		/// </returns>
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

		/// <summary>
		/// Disables this as the active Camera. After this method is called
		/// no active Camera will exist.
		/// </summary>
		void onDisable() override;

		/// <summary>
		/// Enables this as the active Camera. Any other currently enabled
		/// Camera is automatically disabled by this method.
		/// </summary>
		void onEnable() override;

		/// <summary>
		/// Sets a boolean representing whether or not this Camera 
		/// automatically resizes its size to fit the game window when the game
		/// window is resized.
		/// </summary>
		/// <param name="fit">
		/// True if the Camera should automatically resize on a window resize 
		/// event, false otherwise.
		/// </param>
		void setFitToWindow(const bool &fit);

		/// <summary>
		/// Sets the projection width and height of this Camera. Note that this
		/// method has no effect is this camera is set to fit to the window
		/// size.
		/// </summary>
		/// <param name="w">
		/// The new width of the Camera.
		/// </param>
		/// <param name="h">
		/// The new height of the Camera.
		/// </param>
		void setProjectionSize(float w, float h);

		/// <summary>
		/// Sets the projection width and height of this Camera to the current
		/// window size.
		/// </summary>
		void setProjectionSizeToWindowSize();
	private:
		static CameraController *activeCamera; // The active camera

		const static std::string STRUCT_FILE;
		const static std::string STRUCT_NAME;

		float clipFar;              // The far clipping plane
		float clipNear;             // The near clipping plane
		ProjectionType type;        // The projection type
		float typeParameter;        // The projection parameter (FOV / size)
		float projectionHeight;     // The projection height
		float projectionWidth;      // The projection width
		bool fitToWindow;           // Projection size == window size always?

		Honeycomb::Conjuncture::EventHandler 
			windowResizeHandler;    // Handles the window resize event
		Honeycomb::Conjuncture::EventHandler
			transformChangeHandler; // Handles the transform change event

		// Transform of the game object this camera is attached to
		Honeycomb::Component::Physics::Transform *transform;

		mutable Honeycomb::Math::Matrix4f projection;      // Full Projection
		mutable Honeycomb::Math::Matrix4f projectionView;  // View
		mutable Honeycomb::Math::Matrix4f projectionOrien; // Orientation
		mutable Honeycomb::Math::Matrix4f projectionTrans; // Translation

		mutable bool isProjectionDirty;
		mutable bool isProjectionViewDirty;
		mutable bool isProjectionOrienDirty;
		mutable bool isProjectionTransDirty;

		/// <summary>
		/// Calculates the projection matrix, stores it in this instance and
		/// returns it. If any matrices are dirty, they are recalculated
		/// automatically before the final projection matrix is calculated.
		/// </summary>
		/// <returns>
		/// The constant reference to the projection matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& calcProjection() const;

		/// <summary>
		/// Calculates the orientation projection matrix, stores it in this
		/// instance and returns it.
		/// </summary>
		/// <returns>
		/// The constant reference to the orientation matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& calcProjectionOrientation() const;

		/// <summary>
		/// Calculates the translation projection matrix, stores it in this 
		/// instance and returns it.
		/// </summary>
		/// <returns>
		/// The constant reference to the translation view projection.
		/// </returns>
		const Honeycomb::Math::Matrix4f& calcProjectionTranslation() const;

		/// <summary>
		/// Calculates the orthographic view projection matrix, stores it in 
		/// this instance and returns it.
		/// </summary>
		/// <returns>
		/// The constant reference to the orthographic view projection.
		/// </returns>
		const Honeycomb::Math::Matrix4f& calcProjectionViewOrthographic() 
				const;

		/// <summary>
		/// Calculates the perspective view projection matrix, stores it in 
		/// this instance and returns it.
		/// </summary>
		/// <returns>
		/// The constant reference to the perspective view projection.
		/// </returns>
		const Honeycomb::Math::Matrix4f& calcProjectionViewPerspective() const;

		/// <summary>
		/// Calculates the view projection matrix based on the type of this
		/// camera, stores it in this instance and returns it.
		/// </summary>
		/// <returns>
		/// The constant reference to the view projection.
		/// </returns>
		const Honeycomb::Math::Matrix4f& calcProjectionView() const;

		/// <summary>
		/// Internal clone method for the Camera Controller component.
		/// </summary>
		/// <returns>
		/// The pointer to the dynamically allocated Camera Controller 
		/// instance.
		/// </returns>
		virtual CameraController* cloneInternal() const override;

		/// <summary>
		/// Event which should be triggered when the Transform to which this
		/// is attached is changed. This will mark any transform related 
		/// matrices as dirty so that they may be recalculated when they are to
		/// be used.
		/// </summary>
		void onTransformChange();

		/// <summary>
		/// Event which should be triggered when the game window is resized. 
		/// Checks if the Camera is set to be automatically resized to fit the
		/// window scale on a window resize event. If so, the camera's size is
		/// adjusted to fit the window size.
		/// </summary>
		void onWindowResize();
	};
} } }

#endif
