#include "..\..\include\math\Vector3f.h"

#include <math.h>

#include "..\..\include\math\Quaternion.h"

namespace Honeycomb::Math {
	Vector3f Vector3f::forward = Vector3f(0, 0, 1);
	Vector3f Vector3f::right = Vector3f(-1, 0, 0);
	Vector3f Vector3f::up = Vector3f(0, 1, 0);

	Vector3f::Vector3f() : Vector3f(0.0F, 0.0F, 0.0F) { }

	Vector3f::Vector3f(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector3f::~Vector3f() {

	}

	Vector3f Vector3f::add(Vector3f v2) {
		return Vector3f(this->x + v2.x, this->y + v2.y, this->z + v2.z);
	}

	Vector3f Vector3f::addTo(Vector3f v2) {
		Vector3f resultant = this->add(v2);

		this->set(resultant.x, resultant.y, resultant.z);
		return *this;
	}

	float Vector3f::angle(Vector3f v2) {
		// Calculate cos(theta) = (v1 . v2) / (|v1||v2|)
		float dot = this->dot(v2);
		float magMult = this->magnitude() * v2.magnitude();
		float cosTheta = dot / magMult;

		return (float)acos(cosTheta);
	}

	Vector3f Vector3f::cross(Vector3f v2) {
		// Calculate the cross product using the determinant of the cross
		// product matrix of this and the second vector.
		return Vector3f(
			this->y * v2.z - v2.y * this->z, 
			this->z * v2.x - v2.z * this->x, 
			this->x * v2.y - v2.x * this->y);
	}

	Vector3f Vector3f::crossTo(Vector3f v2) {
		Vector3f crossed = this->cross(v2);

		this->set(crossed.x, crossed.y, crossed.z);
		return *this;
	}

	float Vector3f::dot(Vector3f v2) {
		return this->x * v2.x + this->y * v2.y + this->z * v2.z;
	}

	void Vector3f::get(float &x, float &y, float &z) {
		x = this->x;
		y = this->y;
		z = this->z;
	}

	Vector3f& Vector3f::getGlobalForward() {
		return forward;
	}

	Vector3f& Vector3f::getGlobalRight() {
		return right;
	}

	Vector3f& Vector3f::getGlobalUp() {
		return up;
	}

	float& Vector3f::getX() {
		return this->x;
	}

	float& Vector3f::getY() {
		return this->y;
	}

	float& Vector3f::getZ() {
		return this->z;
	}

	float Vector3f::magnitude() {
		return (float)sqrt(x * x + y * y + z * z);
	}

	Vector3f Vector3f::normalize() {
		Vector3f normalized = this->normalized();

		this->set(normalized.x, normalized.y, normalized.z);
		return *this;
	}

	Vector3f Vector3f::normalized() {
		float mag = this->magnitude();

		return Vector3f(this->x / mag, this->y / mag, this->z / mag);
	}

	Vector3f Vector3f::rotate(Vector3f axis, float rad) {
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

	Vector3f Vector3f::rotate(Quaternion quat) {
		Quaternion rotated = quat * (*this) * quat.conjugated();

		return Vector3f(rotated.getX(), rotated.getY(), rotated.getZ());
	}

	Vector3f Vector3f::rotateTo(Vector3f axis, float rad) {
		Vector3f rotated = this->rotate(axis, rad);

		this->set(rotated.x, rotated.y, rotated.z);
		return *this;
	}

	Vector3f Vector3f::rotateTo(Quaternion quat) {
		Vector3f rotated = this->rotate(quat);

		this->set(rotated.x, rotated.y, rotated.z);
		return *this;
	}

	Vector3f Vector3f::scale(float scale) {
		return Vector3f(this->x * scale, this->y * scale, this->z * scale);
	}

	Vector3f Vector3f::scaleTo(float scale) {
		Vector3f scaled = this->scale(scale);

		this->set(scaled.x, scaled.y, scaled.z);
		return *this;
	}

	void Vector3f::set(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void Vector3f::setX(float x) {
		this->x = x;
	}

	void Vector3f::setY(float y) {
		this->y = y;
	}

	void Vector3f::setZ(float z) {
		this->z = z;
	}

	float* Vector3f::vectorsToFloatBuffer(Vector3f vec[], int count) {
		// The float buffer array will store each component (total 3) for each
		// vector (total count), therefore the float buffer must store 
		// 3 * count elements.
		float *floatBuffer = new float[count * 3];

		for (int i = 0; i < count * 3; ) { // Go through the float buffer array
			// Store each component of the element into the float buffer. Each 
			// time a component is copied over, the current index is increased 
			// so that the next component is copied into the next slot in the 
			// float buffer.
			floatBuffer[i++] = vec[i / 3].getX();
			floatBuffer[i++] = vec[i / 3].getY();
			floatBuffer[i++] = vec[i / 3].getZ();
		}

		return floatBuffer;
	}

	Vector3f Vector3f::operator*(float scale) {
		return this->scale(scale);
	}

	Vector3f Vector3f::operator*=(float scale) {
		return this->scaleTo(scale);
	}

	Vector3f Vector3f::operator/(float scale) {
		return this->scale(1.0F / scale);
	}

	Vector3f Vector3f::operator/=(float scale) {
		return this->scale(1.0F / scale);
	}

	Vector3f Vector3f::operator+(Vector3f v2) {
		return this->add(v2);
	}

	Vector3f Vector3f::operator+=(Vector3f v2) {
		return this->addTo(v2);
	}

	Vector3f Vector3f::operator-() {
		return this->scale(-1.0F);
	}

	Vector3f Vector3f::operator-(Vector3f v2) {
		return this->add(-v2);
	}

	Vector3f Vector3f::operator-=(Vector3f v2) {
		return this->addTo(-v2);
	}
}