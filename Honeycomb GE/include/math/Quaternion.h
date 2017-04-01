#pragma once
#ifndef QUATERNION_H
#define QUATERNION_H

#include "../../include/math/Matrix4f.h"
#include "../../include/math/Vector3f.h"

namespace Honeycomb { namespace Math {
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
		/// const float &x : The x component.
		/// const float &y : The y component.
		/// const float &z : The z component.
		/// const float &w : The w component.
		Quaternion(const float &x, const float &y, const float &z, 
				const float &w);

		/// Empty Destructor.
		~Quaternion();

		/// Conjugates this Quaternion such that all imaginary components are
		/// multiplied by -1.
		/// return : This instance, post conjugation.
		Quaternion& conjugate();

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

		/// Returns the inverse Quaternion of this Quaternion.
		/// return : The inverse Quaternion.
		Quaternion getInverse() const;

		/// Gets a vector representing the right of this Quaternion.
		/// return : The right direction vector.
		Vector3f getRightVector() const;

		/// Gets a vector representing the up of this Quaternion.
		/// return : The up direction vector.
		Vector3f getUpVector() const;

		/// Gets the reference to the w-component of the quaternion.
		/// return : The reference to the w-component.
		float& getW();

		/// Gets the constant reference to the w-component of the quaternion.
		/// return : The constant reference to the w-component.
		const float& getW() const;

		/// Gets the reference to the x-component of the quaternion.
		/// return : The reference to the x-component.
		float& getX();

		/// Gets the constant reference to the x-component of the quaternion.
		/// return : The constant reference to the x-component.
		const float& getX() const;

		/// Gets the reference to the y-component of the quaternion.
		/// return : The reference to the y-component.
		float& getY();

		/// Gets the constant reference to the y-component of the quaternion.
		/// return : The constant reference to the y-component.
		const float& getY() const;

		/// Gets the reference to the z-component of the quaternion.
		/// return : The reference to the z-component.
		float& getZ();

		/// Gets the constant reference to the z-component of the quaternion.
		/// return : The constant reference to the z-component.
		const float& getZ() const;

		/// Gets the magnitude of the Quaternion.
		/// return : The magnitude.
		float magnitude() const;

		/// Gets the magnitude of the Quaternion squared.
		/// return : The squared magnitude.
		float magnitude2() const;

		/// Multiplies this and the specified quaternion and returns the 
		/// quaternion representing the product. Neither this nor the specified
		/// Quaternion is modified.
		/// const Quaternion &q2 : The second quaternion.
		/// return : The product quaternion.
		Quaternion multiply(const Quaternion &q2) const;

		/// Multiplies this and the specified vector and returns the quaternion
		/// representing the product. Neither this nor the specified Vector is
		/// modified.
		/// const Vector3f &v : The Vector by which to multiply this 
		///					    Quaternion.
		/// return : The product quaternion.
		Quaternion multiply(const Vector3f &v) const;

		/// Multiplies this and the specified quaternion and stores the product
		/// quaternion in this instance.
		/// const Quaternion &q2 : The second quaternion.
		/// return : This product quaternion.
		Quaternion& multiplyTo(const Quaternion &q2);

		/// Multiplies this and the specified vector and stores the quaternion
		/// representing the product in this instance.
		/// const Vector3f &v : The Vector by which to multiply this 
		///						Quaternion.
		/// return : This product quaternion.
		Quaternion& multiplyTo(const Vector3f &v);

		/// Normalizes this vector.
		/// return : This normalized Quaternion.
		Quaternion& normalize();

		/// Gets a normalized version of this Quaternion, without modifying it.
		/// return : The normalized copy of this Quaternion.
		Quaternion normalized() const;

		/// Sets the x, y, z and w components of the vector.
		/// const float &x : The new x-component.
		/// const float &y : The new y-component.
		/// const float &z : The new z-component.
		/// const float &w : The new w-component.
		void set(const float &x, const float &y, const float &z, 
				const float &w);

		/// Sets the x-component of the quaternion.
		/// const float &x : The new x-component.
		void setX(const float &x);

		/// Sets the y-component of the quaternion.
		/// const float &y : The new y-component.
		void setY(const float &y);

		/// Sets the z-component of the quaternion.
		/// const float &z : The new z-component.
		void setZ(const float &z);

		/// Sets the w-component of the quaternion.
		/// const float &w : The new w-component.
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
		Quaternion& operator*=(const Quaternion &q2);

		/// Overloads the multiplication set operator to return this instance,
		/// after it has been modified to store the product of this and the
		/// specified vector.
		/// Vector3f v : The vector.
		/// return : The product quaternion.
		Quaternion& operator*=(const Vector3f &v);
	private:
		float x; // The x component
		float y; // The y component
		float z; // The z component
		float w; // The w component
	};
} }

#endif
