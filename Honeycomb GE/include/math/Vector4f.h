#pragma once
#ifndef VECTOR_4F_H
#define VECTOR_4F_H

namespace Honeycomb::Math {
	class Vector4f {
	public:
		/// Creates a new four dimensional vector with 0.0 as the x, y, z and w
		/// components.
		Vector4f();

		/// Creates a new three dimensional vector with the specified x, y, z 
		/// and w components.
		/// float x : The x-component.
		/// float y : The y-component.
		/// float z : The z-component.
		/// float w : The w-component.
		Vector4f(float x, float y, float z, float w);

		/// Empty Destructor.
		~Vector4f();

		/// Gets a vector equivalent to the resultant of this vector and the
		/// specified second vector. This instance is not modified.
		/// Vector3f v2 : The second vector.
		/// return : The resultant of the two vectors.
		Vector4f add(Vector4f v2);

		/// Adds the specified vector to this vector, resulting in this 
		/// instance equaling to the resultant of the sum.
		/// Vector3f v2 : The second vector.
		/// return : This resultant vector.
		Vector4f addTo(Vector4f v2);

		/// Gets the dot product of this vector and the specified second vetor.
		/// Vector4f v2 : The second vector.
		/// return : The dot product scalar.
		float dot(Vector4f v2);

		/// Gets the x, y, z, w components of the vector and writes them to the 
		/// passed in reference values.
		/// float &x : The ref. to where the x-component is to be written to.
		/// float &y : The ref. to where the y-component is to be written to.
		/// float &z : The ref. to where the z-component is to be written to.
		/// float &w : The ref. to where the w-component is to be written to.
		void get(float &x, float &y, float &z, float &w);

		/// Gets the x-component of the vector.
		/// return : The x-component.
		float& getX();

		/// Gets the y-component of the vector.
		/// return : The y-component.
		float& getY();

		/// Gets the z-component of the vector.
		/// return : The z-component.
		float& getZ();

		/// Gets the w-component of this vector.
		/// return : The w-component.
		float& getW();

		/// Gets the magnitude of the vector.
		/// return : The magnitude.
		float magnitude();

		/// Normalizes this vector.
		/// return : This normalized vector, pointing in the same direction as
		///			 brefore, but with a magnitude of 1.
		Vector4f normalize();

		/// Gets a normalized version of this vector, without modifying it.
		/// return : A vector which points in the same direction as this 
		///			 instance, but has a magnitude equal to 1.
		Vector4f normalized();

		/// Returns a vector which is equivalent to this vector, but scaled by
		/// the specified scaling factor. This vector is not modified.
		/// float scale : The constant by which to scale the vector.
		/// return : A copy of this vector, scaled by the constant.
		Vector4f scale(float scale);

		/// Scales this vector by specified scalar factor.
		/// float scale : The constant by which to scale the vector.
		/// return : This scaled vector.
		Vector4f scaleTo(float scale);

		/// Sets the x, y, z and w components of the vector.
		/// float x : The new x-component.
		/// float y : The new y-component.
		/// float z : The new z-component.
		/// float w : the new w-component.
		void set(float x, float y, float z, float w);

		/// Sets the x-component of the vector.
		/// float y : The new x-component.
		void setX(float y);

		/// Sets the y-component of the vector.
		/// float y : The new y-component.
		void setY(float y);

		/// Sets the z-component of the vector.
		/// float y : The new z-component.
		void setZ(float z);

		/// Sets the w-component of the vector.
		/// float w : The new w-component.
		void setW(float w);

		/// Overloads the mulitplication operator to return a vector instance
		/// which is equivalent to this vector, scaled by the specified amount.
		/// This vector instance is not modified.
		/// const float &scale : The constant by which to scale the vector.
		/// return : The scaled vector.
		Vector4f operator*(float scale);

		/// Overloads the multiplication set operator to set this vector equal 
		/// to the scaled vector, and return it.
		/// float scale : The constant by which to scale the vector.
		/// return : This scaled vector.
		Vector4f operator*=(float scale);

		/// Overloads the division operator to return a vector instance
		/// which is equivalent to this vector, inversely scaled by the 
		/// specified amount. This vector instance is not modified.
		/// float scale : The inverse constant by which to scale the vector.
		/// return : The scaled vector.
		Vector4f operator/(float scale);

		/// Overloads the division set operator to set this vector to the 
		/// inversely scaled vector. 
		/// float scale : The inverse constant by which to scale this vector.
		/// return : This scaled vector.
		Vector4f operator/=(float scale);

		/// Overloads the addition operator to return a vector instance
		/// which is equivalent to the resultant of this vector and the 
		/// specified vector. Neither this nor the specified vector's values 
		/// are modified.
		/// const Vector4f &v2 : Reference to the second vector.
		/// return : The resultant vector.
		Vector4f operator+(Vector4f v2);

		/// Overloads the addition set operator to set this vector equal to the
		/// resultant of this and the specified vector, and return it.
		/// Vector2f v2 : Reference to the second vector.
		/// return : This resultant vector.
		Vector4f operator+=(Vector4f v2);

		/// Unary operator overload which returns a vector instance which is
		/// equivalent to this vector, negated. This vector is not modified.
		/// return : The negated copy of this vector.
		Vector4f operator-();

		/// Overloads the subtraction operator to return a vector instance
		/// which is equivalent to the difference of this vector and the 
		/// specified vector. Neither this nor the specified vector's values 
		/// are modified.
		/// const Vector4f &v2 : Reference to the second vector.
		/// return : The difference vector.
		Vector4f operator-(Vector4f v2);

		/// Overloads the subtraction set operator to return this vector 
		/// instance, equal to the resultant difference of this and the 
		/// specified vector.
		/// Vector2f v2 : Reference to the second vector.
		/// return : The resultant vector.
		Vector4f operator-=(Vector4f v2);
	private:
		float x; // The x component
		float y; // The y component
		float z; // The z component
		float w; // The w component
	};
}

#endif