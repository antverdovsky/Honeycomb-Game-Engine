#include "..\..\..\include\component\physics\Transform.h"

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

	Transform::Transform(const Vector3f &pos, const Quaternion &rot, 
			const Vector3f &scl) : GameComponent("Transform") {
		this->parent = nullptr;

		this->setTranslation(pos);
		this->setRotation(rot);
		this->setScale(scl);

		this->forward = Vector3f::getGlobalForward();
		this->right = Vector3f::getGlobalRight();
		this->up = Vector3f::getGlobalUp();

		// Whenever the parent changes, recalculate the global transformation
		// matrix for this Transform.
		this->parentChanged.addAction(
			std::bind(&Transform::onParentChange, this));
	}

	Transform* Transform::clone() const {
		Transform *transf = new Transform(*this);

		// Cloned transform becomes an independent component, and thus must
		// lose its parent and its children.
		transf->changedEvent.clearEventHandlers();
		transf->parent = nullptr;

		// We must also rebind the cloned Transform's parent changed event
		transf->parentChanged.clearActions();
		transf->parentChanged.addAction(
			std::bind(&Transform::onParentChange, transf));

		return transf;
	}

	Event& Transform::getChangedEvent() {
		return this->changedEvent;
	}

	const Event& Transform::getChangedEvent() const {
		return this->changedEvent;
	}

	const Vector3f& Transform::getGlobalTranslation() const {
		return this->gblTranslation;
	}

	const Vector3f& Transform::getLocalForward() const {
		return this->forward;
	}

	const Vector3f& Transform::getLocalRight() const {
		return this->right;
	}

	const Vector3f& Transform::getLocalUp() const {
		return this->up;
	}

	const Matrix4f& Transform::getOrientationMatrix() const {
		return this->orientationMatrix;
	}

	const Matrix4f& Transform::getRotationMatrix() const {
		return this->rotationMatrix;
	}

	const Matrix4f& Transform::getScaleMatrix() const {
		return this->scaleMatrix;
	}

	const Matrix4f& Transform::getTransformationMatrix() const {
		return this->transformationMatrix;
	}

	const Matrix4f& Transform::getTranslationMatrix() const {
		return this->translationMatrix;
	}

	const Quaternion& Transform::getLocalRotation() const {
		return this->lclRotation;
	}

	const Vector3f& Transform::getLocalScale() const {
		return this->lclScale;
	}

	const Vector3f& Transform::getLocalTranslation() const {
		return this->lclTranslation;
	}

	Vector3f Transform::inverseTransformPoint(const Vector3f &pos) const {
		if (this->parent == nullptr)
			return pos;
		else
			return pos - this->parent->gblTranslation;
	}
	
	void Transform::start() {
		this->calculateOrientationMatrix();
		this->calculateTranslationMatrix();
		this->calculateRotationMatrix();
		this->calculateScaleMatrix();
		this->calculateTransformationMatrix();
		
		this->changedEvent.onEvent();
	}

	void Transform::setRotation(const Quaternion &quat) {
		this->lclRotation = quat;

		this->calculateOrientationMatrix();
		this->calculateRotationMatrix();
		this->calculateTransformationMatrix();

		this->changedEvent.onEvent();
	}

	void Transform::setScale(const Vector3f &vec) {
		this->lclScale = vec;

		this->calculateScaleMatrix();
		this->calculateTransformationMatrix();

		this->changedEvent.onEvent();
	}

	void Transform::setTranslation(const Vector3f &pos, const Space& space) {
		if (space == Space::LOCAL) {
			// If the translation is local, set the local translation and
			// calculate the new global position using the transform point
			// method.
			this->lclTranslation = pos;
			this->gblTranslation = transformPoint(pos);
		} else {
			// If the translation is global, set the global translation and
			// calculate the new local position using the inverse transform
			// point.
			this->gblTranslation = pos;
			this->lclTranslation = inverseTransformPoint(pos);
		}
		
		this->calculateTranslationMatrix();
		this->calculateTransformationMatrix();

		this->changedEvent.onEvent();
	}

	void Transform::rotate(const Vector3f &axis, const float &rad) {
		this->rotate(Quaternion(axis, rad));
	}

	void Transform::rotate(const Quaternion &quat) {
		this->setRotation(quat * this->lclRotation);
	}

	Vector3f Transform::transformDirection(const Vector3f &dir) const {
		return this->rotationMatrix * dir;
	}

	Vector3f Transform::transformPoint(const Vector3f &pos) const {
		if (this->parent == nullptr) 
			return pos;
		else 
			return this->parent->gblTranslation + pos;
	}

	void Transform::translate(const Vector3f &vec, const Space &space) {
		// If the space specified is global, then the vector passed in is
		// global and can just be added to the local translation. Otherwise,
		// if the space specified is local, then the vector must be changed
		// from the local coordinate system of this Transform to the global.
		Vector3f global = space == Space::GLOBAL ? 
			vec : this->transformDirection(vec);
		this->setTranslation(this->gblTranslation + global);
	}

	void Transform::translate(const Vector3f &vec, const Transform &relTo) {
		// Treat the vector as a local vector of the relative transform, so
		// pass it through the transform direction method to get the global
		// vector, then translate on the global axes.
		this->translate(relTo.transformDirection(vec), Space::GLOBAL);
	}

	const Matrix4f& Transform::calculateOrientationMatrix() {
		this->orientationMatrix = Matrix4f::identity();

		// Calculate new directions using the rotations
		this->forward = this->lclRotation.getForwardVector().normalized();
		this->right = this->lclRotation.getRightVector().normalized();
		this->up = this->lclRotation.getUpVector().normalized();

		// Copy each X component from each directional vector to Orientation,
		// so the result of the first column looks like: [ r.X, u.X, f.X ]'.
		this->orientationMatrix.setAt(0, 0, this->right.getX());
		this->orientationMatrix.setAt(1, 0, this->up.getX());
		this->orientationMatrix.setAt(2, 0, this->forward.getX());

		// Copy each Y component from each directional vector to Orientation,
		// so the result of the second column looks like: [ r.Y, u.Y, f.Y ]'.
		this->orientationMatrix.setAt(0, 1, this->right.getY());
		this->orientationMatrix.setAt(1, 1, this->up.getY());
		this->orientationMatrix.setAt(2, 1, this->forward.getY());

		// Copy each Z component from each directional vector to Orientation,
		// so the result of the third column looks like: [ r.Z, u.Z, f.Z ]'.
		this->orientationMatrix.setAt(0, 2, this->right.getZ());
		this->orientationMatrix.setAt(1, 2, this->up.getZ());
		this->orientationMatrix.setAt(2, 2, this->forward.getZ());

		return this->orientationMatrix;
	}

	const Matrix4f& Transform::calculateTransformationMatrix() {
		// Create individual matricies for each component of the transform
		Matrix4f transMat = this->getTranslationMatrix();
		Matrix4f rotMat = this->getRotationMatrix();
		Matrix4f sclMat = this->getScaleMatrix();

		// Perform matrix multiplication on the components (first scale, then
		// rotate, then translate).
		this->transformationMatrix = transMat *  rotMat * sclMat;
		return this->transformationMatrix;
	}

	const Matrix4f& Transform::calculateRotationMatrix() {
		this->rotationMatrix = this->lclRotation.toRotationMatrix4f();

		return this->rotationMatrix;
	}

	const Matrix4f& Transform::calculateScaleMatrix() {
		this->scaleMatrix = Matrix4f::identity();

		// A scale matrix is composed as an identity matrix whose diagonal
		// equals { X, Y, Z, 1 }
		this->scaleMatrix.setAt(0, 0, this->lclScale.getX());
		this->scaleMatrix.setAt(1, 1, this->lclScale.getY());
		this->scaleMatrix.setAt(2, 2, this->lclScale.getZ());

		// Return the Scale Matrix, which should look like
		// [  X   0.0  0.0  0.0 ]
		// [ 0.0   Y   0.0  0.0 ]
		// [ 0.0  0.0   Z   0.0 ]
		// [ 0.0  0.0  0.0  1.0 ]
		return this->scaleMatrix;
	}

	const Matrix4f& Transform::calculateTranslationMatrix() {
		this->translationMatrix = Matrix4f::identity();

		// A translation matrix is composed as an identity matrix whose last
		// column equals { X, Y, Z, 1 }.				
		this->translationMatrix.setAt(0, 3,
			this->gblTranslation.getX());
		this->translationMatrix.setAt(1, 3,
			this->gblTranslation.getY());
		this->translationMatrix.setAt(2, 3,
			this->gblTranslation.getZ());

		// Return the Translation Matrix, which should look like
		// [ 1.0  0.0  0.0   x  ]
		// [ 0.0  1.0  0.0   y  ]
		// [ 0.0  0.0  1.0   z  ]
		// [ 0.0  0.0  0.0  1.0 ]
		return this->translationMatrix;
	}

	void Transform::onParentChange() {
		// Whenever the parent changes its translation, rotation or scaling,
		// global variables of this Transform must change as well (though local
		// always remains the same when parent changes!).
		this->setTranslation(this->lclTranslation, Space::LOCAL);
	}

	void Transform::setParent(Transform *parent) {
		// If the new parent is NULL and the current parent is not NULL, unlink
		// from the current parent. If the new parent is NULL and the current
		// parent is NULL, nothing is modified.
		if (parent == nullptr && this->parent != nullptr) {
			this->parent->changedEvent -= this->parentChanged;
			this->parent = nullptr;
		} else if (parent != nullptr) {	   // If the new parent is not NULL
			// If the current parent is not NULL, unsubscribe from the current
			// parent's changed event.
			if (this->parent != nullptr)
				this->parent->changedEvent -= this->parentChanged;

			// Subscribe to the new parent's changed event and set the argument
			// as the new parent.
			parent->changedEvent += this->parentChanged;
			this->parent = parent;
		}

		// Transform is technically changed anytime its parent is changed
		this->changedEvent.onEvent();
	}
}