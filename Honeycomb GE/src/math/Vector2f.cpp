#include <math.h>

#include "../../include/math/Vector2f.h"

#include "../../include/math/Matrix4f.h"

namespace Honeycomb { namespace Math {
	Vector2f::Vector2f() : Vector2f(0.0F, 0.0F) {
	
	}

	Vector2f::Vector2f(const float &all) : Vector2f(all, all) {
	
	}

	Vector2f::Vector2f(const float &x, const float &y) {
		this->x = x;
		this->y = y;
	}

	Vector2f Vector2f::add(const Vector2f &v2) const {
		return Vector2f(this->x + v2.x, this->y + v2.y);
	}

	Vector2f& Vector2f::addTo(const Vector2f &v2) {
		Vector2f resultant = this->add(v2);

		this->set(resultant.x, resultant.y);
		return *this;
	}

	float Vector2f::angle(const Vector2f &v2) const {
		// Calculate cos(theta) = (v1 * v2) / (|v1||v2|)
		float dot = this->dot(v2);
		float magMult = this->magnitude() * v2.magnitude();
		float cosTheta = dot / magMult;

		// Inverse cosine to get the theta value
		return (float)acos(cosTheta);
	}

	Vector2f Vector2f::divide(const float &scale) const {
		return Vector2f(this->x / scale, this->y / scale);
	}

	Vector2f Vector2f::divide(const Vector2f &v2) const {
		return Vector2f(this->x / v2.x, this->y / v2.y);
	}

	Vector2f& Vector2f::divideTo(const float &scale) {
		Vector2f divided = this->divide(scale);

		this->set(divided.x, divided.y);
		return *this;
	}

	Vector2f& Vector2f::divideTo(const Vector2f &v2) {
		Vector2f divided = this->divide(v2);

		this->set(divided.x, divided.y);
		return *this;
	}

	float Vector2f::dot(const Vector2f &v2) const {
		return this->x * v2.x + this->y * v2.y;
	}

	void Vector2f::get(float &x, float &y) const {
		x = this->x;
		y = this->y;
	}

	float& Vector2f::getX() {
		return this->x;
	}

	const float& Vector2f::getX() const {
		return this->x;
	}

	float& Vector2f::getY() {
		return this->y;
	}

	const float& Vector2f::getY() const {
		return this->y;
	}

	float Vector2f::magnitude() const {
		return (float)sqrt(this->magnitude2());
	}

	float Vector2f::magnitude2() const {
		return (x * x + y * y);
	}

	Vector2f Vector2f::multiply(const Matrix4f &mat) const {
		return mat.multiply(*this);
	}

	Vector2f Vector2f::multiply(const Vector2f &v2) const {
		return Vector2f(this->x * v2.x, this->y * v2.y);
	}

	Vector2f& Vector2f::multiplyTo(const Matrix4f &mat) {
		Vector2f prod = this->multiply(mat);

		this->set(prod.x, prod.y);
		return *this;
	}

	Vector2f& Vector2f::multiplyTo(const Vector2f &v2) {
		Vector2f prod = this->multiply(v2);

		this->set(prod.x, prod.y);
		return *this;
	}

	Vector2f& Vector2f::normalize() {
		Vector2f normalized = this->normalized();

		this->set(normalized.x, normalized.y);
		return *this;
	}

	Vector2f Vector2f::normalized() const {
		float mag = this->magnitude();

		return Vector2f(this->x / mag, this->y / mag);
	}

	Vector2f Vector2f::rotate(const float &rad) const {
		float cosRad = (float)cos(rad);
		float sinRad = (float)sin(rad);

		// Use the Euclidean space rotation formula
		return Vector2f(x * cosRad - y * sinRad, x * sinRad + y * cosRad);
	}

	Vector2f& Vector2f::rotateTo(const float &rad) {
		Vector2f rotated = this->rotate(rad);

		this->set(rotated.x, rotated.y);
		return *this;
	}

	Vector2f Vector2f::scale(const float &scale) const {
		return Vector2f(this->x * scale, this->y * scale);
	}

	Vector2f& Vector2f::scaleTo(const float &scale) {
		Vector2f scaled = this->scale(scale);

		this->set(scaled.x, scaled.y);
		return *this;
	}

	void Vector2f::set(const float &x, const float &y) {
		this->x = x;
		this->y = y;
	}

	void Vector2f::setX(const float &x) {
		this->x = x;
	}

	void Vector2f::setY(const float &y) {
		this->y = y;
	}

	Vector2f Vector2f::operator*(const float &scale) const {
		return this->scale(scale);
	}

	Vector2f Vector2f::operator*(const Matrix4f &mat) const {
		return this->multiply(mat);
	}

	Vector2f Vector2f::operator*(const Vector2f &v2) const {
		return this->multiply(v2);
	}

	Vector2f& Vector2f::operator*=(const float &scale) {
		return this->scaleTo(scale);
	}

	Vector2f& Vector2f::operator*=(const Matrix4f &mat) {
		return this->multiplyTo(mat);
	}

	Vector2f& Vector2f::operator*=(const Vector2f &v2) {
		return this->multiplyTo(v2);
	}

	Vector2f Vector2f::operator/(const float &scale) const {
		return this->scale(1.0F / scale);
	}

	Vector2f& Vector2f::operator/=(const float &scale) {
		return this->scaleTo(1.0F / scale);
	}

	Vector2f Vector2f::operator+(const Vector2f &v2) const {
		return this->add(v2);
	}

	Vector2f& Vector2f::operator+=(const Vector2f &v2) {
		return this->addTo(v2);
	}

	Vector2f Vector2f::operator-() const {
		return Vector2f(-this->x, -this->y);
	}

	Vector2f Vector2f::operator-(const Vector2f &v2) const {
		return this->add(-v2);
	}

	Vector2f& Vector2f::operator-=(const Vector2f &v2) {
		return this->addTo(-v2);
	}

	bool Vector2f::operator<(const Vector2f &v2) const {
		return this->magnitude2() < v2.magnitude2();
	}

	bool Vector2f::operator>(const Vector2f &v2) const {
		return this->magnitude2() > v2.magnitude2();
	}

	std::ostream& operator<<(std::ostream &stream, const Vector2f &vec) {
		return stream << "(" << vec.getX() << ", " << vec.getY() << ")";
	}
} }
