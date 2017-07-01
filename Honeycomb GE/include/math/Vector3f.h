#pragma once
#ifndef VECTOR_3F_H
#define VECTOR_3F_H

#include <ostream>

namespace Honeycomb { namespace Math { class Matrix4f; } }
namespace Honeycomb { namespace Math { class Quaternion; } }

namespace Honeycomb { namespace Math {
	/// <summary>
	/// Represents a three dimensional float vector containing the x, y, 
	/// z components.
	/// </summary>
	class Vector3f {
	public:
		/// <summary>
		/// Returns the Honeycomb global forward vector ( 0, 0, -1 ).
		/// </summary>
		/// <returns>
		/// The global forward vector.
		/// </returns>
		static const Vector3f& getGlobalForward();

		/// <summary>
		/// Returns the Honeycomb global right vector ( 1, 0, 0 ).
		/// </summary>
		/// <returns>
		/// The global right vector.
		/// </returns>
		static const Vector3f& getGlobalRight();

		/// <summary>
		/// Returns the Honeycomb global up vector ( 0, 1, 0 ).
		/// </summary>
		/// <returns>
		/// The global up vector.
		/// </returns>
		static const Vector3f& getGlobalUp();

		/// <summary>
		/// Creates a new three dimensional vector with zeros for the x, y and
		/// z components.
		/// </summary>
		Vector3f();

		/// <summary>
		/// Creates a new three dimensional vector whose x, y and z component 
		/// values are equal to the specified value.
		/// </summary>
		/// <param name="all">
		/// The value to be used for the x, y and z components of the Vector.
		/// </param>
		Vector3f(const float &all);

		/// <summary>
		/// Creates a new three dimensional vector with the specified values 
		/// for the x, y and z components.
		/// </summary>
		/// <param name="x">
		/// The x component value.
		/// </param>
		/// <param name="y">
		/// The y component value.
		/// </param>
		/// <param name="z">
		/// The z component value.
		/// </param>
		Vector3f(const float &x, const float &y, const float &z);

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
		Vector3f add(const Vector3f& v2) const;

		/// <summary>
		/// Adds the specified vector to this vector and returns this.
		/// </summary>
		/// <param name="v2">
		/// The vector to be added to this.
		/// </param>
		/// <returns>
		/// This vector.
		/// </returns>
		Vector3f& addTo(const Vector3f& v2);

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
		float angle(const Vector3f& v2) const;

		/// <summary>
		/// Calculates the cross product of this and the specified vector, and
		/// returns the vector containing the product.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// The cross product of the vectors.
		/// </returns>
		Vector3f cross(const Vector3f& v2) const;

		/// <summary>
		/// Calculates the cross product of this and the specified vector, and
		/// stores the result in this vector.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// This vector.
		/// </returns>
		Vector3f& crossTo(const Vector3f& v2);

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
		Vector3f divide(const float &scale) const;

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
		Vector3f divide(const Vector3f &v2) const;

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
		Vector3f& divideTo(const float &scale);

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
		Vector3f& divideTo(const Vector3f &v2);

		/// <summary>
		/// Returns the dot product of this vector and the specified vector.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// The dot product of the vectors.
		/// </returns>
		float dot(const Vector3f& v2) const;

		/// <summary>
		/// Fetches the x, y and z component values of this vector and writes 
		/// them to the specified references.
		/// </summary>
		/// <param name="x">
		/// The reference to which the x component is to be written.
		/// </param>
		/// <param name="y">
		/// The reference to which the y component is to be written.
		/// </param>
		/// <param name="z">
		/// The reference to which the z component is to be written.
		/// </param>
		void get(float &x, float &y, float &z) const;

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
		/// Returns the reference to the z component.
		/// </summary>
		/// <returns>
		/// The reference to the z component.
		/// </returns>
		float& getZ();

		/// <summary>
		/// Returns the constant reference to the z component.
		/// </summary>
		/// <returns>
		/// The constant reference to the z component.
		/// </returns>
		const float& getZ() const;

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
		/// Returns an instance of Vector3f which contains the product of this
		/// vector and the specified Matrix4f.
		/// </summary>
		/// <param name="mat">
		/// The matrix to be multiplied with this.
		/// </param>
		/// <returns>
		/// The product vector.
		/// </returns>
		Vector3f multiply(const Matrix4f &mat) const;

		/// <summary>
		/// Returns an instance of Vector3f which contains the component
		/// product of this vector and the specified vector.
		/// </summary>
		/// <param name="v2">
		/// The other vector.
		/// </param>
		/// <returns>
		/// The component product of the vectors.
		/// </returns>
		Vector3f multiply(const Vector3f &vec) const;

		/// <summary>
		/// Multiplies this vector by the specified Matrix4f and returns this.
		/// </summary>
		/// <param name="mat">
		/// The matrix to be multiplied to this.
		/// </param>
		/// <returns>
		/// This vector.
		/// </returns>
		Vector3f& multiplyTo(const Matrix4f &mat);

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
		Vector3f& multiplyTo(const Vector3f &vec);

		/// <summary>
		/// Normalizes this vector and returns it.
		/// </summary>
		/// <returns>
		/// This vector.
		/// </returns>
		Vector3f& normalize();

		/// <summary>
		/// Returns a vector which is the normalized version of this vector.
		/// </summary>
		/// <returns>
		/// The normalized vector.
		/// </returns>
		Vector3f normalized() const;

		/// <summary>
		/// Creates a copy of this vector, and rotates it by the specified
		/// amount on the specified axis.
		/// </summary>
		/// <param name="v2">
		/// The axis on which the vector is to be rotated.
		/// </param>
		/// <param name="rad">
		/// The amount of radians by which the vector is to be rotated on the
		/// global forward axis ( 0, 0, 1 ). A positive amount rotates the
		/// vector counterclockwise, and a negative amount rotates the vector
		/// clockwise.
		/// </param>
		/// <returns>
		/// The rotated Vector.
		/// </returns>
		Vector3f rotate(const Vector3f& v2, const float &rad) const;

		/// <summary>
		/// Creates a copy of this vector, and rotates it by the specified
		/// Quaternion.
		/// </summary>
		/// <param name="quat">
		/// The quaternion by which the vector is to be rotated.
		/// </param>
		/// <returns>
		/// The rotated vector.
		/// </returns>
		Vector3f rotate(const Quaternion& quat) const;

		/// <summary>
		/// Rotates this vector by the specified amount on the specified axis.
		/// </summary>
		/// <param name="v2">
		/// The axis on which the vector is to be rotated.
		/// </param>
		/// <param name="rad">
		/// The amount of radians by which the vector is to be rotated on the
		/// global forward axis ( 0, 0, 1 ). A positive amount rotates the
		/// vector counterclockwise, and a negative amount rotates the vector
		/// clockwise.
		/// </param>
		/// <returns>
		/// This Vector.
		/// </returns>
		Vector3f& rotateTo(const Vector3f& axis, const float &rad);

		/// <summary>
		/// Rotates this vector by the specified quaternion.
		/// </summary>
		/// <param name="quat">
		/// The quaternion by which to rotate the Vector.
		/// </param>
		/// <returns>
		/// This Vector.
		/// </returns>
		Vector3f& rotateTo(const Quaternion& quat);

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
		Vector3f scale(const float &scale) const;

		/// <summary>
		/// Scales this vector by the specified amount and returns it.
		/// </summary>
		/// <param name="scale">
		/// The amount by which the vector is to be scaled on each component.
		/// </param>
		/// <returns>
		/// This vector.
		/// </returns>
		Vector3f& scaleTo(const float &scale);

		/// <summary>
		/// Sets the x, y and z components of the Vector.
		/// </summary>
		/// <param name="x">
		/// The new x component.
		/// </param>
		/// <param name="y">
		/// The new y component.
		/// </param>
		/// <param name="z">
		/// The new z component.
		/// </param>
		void set(const float &x, const float &y, const float &z);

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
		/// Sets the z component of the Vector.
		/// </summary>
		/// <param name="z">
		/// The new z component.
		/// </param>
		void setZ(const float &z);

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
		Vector3f operator*(const float &scale) const;

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
		Vector3f operator*(const Matrix4f &mat) const;

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
		Vector3f operator*(const Vector3f &v2) const;

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
		Vector3f& operator*=(const float &scale);

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
		Vector3f& operator*=(const Matrix4f &mat);

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
		Vector3f& operator*=(const Vector3f &v2);

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
		Vector3f operator/(const float &scale) const;

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
		Vector3f& operator/=(const float &scale);

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
		Vector3f operator+(const Vector3f& v2) const;

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
		Vector3f& operator+=(const Vector3f& v2);

		/// <summary>
		/// Overloads the unary minus operator to return a vector whose
		/// components are the negated components of this vector.
		/// </summary>
		/// <returns>
		/// The negated components Vector.
		/// </returns>
		Vector3f operator-() const;

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
		Vector3f operator-(const Vector3f& v2) const;

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
		Vector3f& operator-=(const Vector3f& v2);

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
		bool operator>(const Vector3f &v2) const;

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
		bool operator<(const Vector3f &v2) const;
	private:
		float x;                           // The x component
		float y;                           // The y component
		float z;                           // The z component
	};

	/// <summary>
	/// Returns an output stream containg the x, y, and z components of the 
	/// vector in the format: "(X, Y, Z)".
	/// </summary>
	std::ostream& operator<<(std::ostream &stream, const Vector3f &vec);
} }

#endif
