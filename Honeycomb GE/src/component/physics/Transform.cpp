#include "../../../include/component/physics/Transform.h"

#include <math.h>

#include "../../../include/math/Matrix4f.h"
#include "../../../include/math/Vector3f.h"
#include "../../../include/math/Quaternion.h"
#include "../../../include/math/MathUtils.h"

using Honeycomb::Conjuncture::Event;
using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Matrix4f;
using Honeycomb::Math::Quaternion;
using namespace Honeycomb::Math::Utils;

namespace Honeycomb { namespace Component { namespace Physics {
	Transform::Transform() : 
			Transform(Vector3f(), Quaternion(), Vector3f(1, 1, 1)) {

	}

	Transform::Transform(const Vector3f &pos, const Quaternion &rot, 
			const Vector3f &scl) {
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

	std::unique_ptr<Transform> Transform::clone() const {
		return std::unique_ptr<Transform>(this->cloneInternal());
	}

	Event& Transform::getChangedEvent() {
		return this->changedEvent;
	}

	const Event& Transform::getChangedEvent() const {
		return this->changedEvent;
	}

	GameComponentID Transform::getGameComponentID() const noexcept {
		return GameComponent::getGameComponentTypeID<Transform>();
	}

	const Quaternion& Transform::getGlobalRotation() const {
		return this->gblRotation;
	}

	const Vector3f& Transform::getGlobalScale() const {
		return this->gblScale;
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

	const Matrix4f& Transform::getMatrixOrientation() const {
		// For orientation/matrix we need to calculate both since each method
		// marks the rotation as being clean.
		if (this->isDirtyRotation) {
			this->calculateOrientationMatrix();
			this->calculateRotationMatrix();
		}

		return this->orientationMatrix;
	}

	const Matrix4f& Transform::getMatrixRotation() const {
		// See above
		if (this->isDirtyRotation) {
			this->calculateOrientationMatrix();
			this->calculateRotationMatrix();
		}

		return this->rotationMatrix;
	}

	const Matrix4f& Transform::getMatrixScale() const {
		if (this->isDirtyScale) {
			this->calculateScaleMatrix();
		}

		return this->scaleMatrix;
	}

	const Matrix4f& Transform::getMatrixTransformation() const {
		if (this->isDirtyTransformation) {
			this->calculateTransformationMatrix();
		}

		return this->transformMatrix;
	}

	const Matrix4f& Transform::getMatrixTranslation() const {
		if (this->isDirtyTranslation) {
			this->calculateTranslationMatrix();
		}

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

	Vector3f Transform::inverseTransformDirection(const Vector3f &dir) const {
		return this->getMatrixRotation().getInverse() * dir;
	}

	Vector3f Transform::inverseTransformPoint(const Vector3f &pos) const {
		return this->getMatrixTransformation().getInverse() * pos;
	}
	
	bool Transform::isOddNegativelyScaled() const {
		// If the Transform is negatively scaled on an odd number of axes, the
		// product of all of the components of the scale will be negative, so
		// we return true. Else, the product of all the components of the scale
		// will be positive, so we return false.
		return 0 >
			this->gblScale.getX() * 
			this->gblScale.getY() *  
			this->gblScale.getZ();
	}

	void Transform::onStart() {
		this->calculateOrientationMatrix();
		this->calculateTranslationMatrix();
		this->calculateRotationMatrix();
		this->calculateScaleMatrix();
		this->calculateTransformationMatrix();
		
		this->changedEvent.onEvent();
	}

	void Transform::setRotation(const Quaternion &rot, const Space &space) {
		if (space == Space::LOCAL) {
			this->lclRotation = rot;
			if (this->parent == nullptr) this->gblRotation = rot;
			else this->gblRotation = this->parent->gblRotation * rot;
		} else {
			this->gblRotation = rot;
			if (this->parent == nullptr) this->lclRotation = rot;
			else this->lclRotation = 
				this->parent->gblRotation.getInverse() * rot;
		}

		this->calculateOrientationMatrix();
		this->calculateRotationMatrix();
		this->calculateTransformationMatrix();

		this->changedEvent.onEvent();
		this->isDirtyRotation = true;
		this->isDirtyTransformation = true;
	}

	void Transform::setScale(const Vector3f &scl, const Space &space) {
		if (space == Space::LOCAL) {
			// If the scaling is local, set the local scale and calculate the 
			// new global scale using the parent's global scale.
			this->lclScale = scl;
			if (this->parent == nullptr) this->gblScale = scl;
			else this->gblScale = this->parent->gblScale.multiply(scl);
		} else {
			// If the scaling is global, set the global scale and calculate the 
			// new local scale using the inverse of the parent's global scale.
			this->gblScale = scl;
			if (this->parent == nullptr) this->lclScale = scl;
			else this->lclScale = this->parent->gblScale.divide(scl);
		}

		this->calculateScaleMatrix();
		this->calculateTransformationMatrix();

		this->changedEvent.onEvent();
		this->isDirtyScale = true;
		this->isDirtyTransformation = true;
	}

	void Transform::setTranslation(const Vector3f &p, const Space& space) {
		if (space == Space::LOCAL) {
			// If the translation is local, set the local translation and
			// calculate the new global position using the transform point
			// relative to the parent.
			this->lclTranslation = p; 
			if (this->parent == nullptr)  this->gblTranslation = p;
			else this->gblTranslation = this->parent->transformPoint(p);
		} else {
			// If the translation is global, set the global translation and
			// calculate the new local position using the inverse transform
			// point relative to the parent.
			this->gblTranslation = p;
			if (this->parent == nullptr) this->lclTranslation = p;
			else this->lclTranslation = this->parent->inverseTransformPoint(p);
		}
		
		// Recalculate Translation & Transformation, trigger changed event
		this->calculateTranslationMatrix();
		this->calculateTransformationMatrix();

		this->changedEvent.onEvent();
		this->isDirtyTranslation = true;
		this->isDirtyTransformation = true;
	}

	void Transform::rotate(const Vector3f &axis, const float &rad, 
			const Space &space) {
		// If the space specified is global, then the vector passed in is
		// global and can just be passed to RotateAround. Otherwise, if the 
		// space specified is local, then the vector must be changed from the 
		// local coordinate system of this Transform to the global.
		Vector3f global = space == Space::GLOBAL ?
			axis : this->transformDirection(axis);
		this->rotateAround(this->gblTranslation, global, rad);
	}

	void Transform::rotateAround(const Vector3f &center, const Vector3f &axis, 
			const float &rad) {
		// Fetch the old position and rotation of this Transform
		Vector3f oldPos = this->gblTranslation;
		Quaternion oldRot = this->gblRotation;
		
		// Get the rotation quaternion for the axis and radian amount provided
		// and the displacement from the current position to the center of the
		// axis of rotation. Rotate this displacement using the rotation 
		// quaternion. Axis must be normalized or the object will rotate more
		// than the amount of radians specified!
		Quaternion rot = Quaternion(axis.normalized(), rad);
		Vector3f direction = oldPos - center;
		direction = direction.rotate(rot);

		// Calculate the new translation of the Transform and the new rotation
		// (for the rotation, the object should look at the center position).
		// Vector3f newPos = center + direction;
		Quaternion newRot = oldRot * oldRot.getInverse() * rot * oldRot;

		// Apply the new Rotation and Translation
		this->setTranslation(center + direction);
		this->setRotation(newRot);
	}

	Vector3f Transform::transformDirection(const Vector3f &dir) const {
		return this->getMatrixRotation() * dir;
	}

	Vector3f Transform::transformPoint(const Vector3f &pos) const {
		// Multiply pos by the transformation matrix in order to account for
		// all transformations (scale, rotation, position).
		return this->getMatrixTransformation() * pos;
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

	const Matrix4f& Transform::calculateOrientationMatrix() const {
		this->orientationMatrix = Matrix4f::getMatrixIdentity();

		// Calculate new directions using the rotations
		this->forward = this->gblRotation.getForwardVector().normalized();
		this->right = this->gblRotation.getRightVector().normalized();
		this->up = this->gblRotation.getUpVector().normalized();

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

		this->isDirtyRotation = false;
		return this->orientationMatrix;
	}

	const Matrix4f& Transform::calculateTransformationMatrix() const {
		// Create individual matricies for each component of the transform
		Matrix4f transMat = this->getMatrixTranslation();
		Matrix4f rotMat = this->getMatrixRotation();
		Matrix4f sclMat = this->getMatrixScale();

		// Perform matrix multiplication on the components (first scale, then
		// rotate, then translate).
		this->transformMatrix = transMat * rotMat * sclMat;

		this->isDirtyTransformation = false;
		return this->transformMatrix;
	}

	const Matrix4f& Transform::calculateRotationMatrix() const {
		this->rotationMatrix = this->gblRotation.toRotationMatrix4f();

		this->isDirtyRotation = false;
		return this->rotationMatrix;
	}

	const Matrix4f& Transform::calculateScaleMatrix() const {
		this->scaleMatrix = Matrix4f::getMatrixIdentity();

		// A scale matrix is composed as an identity matrix whose diagonal
		// equals { X, Y, Z, 1 }
		this->scaleMatrix.setAt(0, 0, this->gblScale.getX());
		this->scaleMatrix.setAt(1, 1, this->gblScale.getY());
		this->scaleMatrix.setAt(2, 2, this->gblScale.getZ());

		// Return the Scale Matrix, which should look like
		// [  X   0.0  0.0  0.0 ]
		// [ 0.0   Y   0.0  0.0 ]
		// [ 0.0  0.0   Z   0.0 ]
		// [ 0.0  0.0  0.0  1.0 ]
		this->isDirtyScale = false;
		return this->scaleMatrix;
	}

	const Matrix4f& Transform::calculateTranslationMatrix() const {
		this->translationMatrix = Matrix4f::getMatrixIdentity();

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
		this->isDirtyTranslation = false;
		return this->translationMatrix;
	}

	void Transform::onParentChange() {
		// Whenever the parent changes its translation, rotation or scaling,
		// global variables of this Transform must change as well (though local
		// always remains the same when parent changes!).
		this->setTranslation(this->lclTranslation, Space::LOCAL);
		this->setRotation(this->lclRotation, Space::LOCAL);
		this->setScale(this->lclScale, Space::LOCAL);
	}

	void Transform::setParent(Transform *parent) {
		// If the new parent is NULL and the current parent is not NULL, unlink
		// from the current parent. If the new parent is NULL and the current
		// parent is NULL, nothing is modified.
		if (parent == nullptr && this->parent != nullptr) {
			this->parent->changedEvent -= &this->parentChanged;
			this->parent = nullptr;
		} else if (parent != nullptr) {	   // If the new parent is not NULL
			// If the current parent is not NULL, unsubscribe from the current
			// parent's changed event.
			if (this->parent != nullptr)
				this->parent->changedEvent -= &this->parentChanged;

			// Subscribe to the new parent's changed event and set the argument
			// as the new parent.
			parent->changedEvent += &this->parentChanged;
			this->parent = parent;
		}

		// Transform is technically changed anytime its parent is changed
		this->changedEvent.onEvent();
	}

	Transform* Transform::cloneInternal() const {
		Transform *transf = new Transform();

		transf->lclTranslation = this->lclTranslation;
		transf->lclRotation = this->lclRotation;
		transf->lclScale = this->lclScale;

		transf->gblTranslation = this->gblTranslation;
		transf->gblRotation = this->gblRotation;
		transf->gblScale = this->gblScale;

		transf->transformMatrix = this->transformMatrix;
		transf->translationMatrix = this->translationMatrix;
		transf->rotationMatrix = this->rotationMatrix;
		transf->scaleMatrix = this->scaleMatrix;
		transf->orientationMatrix = this->orientationMatrix;

		transf->isDirtyRotation = this->isDirtyRotation;
		transf->isDirtyScale = this->isDirtyScale;
		transf->isDirtyTransformation = this->isDirtyTransformation;
		transf->isDirtyRotation = this->isDirtyRotation;

		return transf;
	}

	bool Transform::getProperty_AllowsMultiple() const noexcept {
		return false;
	}

	bool Transform::getProperty_Permanent() const noexcept {
		return true;
	}
} } }
