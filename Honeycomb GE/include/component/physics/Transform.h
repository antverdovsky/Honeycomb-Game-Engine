#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "..\GameComponent.h"
#include "..\..\..\include\conjuncture\Event.h"
#include "..\..\..\include\math\Vector3f.h"
#include "..\..\..\include\math\Matrix4f.h"
#include "..\..\..\include\math\Quaternion.h"

namespace Honeycomb::Component::Physics {
	class Transform : public GameComponent {
		friend class Honeycomb::Object::GameObject;
	public:
		/// Default constructor which initializes the position, rotation and
		/// scale of the transform to default values. The position and rotation
		/// will both be initialized with zeros values, however, the scale will
		/// be initialized with ones values.
		Transform();

		/// Initializes an instance of the Transform object to the specified
		/// position, rotation, and scale.
		/// const Vector3f &pos : The position of the object.
		/// const Quaternion &rot : The rotation of the object.
		/// const Vector3f &scl : The scale of the object.
		Transform(const Honeycomb::Math::Vector3f &pos,
			const Honeycomb::Math::Quaternion &rot,
			const Honeycomb::Math::Vector3f &scl);

		/// Clones this Transform into a new, dynamically allocated Transform. 
		/// This function should be used instead of the copy constructor to 
		/// prevent object slicing. The cloned transform is an independent
		/// component and will lose any parent or children!
		/// return : The pointer to the newly cloned Transform.
		Transform* Transform::clone() const;

		/// Gets the event which will be triggered once the transform is 
		/// changed in any way (scaled, translated or rotated).
		/// return : The reference to the event.
		Honeycomb::Conjuncture::Event& getChangedEvent();

		/// Gets the event which will be triggered once the transform is 
		/// changed in any way (scaled, translated or rotated).
		/// return : The constant reference to the event.
		const Honeycomb::Conjuncture::Event& getChangedEvent() const;

		/// Gets the vector representing the global translation of this
		/// transform.
		/// return : The global translation vector.
		const Honeycomb::Math::Vector3f& getGlobalTranslation() const;

		/// Gets the vector pointing in the local forward direction of this
		/// transform.
		/// return : The local forward vector.
		const Honeycomb::Math::Vector3f& getLocalForward() const;

		/// Gets the vector pointing in the local right direction of this
		/// transform.
		/// return : The local right vector.
		const Honeycomb::Math::Vector3f& getLocalRight() const;

		/// Gets the vector pointing in the local up direction of this
		/// transform.
		/// return : The local up vector.
		const Honeycomb::Math::Vector3f& getLocalUp() const;

		/// Gets the orientation matrix for this transform.
		/// return : The orientation matrix.
		const Honeycomb::Math::Matrix4f& getOrientationMatrix() const;

		/// Gets the rotation quaternion of this transform.
		/// return : The rotation quaternion.
		const Honeycomb::Math::Quaternion& getLocalRotation() const;

		/// Gets the current rotation matrix for this transform.
		/// return : The rotation matrix.
		const Honeycomb::Math::Matrix4f& getRotationMatrix() const;

		/// Gets the scale vector of this uniform.
		/// return : The scale vector.
		const Honeycomb::Math::Vector3f& getLocalScale() const;

		/// Gets the current global scale matrix for this transform.
		/// return : The scale matrix.
		const Honeycomb::Math::Matrix4f& getScaleMatrix() const;

		/// Gets the current global transformation matrix for this transform.
		/// return : The transformation matrix.
		const Honeycomb::Math::Matrix4f& getTransformationMatrix() const;

		/// Gets the local position vector of this transform.
		/// return : The position vector.
		const Honeycomb::Math::Vector3f& getLocalTranslation() const;

		/// Gets the global current translation matrix for this transform.
		/// return : The translation matrix.
		const Honeycomb::Math::Matrix4f& getTranslationMatrix() const;

		/// Starts this Transform instance.
		void start();

		/// Sets the rotation vector of this transform.
		/// const Quaternion &quat : The new rotation quaternion.
		void setRotation(const Honeycomb::Math::Quaternion &quat);

		/// Sets the scale vector of this transform.
		/// const Vector3f &vec : The new scale vector.
		void setScale(const Honeycomb::Math::Vector3f &vec);

		/// Sets the position vector of this transform.
		/// const Vector3f &vec : The new position vector.
		void setTranslation(const Honeycomb::Math::Vector3f &vec);

		/// Rotates this transform by the specified amount of radians on the
		/// axis. A positive amount will rotate the transform counterclockwise,
		/// and a negative amount will rotate the transform clockwise.
		/// const Vector3f &axis : The axis on which to rotate the vector.
		/// const float &rad : The amount by which to rotate the vector, in 
		///					   radians. A positive amount rotates the vector 
		///					   counterclockwise, and a negative amount rotates 
		///					   the angle clockwise.
		void rotate(const Honeycomb::Math::Vector3f &axis, const float &rad);

		/// Rotates this transform by the specified quaternion.
		/// const Quaternion &quat : The quaternion with which to rotate this
		///							 transform.
		void rotate(const Honeycomb::Math::Quaternion &quat);

		/// Translates this transform in the direction and distance specified.
		/// const Vector3f &vec : The direction and distance to translate.
		void translate(const Honeycomb::Math::Vector3f &vec);
	private:
		Transform *parent; // The pointer to the parent of this Transform

		Honeycomb::Math::Vector3f lclTranslation;  // Local position Vector
		Honeycomb::Math::Quaternion lclRotation;   // Local rotation Quaternion
		Honeycomb::Math::Vector3f lclScale;		   // Local scale Vector

		Honeycomb::Math::Vector3f gblTranslation;  // Global position Vector
//		Honeycomb::Math::Quaternion gblRotation;   // Global rotation Quat.
//		Honeycomb::Math::Vector3f gblScale;		   // Global scale Vector

		Honeycomb::Math::Vector3f forward;	// Local Forward Direction
		Honeycomb::Math::Vector3f up;		// Local Up Direction
		Honeycomb::Math::Vector3f right;	// Local Right Direction

		Honeycomb::Math::Matrix4f transformationMatrix; // Transformation Mat
		Honeycomb::Math::Matrix4f translationMatrix;	// Translation Mat
		Honeycomb::Math::Matrix4f rotationMatrix;		// Rotation Mat
		Honeycomb::Math::Matrix4f scaleMatrix;			// Scale Mat
		Honeycomb::Math::Matrix4f orientationMatrix;	// Orientation Mat

		Honeycomb::Conjuncture::Event changedEvent; // Transform changed event
		Honeycomb::Conjuncture::EventHandler parentChanged; // Parent Changed

		/// Calculates the orientation matrix from the forward, up and right of
		/// this transform.
		/// return : The orientation matrix.
		const Honeycomb::Math::Matrix4f& calculateOrientationMatrix();

		/// Constructs a rotation matrix from the rotation vector of this
		/// transform.
		/// return : The rotation matrix.
		const Honeycomb::Math::Matrix4f& calculateRotationMatrix();

		/// Constructs a scale matrix from the scale vector of this transform.
		/// return : The scale vector.
		const Honeycomb::Math::Matrix4f& calculateScaleMatrix();

		/// Calculates the transformation matrix for the transform. This should
		/// be called every time either the rotation, scale, or translation of 
		/// the transform is modified.
		/// return : The updated transformation matrix.
		const Honeycomb::Math::Matrix4f& calculateTransformationMatrix();

		/// Constructs a translation matrix from the position vector of this
		/// transform.
		/// return : The translation matrix.
		const Honeycomb::Math::Matrix4f& calculateTranslationMatrix();

		/// Function called by the parentChanged event handler. Automatically
		/// updates the global position, rotation and scale of this Transform
		/// depending on how the parent was changed.
		void onParentChange();

		/// Sets the parent of this Transformation. This transform will
		/// automatically subscribe to the new parent's transform and if this
		/// transform already has a parent, it will unsubscribe from the old
		/// parent's transform. Once the new transform is set, the world
		/// coordinates of this Transform will remain the same, though the
		/// local coordinates will be modified.
		/// Transform *parent : The pointer to the new Transform (may be null).
		void setParent(Transform *parent);
	};
}

#endif