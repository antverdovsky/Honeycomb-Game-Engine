#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "../GameComponent.h"
#include "../../../include/conjuncture/Event.h"
#include "../../../include/math/Vector3f.h"
#include "../../../include/math/Matrix4f.h"
#include "../../../include/math/Quaternion.h"

namespace Honeycomb { namespace Component { namespace Physics {
	enum Space {
		LOCAL,      // Represents the Local Coordinate System of some Object
		GLOBAL      // Represents the Global Coordinate System of all Objects
	};

	class Transform : public GameComponent {
		friend class Honeycomb::Object::GameObject;
	public:
		/// <summary>
		/// Default Constructor which initializes the position, rotation and
		/// scale of the Transform. The position and rotation will be a default
		/// constructed Vector and Quaternion, respectively, and the scale will
		/// be a vector with a value of one for each component.
		/// </summary>
		Transform();

		/// <summary>
		/// Initializes the Transform using the specified position, rotation
		/// and scale.
		/// </summary>
		/// <param name="pos">
		/// The position of the Transform.
		/// </param>
		/// <param name="rot">
		/// The rotation of the Transform.
		/// </param>
		/// <param name="scl">
		/// The scale of the Transform.
		/// </param>
		Transform(const Honeycomb::Math::Vector3f &pos,
			const Honeycomb::Math::Quaternion &rot,
			const Honeycomb::Math::Vector3f &scl);

		/// <summary>
		/// Clones this Transform component into a new, independent Transform
		/// component.
		/// </summary>
		/// <returns>
		/// The unique pointer to the cloned Transform.
		/// </returns>
		std::unique_ptr<Transform> clone() const;

		/// <summary>
		/// Gets the Changed Event. This event is triggered whenever the
		/// transform is changed in some way.
		/// </summary>
		/// <returns>
		/// The reference to the Changed Event.
		/// </returns>
		Honeycomb::Conjuncture::Event& getChangedEvent();

		/// <summary>
		/// Gets the Changed Event. This event is triggered whenever the
		/// transform is changed in some way.
		/// </summary>
		/// <returns>
		/// The constant reference to the Changed Event.
		/// </returns>
		const Honeycomb::Conjuncture::Event& getChangedEvent() const;

		/// <summary>
		/// Returns the Component ID integer representation of the Transform.
		/// </summary>
		/// <returns>
		/// The Component ID of the Transform Component.
		/// </returns>
		virtual GameComponentID getGameComponentID() const noexcept override;

		/// <summary>
		/// Gets the global rotation of this Transform. This rotation is
		/// dependent on both the local rotation of this Transform and the
		/// global rotation of this Transform's parent.
		/// </summary>
		/// <returns>
		/// The rotation quaternion.
		/// </returns>
		const Honeycomb::Math::Quaternion& getGlobalRotation() const;

		/// <summary>
		/// Gets the global scale of this Transform. This scale is dependent on 
		/// both the local scale of this Transform and the global scale of this
		/// Transform's parent.
		/// </summary>
		/// <returns>
		/// The scale vector.
		/// </returns>
		const Honeycomb::Math::Vector3f& getGlobalScale() const;

		/// <summary>
		/// Gets the global translation of this Transform. This translation is 
		/// dependent on both the local translation of this Transform and the
		/// global translation of this Transform's parent.
		/// </summary>
		/// <returns>
		/// The translation vector.
		/// </returns>
		const Honeycomb::Math::Vector3f& getGlobalTranslation() const;

		/// <summary>
		/// Gets the vector pointing in the local forward direction of this
		/// Transform.
		/// </summary>
		/// <returns>
		/// The local forward vector.
		/// </returns>
		const Honeycomb::Math::Vector3f& getLocalForward() const;

		/// <summary>
		/// Gets the vector pointing in the local right direction of this
		/// Transform.
		/// </summary>
		/// <returns>
		/// The local right vector.
		/// </returns>
		const Honeycomb::Math::Vector3f& getLocalRight() const;

		/// <summary>
		/// Gets the local rotation of this Transform. This rotation is
		/// dependent on the local rotation of this Transform only.
		/// </summary>
		/// <returns>
		/// The local rotation quaternion.
		/// </returns>
		const Honeycomb::Math::Quaternion& getLocalRotation() const;

		/// <summary>
		/// Gets the local scale of this Transform. This scale is dependent on
		/// the local scale of this Transform only.
		/// </summary>
		/// <returns>
		/// The local scale vector.
		/// </returns>
		const Honeycomb::Math::Vector3f& getLocalScale() const;

		/// <summary>
		/// Gets the local translation of this Transform. This translation is
		/// dependent on the local translation of this Transform only.
		/// </summary>
		/// <returns>
		/// The local translation vector.
		/// </returns>
		const Honeycomb::Math::Vector3f& getLocalTranslation() const;

		/// <summary>
		/// Gets the vector pointing in the local up direction of this 
		/// Transform.
		/// </summary>
		/// <returns>
		/// The local up vector.
		/// </returns>
		const Honeycomb::Math::Vector3f& getLocalUp() const;

		/// <summary>
		/// Gets the orientation matrix of this Transform.
		/// </summary>
		/// <returns>
		/// The orientation matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& getMatrixOrientation() const;

		/// <summary>
		/// Gets the rotation matrix of this Transform.
		/// </summary>
		/// <returns>
		/// The rotation matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& getMatrixRotation() const;

		/// <summary>
		/// Gets the scale matrix of this Transform.
		/// </summary>
		/// <returns>
		/// The scale matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& getMatrixScale() const;

		/// <summary>
		/// Gets the transformation matrix of this Transform.
		/// </summary>
		/// <returns>
		/// The transformation matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& getMatrixTransformation() const;

		/// <summary>
		/// Gets the translation matrix of this Transform.
		/// </summary>
		/// <returns>
		/// The translation matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& getMatrixTranslation() const;

		/// <summary>
		/// Transforms the specified global direction vector into a local
		/// direction vector.
		/// </summary>
		/// <param name="dir">
		/// The global direction vector which is to be transformed.
		/// </param>
		/// <returns>
		/// The transformed local direction vector.
		/// </returns>
		Honeycomb::Math::Vector3f inverseTransformDirection(
			const Honeycomb::Math::Vector3f &dir) const;

		/// <summary>
		/// Transforms the specified global position vector into a local
		/// position vector.
		/// </summary>
		/// <param name="pos">
		/// The global position vector which is to be transformed.
		/// </param>
		/// <returns>
		/// The transformed local position vector.
		/// </returns>
		Honeycomb::Math::Vector3f inverseTransformPoint(
			const Honeycomb::Math::Vector3f &pos) const;

		/// <summary>
		/// Checks if this Transform is negatively scaled on an odd number of
		/// axes.
		/// </summary>
		/// <returns>
		/// True if the Transform's scale is negative for an odd number of
		/// axes, false otherwise.
		/// </returns>
		bool isOddNegativelyScaled() const;

		/// <summary>
		/// Starts this Transform. This automatically calculates the initial
		/// matrices of the Transform.
		/// </summary>
		void onStart() override;

		/// <summary>
		/// Sets the rotation of this Transform to the specified quaternion.
		/// If the space parameter is not specified, the rotation is 
		/// automatically set in the global world space.
		/// </summary>
		/// <param name="rot">
		/// The new rotation of the Transform.
		/// </param>
		/// <param name="space">
		/// The space in which the rotation is to be set. If this is not
		/// specified, global is used by default.
		/// </param>
		void setRotation(const Honeycomb::Math::Quaternion &rot,
			const Space &space = Space::GLOBAL);

		/// <summary>
		/// Sets the scaling of this Transform to the specified vector.
		/// If the space parameter is not specified, the scaling is 
		/// automatically set in the global world space.
		/// </summary>
		/// <param name="scl">
		/// The new scale of the Transform.
		/// </param>
		/// <param name="space">
		/// The space in which the scaling is to be set. If this is not
		/// specified, global is used by default.
		/// </param>
		void setScale(const Honeycomb::Math::Vector3f &scl, 
			const Space &space = Space::GLOBAL);

		/// <summary>
		/// Sets the position of this Transform to the specified vector.
		/// If the space parameter is not specified, the position is 
		/// automatically set in the global world space.
		/// </summary>
		/// <param name="pos">
		/// The new position of the Transform.
		/// </param>
		/// <param name="space">
		/// The space in which the position is to be set. If this is not
		/// specified, global is used by default.
		/// </param>
		void setTranslation(const Honeycomb::Math::Vector3f &pos, 
			const Space &space = Space::GLOBAL);

		/// <summary>
		/// Rotates this Transform by the specified amount of radians on the
		/// specified axis.
		/// </summary>
		/// <param name="axis">
		/// The axis on which to rotate the vector. Whether this axis is local
		/// or global is determined by the <paramref name="space"/> 
		/// pararameter.
		/// </param>
		/// <param name="rad">
		/// The amount of radians by which the Transform is to be rotated.
		/// </param>
		/// <param name="space">
		/// The space in which the object is to be rotated. If this is not
		/// specified, local is used by default.
		/// </param>
		void rotate(const Honeycomb::Math::Vector3f &axis, const float &rad,
			const Space &space = Space::LOCAL);

		/// <summary>
		/// Rotates this transform around the specified world axis by the
		/// specified amount of radians.
		/// </summary>
		/// <param name="center">
		/// The point through which the axis goes.
		/// </param>
		/// <param name="axis">
		/// The direction of the axis.
		/// </param>
		/// <param name="rad">
		/// The amount, in radians, by which the object is to be rotated on the
		/// axis.
		/// </param>
		void rotateAround(const Honeycomb::Math::Vector3f &center, 
			const Honeycomb::Math::Vector3f &axis, const float &rad);

		/// <summary>
		/// Transforms the specified local direction vector into a global
		/// direction vector.
		/// </summary>
		/// <param name="dir">
		/// The local direction vector which is to be transformed.
		/// </param>
		/// <returns>
		/// The transformed global direction vector.
		/// </returns>
		Honeycomb::Math::Vector3f transformDirection(
			const Honeycomb::Math::Vector3f &dir) const;

		/// <summary>
		/// Transforms the specified local position vector into a global
		/// position vector.
		/// </summary>
		/// <param name="dir">
		/// The local position vector which is to be transformed.
		/// </param>
		/// <returns>
		/// The transformed global position vector.
		/// </returns>
		Honeycomb::Math::Vector3f transformPoint(
			const Honeycomb::Math::Vector3f &p) const;

		/// <summary>
		/// Translates this Transform by the specified vector. If the space
		/// parameter is set to local, the Transform is translated along its
		/// local coordinate system. Otherwise, the Transform is translated
		/// along the world coordinate system.
		/// </summary>
		/// <param name="vec">
		/// The distance to travel, where each component represents the 
		/// displacement on each axis.
		/// </param>
		/// <param name="space">
		/// The space on which to travel. If this is not specified, local space
		/// is used by default.
		/// </param>
		void translate(const Honeycomb::Math::Vector3f &vec, 
			const Space &space = Space::LOCAL);

		/// <summary>
		/// Translates this Transform by the specified amount relative to the
		/// specified Transform. This Transform will be translated on the local
		/// coordinate axes of the relative Transform.
		/// </summary>
		/// <param name="vec">
		/// The distance to travel, where each component represents the 
		/// displacement on each axis.
		/// </param>
		/// <param name="relTo">
		/// The Transform, relative to which, the displacement is to occur.
		/// </param>
		void translate(const Honeycomb::Math::Vector3f &vec, 
			const Transform &relTo);
	private:
		Transform *parent;                                   // Pointer->Parent

		mutable Honeycomb::Math::Vector3f lclTranslation;    // Local Position
		mutable Honeycomb::Math::Quaternion lclRotation;     // Local Rotation
		mutable Honeycomb::Math::Vector3f lclScale;          // Local Scale

		mutable Honeycomb::Math::Vector3f gblTranslation;    // Global Position
		mutable Honeycomb::Math::Quaternion gblRotation;     // Global Rotation
		mutable Honeycomb::Math::Vector3f gblScale;          // Global Scale

		mutable Honeycomb::Math::Vector3f forward;           // Local Forward
		mutable Honeycomb::Math::Vector3f right;             // Local Right
		mutable Honeycomb::Math::Vector3f up;                // Local Up

		// Do note that due to the clean/dirty states, these should NEVER be
		// used directly. Always use the appropriate get methods for each
		// matrix since these will automatically recompute the matrix values
		// should it be dirty.
		mutable Honeycomb::Math::Matrix4f transformMatrix;   // Transf. Mat
		mutable Honeycomb::Math::Matrix4f translationMatrix; // Translation Mat
		mutable Honeycomb::Math::Matrix4f rotationMatrix;    // Rotation Mat
		mutable Honeycomb::Math::Matrix4f scaleMatrix;       // Scale Mat
		mutable Honeycomb::Math::Matrix4f orientationMatrix; // Orientation Mat

		// For each of these variables, a property is considered dirty if it
		// has been modified since the last calculation of its matrix.
		mutable bool isDirtyRotation;
		mutable bool isDirtyScale;
		mutable bool isDirtyTranslation;
		mutable bool isDirtyTransformation;

		Honeycomb::Conjuncture::Event changedEvent;          // This Changed
		Honeycomb::Conjuncture::EventHandler parentChanged;  // Parent Changed

		/// <summary>
		/// Calculates the orientation matrix for this Transform based on the
		/// current rotation.
		/// </summary>
		/// <returns>
		/// The orientation matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& calculateOrientationMatrix() const;

		/// <summary>
		/// Calculates the rotation matrix for this Transform based on the
		/// current rotation.
		/// </summary>
		/// <returns>
		/// The rotation matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& calculateRotationMatrix() const;

		/// <summary>
		/// Calculates the scale matrix for this Transform based on the
		/// current scale.
		/// </summary>
		/// <returns>
		/// The scale matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& calculateScaleMatrix() const;

		/// <summary>
		/// Calculates the transformation matrix for this Transform based on 
		/// the current rotation, scale and translation matrices. Note that 
		/// these matrices must be calculated before this method is called.
		/// </summary>
		/// <returns>
		/// The rotation matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& calculateTransformationMatrix()
				const;

		/// <summary>
		/// Calculates the translation matrix for this Transform based on the
		/// current translation.
		/// </summary>
		/// <returns>
		/// The translation matrix.
		/// </returns>
		const Honeycomb::Math::Matrix4f& calculateTranslationMatrix() const;

		/// <summary>
		/// Callback function which is called when the parent of this Transform
		/// changes. This function adjusts the global properties of this
		/// Transform.
		/// </summary>
		void onParentChange();

		/// <summary>
		/// Sets the parent of this Transformation. This transform will
		/// automatically subscribe to the new parent's transform and if this
		/// transform already has a parent, it will unsubscribe from the old
		/// parent's transform. Once the new transform is set, the world
		/// coordinates of this Transform will remain the same, though the
		/// local coordinates will be modified.
		/// </summary>
		/// <param name="parent">
		/// The pointer to the new Transform. If the Transform loses a parent,
		/// this should be a nullptr.
		/// </param>
		void setParent(Transform *parent);

		/// <summary>
		/// Clones this Transform instance. All values are copied with the
		/// exception of the parent, and the event/event handlers.
		/// </summary>
		/// <returns>
		/// The pointer to the dynamically allocated Transform instance.
		/// </returns>
		virtual Transform* cloneInternal() const override;

		/// <summary>
		/// Overrides the [AllowsMultiple] property to always return false, 
		/// since at most one Transform may be attached to a Game Object at one
		/// time.
		/// </summary>
		/// <returns>
		/// False.
		/// </returns>
		virtual bool getProperty_AllowsMultiple() const noexcept override;

		/// <summary>
		/// Overrides the [Permanent] property to always return true, 
		/// since a Transform is a required component and should not be 
		/// removed.
		/// </summary>
		/// <returns>
		/// True.
		/// </returns>
		virtual bool getProperty_Permanent() const noexcept override;
	};
} } }

#endif
