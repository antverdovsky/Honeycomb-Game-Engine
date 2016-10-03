#pragma once
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "..\..\include\math\Vector3f.h";
#include "..\..\include\math\Matrix4f.h"

namespace Honeycomb::Object {
	class Transform {
	public:
		/// Default constructor which initializes the position, rotation and
		/// scale of the transform to default values.
		Transform();

		/// Initializes an instance of the Transform object to the specified
		/// position, rotation, scale, and local directions.
		/// Vector3f pos : The position of the object.
		/// Vector3f rot : The rotation of the object.
		/// Vector3f scl : The scale of the object.
		/// Vector3f lFor : The forward direction of the object.
		/// Vector3f lUp : The up direction of the object;
		/// Vector3f lRig : The right direction of the object.
		Transform(Honeycomb::Math::Vector3f pos, Honeycomb::Math::Vector3f rot,
			Honeycomb::Math::Vector3f scl, Honeycomb::Math::Vector3f lFor,
			Honeycomb::Math::Vector3f lRig, Honeycomb::Math::Vector3f lUp);

		/// Gets the vector pointing in the local forward direction of this
		/// transform.
		/// return : The local forward vector.
		Honeycomb::Math::Vector3f getLocalForward();

		/// Gets the vector pointing in the local right direction of this
		/// transform.
		/// return : The local right vector.
		Honeycomb::Math::Vector3f getLocalRight();

		/// Gets the vector pointing in the local up direction of this
		/// transform.
		/// return : The local up vector.
		Honeycomb::Math::Vector3f getLocalUp();

		/// Gets the current orientation matrix for this transform.
		/// return : The orientation matrix.
		Honeycomb::Math::Matrix4f getOrientationMatrix();

		/// Gets the current transformation matrix for this transform.
		/// return : The transformation matrix.
		Honeycomb::Math::Matrix4f getTransformationMatrix();

		/// Gets the current translation matrix for this transform.
		/// return : The translation matrix.
		Honeycomb::Math::Matrix4f getTranslationMatrix();

		/// Gets the current rotation matrix for this transform.
		/// return : The rotation matrix.
		Honeycomb::Math::Matrix4f getRotationMatrix();

		/// Gets the current scale matrix for this transform.
		/// return : The scale matrix.
		Honeycomb::Math::Matrix4f getScaleMatrix();

		/// Gets the rotation vector of this transform.
		/// return : The rotation vector.
		Honeycomb::Math::Vector3f getRotation();

		/// Gets the scale vector of this uniform.
		/// return : The scale vector.
		Honeycomb::Math::Vector3f getScale();

		/// Gets the position vector of this transform.
		/// return : The position vector.
		Honeycomb::Math::Vector3f getTranslation();

		/// Sets the rotation vector of this transform.
		/// Vector3f vec : The new rotation vector.
		void setRotation(Honeycomb::Math::Vector3f vec);

		/// Sets the scale vector of this transform.
		/// Vector3f vec : The new scale vector.
		void setScale(Honeycomb::Math::Vector3f vec);

		/// Sets the position vector of this transform.
		/// Vector3f vec : The new position vector.
		void setTranslation(Honeycomb::Math::Vector3f vec);

		/// Rotates this transform by the specified amount of radians on each
		/// axis. A positive amount will rotate the transform counterclockwise,
		/// and a negative amount will rotate the transform clockwise.
		/// Vector3f vec : The amounts, in radians, by which to rotate on each
		///				   major axis.
		void rotate(Honeycomb::Math::Vector3f vec);

		/// Translates this transform in the direction and distance specified.
		/// Vector3f vec : The direction and distance to translate.
		void translate(Honeycomb::Math::Vector3f vec);
	private:
		Honeycomb::Math::Vector3f rotation; // Stores the local rotation
		Honeycomb::Math::Vector3f translation; // Stores the local position
		Honeycomb::Math::Vector3f scale; // Stores the local scale

		Honeycomb::Math::Vector3f localForward; // Local Forward Direction
		Honeycomb::Math::Vector3f localUp; // Local Up Direction
		Honeycomb::Math::Vector3f localRight; // Local Right Direction

		Honeycomb::Math::Matrix4f orientationMatrix; // Orientation Mat
		Honeycomb::Math::Matrix4f transformationMatrix; // Transformation Mat

		Honeycomb::Math::Matrix4f translationMatrix; // Translation Mat
		Honeycomb::Math::Matrix4f rotationMatrix; // Rotation Mat
		Honeycomb::Math::Matrix4f scaleMatrix; // Scale Mat

		/// Calculates the orientation matrix (matrix composed of the local
		/// forward, up and right directions) for this transform. This should 
		/// be called every time the object's orientation changes.
		/// return : The updated directional matrix.
		Honeycomb::Math::Matrix4f calculateOrientationMatrix();

		/// Calculates the transformation matrix for the transform. This should
		/// be called every time either the rotation, scale, or translation of 
		/// the transform is modified.
		/// return : The updated transformation matrix.
		Honeycomb::Math::Matrix4f calculateTransformationMatrix();

		/// Constructs a rotation matrix from the rotation vector of this
		/// transform.
		/// return : The rotation matrix.
		Honeycomb::Math::Matrix4f calculateRotationMatrix();

		/// Constructs a scale matrix from the scale vector of this transform.
		/// return : The scale vector.
		Honeycomb::Math::Matrix4f calculateScaleMatrix();

		/// Constructs a translation matrix from the position vector of this
		/// transform.
		/// return : The translation matrix.
		Honeycomb::Math::Matrix4f calculateTranslationMatrix();
	};
}

#endif