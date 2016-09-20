#include <math.h>

#include "..\..\include\math\Quaternion.h"
#include "..\..\include\math\Vector3f.h"

using Honeycomb::Math::Vector3f;

namespace Honeycomb::Math {
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

	float Quaternion::getW() {
		return this->w;
	}

	float Quaternion::getX() {
		return this->x;
	}

	float Quaternion::getY() {
		return this->y;
	}

	float Quaternion::getZ() {
		return this->z;
	}

	float Quaternion::magnitude() {
		return sqrt(x * x + y * y + z * z + w * w);
	}

	Quaternion Quaternion::multiply(Quaternion q2) {
		float x_ = q2.w * x + q2.x * w - q2.y * z + q2.z * y;
		float y_ = q2.w * y + q2.x * z + q2.y * w - q2.z * x;
		float z_ = q2.w * z - q2.x * y + q2.y * x + q2.z * w;
		float w_ = q2.w * w - q2.x * x - q2.y * y - q2.z * z;

		return Quaternion(x_, y_, z_, w_);
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
		Quaternion normalized = this->normalize();

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