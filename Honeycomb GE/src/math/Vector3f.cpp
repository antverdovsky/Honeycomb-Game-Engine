#include "../../include/math/Vector3f.h"

#include <math.h>

#include "../../include/math/Quaternion.h"

namespace Honeycomb { namespace Math {
	const Vector3f& Vector3f::getGlobalForward() {
		static Vector3f forward{ 0.0F, 0.0F, -1.0F };
		return forward;
	}

	const Vector3f& Vector3f::getGlobalRight() {
		static Vector3f right{ 1.0F, 0.0F, 0.0F };
		return right;
	}

	const Vector3f& Vector3f::getGlobalUp() {
		static Vector3f up{ 0.0F, 1.0F, 0.0F };
		return up;
	}

	Vector3f::Vector3f() : Vector3f(0.0F, 0.0F, 0.0F) {
	
	}

	Vector3f::Vector3f(const float &all) : Vector3f(all, all, all) {

	}

	Vector3f::Vector3f(const float &x, const float &y, const float &z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3f Vector3f::add(const Vector3f& v2) const {
		return Vector3f(this->x + v2.x, this->y + v2.y, this->z + v2.z);
	}
	
	Vector3f& Vector3f::addTo(const Vector3f& v2) {
		Vector3f resultant = this->add(v2);

		this->set(resultant.x, resultant.y, resultant.z);
		return *this;
	}

	float Vector3f::angle(const Vector3f& v2) const {
		// Calculate cos(theta) = (v1 . v2) / (|v1||v2|)
		float dot = this->dot(v2);
		float magMult = this->magnitude() * v2.magnitude();
		float cosTheta = dot / magMult;

		return (float)acos(cosTheta);
	}

	Vector3f Vector3f::cross(const Vector3f& v2) const {
		// Calculate the cross product using the determinant of the cross
		// product matrix of this and the second vector.
		return Vector3f(
			this->y * v2.z - v2.y * this->z, 
			this->z * v2.x - v2.z * this->x, 
			this->x * v2.y - v2.x * this->y);
	}

	Vector3f& Vector3f::crossTo(const Vector3f& v2) {
		Vector3f crossed = this->cross(v2);

		this->set(crossed.x, crossed.y, crossed.z);
		return *this;
	}

	Vector3f Vector3f::divide(const float &scale) const {
		return Vector3f(this->x / scale, this->y / scale, this->z / scale);
	}

	Vector3f Vector3f::divide(const Vector3f &v2) const {
		return Vector3f(this->x / v2.x, this->y / v2.y, this->z / v2.z);
	}

	Vector3f& Vector3f::divideTo(const float &scale) {
		Vector3f divided = this->divide(scale);

		this->set(divided.x, divided.y, divided.z);
		return *this;
	}

	Vector3f& Vector3f::divideTo(const Vector3f &v2) {
		Vector3f divided = this->divide(v2);

		this->set(divided.x, divided.y, divided.z);
		return *this;
	}

	float Vector3f::dot(const Vector3f& v2) const {
		return this->x * v2.x + this->y * v2.y + this->z * v2.z;
	}

	void Vector3f::get(float &x, float &y, float &z) const {
		x = this->x;
		y = this->y;
		z = this->z;
	}

	float& Vector3f::getX() {
		return this->x;
	}

	const float& Vector3f::getX() const {
		return this->x;
	}

	float& Vector3f::getY() {
		return this->y;
	}

	const float& Vector3f::getY() const {
		return this->y;
	}

	float& Vector3f::getZ() {
		return this->z;
	}

	const float& Vector3f::getZ() const {
		return this->z;
	}

	float Vector3f::magnitude() const {
		return (float)sqrt(this->magnitude2());
	}

	float Vector3f::magnitude2() const {
		return x * x + y * y + z * z;
	}

	Vector3f Vector3f::multiply(const Matrix4f &mat) const {
		return mat.multiply(*this);
	}

	Vector3f Vector3f::multiply(const Vector3f &vec) const {
		return Vector3f(this->x * vec.x, this->y * vec.y, this->z * vec.z);
	}

	Vector3f& Vector3f::multiplyTo(const Matrix4f &mat) {
		Vector3f prod = this->multiply(mat);

		this->set(prod.x, prod.y, prod.z);
		return *this;
	}

	Vector3f& Vector3f::multiplyTo(const Vector3f &vec) {
		Vector3f prod = this->multiply(vec);

		this->set(prod.x, prod.y, prod.z);
		return *this;
	}

	Vector3f& Vector3f::normalize() {
		Vector3f normalized = this->normalized();

		this->set(normalized.x, normalized.y, normalized.z);
		return *this;
	}

	Vector3f Vector3f::normalized() const {
		float mag = this->magnitude();

		return Vector3f(this->x / mag, this->y / mag, this->z / mag);
	}

	Vector3f Vector3f::rotate(const Vector3f &axis, const float &rad) const {
		// Construct a Rotation Quaternion which will rotate the vector.
		Quaternion rotQuat = Quaternion(axis, rad);
		Quaternion rotQuatConj = rotQuat.conjugated();

		// Multiply the Quaternion by this Vector instance to get the resulting
		// rotated Quaternion, and multiply by conjugate to cancel out the 
		// imaginary components.
		Quaternion result = rotQuat * (*this) * rotQuatConj;

		// All components of the rotated vector lie within the Quaternion.
		return Vector3f(result.getX(), result.getY(), result.getZ());
	}

	Vector3f Vector3f::rotate(const Quaternion &quat) const {
		Quaternion rotated = quat * (*this) * quat.conjugated();

		return Vector3f(rotated.getX(), rotated.getY(), rotated.getZ());
	}

	Vector3f& Vector3f::rotateTo(const Vector3f &axis, const float &rad) {
		Vector3f rotated = this->rotate(axis, rad);

		this->set(rotated.x, rotated.y, rotated.z);
		return *this;
	}

	Vector3f& Vector3f::rotateTo(const Quaternion &quat) {
		Vector3f rotated = this->rotate(quat);

		this->set(rotated.x, rotated.y, rotated.z);
		return *this;
	}

	Vector3f Vector3f::scale(const float &scale) const {
		return Vector3f(this->x * scale, this->y * scale, this->z * scale);
	}

	Vector3f& Vector3f::scaleTo(const float &scale) {
		Vector3f scaled = this->scale(scale);

		this->set(scaled.x, scaled.y, scaled.z);
		return *this;
	}

	void Vector3f::set(const float &x, const float &y, const float &z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Vector3f::setX(const float &x) {
		this->x = x;
	}

	void Vector3f::setY(const float &y) {
		this->y = y;
	}

	void Vector3f::setZ(const float &z) {
		this->z = z;
	}

	Vector3f Vector3f::operator*(const float &scale) const {
		return this->scale(scale);
	}

	Vector3f Vector3f::operator*(const Matrix4f &mat) const {
		return this->multiply(mat);
	}

	Vector3f Vector3f::operator*(const Vector3f &v2) const {
		return this->multiply(v2);
	}

	Vector3f& Vector3f::operator*=(const float &scale) {
		return this->scaleTo(scale);
	}

	Vector3f& Vector3f::operator*=(const Matrix4f &mat) {
		return this->multiplyTo(mat);
	}

	Vector3f& Vector3f::operator*=(const Vector3f &v2) {
		return this->multiplyTo(v2);
	}

	Vector3f Vector3f::operator/(const float &scale) const {
		return this->scale(1.0F / scale);
	}

	Vector3f& Vector3f::operator/=(const float &scale) {
		return this->scaleTo(1.0F / scale);
	}
	
	Vector3f Vector3f::operator+(const Vector3f &v2) const {
		return this->add(v2);
	}

	Vector3f& Vector3f::operator+=(const Vector3f &v2) {
		return this->addTo(v2);
	}

	Vector3f Vector3f::operator-() const {
		return this->scale(-1.0F);
	}

	Vector3f Vector3f::operator-(const Vector3f &v2) const {
		return this->add(-v2);
	}

	Vector3f& Vector3f::operator-=(const Vector3f &v2) {
		return this->addTo(-v2);
	}

	bool Vector3f::operator<(const Vector3f &v2) const {
		return this->magnitude2() < v2.magnitude2();
	}

	bool Vector3f::operator>(const Vector3f &v2) const {
		return this->magnitude2() > v2.magnitude2();
	}

	std::ostream& operator<<(std::ostream &stream, const Vector3f &vec) {
		return stream << "(" << vec.getX() << ", " << vec.getY() << ", " <<
				vec.getZ() << ")";
	}
} }
