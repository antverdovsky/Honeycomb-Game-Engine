#include "../../include/math/Quaternion.h"

#include <math.h>

#include "../../include/math/Vector3f.h"

using Honeycomb::Math::Matrix4f;
using Honeycomb::Math::Vector3f;

namespace Honeycomb { namespace Math {
	Quaternion::Quaternion() : Quaternion(0.0F, 0.0F, 0.0F, 1.0F) {

	}

	Quaternion::Quaternion(const Vector3f &axis, const float &rad) {
		// Calculate the sin and cos of the half angle.
		float sinHalfAngle = (float)sin(rad / 2);
		float cosHalfAngle = (float)cos(rad / 2);

		// Construct a Rotation Quaternion
		this->x = axis.getX() * sinHalfAngle;
		this->y = axis.getY() * sinHalfAngle;
		this->z = axis.getZ() * sinHalfAngle;
		this->w = cosHalfAngle;

		this->normalize();
	}

	Quaternion::Quaternion(const float &x, const float &y, const float &z, 
			const float &w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion::~Quaternion() {

	}

	Quaternion& Quaternion::conjugate() {
		Quaternion conjugated = this->conjugated();

		this->set(conjugated.x, conjugated.y, conjugated.z, conjugated.w);
		return *this;
	}

	Quaternion Quaternion::conjugated() const {
		return Quaternion(-x, -y, -z, w);
	}

	void Quaternion::get(float &x, float &y, float &z, float &w) const {
		x = this->x;
		y = this->y;
		z = this->z;
		w = this->w;
	}

	Vector3f Quaternion::getForwardVector() const {
		return Vector3f::getGlobalForward().rotate(*this);
	}

	Quaternion Quaternion::getInverse() const {
		float mag2 = this->magnitude2();
		return Quaternion(
			-this->x / mag2, -this->y / mag2, -this->z / mag2, this->w / mag2);
	}

	Vector3f Quaternion::getRightVector() const {
		return Vector3f::getGlobalRight().rotate(*this);
	}

	Vector3f Quaternion::getUpVector() const {
		return Vector3f::getGlobalUp().rotate(*this);
	}

	float& Quaternion::getW() {
		return this->w;
	}

	const float& Quaternion::getW() const {
		return this->w;
	}

	float& Quaternion::getX() {
		return this->x;
	}

	const float& Quaternion::getX() const {
		return this->x;
	}

	float& Quaternion::getY() {
		return this->y;
	}

	const float& Quaternion::getY() const {
		return this->y;
	}

	float& Quaternion::getZ() {
		return this->z;
	}

	const float& Quaternion::getZ() const {
		return this->z;
	}

	float Quaternion::magnitude() const {
		return (float)sqrt(this->magnitude2());
	}

	float Quaternion::magnitude2() const {
		return (float)(x * x + y * y + z * z + w * w);
	}
	
	Quaternion Quaternion::multiply(const Quaternion &q2) const {
		// Calculate the vectors composed of the real components of the
		// quaternions and calculate the cross and dot products of the vectors.
		Vector3f a = Vector3f(this->x, this->y, this->z);
		Vector3f b = Vector3f(q2.x, q2.y, q2.z);
		Vector3f cross = a.cross(b);
		float dot = a.dot(b);

		// Calculate the sum of the a and b vectors after they have been scaled
		// by the w-components. Then add the sum to the cross product to get 
		// the real components of the new Quaternion.
		Vector3f part = (b * this->w) + (a * q2.w);
		Vector3f full = part + cross;

		return Quaternion(full.getX(), full.getY(), full.getZ(),
			this->w * q2.w - dot);
	}

	Quaternion Quaternion::multiply(const Vector3f &v) const {
		// Convert the specified vector to a quaternion (multiplication code
		// will remain the same).
		Quaternion vecAsQuat = Quaternion(v.getX(), v.getY(), v.getZ(), 0.0F);

		return this->multiply(vecAsQuat);
	}

	Quaternion& Quaternion::multiplyTo(const Quaternion &q2) {
		Quaternion multiplied = this->multiply(q2);

		this->set(multiplied.x, multiplied.y, multiplied.z, multiplied.w);
		return *this;
	}

	Quaternion& Quaternion::multiplyTo(const Vector3f &v) {
		Quaternion vecAsQuat = Quaternion(v.getX(), v.getY(), v.getZ(), 0.0F);

		return this->multiplyTo(vecAsQuat);
	}

	Quaternion& Quaternion::normalize() {
		Quaternion normalized = this->normalized();

		this->set(normalized.x, normalized.y, normalized.z, normalized.w);
		return *this;
	}

	Quaternion Quaternion::normalized() const {
		float mag = this->magnitude();

		return Quaternion(this->x / mag, this->y / mag, this->z / mag,
			this->w / mag);
	}

	void Quaternion::set(const float &x, const float &y, const float &z, 
			const float &w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	void Quaternion::setW(const float &W) {
		this->w = w;
	}

	void Quaternion::setX(const float &x) {
		this->x = x;
	}

	void Quaternion::setY(const float &y) {
		this->y = y;
	}

	void Quaternion::setZ(const float &z) {
		this->z = z;
	}

	Matrix4f Quaternion::toRotationMatrix4f() {
		Matrix4f rotMat = Matrix4f::getMatrixIdentity();
		this->normalize();

		rotMat.setAt(0, 0, 1 - 2 * this->y * this->y - 2 * this->z * this->z);
		rotMat.setAt(0, 1, 2 * this->x * this->y - 2 * this->z * this->w);
		rotMat.setAt(0, 2, 2 * this->x * this->z + 2 * this->y * this->w);

		rotMat.setAt(1, 0, 2 * this->x * this->y + 2 * this->z * this->w);
		rotMat.setAt(1, 1, 1 - 2 * this->x * this->x - 2 * this->z * this->z);
		rotMat.setAt(1, 2, 2 * this->y * this->z - 2 * this->x * this->w);

		rotMat.setAt(2, 0, 2 * this->x * this->z - 2 * this->y * this->w);
		rotMat.setAt(2, 1, 2 * this->y * this->z + 2 * this->x * this->w);
		rotMat.setAt(2, 2, 1 - 2 * this->x * this->x - 2 * this->y * this->y);

		return rotMat;
	}

	Quaternion Quaternion::operator*(const Quaternion &q2) const {
		return this->multiply(q2);
	}

	Quaternion Quaternion::operator*(const Vector3f &v) const {
		return this->multiply(v);
	}

	Quaternion& Quaternion::operator*=(const Quaternion &q2) {
		return this->multiplyTo(q2);
	}

	Quaternion& Quaternion::operator*=(const Vector3f &v) {
		return this->multiplyTo(v);
	}
} }
