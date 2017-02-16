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
		/// prevent object slicing.
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
		const Honeycomb::Math::Quaternion& getRotation() const;

		/// Gets the current rotation matrix for this transform.
		/// return : The rotation matrix.
		const Honeycomb::Math::Matrix4f& getRotationMatrix() const;

		/// Gets the scale vector of this uniform.
		/// return : The scale vector.
		const Honeycomb::Math::Vector3f& getScale() const;

		/// Gets the current scale matrix for this transform.
		/// return : The scale matrix.
		const Honeycomb::Math::Matrix4f& getScaleMatrix() const;

		/// Gets the current transformation matrix for this transform.
		/// return : The transformation matrix.
		const Honeycomb::Math::Matrix4f& getTransformationMatrix() const;

		/// Gets the position vector of this transform.
		/// return : The position vector.
		const Honeycomb::Math::Vector3f& getTranslation() const;

		/// Gets the current translation matrix for this transform.
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
		Honeycomb::Math::Vector3f translation; // Stores the local position
		Honeycomb::Math::Quaternion rotation; // Local rotation quaternion
		Honeycomb::Math::Vector3f scale; // Stores the local scale

		Honeycomb::Math::Vector3f localForward; // Local Forward Direction
		Honeycomb::Math::Vector3f localUp; // Local Up Direction
		Honeycomb::Math::Vector3f localRight; // Local Right Direction

		Honeycomb::Math::Matrix4f transformationMatrix; // Transformation Mat
		Honeycomb::Math::Matrix4f translationMatrix; // Translation Mat
		Honeycomb::Math::Matrix4f rotationMatrix; // Rotation Mat
		Honeycomb::Math::Matrix4f scaleMatrix; // Scale Mat
		Honeycomb::Math::Matrix4f orientationMatrix; // Orientation Mat

		Honeycomb::Conjuncture::Event changedEvent; // Transform changed event

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
	};
}

#endif