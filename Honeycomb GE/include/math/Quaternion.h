#pragma once
#ifndef QUATERNION_H
#define QUATERNION_H

namespace Honeycomb::Math { class Vector3f; }

namespace Honeycomb::Math {
	class Quaternion {
	public:
		/// Initializes a new Quaternion to 0.0 for x, y, and z and 1.0 for the
		/// w component.
		Quaternion();

		/// Initializes a new rotation Quaternion.
		/// Vector3f axis : ?
		/// float rad : ? todo
		Quaternion(Vector3f axis, float rad);

		/// Initializes a new Quaternion with the specified x, y, z, and w 
		/// components.
		/// float x : The x component.
		/// float y : The y component.
		/// float z : The z component.
		/// float w : The w component.
		Quaternion(float x, float y, float z, float w);

		/// Empty Destructor.
		~Quaternion();

		/// Conjugates this Quaternion such that all imaginary components are
		/// multiplied by -1.
		/// return : This conjugated instance.
		Quaternion conjugate();

		/// Returns a Quaternion instance, equivalent to this instance, but
		/// conjugated.
		/// return : The conjugated instance.
		Quaternion conjugated();

		/// Gets the x, y, z, w components of the vector and writes them to the 
		/// passed in reference values.
		/// float &x : The ref. to where the x-component is to be written to.
		/// float &y : The ref. to where the y-component is to be written to.
		/// float &z : The ref. to where the z-component is to be written to.
		/// float &w : The ref. to where the w-component is to be written to.
		void get(float &x, float &y, float &z, float &w);

		/// Gets a vector representing the forward of this Quaternion.
		/// return : The forward direction vector.
		Vector3f getForwardVector();

		/// Gets a vector representing the right of this Quaternion.
		/// return : The right direction vector.
		Vector3f getRightVector();

		/// Gets a vector representing the up of this Quaternion.
		/// return : The up direction vector.
		Vector3f getUpVector();

		/// Gets the x-component of the quaternion.
		/// return : The x-component.
		float getX();

		/// Gets the y-component of the quaternion.
		/// return : The y-component.
		float getY();

		/// Gets the z-component of the quaternion.
		/// return : The z-component.
		float getZ();

		/// Gets the w-component of the quaternion.
		/// return : The w-component.
		float getW();

		/// Gets the magnitude of the Quaternion.
		/// return : The magnitude.
		float magnitude();

		/// Multiplies this and the specified quaternion and returns the 
		/// quaternion representing the product. Neither this nor the specified
		/// Quaternion is modified.
		/// Quaternion q2 : The second quaternion.
		/// return : The product quaternion.
		Quaternion multiply(Quaternion q2);

		/// Multiplies this and the specified vector and returns the quaternion
		/// representing the product. Neither this nor the specified Vector is
		/// modified.
		/// Vector3f v : The Vector by which to multiply this Quaternion.
		/// return : The product quaternion.
		Quaternion multiply(Vector3f v);

		/// Multiplies this and the specified quaternion and stores the product
		/// quaternion in this instance.
		/// Quaternion q2 : The second quaternion.
		/// return : This product quaternion.
		Quaternion multiplyTo(Quaternion q2);

		/// Multiplies this and the specified vector and stores the quaternion
		/// representing the product in this instance.
		/// Vector3f v : The Vector by which to multiply this Quaternion.
		/// return : This product quaternion.
		Quaternion multiplyTo(Vector3f v);

		/// Normalizes this vector.
		/// return : This normalized Quaternion.
		Quaternion normalize();

		/// Gets a normalized version of this Quaternion, without modifying it.
		/// return : The normalized copy of this Quaternion.
		Quaternion normalized();

		/// Sets the x, y, z and w components of the vector.
		/// float x : The new x-component.
		/// float y : The new y-component.
		/// float z : The new z-component.
		/// float w : The new w-component.
		void set(float x, float y, float z, float w);

		/// Sets the x-component of the quaternion.
		/// float y : The new x-component.
		void setX(float y);

		/// Sets the y-component of the quaternion.
		/// float y : The new y-component.
		void setY(float y);

		/// Sets the z-component of the quaternion.
		/// float y : The new z-component.
		void setZ(float z);

		/// Sets the w-component of the quaternion.
		/// float w : The new w-component.
		void setW(float w);

		/// Overloads the multiplication operator to return the product of this
		/// and the specified quaternion.
		/// Quaternion q2 : The second quaternion.
		/// return : The product quaternion.
		Quaternion operator*(Quaternion q2);

		/// Overloads the multiplication operator to return the product of this
		/// and the specified vector.
		/// Vector3f v : The vector.
		/// return : The product quaternion.
		Quaternion operator*(Vector3f v);

		/// Overloads the multiplication set operator to return this instance,
		/// after it has been modified to store the product of this and the
		/// specified quaternion.
		/// Quaternion q2 : The second quaternion.
		/// return : The product quaternion.
		Quaternion operator*=(Quaternion q2);

		/// Overloads the multiplication set operator to return this instance,
		/// after it has been modified to store the product of this and the
		/// specified vector.
		/// Vector3f v : The vector.
		/// return : The product quaternion.
		Quaternion operator*=(Vector3f v);
	private:
		float x; // The x component
		float y; // The y component
		float z; // The z component
		float w; // The w component
	};
}

#endif