#include "..\..\include\object\Transform.h"

#include <math.h>

#include "..\..\include\math\Matrix4f.h"
#include "..\..\include\math\Vector3f.h"

using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Matrix4f;

namespace Honeycomb::Object {
	Transform::Transform() {
		this->translation = new Vector3f();
		this->rotation = new Vector3f();
		this->scale = new Vector3f(1, 1, 1); // Default scale is full size
	}

	Transform::~Transform() {
		delete this->translation;
		delete this->rotation;
		delete this->scale;
	}

	Matrix4f Transform::cumulateTransformations() {
		// Create individual matricies for each component of the transform
		Matrix4f transMat = this->matrixTranslation();
		Matrix4f rotMat = this->matrixRotation();
		Matrix4f sclMat = this->matrixScale();

		// Perform matrix multiplication on the components (first scale, then
		// rotate, then translate).
		return transMat * rotMat * sclMat;
	}

	Vector3f* Transform::getRotation() {
		return this->rotation;
	}

	Vector3f* Transform::getScale() {
		return this->scale;
	}

	Vector3f* Transform::getTranslation() {
		return this->translation;
	}

	void Transform::setRotation(Vector3f vec) {
		this->rotation->set(vec.getX(), vec.getY(), vec.getZ());
	}

	void Transform::setScale(Vector3f vec) {
		this->scale->set(vec.getX(), vec.getY(), vec.getZ());
	}

	void Transform::setTranslation(Vector3f vec) {
		this->translation->set(vec.getX(), vec.getY(), vec.getZ());
	}

	void Transform::rotate(Vector3f vec) {
		this->setRotation(*this->rotation + vec);
	}

	void Transform::translate(Vector3f vec) {
		this->setTranslation(*this->translation + vec);
	}

	Matrix4f Transform::matrixRotation() {
		// Get the three identity matricies (one for which axis in vector)
		Matrix4f rotX = Matrix4f::identity();
		Matrix4f rotY = Matrix4f::identity();
		Matrix4f rotZ = Matrix4f::identity();

		{ // Local scope for calculating the rotation matrix for X
			float x = this->rotation->getX();
			float cosX = cos(x);
			float sinX = sin(x);

			rotX.setAt(1, 1,  cosX);	//  1   0   0   0
			rotX.setAt(1, 2, -sinX);    //  0 +cos -sin 0
			rotX.setAt(2, 1,  sinX);	//  0 +sin +cos 0
			rotX.setAt(2, 2,  cosX);    //  0   0   0   1
		}

		{ // Local scope for calculating the rotation matrix for Y
			float y = this->rotation->getY();
			float cosY = cos(y);
			float sinY = sin(y);

			rotY.setAt(0, 0,  cosY);	// +cos 0 +sin 0
			rotY.setAt(0, 2,  sinY);	//  0   1   0  0
			rotY.setAt(2, 0, -sinY);	// -sin 0 +cos 0
			rotY.setAt(2, 2,  cosY);	//  0   0   0  1
		}

		{ // Local scope for calculating the rotation matrix for Z
			float z = this->rotation->getZ();
			float cosZ = cos(z);
			float sinZ = sin(z);

			rotZ.setAt(0, 0,  cosZ);	// +cos -sin 0   0
			rotZ.setAt(0, 1, -sinZ);	// +sin +cos 0   0
			rotZ.setAt(1, 0,  sinZ);	//   0   0   1   0
			rotZ.setAt(1, 1,  cosZ);	//   0   0   0   1
		}

		return rotZ * rotY * rotX; // Matrix Multiplication (order matters!)
	}

	Matrix4f Transform::matrixScale() {
		Matrix4f scl = Matrix4f::identity(); // Get an identity matrix

		// A scale matrix is composed as an identity matrix whose diagonal
		// equals { X, Y, Z, 1 }				// x 0 0 0
		scl.setAt(0, 0, this->scale->getX());	// 0 y 0 0
		scl.setAt(1, 1, this->scale->getY());	// 0 0 z 0
		scl.setAt(2, 2, this->scale->getZ());	// 0 0 0 1

		return scl;
	}

	Matrix4f Transform::matrixTranslation() {
		Matrix4f trans = Matrix4f::identity(); // Get an identity matrix

		// A translation matrix is composed as an identity matrix whose last
		// column equals { X, Y, Z, 1 }.				// 1 0 0 x
		trans.setAt(0, 3, this->translation->getX());	// 0 1 0 y
		trans.setAt(1, 3, this->translation->getY());	// 0 0 1 z
		trans.setAt(2, 3, this->translation->getZ());	// 0 0 0 1

		return trans;
	}
}