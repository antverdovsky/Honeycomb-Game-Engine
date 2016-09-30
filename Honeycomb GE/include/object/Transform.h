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

		/// Deletes the position, rotation and scale vectors of this transform.
		~Transform();

		/// Cumulates all of the transformations (position, rotation, scale) by
		/// multiplying all of their matricies together and returning the
		/// resulting model transformation matrix.
		/// return : The cumulation of the transformations matrix.
		Honeycomb::Math::Matrix4f modelTransformation();

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
		/// axis.
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

		Honeycomb::Math::Matrix4f transformation; // Stores the transformation

		/// Calculates the transformation matrix for the transform. This should
		/// automatically be called every time either the rotation, scale, or
		/// translation of the transform is modified.
		/// return : The updated transformation matrix.
		Honeycomb::Math::Matrix4f calculateTransformation();

		/// Constructs a rotation matrix from the rotation vector of this
		/// transform.
		/// return : The rotation matrix.
		Honeycomb::Math::Matrix4f matrixRotation();

		/// Constructs a scale matrix from the scale vector of this transform.
		/// return : The scale vector.
		Honeycomb::Math::Matrix4f matrixScale();

		/// Constructs a translation matrix from the position vector of this
		/// transform.
		/// return : The translation matrix.
		Honeycomb::Math::Matrix4f matrixTranslation();
	};
}

#endif