#pragma once
#ifndef VECTOR_2F_H
#define VECTOR_2F_H

#include <ostream>

namespace Honeycomb { namespace Math { class Matrix4f; } }

namespace Honeycomb { namespace Math {
	/// <summary>
	/// Represents a two dimensional float vector containing the x, y 
	/// components.
	/// </summary>
	class Vector2f {
	public:
		/// <summary>
		/// Creates a new two dimensional vector with zeros for the x and y
		/// components.
		/// </summary>
		Vector2f();
		
		/// <summary>
		/// Creates a new two dimensional vector whose x and y component values
		/// are equal to the specified value.
		/// </summary>
		/// <param name="all">
		/// The value to be used for the x and y components of the Vector.
		/// </param>
		Vector2f(const float &all);

		/// <summary>
		/// Creates a new two dimensional vector with the specified values for
		/// the x and y components.
		/// </summary>
		/// <param name="x">
		/// The x component value.
		/// </param>
		/// <param name="y">
		/// The y component value.
		/// </param>
		Vector2f(const float &x, const float &y);

		/// <summary>
		/// Returns a vector which is equivalent to the component sum of this
		/// vector and the specified vector.
		/// </summary>
		/// <param name="v2">
		/// The vector to be added with this.
		/// </param>
		/// <returns>
		/// The sum vector.
		/// </returns>
		Vector2f add(const Vector2f &v2) const;

		/// <summary>
		/// Adds the specified vector to this vector and returns this.
		/// </summary>
		/// <param name="v2">
		/// The vector to be added to this.
		/// </param>
		/// <returns>
		/// This vector.
		/// </returns>
		Vector2f& addTo(const Vector2f &v2);

		/// <summary>
		/// Calculates the angle, in radians, between this vector and the
		/// specified vector.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// The angle between the vectors, in radians.
		/// </returns>
		float angle(const Vector2f &v2) const;

		/// <summary>
		/// Returns a copy of this vector where each component of the vector is
		/// divided by the specified scale factor.
		/// </summary>
		/// <param name="scale">
		/// The scale factor.
		/// </param>
		/// <returns>
		/// The divided vector.
		/// </returns>
		Vector2f divide(const float &scale) const;

		/// <summary>
		/// Returns a copy of this vector where each component of the vector is
		/// divided by the respective component of the specified vector.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// The divided vector.
		/// </returns>
		Vector2f divide(const Vector2f &v2) const;

		/// <summary>
		/// Divides each component of this Vector by the specified scale 
		/// factor.
		/// </summary>
		/// <param name="scale">
		/// The scale factor.
		/// </param>
		/// <returns>
		/// This Vector.
		/// </returns>
		Vector2f& divideTo(const float &scale);

		/// <summary>
		/// Divides each component of this Vector by the respective component
		/// of the specified vector.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// This Vector.
		/// </returns>
		Vector2f& divideTo(const Vector2f &v2);

		/// <summary>
		/// Returns the dot product of this vector and the specified vector.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// The dot product of the vectors.
		/// </returns>
		float dot(const Vector2f &v2) const;

		/// <summary>
		/// Fetches the x and y component values of this vector and writes them
		/// to the specified references.
		/// </summary>
		/// <param name="x">
		/// The reference to which the x component is to be written.
		/// </param>
		/// <param name="y">
		/// The reference to which the y component is to be written.
		/// </param>
		void get(float &x, float &y) const;

		/// <summary>
		/// Returns the reference to the x component.
		/// </summary>
		/// <returns>
		/// The reference to the x component.
		/// </returns>
		float& getX();

		/// <summary>
		/// Returns the constant reference to the x component.
		/// </summary>
		/// <returns>
		/// The constant reference to the x component.
		/// </returns>
		const float& getX() const;

		/// <summary>
		/// Returns the reference to the y component.
		/// </summary>
		/// <returns>
		/// The reference to the y component.
		/// </returns>
		float& getY();

		/// <summary>
		/// Returns the constant reference to the y component.
		/// </summary>
		/// <returns>
		/// The constant reference to the y component.
		/// </returns>
		const float& getY() const;

		/// <summary>
		/// Calculates, and returns the magnitude of this Vector.
		/// </summary>
		/// <returns>
		/// The magnitude value.
		/// </returns>
		float magnitude() const;

		/// <summary>
		/// Calculates, and returns the squared magnitude of this Vector. This
		/// does not perform the square root operation when calculating the
		/// magnitude and is therefore faster than <see cref="magnitude"/>, but
		/// should only be used for comparing whether vectors are bigger.
		/// </summary>
		/// <returns>
		/// The squared magnitude value.
		/// </returns>
		float magnitude2() const;

		/// <summary>
		/// Returns an instance of Vector2f which contains the product of this
		/// vector and the specified Matrix4f.
		/// </summary>
		/// <param name="mat">
		/// The matrix to be multiplied with this.
		/// </param>
		/// <returns>
		/// The product vector.
		/// </returns>
		Vector2f multiply(const Matrix4f &mat) const;

		/// <summary>
		/// Returns an instance of Vector2f which contains the component
		/// product of this vector and the specified vector.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// The component product of the vectors.
		/// </returns>
		Vector2f multiply(const Vector2f &v2) const;

		/// <summary>
		/// Multiplies this vector by the specified Matrix4f and returns this.
		/// </summary>
		/// <param name="mat">
		/// The matrix to be multiplied to this.
		/// </param>
		/// <returns>
		/// This vector.
		/// </returns>
		Vector2f& multiplyTo(const Matrix4f &mat);

		/// <summary>
		/// Multiplies this vector by the specified Matrix4f and stores the
		/// product in this instance.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// This vector.
		/// </returns>
		Vector2f& multiplyTo(const Vector2f &v2);

		/// <summary>
		/// Normalizes this vector and returns it.
		/// </summary>
		/// <returns>
		/// This vector.
		/// </returns>
		Vector2f& normalize();

		/// <summary>
		/// Returns a vector which is the normalized version of this vector.
		/// </summary>
		/// <returns>
		/// The normalized vector.
		/// </returns>
		Vector2f normalized() const;

		/// <summary>
		/// Creates a copy of this vector, rotates it by the specified amount
		/// and returns it.
		/// </summary>
		/// <param name="rad">
		/// The amount of radians by which the vector is to be rotated on the
		/// global forward axis ( 0, 0, 1 ). A positive amount rotates the
		/// vector counterclockwise, and a negative amount rotates the vector
		/// clockwise.
		/// </param>
		/// <returns>
		/// The rotated Vector.
		/// </returns>
		Vector2f rotate(const float &rad) const;

		/// <summary>
		/// Rotates this vector by the specified amount and returns it.
		/// </summary>
		/// <param name="rad">
		/// The amount of radians by which the vector is to be rotated on the
		/// global forward axis ( 0, 0, 1 ). A positive amount rotates the
		/// vector counterclockwise, and a negative amount rotates the vector
		/// clockwise.
		/// </param>
		/// <returns>
		/// This Vector.
		/// </returns>
		Vector2f& rotateTo(const float &rad);

		/// <summary>
		/// Creates a copy of this Vector, scales it by the specified amount
		/// and returns it.
		/// </summary>
		/// <param name="scale">
		/// The amount by which the vector is to be scaled on each component.
		/// </param>
		/// <returns>
		/// The scaled vector.
		/// </returns>
		Vector2f scale(const float &scale) const;

		/// <summary>
		/// Scales this vector by the specified amount and returns it.
		/// </summary>
		/// <param name="scale">
		/// The amount by which the vector is to be scaled on each component.
		/// </param>
		/// <returns>
		/// This vector.
		/// </returns>
		Vector2f& scaleTo(const float &scale);

		/// <summary>
		/// Sets the x and y components of the Vector.
		/// </summary>
		/// <param name="x">
		/// The new x component.
		/// </param>
		/// <param name="y">
		/// The new y component.
		/// </param>
		void set(const float &x, const float &y);

		/// <summary>
		/// Sets the x component of the Vector.
		/// </summary>
		/// <param name="x">
		/// The new x component.
		/// </param>
		void setX(const float &x);

		/// <summary>
		/// Sets the y component of the Vector.
		/// </summary>
		/// <param name="y">
		/// The new y component.
		/// </param>
		void setY(const float &y);

		/// <summary>
		/// Overloads the multiplication operator to return a copy of this
		/// vector scaled by the right hand side.
		/// </summary>
		/// <param name="scale">
		/// The amount by which to scale the vector.
		/// </param>
		/// <returns>
		/// The scaled copy of this Vector.
		/// </returns>
		Vector2f operator*(const float &scale) const;

		/// <summary>
		/// Overloads the multiplication operator to return a copy of this
		/// vector multiplied by the right hand side.
		/// </summary>
		/// <param name="mat">
		/// The amount by which to multiply the vector.
		/// </param>
		/// <returns>
		/// The product copy of this Vector.
		/// </returns>
		Vector2f operator*(const Matrix4f &mat) const;

		/// <summary>
		/// Overloads the multiplication operator to return the component
		/// product of this vector and the specified vector.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// The product copy of this Vector.
		/// </returns>
		Vector2f operator*(const Vector2f &v2) const;

		/// <summary>
		/// Overloads the multiplication-set operator to multiply this
		/// instance by the specified scale and return this.
		/// </summary>
		/// <param name="scale">
		/// The amount by which to scale the vector.
		/// </param>
		/// <returns>
		/// This Vector.
		/// </returns>
		Vector2f& operator*=(const float &scale);

		/// <summary>
		/// Overloads the multiplication-set operator to multiply this
		/// instance by the specified matrix and return this.
		/// </summary>
		/// <param name="mat">
		/// The amount by which to multiply this vector.
		/// </param>
		/// <returns>
		/// This Vector.
		/// </returns>
		Vector2f& operator*=(const Matrix4f &mat);

		/// <summary>
		/// Overloads the multiplication-set operator to component multiply
		/// this instance by the specified vector and return this.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// This Vector.
		/// </returns>
		Vector2f& operator*=(const Vector2f &v2);

		/// <summary>
		/// Overloads the division operator to return a copy of this Vector,
		/// inversely scaled by the specified amount.
		/// </summary>
		/// <param name="scale">
		/// The amount by which to inversely scale the vector.
		/// </param>
		/// <returns>
		/// The inversely scaled Vector.
		/// </returns>
		Vector2f operator/(const float &scale) const;

		/// <summary>
		/// Overloads the division-set operator to inversely scale this Vector
		/// by the specified amount and return this.
		/// </summary>
		/// <param name="scale">
		/// The right hand side by which to inversely scale this vector.
		/// </param>
		/// <returns>
		/// This Vector.
		/// </returns>
		Vector2f& operator/=(const float &scale);

		/// <summary>
		/// Overloads the addition operator to return the component sum of the 
		/// copy of this Vector and the specified vector.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// The sum Vector.
		/// </returns>
		Vector2f operator+(const Vector2f &v2) const;

		/// <summary>
		/// Overloads the addition-set operator to the add the specified
		/// vector to this vector, by component, and return this vector.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// This Vector.
		/// </returns>
		Vector2f& operator+=(const Vector2f &v2);

		/// <summary>
		/// Overloads the unary minus operator to return a vector whose
		/// components are the negated components of this vector.
		/// </summary>
		/// <returns>
		/// The negated components Vector.
		/// </returns>
		Vector2f operator-() const;

		/// <summary>
		/// Overloads the subtraction operator to return the component 
		/// difference between this vector and the specified vector.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// The component difference Vector.
		/// </returns>
		Vector2f operator-(const Vector2f &v2) const;

		/// <summary>
		/// Overloads the subtraction-set operator to component subtract the
		/// specified vector from this vector.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// This vector.
		/// </returns>
		Vector2f& operator-=(const Vector2f &v2);

		/// <summary>
		/// Overloads the greater than operator to return whether this 
		/// instance's magnitude is larger than the specified instance's
		/// magnitude.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// True if the magnitude of this vector is greater than the magnitude
		/// of the specified vector.
		/// </returns>
		bool operator>(const Vector2f &v2) const;

		/// <summary>
		/// Overloads the less than operator to return whether this instance's
		/// magnitude is less than the specified instance's magnitude.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// True if the magnitude of this vector is less than the magnitude of
		/// the specified vector.
		/// </returns>
		bool operator<(const Vector2f &v2) const;
	private:
		float x;                           // The x-component
		float y;                           // The y-component
	};

	/// <summary>
	/// Returns an output stream containg the x and y components of the vector
	/// in the format: "(X, Y)".
	/// </summary>
	std::ostream& operator<<(std::ostream &stream, const Vector2f &vec);
} }

#endif
