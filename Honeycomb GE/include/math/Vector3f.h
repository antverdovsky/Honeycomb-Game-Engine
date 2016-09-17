#pragma once
#ifndef VECTOR_3F_H
#define VECTOR_3F_H

class Vector3f {
public:
	/// Creates a new three dimensional vector with the specified x, y and z
	/// components.
	/// float x : The x-component.
	/// float y : The y-component.
	/// float z : The z-component.
	Vector3f(float x, float y, float z);

	/// Empty Destructor.
	~Vector3f();

	/// Gets a vector equivalent to the resultant of this vector and the
	/// specified second vector. This instance is not modified.
	/// Vector3f v2 : The second vector.
	/// return : The resultant of the two vectors.
	Vector3f add(Vector3f v2);

	/// Adds the specified vector to this vector, resulting in this instance
	/// equaling to the resultant of the sum.
	/// Vector3f v2 : The second vector.
	/// return : This resultant vector.
	Vector3f addTo(Vector3f v2);

	/// Calculates the angle (in radians) between this vector and the specified
	/// second vector.
	/// Vector3f v2 : The second vector.
	/// return : The angle between, in radians.
	float angle(Vector3f v2);

	/// Calculates the cross product of this vector and the specified second
	/// vector and returns the product.
	/// Vector3f v2 : The second vector.
	/// return : The cross product vector.
	Vector3f cross(Vector3f v2);

	/// Calculates the cross product of this vector and the specified vector and
	/// then overrides this vector to store the product.
	/// Vector3f v2 : The second vector.
	/// return : This cross product vector.
	Vector3f crossTo(Vector3f v2);

	/// Gets the dot product of this vector and the specified second vetor.
	/// Vector3f v2 : The second vector.
	/// return : The dot product scalar.
	float dot(Vector3f v2);

	/// Gets the x, y, z components of the vector and writes them to the passed
	/// in reference values.
	/// float &x : The reference to where the x-component is to be written to.
	/// float &y : The reference to where the y-component is to be written to.
	/// float &z : The reference to where the z-component is to be written to.
	void get(float &x, float &y, float &z);

	/// Gets the x-component of the vector.
	/// return : The x-component.
	float getX();

	/// Gets the y-component of the vector.
	/// return : The y-component.
	float getY();

	/// Gets the z-component of the vector.
	/// return : The z-component.
	float getZ();

	/// Gets the magnitude of the vector.
	/// return : The magnitude.
	float magnitude();

	/// Normalizes this vector.
	/// return : This normalized vector, pointing in the same direction as
	///			 brefore, but with a magnitude of 1.
	Vector3f normalize();

	/// Gets a normalized version of this vector, without modifying it.
	/// return : A vector which points in the same direction as this instance,
	///			 but has a magnitude equal to 1.
	Vector3f normalized();

	/// Returns a vector which is equivalent to this instance, rotated by the
	/// specified amount of radians, on the specified vector axis.
	/// Vector3f axis : The axis on which to rotate the vector.
	/// float rad : The amount by which to rotate the vector, in radians. A
	///				positive amount will rotate the vector counterclockwise,
	///				and a negative amount will rotate the angle clockwise.
	/// return : The rotated vector.
	Vector3f rotate(Vector3f axis, float rad);

	/// Rotates this vector by the specified amount of radians, on the 
	/// specified vector axis.
	/// Vector3f axis : The axis on which to rotate the vector.
	/// float rad : The amount by which to rotate the vector, in radians. A
	///				positive amount will rotate the vector counterclockwise,
	///				and a negative amount will rotate the angle clockwise.
	/// return : The rotated vector.
	Vector3f rotateTo(Vector3f axis, float rad);

	/// Returns a vector which is equivalent to this vector, but scaled by
	/// the specified scaling factor. This vector is not modified.
	/// float scale : The constant by which to scale the vector.
	/// return : A copy of this vector, scaled by the constant.
	Vector3f scale(float scale);

	/// Scales this vector by specified scalar factor.
	/// float scale : The constant by which to scale the vector.
	/// return : This scaled vector.
	Vector3f scaleTo(float scale);

	/// Sets the x, y and z components of the vector.
	/// float x : The new x-component.
	/// float y : The new y-component.
	/// float z : The new z-component.
	void set(float x, float y, float z);

	/// Sets the x-component of the vector.
	/// float y : The new x-component.
	void setX(float y);

	/// Sets the y-component of the vector.
	/// float y : The new y-component.
	void setY(float y);

	/// Sets the z-component of the vector.
	/// float y : The new z-component.
	void setZ(float z);

	/// Overloads the mulitplication operator to return a vector instance
	/// which is equivalent to this vector, scaled by the specified amount.
	/// This vector instance is not modified.
	/// const float &scale : The constant by which to scale the vector.
	/// return : The scaled vector.
	Vector3f operator*(float scale);

	/// Overloads the multiplication set operator to set this vector equal to
	/// the scaled vector, and return it.
	/// float scale : The constant by which to scale the vector.
	/// return : This scaled vector.
	Vector3f operator*=(float scale);

	/// Overloads the division operator to return a vector instance
	/// which is equivalent to this vector, inversely scaled by the specified 
	/// amount. This vector instance is not modified.
	/// float scale : The inverse constant by which to scale the vector.
	/// return : The scaled vector.
	Vector3f operator/(float scale);

	/// Overloads the division set operator to set this vector to the inversely
	/// scaled vector. 
	/// float scale : The inverse constant by which to scale this vector.
	/// return : This scaled vector.
	Vector3f operator/=(float scale);

	/// Overloads the addition operator to return a vector instance
	/// which is equivalent to the resultant of this vector and the specified
	/// vector. Neither this nor the specified vector's values are modified.
	/// const Vector3f &v2 : Reference to the second vector.
	/// return : The resultant vector.
	Vector3f operator+(Vector3f v2);

	/// Overloads the addition set operator to set this vector equal to the
	/// resultant of this and the specified vector, and return it.
	/// Vector2f v2 : Reference to the second vector.
	/// return : This resultant vector.
	Vector3f operator+=(Vector3f v2);

	/// Unary operator overload which returns a vector instance which is
	/// equivalent to this vector, negated. This vector is not modified.
	/// return : The negated copy of this vector.
	Vector3f operator-();

	/// Overloads the subtraction operator to return a vector instance
	/// which is equivalent to the difference of this vector and the specified
	/// vector. Neither this nor the specified vector's values are modified.
	/// const Vector3f &v2 : Reference to the second vector.
	/// return : The difference vector.
	Vector3f operator-(Vector3f v2);

	/// Overloads the subtraction set operator to return this vector instance,
	/// equal to the resultant difference of this and the specified vector.
	/// Vector2f v2 : Reference to the second vector.
	/// return : The resultant vector.
	Vector3f operator-=(Vector3f v2);
private:
	float x; // The x component
	float y; // The y component
	float z; // The z component
};

#endif