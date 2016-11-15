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
		/// scale of the transform to default values.
		Transform();

		/// Initializes an instance of the Transform object to the specified
		/// position, rotation, and scale.
		/// Vector3f pos : The position of the object.
		/// Quaternion rot : The rotation of the object.
		/// Vector3f scl : The scale of the object.
		Transform(Honeycomb::Math::Vector3f pos, 
			Honeycomb::Math::Quaternion rot, Honeycomb::Math::Vector3f scl);

		/// Gets an event which will be triggered once the transform is changed
		/// in any way (scaled, translated or rotated).
		/// return : The event.
		Honeycomb::Conjuncture::Event& getChangedEvent();

		/// Gets the vector pointing in the local forward direction of this
		/// transform.
		/// return : The local forward vector.
		Honeycomb::Math::Vector3f& getLocalForward();

		/// Gets the vector pointing in the local right direction of this
		/// transform.
		/// return : The local right vector.
		Honeycomb::Math::Vector3f& getLocalRight();

		/// Gets the vector pointing in the local up direction of this
		/// transform.
		/// return : The local up vector.
		Honeycomb::Math::Vector3f& getLocalUp();

		/// Gets the orientation matrix for this transform.
		/// return : The orientation matrix.
		Honeycomb::Math::Matrix4f getOrientationMatrix();

		/// Gets the rotation quaternion of this transform.
		/// return : The rotation quaternion.
		Honeycomb::Math::Quaternion& getRotation();

		/// Gets the current rotation matrix for this transform.
		/// return : The rotation matrix.
		Honeycomb::Math::Matrix4f getRotationMatrix();

		/// Gets the scale vector of this uniform.
		/// return : The scale vector.
		Honeycomb::Math::Vector3f& getScale();

		/// Gets the current scale matrix for this transform.
		/// return : The scale matrix.
		Honeycomb::Math::Matrix4f getScaleMatrix();

		/// Gets the current transformation matrix for this transform.
		/// return : The transformation matrix.
		Honeycomb::Math::Matrix4f getTransformationMatrix();

		/// Gets the position vector of this transform.
		/// return : The position vector.
		Honeycomb::Math::Vector3f& getTranslation();

		/// Gets the current translation matrix for this transform.
		/// return : The translation matrix.
		Honeycomb::Math::Matrix4f getTranslationMatrix();

		/// Starts this Transform instance.
		void start();

		/// Sets the rotation vector of this transform.
		/// Quaternion quat : The new rotation quaternion.
		void setRotation(Honeycomb::Math::Quaternion quat);

		/// Sets the scale vector of this transform.
		/// Vector3f vec : The new scale vector.
		void setScale(Honeycomb::Math::Vector3f vec);

		/// Sets the position vector of this transform.
		/// Vector3f vec : The new position vector.
		void setTranslation(Honeycomb::Math::Vector3f vec);

		/// Rotates this transform by the specified amount of radians on the
		/// axis. A positive amount will rotate the transform counterclockwise,
		/// and a negative amount will rotate the transform clockwise.
		/// Vector3f axis : The axis on which to rotate the vector.
		/// float rad : The amount by which to rotate the vector, in radians.
		///				A positive amount rotates the vector counterclockwise,
		///				and a negative amount rotates the angle clockwise.
		void rotate(Honeycomb::Math::Vector3f axis, float rad);

		/// Translates this transform in the direction and distance specified.
		/// Vector3f vec : The direction and distance to translate.
		void translate(Honeycomb::Math::Vector3f vec);
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
		Honeycomb::Math::Matrix4f calculateOrientationMatrix();

		/// Constructs a rotation matrix from the rotation vector of this
		/// transform.
		/// return : The rotation matrix.
		Honeycomb::Math::Matrix4f calculateRotationMatrix();

		/// Constructs a scale matrix from the scale vector of this transform.
		/// return : The scale vector.
		Honeycomb::Math::Matrix4f calculateScaleMatrix();

		/// Calculates the transformation matrix for the transform. This should
		/// be called every time either the rotation, scale, or translation of 
		/// the transform is modified.
		/// return : The updated transformation matrix.
		Honeycomb::Math::Matrix4f calculateTransformationMatrix();

		/// Constructs a translation matrix from the position vector of this
		/// transform.
		/// return : The translation matrix.
		Honeycomb::Math::Matrix4f calculateTranslationMatrix();
	};
}

#endif