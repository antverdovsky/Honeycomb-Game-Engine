#include <math.h>

#include "..\..\include\math\Vector2f.h"

Vector2f::Vector2f(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2f::~Vector2f() {

}

Vector2f Vector2f::add(Vector2f v2) {
	return Vector2f(this->x + v2.x, this->y + v2.y);
}

float Vector2f::angle(Vector2f v2) {
	// Calculate cos(theta) = (v1 * v2) / (|v1||v2|)
	float dot = this->dot(v2);
	float magMult = this->magnitude() * v2.magnitude();
	float cosTheta = dot / magMult;

	return acos(cosTheta);
}

float Vector2f::dot(Vector2f v2) {
	return this->x * v2.x + this->y * v2.y;
}

void Vector2f::get(float &x, float &y) {
	x = this->x;
	y = this->y;
}

float Vector2f::getX() {
	return this->x;
}

float Vector2f::getY() {
	return this->y;
}

float Vector2f::magnitude() {
	return sqrt(x * x + y * y);
}

Vector2f Vector2f::normalized() {
	float mag = this->magnitude();

	return Vector2f(this->x / mag, this->y / mag);
}

Vector2f Vector2f::rotate(float rad) {
	// TODO (matricies requried!)
	
	return Vector2f(0, 0);
}

Vector2f Vector2f::scale(float scale) {
	return Vector2f(this->x * scale, this->y * scale);
}

void Vector2f::set(float x, float y) {
	this->x = x;
	this->y = y;
}

void Vector2f::setX(float x) {
	this->x = x;
}

void Vector2f::setY(float y) {
	this->y = y;
}

Vector2f Vector2f::operator+(const Vector2f &v2) {
	return this->add(v2);
}

Vector2f Vector2f::operator*(const float &scale) {
	return this->scale(scale);
}

Vector2f Vector2f::operator-() const {
	return Vector2f(-this->x, -this->y);
}

Vector2f Vector2f::operator-(const Vector2f &v2) {
	return this->add(-v2);
}