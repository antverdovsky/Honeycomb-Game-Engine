#pragma once
#ifndef VECTOR_2F_H
#define VECTOR_2F_H

namespace Honeycomb::Math {
	class Vector2f {
	public:
		/// Creates a new two dimensional vector with 0.0 for both the x and y
		/// components.
		Vector2f();

		/// Creates a new two dimensional vector with the specified x and y
		/// components.
		/// const float &x : The x-component.
		/// const float &y : The y-component.
		Vector2f(const float &x, const float &y);

		/// Gets a vector equivalent to the resultant of this vector and the
		/// specified second vector. This instance is not modified.
		/// const Vector2f &v2 : The second vector.
		/// return : The resultant of the two vectors.
		Vector2f add(const Vector2f &v2) const;

		/// Adds the specified vector to this vector, resulting in this 
		/// instance equaling to the resultant of the sum.
		/// const Vector2f &v2 : The second vector.
		/// return : This resultant vector.
		Vector2f& addTo(const Vector2f &v2);

		/// Calculates the angle (in radians) between this vector and the 
		/// specified second vector.
		/// const Vector2f &v2 : The second vector.
		/// return : The angle between, in radians.
		float angle(const Vector2f &v2) const;

		/// Gets the dot product of this vector and the specified second vetor.
		/// const Vector2f &v2 : The second vector.
		/// return : The dot product scalar.
		float dot(const Vector2f &v2) const;

		/// Gets the x and y components of the vector and writes them to the 
		/// passed in reference values.
		/// float &x : The ref. to where the x-component is to be written to.
		/// float &y : The ref. to where the y-component is to be written to.
		void get(float &x, float &y) const;

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

		/// Gets the magnitude of the vector.
		/// return : The magnitude.
		float magnitude() const;

		/// Normalizes this vector.
		/// return : The reference to this normalized vector.
		Vector2f& normalize();

		/// Gets a normalized version of this vector, without modifying it.
		/// return : A copy of this vector, normalized.
		Vector2f normalized() const;

		/// Returns a vector which is equivalent to this instance, rotated by 
		/// the specified amount of radians, on the { 1, 0, 0 } vector axis.
		/// const float &rad : The amount by which to rotate the vector, in 
		///					   radians. A positive amount rotates the vector 
		///					   counterclockwise, and a negative amount rotates 
		///					   the vector clockwise.
		/// return : The rotated vector.
		Vector2f rotate(const float &rad) const;

		/// Rotates this vector by the specified amount in radians, on the 
		/// { 1, 0, 0 } vector axis.
		/// const float &rad : The amount by which to rotate the vector, in 
		///					   radians. A positive amount rotates the vector 
		///					   counterclockwise, and a negative amount rotates 
		///					   the vector clockwise.
		/// return : The reference to this rotated vector.
		Vector2f& rotateTo(const float &rad);

		/// Returns a vector which is equivalent to this vector, but scaled by
		/// the specified scaling factor. This vector is not modified.
		/// const float &scale : The constant by which to scale the vector.
		/// return : A copy of this vector, scaled by the constant.
		Vector2f scale(const float &scale) const;

		/// Scales this vector by specified scalar factor.
		/// const float &scale : The constant by which to scale the vector.
		/// return : This scaled vector.
		Vector2f& scaleTo(const float &scale);

		/// Sets the x and y components of the vector.
		/// const float &x : The new x-component.
		/// const float &y : The new y-component.
		void set(const float &x, const float &y);

		/// Sets the x-component of the vector.
		/// const float &x : The new x-component.
		void setX(const float &x);

		/// Sets the y-component of the vector.
		/// const float &y : The new y-component.
		void setY(const float &y);

		/// Overloads the mulitplication operator to return a vector instance
		/// which is equivalent to this vector, scaled by the specified amount.
		/// This vector instance is not modified.
		/// const float &scale : The constant by which to scale the vector.
		/// return : The scaled vector.
		Vector2f operator*(const float &scale) const;

		/// Overloads the multiplication set operator to set this vector equal 
		/// to the scaled vector, and return it.
		/// const float &scale : The constant by which to scale this vector.
		/// return : This scaled vector.
		Vector2f& operator*=(const float &scale);

		/// Overloads the division operator to return a vector instance
		/// which is equivalent to this vector, inversely scaled by the 
		/// specified amount. This vector instance is not modified.
		/// const float &scale : The inverse constant by which to scale the 
		///						 vector.
		/// return : The scaled vector.
		Vector2f operator/(const float &scale) const;

		/// Overloads the division set operator to set this vector to the 
		/// inversely scaled vector. 
		/// const float &scale : The inverse constant by which to scale this 
		///					     vector.
		/// return : This scaled vector.
		Vector2f& operator/=(const float &scale);

		/// Overloads the addition operator to return a vector instance
		/// which is equivalent to the resultant of this vector and the 
		/// specified vector. Neither this nor the specified vector's values 
		/// are modified.
		/// const Vector2f &v2 : Reference to the second vector.
		/// return : The resultant vector.
		Vector2f operator+(const Vector2f &v2) const;;

		/// Overloads the addition set operator to set this vector equal to the
		/// resultant of this and the specified vector, and return it.
		/// const Vector2f &v2 : Reference to the second vector.
		/// return : This resultant vector.
		Vector2f& operator+=(const Vector2f &v2);

		/// Unary operator overload which returns a vector instance which is
		/// equivalent to this vector, negated. This vector is not modified.
		/// return : The negated copy of this vector.
		Vector2f operator-() const;

		/// Overloads the subtraction operator to return a vector instance
		/// which is equivalent to the difference of this vector and the 
		/// specified vector. Neither this nor the specified vector's values 
		/// are modified.
		/// const Vector2f &v2 : Reference to the second vector.
		/// return : The resultant vector.
		Vector2f operator-(const Vector2f &v2) const;

		/// Overloads the subtraction set operator to return this vector 
		/// instance, equal to the resultant difference of this and the 
		/// specified vector.
		/// const Vector2f &v2 : Reference to the second vector.
		/// return : The resultant vector.
		Vector2f& operator-=(const Vector2f &v2);
	private:
		float x; // The x-component
		float y; // The y-component
	};
}

#endif