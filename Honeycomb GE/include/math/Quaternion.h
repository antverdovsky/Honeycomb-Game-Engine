#pragma once
#ifndef QUATERNION_H
#define QUATERNION_H

#include "..\..\include\math\Matrix4f.h"
#include "..\..\include\math\Vector3f.h"

namespace Honeycomb::Math {
	class Quaternion {
	public:
		/// Initializes a new Quaternion to 0.0 for x, y, and z and 1.0 for the
		/// w component.
		Quaternion();

		/// Initializes a new rotation Quaternion.
		/// Vector3f axis : The axis on which the rotation occurs.
		/// float rad : The value, in radians, of the rotation on the axis.
		Quaternion(const Vector3f &axis, const float &rad);

		/// Initializes a new Quaternion with the specified x, y, z, and w 
		/// components.
		/// float x : The x component.
		/// float y : The y component.
		/// float z : The z component.
		/// float w : The w component.
		Quaternion(const float &x, const float &y, const float &z, 
				const float &w);

		/// Empty Destructor.
		~Quaternion();

		/// Conjugates this Quaternion such that all imaginary components are
		/// multiplied by -1.
		/// return : This conjugated instance.
		Quaternion conjugate();

		/// Returns a Quaternion instance, equivalent to this instance, but
		/// conjugated.
		/// return : The conjugated instance.
		Quaternion conjugated() const;

		/// Gets the x, y, z, w components of the vector and writes them to the 
		/// passed in reference values.
		/// float &x : The ref. to where the x-component is to be written to.
		/// float &y : The ref. to where the y-component is to be written to.
		/// float &z : The ref. to where the z-component is to be written to.
		/// float &w : The ref. to where the w-component is to be written to.
		void get(float &x, float &y, float &z, float &w) const;

		/// Gets a vector representing the forward of this Quaternion.
		/// return : The forward direction vector.
		Vector3f getForwardVector() const;

		/// Gets a vector representing the right of this Quaternion.
		/// return : The right direction vector.
		Vector3f getRightVector() const;

		/// Gets a vector representing the up of this Quaternion.
		/// return : The up direction vector.
		Vector3f getUpVector() const;

		/// Gets the x-component of the quaternion.
		/// return : The x-component.
		const float& getX() const;

		/// Gets the y-component of the quaternion.
		/// return : The y-component.
		const float& getY() const;

		/// Gets the z-component of the quaternion.
		/// return : The z-component.
		const float& getZ() const;

		/// Gets the w-component of the quaternion.
		/// return : The w-component.
		const float& getW() const;

		/// Gets the magnitude of the Quaternion.
		/// return : The magnitude.
		float magnitude() const;

		/// Multiplies this and the specified quaternion and returns the 
		/// quaternion representing the product. Neither this nor the specified
		/// Quaternion is modified.
		/// Quaternion q2 : The second quaternion.
		/// return : The product quaternion.
		Quaternion multiply(const Quaternion &q2) const;

		/// Multiplies this and the specified vector and returns the quaternion
		/// representing the product. Neither this nor the specified Vector is
		/// modified.
		/// Vector3f v : The Vector by which to multiply this Quaternion.
		/// return : The product quaternion.
		Quaternion multiply(const Vector3f &v) const;

		/// Multiplies this and the specified quaternion and stores the product
		/// quaternion in this instance.
		/// Quaternion q2 : The second quaternion.
		/// return : This product quaternion.
		Quaternion multiplyTo(const Quaternion &q2);

		/// Multiplies this and the specified vector and stores the quaternion
		/// representing the product in this instance.
		/// Vector3f v : The Vector by which to multiply this Quaternion.
		/// return : This product quaternion.
		Quaternion multiplyTo(const Vector3f &v);

		/// Normalizes this vector.
		/// return : This normalized Quaternion.
		Quaternion normalize();

		/// Gets a normalized version of this Quaternion, without modifying it.
		/// return : The normalized copy of this Quaternion.
		Quaternion normalized() const;

		/// Sets the x, y, z and w components of the vector.
		/// float x : The new x-component.
		/// float y : The new y-component.
		/// float z : The new z-component.
		/// float w : The new w-component.
		void set(const float &x, const float &y, const float &z, 
				const float &w);

		/// Sets the x-component of the quaternion.
		/// float x : The new x-component.
		void setX(const float &x);

		/// Sets the y-component of the quaternion.
		/// float y : The new y-component.
		void setY(const float &y);

		/// Sets the z-component of the quaternion.
		/// float y : The new z-component.
		void setZ(const float &z);

		/// Sets the w-component of the quaternion.
		/// float w : The new w-component.
		void setW(const float &w);

		/// Converts this Quaternion to a 4x4 Rotation Matrix and returns it.
		/// return : The rotation matrix.
		Matrix4f toRotationMatrix4f();

		/// Overloads the multiplication operator to return the product of this
		/// and the specified quaternion.
		/// Quaternion q2 : The second quaternion.
		/// return : The product quaternion.
		Quaternion operator*(const Quaternion &q2) const;

		/// Overloads the multiplication operator to return the product of this
		/// and the specified vector.
		/// Vector3f v : The vector.
		/// return : The product quaternion.
		Quaternion operator*(const Vector3f &v) const;

		/// Overloads the multiplication set operator to return this instance,
		/// after it has been modified to store the product of this and the
		/// specified quaternion.
		/// Quaternion q2 : The second quaternion.
		/// return : The product quaternion.
		Quaternion operator*=(const Quaternion &q2);

		/// Overloads the multiplication set operator to return this instance,
		/// after it has been modified to store the product of this and the
		/// specified vector.
		/// Vector3f v : The vector.
		/// return : The product quaternion.
		Quaternion operator*=(const Vector3f &v);
	private:
		float x; // The x component
		float y; // The y component
		float z; // The z component
		float w; // The w component
	};
}

#endif