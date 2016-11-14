#include "..\..\..\include\component\physics\Transform.h";

#include <math.h>

#include "..\..\..\include\math\Matrix4f.h"
#include "..\..\..\include\math\Vector3f.h"
#include "..\..\..\include\math\Quaternion.h"
#include "..\..\..\include\math\MathUtils.h"

using Honeycomb::Conjuncture::Event;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Math::Quaternion;
using namespace Honeycomb::Math::Utils;

namespace Honeycomb::Component::Physics {
	Transform::Transform() : 
			Transform(Vector3f(), Quaternion(), Vector3f(1, 1, 1)) {

	}

	Transform::Transform(Vector3f pos, Quaternion rot, Vector3f scl)
			: GameComponent("Transform") {
		this->setTranslation(pos);
		this->setRotation(rot);
		this->setScale(scl);

		this->localForward = Vector3f::getGlobalForward();
		this->localRight = Vector3f::getGlobalRight();
		this->localUp = Vector3f::getGlobalUp();
	}

	Event& Transform::getChangedEvent() {
		return this->changedEvent;
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

	Matrix4f Transform::getRotationMatrix() {
		return this->rotationMatrix;
	}

	Matrix4f Transform::getScaleMatrix() {
		return this->scaleMatrix;
	}

	Matrix4f Transform::getTransformationMatrix() {
		return this->transformationMatrix;
	}

	Matrix4f Transform::getTranslationMatrix() {
		return this->translationMatrix;
	}

	Quaternion Transform::getRotation() {
		return this->rotation;
	}

	Vector3f Transform::getScale() {
		return this->scale;
	}

	Vector3f Transform::getTranslation() {
		return this->translation;
	}
	
	void Transform::start() {
		this->calculateOrientationMatrix();
		this->calculateTranslationMatrix();
		this->calculateRotationMatrix();
		this->calculateScaleMatrix();
		this->calculateTransformationMatrix();
	}

	void Transform::setRotation(Quaternion quat) {
		this->rotation.set(quat.getX(), quat.getY(), quat.getZ(), quat.getW());

		this->calculateOrientationMatrix();
		this->calculateRotationMatrix();
		this->calculateTransformationMatrix();

		this->changedEvent.onEvent();
	}

	void Transform::setScale(Vector3f vec) {
		this->scale.set(vec.getX(), vec.getY(), vec.getZ());

		this->calculateScaleMatrix();
		this->calculateTransformationMatrix();

		this->changedEvent.onEvent();
	}

	void Transform::setTranslation(Vector3f vec) {
		this->translation.set(vec.getX(), vec.getY(), vec.getZ());

		this->calculateTranslationMatrix();
		this->calculateTransformationMatrix();

		this->changedEvent.onEvent();
	}

	void Transform::rotate(Vector3f axis, float rad) {
		this->setRotation(Quaternion(axis, rad) * this->rotation);
	}

	void Transform::translate(Vector3f vec) {
		this->setTranslation(this->translation + vec);
	}

	Matrix4f Transform::calculateOrientationMatrix() {
		this->orientationMatrix = Matrix4f::identity();

		// Calculate new directions using the rotations
		this->localForward = this->rotation.getForwardVector().normalized();
		this->localRight = this->rotation.getRightVector().normalized();
		this->localUp = this->rotation.getUpVector().normalized();

		// Copy each X component from each directional vector to Orientation,
		// so the result of the first column looks like: [ r.X, u.X, f.X ]'.
		this->orientationMatrix.setAt(0, 0, this->localRight.getX());
		this->orientationMatrix.setAt(1, 0, this->localUp.getX());
		this->orientationMatrix.setAt(2, 0, this->localForward.getX());

		// Copy each Y component from each directional vector to Orientation,
		// so the result of the second column looks like: [ r.Y, u.Y, f.Y ]'.
		this->orientationMatrix.setAt(0, 1, this->localRight.getY());
		this->orientationMatrix.setAt(1, 1, this->localUp.getY());
		this->orientationMatrix.setAt(2, 1, this->localForward.getY());

		// Copy each Z component from each directional vector to Orientation,
		// so the result of the third column looks like: [ r.Z, u.Z, f.Z ]'.
		this->orientationMatrix.setAt(0, 2, this->localRight.getZ());
		this->orientationMatrix.setAt(1, 2, this->localUp.getZ());
		this->orientationMatrix.setAt(2, 2, this->localForward.getZ());

		return this->orientationMatrix;
	}

	Matrix4f Transform::calculateTransformationMatrix() {
		// Create individual matricies for each component of the transform
		Matrix4f transMat = this->getTranslationMatrix();
		Matrix4f rotMat = this->getRotationMatrix();
		Matrix4f sclMat = this->getScaleMatrix();

		// Perform matrix multiplication on the components (first scale, then
		// rotate, then translate).
		this->transformationMatrix = transMat *  rotMat * sclMat;
		return this->transformationMatrix;
	}

	Matrix4f Transform::calculateRotationMatrix() {
		this->rotationMatrix = this->rotation.toRotationMatrix4f();

		return this->rotationMatrix;
	}

	Matrix4f Transform::calculateScaleMatrix() {
		this->scaleMatrix = Matrix4f::identity();

		// A scale matrix is composed as an identity matrix whose diagonal
		// equals { X, Y, Z, 1 }
		this->scaleMatrix.setAt(0, 0, this->scale.getX());
		this->scaleMatrix.setAt(1, 1, this->scale.getY());
		this->scaleMatrix.setAt(2, 2, this->scale.getZ());

		// Return the Scale Matrix, which should look like
		// [  X   0.0  0.0  0.0 ]
		// [ 0.0   Y   0.0  0.0 ]
		// [ 0.0  0.0   Z   0.0 ]
		// [ 0.0  0.0  0.0  1.0 ]
		return this->scaleMatrix;
	}

	Matrix4f Transform::calculateTranslationMatrix() {
		this->translationMatrix = Matrix4f::identity();

		// A translation matrix is composed as an identity matrix whose last
		// column equals { X, Y, Z, 1 }.				
		this->translationMatrix.setAt(0, 3,
			this->translation.getX());
		this->translationMatrix.setAt(1, 3,
			this->translation.getY());
		this->translationMatrix.setAt(2, 3,
			this->translation.getZ());

		// Return the Translation Matrix, which should look like
		// [ 1.0  0.0  0.0   x  ]
		// [ 0.0  1.0  0.0   y  ]
		// [ 0.0  0.0  1.0   z  ]
		// [ 0.0  0.0  0.0  1.0 ]
		return this->translationMatrix;
	}
}