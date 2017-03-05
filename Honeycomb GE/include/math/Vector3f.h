#pragma once
#ifndef VECTOR_3F_H
#define VECTOR_3F_H

namespace Honeycomb::Math { class Matrix4f; }
namespace Honeycomb::Math { class Quaternion; }

namespace Honeycomb::Math {
	class Vector3f {
	public:
		/// Creates a new three dimensional vector with 0.0 as the x, y and z
		/// components.
		Vector3f();

		/// Creates a new three dimensional vector with the specified x, y and 
		/// z components.
		/// const float &x : The x-component.
		/// const float &y : The y-component.
		/// const float &z : The z-component.
		Vector3f(const float &x, const float &y, const float &z);

		/// Empty Destructor.
		~Vector3f();

		/// Gets a vector equivalent to the resultant of this vector and the
		/// specified second vector. This instance is not modified.
		/// const Vector3f &v2 : The second vector.
		/// return : The resultant of the two vectors.
		Vector3f add(const Vector3f& v2) const;

		/// Adds the specified vector to this vector, resulting in this 
		/// instance equaling to the resultant of the sum.
		/// const Vector3f &v2 : The second vector.
		/// return : This reference to this resultant vector.
		Vector3f& addTo(const Vector3f& v2);

		/// Calculates the angle (in radians) between this vector and the 
		/// specified second vector.
		/// Vector3f v2 : The second vector.
		/// return : The angle between, in radians.
		float angle(const Vector3f& v2) const;

		/// Calculates the cross product of this vector and the specified 
		/// second vector and returns the product.
		/// const Vector3f &v2 : The second vector.
		/// return : The cross product vector.
		Vector3f cross(const Vector3f& v2) const;

		/// Calculates the cross product of this vector and the specified 
		/// vector and then overrides this vector to store the product.
		/// const Vector3f &v2 : The second vector.
		/// return : This reference to this cross product vector.
		Vector3f& crossTo(const Vector3f& v2);

		/// Returns an instance of a Vector3f equal to the inverse product of 
		/// this Vector and the specified Vector, where the product Vector is a
		/// Vector whose components are the products of this' and the specified
		/// Vector's components.
		/// const Vector3f &vec : The other vector.
		/// return : The inverse product of this vector and the specified 
		///			 vector.
		Vector3f divide(const Vector3f &vec) const;

		/// Divides this instance's individual components by the individual
		/// components of the specified Vector.
		/// const Vector3f &vec : The other vector.
		/// return : This instance, as the inverse product of this Vector and 
		///			 the specified Vector.
		Vector3f& divideTo(const Vector3f &vec);

		/// Gets the dot product of this vector and the specified second vetor.
		/// const Vector3f &v2 : The second vector.
		/// return : The dot product scalar.
		float dot(const Vector3f& v2) const;

		/// Gets the x, y, z components of the vector and writes them to the 
		/// passed in reference values.
		/// float &x : The ref. to where the x-component is to be written to.
		/// float &y : The ref. to where the y-component is to be written to.
		/// float &z : The ref. to where the z-component is to be written to.
		void get(float &x, float &y, float &z) const;

		/// Returns the global forward vector { 0, 0, 1 }.
		/// return : The vector.
		static Vector3f& getGlobalForward();

		/// Returns the global right vector { 1, 0, 0 }.
		/// return : The vector.
		static Vector3f& getGlobalRight();

		/// Returns the global up vector { 0, 1, 0 }.
		/// return : The vector.
		static Vector3f& getGlobalUp();

		/// Gets the reference to the x-component of the vector.
		/// return : The reference to the x-component.
		float& getX();

		/// Gets the constant reference to the x-component of the vector.
		/// return : The constant reference to the x-component.
		const float& getX() const;

		/// Gets the reference to the y-component of the vector.
		/// return : The reference to the y-component.
		float& getY();

		/// Gets the constant reference to the y-component of the vector.
		/// return : The constant reference to the y-component.
		const float& getY() const;

		/// Gets the reference to the z-component of the vector.
		/// return : The reference to the z-component.
		float& getZ();

		/// Gets the constant reference to the z-component of the vector.
		/// return : The constant reference to the z-component.
		const float& getZ() const;

		/// Gets the magnitude of the vector.
		/// return : The magnitude.
		float magnitude() const;

		/// Returns an instance of a Vector3f equal to the product of this
		/// Vector and the specified Matrix.
		/// const Matrix4f &mat : The matrix to be multiplied by this instance.
		/// return : The product of this vector and that matrix.
		Vector3f multiply(const Matrix4f &mat) const;

		/// Returns an instance of a Vector3f equal to the product of this
		/// Vector and the specified Vector, where the product Vector is a
		/// Vector whose components are the products of this' and the specified
		/// Vector's components.
		/// const Vector3f &vec : The other vector.
		/// return : The product of this vector and the specified vector.
		Vector3f multiply(const Vector3f &vec) const;

		/// Multiplies this instance by the specified Matrix and returns this
		/// instance.
		/// const Matrix4f &mat : The matrix to be multiplied to this instance.
		/// return : This instance, as the product of this Vector and the 
		///			 matrix.
		Vector3f& multiplyTo(const Matrix4f &mat);

		/// Multiplies this instance's individual components by the individual
		/// components of the specified Vector.
		/// const Vector3f &vec : The other vector.
		/// return : This instance, as the product of this Vector and the
		///			 specified Vector.
		Vector3f& multiplyTo(const Vector3f &vec);

		/// Normalizes this vector.
		/// return : This normalized vector, pointing in the same direction as
		///			 brefore, but with a magnitude of 1.
		Vector3f& normalize();

		/// Gets a normalized version of this vector, without modifying it.
		/// return : A vector which points in the same direction as this 
		///			 instance, but has a magnitude equal to 1.
		Vector3f normalized() const;

		/// Returns a vector which is equivalent to this instance, rotated by 
		/// the specified amount of radians, on the specified vector axis.
		/// const Vector3f &axis : The axis on which to rotate the vector.
		/// const float &rad : The amount by which to rotate the vector, in 
		///					   radians. A positive amount rotates the vector 
		///					   counterclockwise, and a negative amount rotates 
		///					   the vector clockwise.
		/// return : The rotated vector.
		Vector3f rotate(const Vector3f& v2, const float &rad) const;

		/// Returns a vector which is equivalent to this instance, rotated by
		/// the specified quaternion.
		/// const Quaternion& quat : The quaternion by which to rotate the
		///							 Vector.
		/// return : The rotated vector.
		Vector3f rotate(const Quaternion& quat) const;

		/// Rotates this vector by the specified amount of radians, on the 
		/// specified vector axis.
		/// const Vector3f &axis : The axis on which to rotate the vector.
		/// const float &rad : The amount by which to rotate the vector, in 
		///					   radians. A positive amount rotates the vector 
		///					   counterclockwise, and a negative amount rotates 
		///					   the vector clockwise.
		/// return : This rotated vector.
		Vector3f& rotateTo(const Vector3f& axis, const float &rad);

		/// Rotates this vector by the specified quaternion.
		/// const Quaternion& quat : The quaternion by which to rotate this
		///							 Vector.
		/// return : This rotated vector.
		Vector3f& rotateTo(const Quaternion& quat);

		/// Returns a vector which is equivalent to this vector, but scaled by
		/// the specified scaling factor. This vector is not modified.
		/// const float &scale : The constant by which to scale the vector.
		/// return : A copy of this vector, scaled by the constant.
		Vector3f scale(const float &scale) const;

		/// Scales this vector by specified scalar factor.
		/// const float &scale : The constant by which to scale the vector.
		/// return : This scaled vector.
		Vector3f& scaleTo(const float &scale);

		/// Sets the x, y and z components of the vector.
		/// const float &x : The new x-component.
		/// const float &y : The new y-component.
		/// const float &z : The new z-component.
		void set(const float &x, const float &y, const float &z);

		/// Sets the x-component of the vector.
		/// const float &x : The new x-component.
		void setX(const float &x);

		/// Sets the y-component of the vector.
		/// const float &y : The new y-component.
		void setY(const float &y);

		/// Sets the z-component of the vector.
		/// const float &y : The new z-component.
		void setZ(const float &z);

		/// Overloads the mulitplication operator to return a vector instance
		/// which is equivalent to this vector, scaled by the specified amount.
		/// This vector instance is not modified.
		/// const float &scale : The constant by which to scale the vector.
		/// return : The scaled vector.
		Vector3f operator*(const float &scale) const;

		/// Overloads the multiplication operator to return a vector instance
		/// which is equivalent to this Vector, multiplied by the specified
		/// Matrix. Do note that the Matrix is treated as a 3x3 for this
		/// calculation.
		/// const Matrix4f &mat : The Matrix by whih to multiply this vector.
		/// return : The Vector, post multiplication.
		Vector3f operator*(const Matrix4f &mat) const;

		/// Overloads the multiplication set operator to set this vector equal 
		/// to the scaled vector, and return it.
		/// const float &scale : The constant by which to scale the vector.
		/// return : This scaled vector.
		Vector3f& operator*=(const float &scale);

		/// Overloads the multiplication set operator to set this vector equal
		/// to the product of this Vector and the specified Matrix, and return
		/// it. Do note that the Matrix is treated as a 3x3 for this
		/// calculation.
		/// const Matrix4f &mat : The Matrix by which to multiply this Vector.
		/// return : This Vector, post multiplication.
		Vector3f& operator*=(const Matrix4f &mat);

		/// Overloads the division operator to return a vector instance
		/// which is equivalent to this vector, inversely scaled by the 
		/// specified amount. This vector instance is not modified.
		/// const float &scale : The inverse constant by which to scale the 
		///						 vector.
		/// return : The scaled vector.
		Vector3f operator/(const float &scale) const;

		/// Overloads the division set operator to set this vector to the 
		/// inversely scaled vector. 
		/// const float &scale : The inverse constant by which to scale this 
		///						 vector.
		/// return : This scaled vector.
		Vector3f& operator/=(const float &scale);

		/// Overloads the addition operator to return a vector instance
		/// which is equivalent to the resultant of this vector and the 
		/// specified vector. Neither this nor the specified vector's values 
		/// are modified.
		/// const Vector3f &v2 : Reference to the second vector.
		/// return : The resultant vector.
		Vector3f operator+(const Vector3f& v2) const;

		/// Overloads the addition set operator to set this vector equal to the
		/// resultant of this and the specified vector, and return it.
		/// const Vector3f &v2 : Reference to the second vector.
		/// return : This resultant vector.
		Vector3f& operator+=(const Vector3f& v2);

		/// Unary operator overload which returns a vector instance which is
		/// equivalent to this vector, negated. This vector is not modified.
		/// return : The negated copy of this vector.
		Vector3f operator-() const;

		/// Overloads the subtraction operator to return a vector instance
		/// which is equivalent to the difference of this vector and the 
		/// specified vector. Neither this nor the specified vector's values 
		/// are modified.
		/// const Vector3f &v2 : Reference to the second vector.
		/// return : The difference vector.
		Vector3f operator-(const Vector3f& v2) const;

		/// Overloads the subtraction set operator to return this vector 
		/// instance, equal to the resultant difference of this and the 
		/// specified vector.
		/// const Vector3f &v2 : Reference to the second vector.
		/// return : The resultant vector.
		Vector3f& operator-=(const Vector3f& v2);
	private:
		float x; // The x component
		float y; // The y component
		float z; // The z component

		static Vector3f forward; // Global Forward Vector { 0, 0, 1 }
		static Vector3f right; // Global Right Vector { 1, 0, 0 }
		static Vector3f up; // Global Up Vector { 0, 1, 0 }
	};
}

#endif