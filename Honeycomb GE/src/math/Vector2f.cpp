#include <math.h>

#include "..\..\include\math\Vector2f.h"

namespace Honeycomb::Math {
	Vector2f::Vector2f() : Vector2f(0.0F, 0.0F) { }

	Vector2f::Vector2f(float x, float y) {
		this->x = x;
		this->y = y;
	}

	Vector2f::~Vector2f() {

	}

	Vector2f Vector2f::add(Vector2f v2) {
		return Vector2f(this->x + v2.x, this->y + v2.y);
	}

	Vector2f Vector2f::addTo(Vector2f v2) {
		Vector2f resultant = this->add(v2);

		this->set(resultant.x, resultant.y);
		return *this;
	}

	float Vector2f::angle(Vector2f v2) {
		// Calculate cos(theta) = (v1 * v2) / (|v1||v2|)
		float dot = this->dot(v2);
		float magMult = this->magnitude() * v2.magnitude();
		float cosTheta = dot / magMult;

		return (float)acos(cosTheta);
	}

	float Vector2f::dot(Vector2f v2) {
		return this->x * v2.x + this->y * v2.y;
	}

	void Vector2f::get(float &x, float &y) {
		x = this->x;
		y = this->y;
	}

	float& Vector2f::getX() {
		return this->x;
	}

	float& Vector2f::getY() {
		return this->y;
	}

	float Vector2f::magnitude() {
		return (float)sqrt(x * x + y * y);
	}

	Vector2f Vector2f::normalize() {
		Vector2f normalized = this->normalized();

		this->set(normalized.x, normalized.y);
		return *this;
	}

	Vector2f Vector2f::normalized() {
		float mag = this->magnitude();

		return Vector2f(this->x / mag, this->y / mag);
	}

	Vector2f Vector2f::rotate(float rad) {
		float cosRad = cos(rad);
		float sinRad = sin(rad);

		// Use the Euclidean space rotation formula
		return Vector2f(x * cosRad - y * sinRad, x * sinRad + y * cosRad);
	}

	Vector2f Vector2f::rotateTo(float rad) {
		Vector2f rotated = this->rotate(rad);

		this->set(rotated.x, rotated.y);
		return *this;
	}

	Vector2f Vector2f::scale(float scale) {
		return Vector2f(this->x * scale, this->y * scale);
	}

	Vector2f Vector2f::scaleTo(float scale) {
		Vector2f scaled = this->scale(scale);

		this->set(scaled.x, scaled.y);
		return *this;
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

	Vector2f Vector2f::operator*(float scale) {
		return this->scale(scale);
	}

	Vector2f Vector2f::operator*=(float scale) {
		return this->scaleTo(scale);
	}

	Vector2f Vector2f::operator/(float scale) {
		return this->scale(1.0F / scale);
	}

	Vector2f Vector2f::operator/=(float scale) {
		return this->scale(1.0F / scale);
	}

	Vector2f Vector2f::operator+(Vector2f v2) {
		return this->add(v2);
	}

	Vector2f Vector2f::operator+=(Vector2f v2) {
		return this->addTo(v2);
	}

	Vector2f Vector2f::operator-() {
		return Vector2f(-this->x, -this->y);
	}

	Vector2f Vector2f::operator-(Vector2f v2) {
		return this->add(-v2);
	}

	Vector2f Vector2f::operator-=(Vector2f v2) {
		return this->addTo(-v2);
	}
}