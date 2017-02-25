#pragma once
#ifndef MATRIX_4F
#define MATRIX_4f

#include <array>

#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

namespace Honeycomb::Math {
	class Matrix4f {
	public:
		/// Returns an instance of the Matrix class which is initialized to a 
		/// 4x4 identity matrix.
		/// return : The 4x4 identity matrix.
		static const Matrix4f& identity();

		/// Returns an instance of the Matrix class which is initialized to a
		/// 4x4 zero matrix.
		/// return : The 4x4 zero matrix.
		static const Matrix4f& zero();

		/// Creates an empty 4x4 Matrix. All the values of the Matrix will be
		/// set to zero.
		Matrix4f();

		/// Creaates a 4x4 Matrix initialized to the specified 2D 4x4 array.
		/// float m[4][4] : The 2D 4x4 Matrix array.
		Matrix4f(const float m[4][4]);

		/// Copies the the specified Matrix into a new Matrix. The Inverse
		/// Matrix will also be copied into the new Matrix.
		/// const Matrix4f &matrix : The matrix to be copied into this.
		Matrix4f(const Matrix4f &matrix);

		/// Destroys this Matrix and its inverse Matrix.
		~Matrix4f();

		/// Returns an instance of the Matrix class initialized to the matrix
		/// sum of this and the specified second matrix. Neither matrix is 
		/// modified in the process.
		/// const Matrix4f &m2 : The second matrix.
		/// return : The summation matrix.
		Matrix4f add(const Matrix4f &m2) const;

		/// Adds the specified second matrix to this current matrix.
		/// const Matrix4f &m2 : The second matrix.
		/// return : The reference to this matrix, post addition.
		Matrix4f& addTo(const Matrix4f &m2);

		/// Returns an array of all of the elements of this Matrix. The array
		/// returned will be in row-major order.
		/// return : The array containing all of the elements of this Matrix.
		std::array<float, 16> get() const;

		/// Gets the value in the 4x4 Matrix at the specified row and column.
		/// const int &r : The row position.
		/// const int &c : The column position.
		/// return : The value at the position.
		const float& getAt(const int &r, const int &c) const;

		/// Returns the specified column of the Matrix as a Vector.
		/// const int &c : The column which is to be returned (0 is the first 
		///				   column and 3 is the last). If this argument is out 
		///				   of range a default constructed Vector is returned 
		///				   instead.
		/// return : The row of the Matrix.
		Vector4f getColAt(const int &c) const;

		/// Returns the Determinant of this Matrix.
		/// return : The Determinant.
		const float& getDeterminant() const;

		/// Returns the Inverse Matrix of this Matrix. Note that if this Matrix
		/// does not have an Inverse (i.e. if the Determinant is zero) the
		/// returned matrix will have all zero values.
		/// return : The Inverse Matrix.
		const Matrix4f& getInverse() const;

		/// Returns the specified row of the Matrix as a Vector.
		/// const int &r : The row which is to be returned (0 is the first row
		///				   and 3 is the last). If this argument is out of range
		///				   a default constructed Vector is returned instead.
		/// return : The row of the Matrix.
		Vector4f getRowAt(const int &r) const;

		/// Returns an instance of the Matrix equal to the product of this 
		/// matrix and the specified other matrix.
		/// const Matrix4f &m2 : The second matrix.
		/// return : The product of the two matricies.
		Matrix4f multiply(const Matrix4f& m2) const;

		/// Returns an instance of a Vector2f equal to the product of this
		/// Matrix and the specified Vector. The Vector specified will be
		/// converted to a Vector4f with 1.0F as the values of Z and W.
		/// const Vector2f &v : The vector to be multiplied by this instance.
		/// return : The product of this matrix and that vector.
		Vector2f multiply(const Vector2f &v) const;

		/// Returns an instance of a Vector3f equal to the product of this
		/// Matrix and the specified Vector. The Vector specified will be
		/// converted to a Vector4f with 1.0F as the value of Z.
		/// const Vector3f &v : The vector to be multiplied by this instance.
		/// return : The product of this matrix and that vector.
		Vector3f multiply(const Vector3f &v) const;

		/// Returns an instance of a Vector4f equal to the product of this
		/// Matrix and the specified Vector.
		/// const Vector4f &v : The vector to be multiplied by this instance.
		/// return : The product of this matrix and that vector.
		Vector4f multiply(const Vector4f &v) const;

		/// Multiplies this and the specified matrix and stores the result in 
		/// this matrix instance.
		/// const Matrix4f &m2 : The second matrix.
		/// return : The reference to this matrix, post multiplication.
		Matrix4f& multiplyTo(const Matrix4f& m2);

		/// Returns an instance of the Matrix class initialized to this matrix
		/// scaled by the scalar quantity specified. The contents of this 
		/// matrix are not changed.
		/// const float &scale : The scale by which to scale the matrix.
		/// return : The scaled copy of this Matrix.
		Matrix4f scale(const float &scale) const;

		/// Scales this matrix by specified scalar factor.
		/// const float &scale : The constant by which to scale the matrix.
		/// return : The reference to this matrix, post scaling.
		Matrix4f& scaleTo(const float &scale);

		/// Sets the value in the 4x4 Matrix at the specified row and column 
		/// position to the specified value.
		/// int r : The row position.
		/// int c : The column position.
		/// return : The value at the position.
		void setAt(const int &r, const int &c, const float &val);

		/// Sets the entire matrix to the specified 2D 4x4 array.
		/// float f[4][4] : The 4x4 array to override this matrix.
		void setMatrix(float f[4][4]);

		/// Sets the entire matrix to the specified 2D 4x4 array.
		/// float f[4][4] : The 4x4 array to override this matrix.
		void setMatrix(const float f[4][4]);

		/// Writes the specified Matrix into this Matrix. The Inverse Matrix
		/// will also be copied into this Matrix.
		/// const Matrix4f &matrix : The matrix to be written to this Matrix.
		Matrix4f& operator=(const Matrix4f &matrix);

		/// Overloads the mulitplication operator to return a matrix instance
		/// which is equivalent to this matrix, scaled by the specified amount.
		/// This matrix instance is not modified.
		/// const float &scale : The constant by which to scale the matrix.
		/// return : The scaled matrix.
		Matrix4f operator*(const float &scale) const;

		/// Overloads the mulitplication set operator to set this matrix 
		/// instance equal to this matrix scaled by the specified constant.
		/// const float &scale : The constant by which to scale the matrix.
		/// return : The scaled matrix.
		Matrix4f& operator*=(const float &scale);

		/// Overloads the mulitplication operator to return a matrix instance
		/// which is equivalent to this matrix, multiplied by the specified 
		/// matrix. Neither this or the specified matrix's values are modified.
		/// const Matrix4f &m2 : The second matrix.
		/// return : The product of the matricies.
		Matrix4f operator*(const Matrix4f& m2) const;

		/// Overloads the multiplication operator to return a Vector instance
		/// which is equivalent to this matrix, multiplied by the specified
		/// Vector. Do note that the Matrix will be treated as a 2x2 for this
		/// calculation.
		/// const Vector2f &v : The vector to multiply this Matrix by.
		/// return : The product of the matrix and the Vector.
		Vector2f operator*(const Vector2f &v) const;

		/// Overloads the multiplication operator to return a Vector instance
		/// which is equivalent to this matrix, multiplied by the specified
		/// Vector. Do note that the Matrix will be treated as a 3x3 for this
		/// calculation.
		/// const Vector3f &v : The vector to multiply this Matrix by.
		/// return : The product of the matrix and the Vector.
		Vector3f operator*(const Vector3f &v) const;

		/// Overloads the multiplication operator to return a Vector instance
		/// which is equivalent to this matrix, multiplied by the specified
		/// Vector.
		/// const Vector4f &v : The vector to multiply this Matrix by.
		/// return : The product of the matrix and the Vector.
		Vector4f operator*(const Vector4f &v) const;

		/// Overloads the multiplication set operator to set this matrix equal 
		/// to the product of this matrix and the specified matrix.
		/// const Matrix4f &m2 : The second matrix.
		/// return : This product of the matricies.
		Matrix4f& operator*=(const Matrix4f& m2);

		/// Overloads the division operator to return a matrix instance which 
		/// is equivalent to this matrix, divided by the specified scalar.
		/// This matrix instance is not modified.
		/// const float &scale : The scale by which to scale the matrix.
		/// return : The scaled matrix.
		Matrix4f operator/(const float &scale) const;

		/// Overloads the division set operator to set this matrix equal to the
		/// original matrix divided by the scaling factor.
		/// const float &scale : The scale by which to scale the matrix.
		/// return : This scaled matrix.
		Matrix4f& operator/=(const float &scale);

		/// Overloads the addition operator to return a matrix instance
		/// which is equivalent to the sum of this matrix and the specified
		/// matrix. Neither this or the specified matrix's values are modified.
		/// const Matrix4f &m2 : The second matrix.
		/// return : The sum matrix.
		Matrix4f operator+(const Matrix4f& m2) const;

		/// Overloads the addition set operator to set this matrix equal to the
		/// resultant of this and the specified matrix, and return it.
		/// const Matrix4f &m2 : The second matrix.
		/// return : This resultant matrix.
		Matrix4f& operator+=(const Matrix4f& m2);

		/// Unary operator overload which returns a matrix instance which is
		/// equivalent to this matrix, negated. This matrix is not modified.
		/// return : The negated copy of this matrix.
		Matrix4f operator-() const;

		/// Overloads the subtraction operator to return a matrix instance
		/// which is equivalent to the difference of this matrix and the 
		/// specified matrix. Neither this nor the specified matrix's values 
		/// are modified.
		/// const Matrix4f &m2 : The second matrix.
		/// return : The difference matrix.
		Matrix4f operator-(const Matrix4f& m2) const;

		/// Overloads the subtraction set operator to set this matrix equal to 
		/// the difference of this and the specified matrix, and return it.
		/// const Matrix4f &m2 : The second matrix.
		/// return : This difference matrix.
		Matrix4f& operator-=(const Matrix4f& m2);
	private:
		static float M_IDENTITY[4][4];
		static float M_ZERO[4][4];

		static Matrix4f IDENTITY;
		static Matrix4f ZERO;

		/// Constructor which does not initialize an inverse matrix. Inverse
		/// matrices should be created with this constructor, otherwise there
		/// will be infinitely many matrices. This matrix will have all values
		/// of zero by default.
		/// Matrix4f *orig : The matrix of which this is an inverse of (the
		///					 original matrix).
		Matrix4f(Matrix4f *orig);

		float matrix[4][4]; // Stores the 4x4 array which represents the matrix
		
		Matrix4f *inverse; // The inverse of this Matrix
		float determinant; // The determinant of this Matrix

		bool isInverse;    // Is this an inverse Matrix?

		/// Updates the inverse and determinant of this Matrix. Due to the
		/// expensiveness of these calculations, this should only be called
		/// when the Matrix is updated.
		void update();
	};
}

#endif