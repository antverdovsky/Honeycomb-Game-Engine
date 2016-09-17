#include <math.h>

#include "..\..\include\math\Vector3f.h"

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
	// Calculate cos(theta) = (v1 * v2) / (|v1||v2|)
	float dot = this->dot(v2);
	float magMult = this->magnitude() * v2.magnitude();
	float cosTheta = dot / magMult;

	return acos(cosTheta);
}

Vector3f Vector3f::cross(Vector3f v2) {
	// TODO (matricies requried!)

	return Vector3f(0, 0, 0);
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

float Vector3f::getX() {
	return this->x;
}

float Vector3f::getY() {
	return this->y;
}

float Vector3f::getZ() {
	return this->z;
}

float Vector3f::magnitude() {
	return sqrt(x * x + y * y + z * z);
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
	// TODO (matricies requried!)

	return Vector3f(0, 0, 0);
}

Vector3f Vector3f::rotateTo(Vector3f axis, float rad) {
	// TODO (matrices required!)

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