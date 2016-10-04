#include "..\..\include\object\Transform.h"

#include <math.h>

#include "..\..\include\math\Matrix4f.h"
#include "..\..\include\math\Vector3f.h"
#include "..\..\include\math\MathUtils.h"

using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Matrix4f;
using namespace Honeycomb::Math::Utils;

namespace Honeycomb::Object {
	Transform::Transform() {
		this->setTranslation(Vector3f());
		this->setRotation(Vector3f());
		this->setScale(Vector3f(1, 1, 1)); // Default scale is full size

		this->localForward = Vector3f::getGlobalForward();
		this->localRight = Vector3f::getGlobalRight();
		this->localUp = Vector3f::getGlobalUp();

		this->calculateTranslationMatrix();
		this->calculateRotationMatrix();
		this->calculateScaleMatrix();
		this->calculateOrientationMatrix();
		this->calculateTransformationMatrix();
	}

	Transform::Transform(Vector3f pos, Vector3f rot, Vector3f scl,
		Vector3f lFor, Vector3f lRig, Vector3f lUp) {
		this->translation = pos;
		this->rotation = rot;
		this->scale = scl;

		this->localForward = lFor;
		this->localRight = lRig;
		this->localUp = lUp;

		this->calculateTranslationMatrix();
		this->calculateRotationMatrix();
		this->calculateScaleMatrix();
		this->calculateOrientationMatrix();
		this->calculateTransformationMatrix();
	}

	Vector3f Transform::getLocalForward() {
		return this->localForward;
	}

	Vector3f Transform::getLocalRight() {
		return this->localRight;
	}

	Vector3f Transform::getLocalUp() {
		return this->localUp;
	}

	Matrix4f Transform::getOrientationMatrix() {
		return this->orientationMatrix;
	}

	Matrix4f Transform::getTransformationMatrix() {
		return this->transformationMatrix;
	}

	Matrix4f Transform::getTranslationMatrix() {
		return this->translationMatrix;
	}

	Matrix4f Transform::getRotationMatrix() {
		return this->rotationMatrix;
	}

	Matrix4f Transform::getScaleMatrix() {
		return this->scaleMatrix;
	}

	Vector3f Transform::getRotation() {
		return this->rotation;
	}

	Vector3f Transform::getScale() {
		return this->scale;
	}

	Vector3f Transform::getTranslation() {
		return this->translation;
	}

	void Transform::setRotation(Vector3f vec) {
		Vector3f orig = this->rotation;

		this->rotation.set(vec.getX(), vec.getY(), vec.getZ());

		this->calculateRotationMatrix();
		this->calculateTransformationMatrix();

		// Get the change in rotation from the original transform and the newly
		// rotated one.
		Vector3f del = this->rotation - orig;

		// Rotate the Local Forward, Right and Up vectors according to the 
		// rotation passed in. todo...

		// z rot
		this->localForward.rotateTo(Vector3f::getGlobalForward(), del.getZ());
		this->localRight.rotateTo(Vector3f::getGlobalForward(), del.getZ());
		this->localUp.rotateTo(Vector3f::getGlobalForward(), del.getZ());

		// y rot
		this->localForward.rotateTo(Vector3f::getGlobalUp(), del.getY());
		this->localRight.rotateTo(Vector3f::getGlobalUp(), del.getY());
		this->localUp.rotateTo(Vector3f::getGlobalUp(), del.getY());

		// x rot
		this->localForward.rotateTo(Vector3f::getGlobalRight(), del.getX());
		this->localRight.rotateTo(Vector3f::getGlobalRight(), del.getX());
		this->localUp.rotateTo(Vector3f::getGlobalRight(), del.getX());
		
		this->localForward.normalize();
		this->localRight.normalize();
		this->localUp.normalize();

		this->calculateOrientationMatrix();
	}

	void Transform::setScale(Vector3f vec) {
		this->scale.set(vec.getX(), vec.getY(), vec.getZ());

		this->calculateScaleMatrix();
		this->calculateTransformationMatrix();
	}

	void Transform::setTranslation(Vector3f vec) {
		this->translation.set(vec.getX(), vec.getY(), vec.getZ());

		this->calculateTranslationMatrix();
		this->calculateTransformationMatrix();
	}

	void Transform::rotate(Vector3f vec) {
		this->setRotation(this->rotation + vec);
	}

	void Transform::translate(Vector3f vec) {
		this->setTranslation(this->translation + vec);
	}

	Matrix4f Transform::calculateOrientationMatrix() {
		this->orientationMatrix = Matrix4f::identity();
		
		// Copy each X component from each directional vector to Orientation,
		// so the result of the first column looks like: [ r.X, u.X, f.X ]'.
		this->orientationMatrix.setAt(0, 0, this->localRight.getX());
		this->orientationMatrix.setAt(1, 0, this->localUp.getX());
		this->orientationMatrix.setAt(2, 0, -this->localForward.getX());

		// Copy each Y component from each directional vector to Orientation,
		// so the result of the second column looks like: [ r.Y, u.Y, f.Y ]'.
		this->orientationMatrix.setAt(0, 1, this->localRight.getY());
		this->orientationMatrix.setAt(1, 1, this->localUp.getY());
		this->orientationMatrix.setAt(2, 1, -this->localForward.getY());

		// Copy each Z component from each directional vector to Orientation,
		// so the result of the third column looks like: [ r.Z, u.Z, f.Z ]'.
		this->orientationMatrix.setAt(0, 2, this->localRight.getZ());
		this->orientationMatrix.setAt(1, 2, this->localUp.getZ());
		this->orientationMatrix.setAt(2, 2, -this->localForward.getZ());

		// Return the Orientation Matrix, which should look like:
		// [ r.X  r.Y  r.Z  0.0 ]
		// [ u.X  u.Y  u.Z  0.0 ]
		// [ f.X  f.Y  f.Z  0.0 ]
		// [ 0.0  0.0  0.0  1.0 ]
		//this->orientationMatrix *= -1.0F; // todo
		return this->orientationMatrix;
	}

	Matrix4f Transform::calculateTransformationMatrix() {
		// Create individual matricies for each component of the transform
		Matrix4f transMat = this->getTranslationMatrix();
		Matrix4f rotMat = this->getRotationMatrix();
		Matrix4f sclMat = this->getScaleMatrix();

		Matrix4f test = this->getOrientationMatrix();

		// Perform matrix multiplication on the components (first scale, then
		// rotate, then translate).
		this->transformationMatrix = transMat *  rotMat * sclMat;
		return this->transformationMatrix;
	}

	Matrix4f Transform::calculateRotationMatrix() {
		// Get the three identity matricies (one for which axis in vector)
		Matrix4f rotX = Matrix4f::identity();
		Matrix4f rotY = Matrix4f::identity();
		Matrix4f rotZ = Matrix4f::identity();

		{ // Local scope for calculating the rotation matrix for X
			float x = this->rotation.getX();
			float cosX = cos(x);
			float sinX = sin(x);

			rotX.setAt(1, 1,  cosX);	//  1   0   0   0
			rotX.setAt(1, 2, -sinX);    //  0 +cos -sin 0
			rotX.setAt(2, 1,  sinX);	//  0 +sin +cos 0
			rotX.setAt(2, 2,  cosX);    //  0   0   0   1
		}

		{ // Local scope for calculating the rotation matrix for Y
			float y = this->rotation.getY();
			float cosY = cos(y);
			float sinY = sin(y);

			rotY.setAt(0, 0,  cosY);	// +cos 0 +sin 0
			rotY.setAt(0, 2,  sinY);	//  0   1   0  0
			rotY.setAt(2, 0, -sinY);	// -sin 0 +cos 0
			rotY.setAt(2, 2,  cosY);	//  0   0   0  1
		}

		{ // Local scope for calculating the rotation matrix for Z
			float z = this->rotation.getZ();
			float cosZ = cos(z);
			float sinZ = sin(z);

			rotZ.setAt(0, 0,  cosZ);	// +cos -sin 0   0
			rotZ.setAt(0, 1, -sinZ);	// +sin +cos 0   0
			rotZ.setAt(1, 0,  sinZ);	//   0   0   1   0
			rotZ.setAt(1, 1,  cosZ);	//   0   0   0   1
		}

		this->rotationMatrix = rotZ * rotY * rotX;
		return this->rotationMatrix;
	}

	Matrix4f Transform::calculateScaleMatrix() {
		this->scaleMatrix = Matrix4f::identity();

		// A scale matrix is composed as an identity matrix whose diagonal
		// equals { X, Y, Z, 1 }							// x 0 0 0
		this->scaleMatrix.setAt(0, 0, this->scale.getX());	// 0 y 0 0
		this->scaleMatrix.setAt(1, 1, this->scale.getY());	// 0 0 z 0
		this->scaleMatrix.setAt(2, 2, this->scale.getZ());	// 0 0 0 1

		return this->scaleMatrix;
	}

	Matrix4f Transform::calculateTranslationMatrix() {
		this->translationMatrix = Matrix4f::identity();

		// A translation matrix is composed as an identity matrix whose last
		// column equals { X, Y, Z, 1 }.				// 1 0 0 x
		this->translationMatrix.setAt(0, 3, 
			this->translation.getX());					// 0 1 0 y
		this->translationMatrix.setAt(1, 3, 
			this->translation.getY());					// 0 0 1 z
		this->translationMatrix.setAt(2, 3, 
			this->translation.getZ());					// 0 0 0 1

		return this->translationMatrix;
	}
}