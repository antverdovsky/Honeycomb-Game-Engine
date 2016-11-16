#include "..\..\include\math\Vector4f.h"

#include <math.h>

namespace Honeycomb::Math {
	Vector4f::Vector4f() : Vector4f(0.0F, 0.0F, 0.0F, 0.0F) { }

	Vector4f::Vector4f(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4f::~Vector4f() {

	}

	Vector4f Vector4f::add(Vector4f v2) {
		return Vector4f(this->x + v2.x, this->y + v2.y, this->z + v2.z,
			this->w + v2.w);
	}

	Vector4f Vector4f::addTo(Vector4f v2) {
		Vector4f resultant = this->add(v2);

		this->set(resultant.x, resultant.y, resultant.z, resultant.w);
		return *this;
	}

	float Vector4f::dot(Vector4f v2) {
		return this->x * v2.x + this->y * v2.y + this->z * v2.z +
			this->w * v2.w;
	}

	void Vector4f::get(float &x, float &y, float &z, float &w) {
		x = this->x;
		y = this->y;
		z = this->z;
		w = this->w;
	}

	float& Vector4f::getX() {
		return this->x;
	}

	float& Vector4f::getY() {
		return this->y;
	}

	float& Vector4f::getZ() {
		return this->z;
	}

	float& Vector4f::getW() {
		return this->w;
	}

	float Vector4f::magnitude() {
		return (float)sqrt(x * x + y * y + z * z);
	}

	Vector4f Vector4f::normalize() {
		Vector4f normalized = this->normalized();

		this->set(normalized.x, normalized.y, normalized.z, normalized.w);
		return *this;
	}

	Vector4f Vector4f::normalized() {
		float mag = this->magnitude();

		return Vector4f(this->x / mag, this->y / mag, this->z / mag, 
			this->w / mag);
	}

	Vector4f Vector4f::scale(float scale) {
		return Vector4f(this->x * scale, this->y * scale, this->z * scale,
			this->w * scale);
	}

	Vector4f Vector4f::scaleTo(float scale) {
		Vector4f scaled = this->scale(scale);

		this->set(scaled.x, scaled.y, scaled.z, scaled.w);
		return *this;
	}

	void Vector4f::set(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	void Vector4f::setX(float x) {
		this->x = x;
	}

	void Vector4f::setY(float y) {
		this->y = y;
	}

	void Vector4f::setZ(float z) {
		this->z = z;
	}

	void Vector4f::setW(float w) {
		this->w = w;
	}

	Vector4f Vector4f::operator*(float scale) {
		return this->scale(scale);
	}

	Vector4f Vector4f::operator*=(float scale) {
		return this->scaleTo(scale);
	}

	Vector4f Vector4f::operator/(float scale) {
		return this->scale(1.0F / scale);
	}

	Vector4f Vector4f::operator/=(float scale) {
		return this->scale(1.0F / scale);
	}

	Vector4f Vector4f::operator+(Vector4f v2) {
		return this->add(v2);
	}

	Vector4f Vector4f::operator+=(Vector4f v2) {
		return this->addTo(v2);
	}

	Vector4f Vector4f::operator-() {
		return this->scale(-1.0F);
	}

	Vector4f Vector4f::operator-(Vector4f v2) {
		return this->add(-v2);
	}

	Vector4f Vector4f::operator-=(Vector4f v2) {
		return this->addTo(-v2);
	}
}