#pragma once
#ifndef VECTOR_4F_H
#define VECTOR_4F_H

namespace Honeycomb { namespace Math { class Matrix4f; } }

namespace Honeycomb { namespace Math {
	class Vector4f {
	public:
		/// Creates a new four dimensional vector with 0.0 as the x, y, z and w
		/// components.
		Vector4f();

		/// Creates a new three dimensional vector with the specified x, y, z 
		/// and w components.
		/// const float &x : The x component.
		/// const float &y : The y component.
		/// const float &z : The z component.
		/// const float &w : The w component.
		Vector4f(const float &x, const float &y, const float &z, 
				const float &w);

		/// Empty Destructor.
		~Vector4f();

		/// Gets a vector equivalent to the resultant of this vector and the
		/// specified second vector. This instance is not modified.
		/// const Vector4f &v2 : The second vector.
		/// return : The resultant of the two vectors.
		Vector4f add(const Vector4f &v2) const;

		/// Adds the specified vector to this vector, resulting in this 
		/// instance equaling to the resultant of the sum.
		/// const Vector4f &v2 : The second vector.
		/// return : This resultant vector.
		Vector4f& addTo(const Vector4f &v2);

		/// Gets the dot product of this vector and the specified second vetor.
		/// const Vector4f &v2 : The second vector.
		/// return : The dot product scalar.
		float dot(const Vector4f &v2) const;

		/// Gets the x, y, z, w components of the vector and writes them to the 
		/// passed in reference values.
		/// float &x : The ref. to where the x-component is to be written to.
		/// float &y : The ref. to where the y-component is to be written to.
		/// float &z : The ref. to where the z-component is to be written to.
		/// float &w : The ref. to where the w-component is to be written to.
		void get(float &x, float &y, float &z, float &w) const;

		/// Gets the reference to the w-component of the vector.
		/// return : The reference to the w-component.
		float& getW();

		/// Gets the constant reference to the w-component of the vector.
		/// return : The constant reference to the w-component.
		const float& getW() const;

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

		/// Returns an instance of a Vector4f equal to the product of this
		/// Vector and the specified Matrix.
		/// const Matrix4f &mat : The matrix to be multiplied by this instance.
		/// return : The product of this vector and that matrix.
		Vector4f multiply(const Matrix4f &mat) const;

		/// Multiplies this instance by the specified Matrix and returns this
		/// instance.
		/// const Matrix4f &mat : The matrix to be multiplied to this instance.
		/// return : This instance, as the product of this Vector and the 
		///			 matrix.
		Vector4f& multiplyTo(const Matrix4f &mat);

		/// Normalizes this vector.
		/// return : This normalized vector, pointing in the same direction as
		///			 brefore, but with a magnitude of 1.
		Vector4f& normalize();

		/// Gets a normalized version of this vector, without modifying it.
		/// return : A vector which points in the same direction as this 
		///			 instance, but has a magnitude equal to 1.
		Vector4f normalized() const;

		/// Returns a vector which is equivalent to this vector, but scaled by
		/// the specified scaling factor. This vector is not modified.
		/// const float &scale : The constant by which to scale the vector.
		/// return : A copy of this vector, scaled by the constant.
		Vector4f scale(const float &scale) const;

		/// Scales this vector by specified scalar factor.
		/// const float &scale : The constant by which to scale the vector.
		/// return : This scaled vector.
		Vector4f& scaleTo(const float &scale);

		/// Sets the x, y, z and w components of the vector.
		/// const float &x : The new x-component.
		/// const float &y : The new y-component.
		/// const float &z : The new z-component.
		/// const float &w : the new w-component.
		void set(const float &x, const float &y, const float &z, 
				const float &w);

		/// Sets the x-component of the vector.
		/// const float &x : The new x-component.
		void setX(const float &x);

		/// Sets the y-component of the vector.
		/// const float &y : The new y-component.
		void setY(const float &y);

		/// Sets the z-component of the vector.
		/// const float &z : The new z-component.
		void setZ(const float &z);

		/// Sets the w-component of the vector.
		/// const float &w : The new w-component.
		void setW(const float &w);

		/// Overloads the mulitplication operator to return a vector instance
		/// which is equivalent to this vector, scaled by the specified amount.
		/// This vector instance is not modified.
		/// const float &scale : The constant by which to scale the vector.
		/// return : The scaled vector.
		Vector4f operator*(const float &scale) const;

		/// Overloads the multiplication operator to return a vector instance
		/// which is equivalent to this Vector, multiplied by the specified
		/// Matrix.
		/// const Matrix4f &mat : The Matrix by whih to multiply this vector.
		/// return : The Vector, post multiplication.
		Vector4f operator*(const Matrix4f &mat) const;

		/// Overloads the multiplication set operator to set this vector equal 
		/// to the scaled vector, and return it.
		/// const float &scale : The constant by which to scale the vector.
		/// return : This scaled vector.
		Vector4f& operator*=(const float &scale);

		/// Overloads the multiplication set operator to set this vector equal
		/// to the product of this Vector and the specified Matrix, and return
		/// it.
		/// const Matrix4f &mat : The Matrix by which to multiply this Vector.
		/// return : This Vector, post multiplication.
		Vector4f& operator*=(const Matrix4f &mat);

		/// Overloads the division operator to return a vector instance
		/// which is equivalent to this vector, inversely scaled by the 
		/// specified amount. This vector instance is not modified.
		/// const float &scale : The inverse constant by which to scale the 
		///						 vector.
		/// return : The scaled vector.
		Vector4f operator/(const float &scale) const;

		/// Overloads the division set operator to set this vector to the 
		/// inversely scaled vector. 
		/// const float &scale : The inverse constant by which to scale this 
		///						 vector.
		/// return : This scaled vector.
		Vector4f& operator/=(const float &scale);

		/// Overloads the addition operator to return a vector instance
		/// which is equivalent to the resultant of this vector and the 
		/// specified vector. Neither this nor the specified vector's values 
		/// are modified.
		/// const Vector4f &v2 : Reference to the second vector.
		/// return : The resultant vector.
		Vector4f operator+(const Vector4f &v2) const;

		/// Overloads the addition set operator to set this vector equal to the
		/// resultant of this and the specified vector, and return it.
		/// const Vector4f &v2 : Reference to the second vector.
		/// return : This resultant vector.
		Vector4f& operator+=(const Vector4f &v2);

		/// Unary operator overload which returns a vector instance which is
		/// equivalent to this vector, negated. This vector is not modified.
		/// return : The negated copy of this vector.
		Vector4f operator-() const;

		/// Overloads the subtraction operator to return a vector instance
		/// which is equivalent to the difference of this vector and the 
		/// specified vector. Neither this nor the specified vector's values 
		/// are modified.
		/// const Vector4f &v2 : Reference to the second vector.
		/// return : The difference vector.
		Vector4f operator-(const Vector4f &v2) const;

		/// Overloads the subtraction set operator to return this vector 
		/// instance, equal to the resultant difference of this and the 
		/// specified vector.
		/// const Vector4f &v2 : Reference to the second vector.
		/// return : The resultant vector.
		Vector4f& operator-=(const Vector4f &v2);
	private:
		float x; // The x component
		float y; // The y component
		float z; // The z component
		float w; // The w component
	};
} }

#endif
