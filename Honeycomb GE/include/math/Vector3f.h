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

	/// Calculates the angle (in radians) between this vector and the specified
	/// second vector.
	/// Vector3f v2 : The second vector.
	/// return : The angle between, in radians.
	float angle(Vector3f v2);

	/// Calculates the cross product of this vector and the specified second
	/// vector.
	/// Vector3f v2 : The second vector.
	/// return : The cross product vector.
	Vector3f cross(Vector3f v2);

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

	/// Gets a normalized version of this vector, without modifying it.
	/// return : A vector which points in the same direction as this instance,
	///			 but has a magnitude equal to 1.
	Vector3f normalized();

	/// Returns a vector which is equivalent to this instance, rotated by the
	/// specified amount of radians, on the { 1, 0, 0 } vector axis.
	/// float rad : The amount by which to rotate the vector, in radians.
	/// return : The rotated vector.
	Vector3f rotate(float rad);

	/// Returns a vector which is equivalent to this vector, but scaled by
	/// the specified scaling factor. This vector is not modified.
	/// float scale : The constant by which to scale the vector.
	/// return : A copy of this vector, scaled by the constant.
	Vector3f scale(float scale);

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
	/// float y : The new x-component.
	void setZ(float z);

	/// Overloads the addition operator to return a vector instance
	/// which is equivalent to the resultant of this vector and the specified
	/// vector. Neither this nor the specified vector's values are modified.
	/// const Vector3f &v2 : Reference to the second vector.
	/// return : The resultant vector.
	Vector3f operator+(const Vector3f &v2);

	/// Overloads the mulitplication operator to return a vector instance
	/// which is equivalent to this vector, scaled by the specified amount.
	/// This vector instance is not modified.
	/// const float &scale : The constant by which to scale the vector.
	/// return : The scaled vector.
	Vector3f operator*(const float &scale);

	/// Unary operator overload which returns a vector instance which is
	/// equivalent to this vector, negated. This vector is not modified.
	/// return : The negated copy of this vector.
	Vector3f operator-() const;

	/// Overloads the subtraction operator to return a vector instance
	/// which is equivalent to the difference of this vector and the specified
	/// vector. Neither this nor the specified vector's values are modified.
	/// const Vector3f &v2 : Reference to the second vector.
	/// return : The difference vector.
	Vector3f operator-(const Vector3f &v2);
private:
	float x;
	float y;
	float z;
};

#endif