#include <math.h>

#include "..\..\include\math\Quaternion.h"
#include "..\..\include\math\Vector3f.h"

using Honeycomb::Math::Vector3f;
using Honeycomb::Math::Matrix4f;

namespace Honeycomb::Math {
	Quaternion::Quaternion() : Quaternion(0.0F, 0.0F, 0.0F, 1.0F) {

	}

	Quaternion::Quaternion(Vector3f axis, float rad) {
		// Calculate the sin and cos of the half angle.
		float sinHalfAngle = sin(rad / 2);
		float cosHalfAngle = cos(rad / 2);

		// Construct a Rotation Quaternion
		this->x = axis.getX() * sinHalfAngle;
		this->y = axis.getY() * sinHalfAngle;
		this->z = axis.getZ() * sinHalfAngle;
		this->w = cosHalfAngle;

		this->normalize();
	}

	Quaternion::Quaternion(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Quaternion::~Quaternion() {

	}

	Quaternion Quaternion::conjugate() {
		Quaternion conjugated = this->conjugated();

		this->set(conjugated.x, conjugated.y, conjugated.z, conjugated.w);
		return *this;
	}

	Quaternion Quaternion::conjugated() {
		return Quaternion(-x, -y, -z, w);
	}

	void Quaternion::get(float &x, float &y, float &z, float &w) {
		x = this->x;
		y = this->y;
		z = this->z;
		w = this->w;
	}

	Vector3f Quaternion::getForwardVector() {
		return Vector3f::getGlobalForward().rotate(*this);
	}

	Vector3f Quaternion::getRightVector() {
		return Vector3f::getGlobalRight().rotate(*this);
	}

	Vector3f Quaternion::getUpVector() {
		return Vector3f::getGlobalUp().rotate(*this);
	}

	float& Quaternion::getW() {
		return this->w;
	}

	float& Quaternion::getX() {
		return this->x;
	}

	float& Quaternion::getY() {
		return this->y;
	}

	float& Quaternion::getZ() {
		return this->z;
	}

	float Quaternion::magnitude() {
		return (float)sqrt(x * x + y * y + z * z + w * w);
	}

	Quaternion Quaternion::multiply(Quaternion q2) {
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

	Quaternion Quaternion::multiply(Vector3f v) {
		// Convert the specified vector to a quaternion (multiplication code
		// will remain the same).
		Quaternion vecAsQuat = Quaternion(v.getX(), v.getY(), v.getZ(), 0.0F);

		return this->multiply(vecAsQuat);
	}

	Quaternion Quaternion::multiplyTo(Quaternion q2) {
		Quaternion multiplied = this->multiply(q2);

		this->set(multiplied.x, multiplied.y, multiplied.z, multiplied.w);
		return *this;
	}

	Quaternion Quaternion::multiplyTo(Vector3f v) {
		Quaternion vecAsQuat = Quaternion(v.getX(), v.getY(), v.getZ(), 0.0F);

		return this->multiplyTo(vecAsQuat);
	}

	Quaternion Quaternion::normalize() {
		Quaternion normalized = this->normalized();

		this->set(normalized.x, normalized.y, normalized.z, normalized.w);
		return *this;
	}

	Quaternion Quaternion::normalized() {
		float mag = this->magnitude();

		return Quaternion(this->x / mag, this->y / mag, this->z / mag,
			this->w / mag);
	}

	void Quaternion::set(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	void Quaternion::setW(float w) {
		this->w = w;
	}

	void Quaternion::setX(float x) {
		this->x = x;
	}

	void Quaternion::setY(float y) {
		this->y = y;
	}

	void Quaternion::setZ(float z) {
		this->z = z;
	}

	Matrix4f Quaternion::toRotationMatrix4f() {
		Matrix4f rotMat = Matrix4f::identity();
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

	Quaternion Quaternion::operator*(Quaternion q2) {
		return this->multiply(q2);
	}

	Quaternion Quaternion::operator*(Vector3f v) {
		return this->multiply(v);
	}

	Quaternion Quaternion::operator*=(Quaternion q2) {
		return this->multiplyTo(q2);
	}

	Quaternion Quaternion::operator*=(Vector3f v) {
		return this->multiplyTo(v);
	}
}