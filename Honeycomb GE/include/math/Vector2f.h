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
		/// float x : The x-component.
		/// float y : The y-component.
		Vector2f(float x, float y);

		/// Empty Destructor.
		~Vector2f();

		/// Gets a vector equivalent to the resultant of this vector and the
		/// specified second vector. This instance is not modified.
		/// Vector2f v2 : The second vector.
		/// return : The resultant of the two vectors.
		Vector2f add(Vector2f v2);

		/// Adds the specified vector to this vector, resulting in this 
		/// instance equaling to the resultant of the sum.
		/// Vector2f v2 : The second vector.
		/// return : This resultant vector.
		Vector2f addTo(Vector2f v2);

		/// Calculates the angle (in radians) between this vector and the 
		/// specified second vector.
		/// Vector2f v2 : The second vector.
		/// return : The angle between, in radians.
		float angle(Vector2f v2);

		/// Gets the dot product of this vector and the specified second vetor.
		/// Vector2f v2 : The second vector.
		/// return : The dot product scalar.
		float dot(Vector2f v2);

		/// Gets the x and y components of the vector and writes them to the 
		/// passed in reference values.
		/// float &x : The ref. to where the x-component is to be written to.
		/// float &y : The ref. to where the y-component is to be written to.
		void get(float &x, float &y);

		/// Gets the x-component of the vector.
		/// return : The x-component.
		float& getX();

		/// Gets the y-component of the vector.
		/// return : The y-component.
		float& getY();

		/// Gets the magnitude of the vector.
		/// return : The magnitude.
		float magnitude();

		/// Normalizes this vector.
		/// return : This normalized vector, pointing in the same direction as
		///			 brefore, but with a magnitude of 1.
		Vector2f normalize();

		/// Gets a normalized version of this vector, without modifying it.
		/// return : A vector which points in the same direction as this 
		///			 instance, but has a magnitude equal to 1.
		Vector2f normalized();

		/// Returns a vector which is equivalent to this instance, rotated by 
		/// the specified amount of radians, on the { 1, 0, 0 } vector axis.
		/// float rad : The amount by which to rotate the vector, in radians.
		///				A positive amount rotates the vector counterclockwise,
		///				and a negative amount rotates the angle clockwise.
		/// return : The rotated vector.
		Vector2f rotate(float rad);

		/// Rotates this vector by the specified amount in radians, on the 
		/// { 1, 0, 0 } vector axis.
		/// float rad : The amount by which to rotate the vector, in radians.
		///				A positive amount rotates the vector counterclockwise,
		///				and a negative amount rotates the angle clockwise.
		/// return : This rotated vector.
		Vector2f rotateTo(float rad);

		/// Returns a vector which is equivalent to this vector, but scaled by
		/// the specified scaling factor. This vector is not modified.
		/// float scale : The constant by which to scale the vector.
		/// return : A copy of this vector, scaled by the constant.
		Vector2f scale(float scale);

		/// Scales this vector by specified scalar factor.
		/// float scale : The constant by which to scale the vector.
		/// return : This scaled vector.
		Vector2f scaleTo(float scale);

		/// Sets the x and y components of the vector.
		/// float x : The new x-component.
		/// float y : The new y-component.
		void set(float x, float y);

		/// Sets the x-component of the vector.
		/// float y : The new x-component.
		void setX(float y);

		/// Sets the y-component of the vector.
		/// float y : The new y-component.
		void setY(float y);

		/// Overloads the mulitplication operator to return a vector instance
		/// which is equivalent to this vector, scaled by the specified amount.
		/// This vector instance is not modified.
		/// float scale : The constant by which to scale the vector.
		/// return : The scaled vector.
		Vector2f operator*(float scale);

		/// Overloads the multiplication set operator to set this vector equal 
		/// to the scaled vector, and return it.
		/// float scale : The constant by which to scale the vector.
		/// return : This scaled vector.
		Vector2f operator*=(float scale);

		/// Overloads the division operator to return a vector instance
		/// which is equivalent to this vector, inversely scaled by the 
		/// specified amount. This vector instance is not modified.
		/// float scale : The inverse constant by which to scale the vector.
		/// return : The scaled vector.
		Vector2f operator/(float scale);

		/// Overloads the division set operator to set this vector to the 
		/// inversely scaled vector. 
		/// float scale : The inverse constant by which to scale this vector.
		/// return : This scaled vector.
		Vector2f operator/=(float scale);

		/// Overloads the addition operator to return a vector instance
		/// which is equivalent to the resultant of this vector and the 
		/// specified vector. Neither this nor the specified vector's values 
		/// are modified.
		/// Vector2f v2 : Reference to the second vector.
		/// return : The resultant vector.
		Vector2f operator+(Vector2f v2);

		/// Overloads the addition set operator to set this vector equal to the
		/// resultant of this and the specified vector, and return it.
		/// Vector2f v2 : Reference to the second vector.
		/// return : This resultant vector.
		Vector2f operator+=(Vector2f v2);

		/// Unary operator overload which returns a vector instance which is
		/// equivalent to this vector, negated. This vector is not modified.
		/// return : The negated copy of this vector.
		Vector2f operator-();

		/// Overloads the subtraction operator to return a vector instance
		/// which is equivalent to the difference of this vector and the 
		/// specified vector. Neither this nor the specified vector's values 
		/// are modified.
		/// Vector2f v2 : Reference to the second vector.
		/// return : The resultant vector.
		Vector2f operator-(Vector2f v2);

		/// Overloads the subtraction set operator to return this vector 
		/// instance, equal to the resultant difference of this and the 
		/// specified vector.
		/// Vector2f v2 : Reference to the second vector.
		/// return : The resultant vector.
		Vector2f operator-=(Vector2f v2);
	private:
		float x; // The x-component
		float y; // The y-component
	};
}

#endif