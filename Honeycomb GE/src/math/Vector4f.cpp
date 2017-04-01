#include "../../include/math/Vector4f.h"

#include <math.h>

#include "../../include/math/Matrix4f.h"

namespace Honeycomb { namespace Math {
	Vector4f::Vector4f() : Vector4f(0.0F, 0.0F, 0.0F, 0.0F) { }

	Vector4f::Vector4f(const float &x, const float &y, const float &z, 
			const float &w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	Vector4f::~Vector4f() {

	}

	Vector4f Vector4f::add(const Vector4f &v2) const {
		return Vector4f(this->x + v2.x, this->y + v2.y, this->z + v2.z,
			this->w + v2.w);
	}

	Vector4f& Vector4f::addTo(const Vector4f &v2) {
		Vector4f resultant = this->add(v2);

		this->set(resultant.x, resultant.y, resultant.z, resultant.w);
		return *this;
	}

	float Vector4f::dot(const Vector4f &v2) const {
		return this->x * v2.x + this->y * v2.y + this->z * v2.z +
			this->w * v2.w;
	}

	void Vector4f::get(float &x, float &y, float &z, float &w) const {
		x = this->x;
		y = this->y;
		z = this->z;
		w = this->w;
	}

	float& Vector4f::getW() {
		return this->w;
	}

	const float& Vector4f::getW() const {
		return this->w;
	}

	float& Vector4f::getX() {
		return this->x;
	}

	const float& Vector4f::getX() const {
		return this->x;
	}

	float& Vector4f::getY() {
		return this->y;
	}

	const float& Vector4f::getY() const {
		return this->y;
	}

	float& Vector4f::getZ() {
		return this->z;
	}

	const float& Vector4f::getZ() const {
		return this->z;
	}

	float Vector4f::magnitude() const {
		return (float)sqrt(x * x + y * y + z * z);
	}

	Vector4f Vector4f::multiply(const Matrix4f &mat) const {
		return mat.multiply(*this);
	}

	Vector4f& Vector4f::multiplyTo(const Matrix4f &mat) {
		Vector4f prod = this->multiply(mat);

		this->set(prod.x, prod.y, prod.z, prod.w);
		return *this;
	}

	Vector4f& Vector4f::normalize() {
		Vector4f normalized = this->normalized();

		this->set(normalized.x, normalized.y, normalized.z, normalized.w);
		return *this;
	}

	Vector4f Vector4f::normalized() const {
		float mag = this->magnitude();

		return Vector4f(this->x / mag, this->y / mag, this->z / mag, 
			this->w / mag);
	}

	Vector4f Vector4f::scale(const float &scale) const {
		return Vector4f(this->x * scale, this->y * scale, this->z * scale,
			this->w * scale);
	}

	Vector4f& Vector4f::scaleTo(const float &scale) {
		Vector4f scaled = this->scale(scale);

		this->set(scaled.x, scaled.y, scaled.z, scaled.w);
		return *this;
	}

	void Vector4f::set(const float &x, const float &y, const float &z, 
		const float &w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	void Vector4f::setX(const float &x) {
		this->x = x;
	}

	void Vector4f::setY(const float &y) {
		this->y = y;
	}

	void Vector4f::setZ(const float &z) {
		this->z = z;
	}

	void Vector4f::setW(const float &w) {
		this->w = w;
	}

	Vector4f Vector4f::operator*(const float &scale) const {
		return this->scale(scale);
	}

	Vector4f Vector4f::operator*(const Matrix4f &mat) const {
		return this->multiply(mat);
	}

	Vector4f& Vector4f::operator*=(const float &scale) {
		return this->scaleTo(scale);
	}

	Vector4f& Vector4f::operator*=(const Matrix4f &mat) {
		return this->multiplyTo(mat);
	}

	Vector4f Vector4f::operator/(const float &scale) const {
		return this->scale(1.0F / scale);
	}

	Vector4f& Vector4f::operator/=(const float &scale) {
		return this->scaleTo(1.0F / scale);
	}

	Vector4f Vector4f::operator+(const Vector4f &v2) const {
		return this->add(v2);
	}

	Vector4f& Vector4f::operator+=(const Vector4f &v2) {
		return this->addTo(v2);
	}

	Vector4f Vector4f::operator-() const{
		return this->scale(-1.0F);
	}

	Vector4f Vector4f::operator-(const Vector4f &v2) const {
		return this->add(-v2);
	}

	Vector4f& Vector4f::operator-=(const Vector4f &v2) {
		return this->addTo(-v2);
	}
} }
