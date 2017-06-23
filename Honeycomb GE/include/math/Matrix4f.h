#pragma once
#ifndef MATRIX_4F
#define MATRIX_4f

#include <array>

#include "Vector2f.h"
#include "Vector3f.h"
#include "Vector4f.h"

namespace Honeycomb { namespace Math {
	class Matrix4f {
	public:
		/// <summary>
		/// Gets the Identity Matrix. The Identity Matrix has all zeros except
		/// for the diagonal from upper left to lower right, which is filled
		/// with ones.
		/// </summary>
		/// <returns>
		/// The Identity Matrix.
		/// </returns>
		static const Matrix4f& getMatrixIdentity();

		/// <summary>
		/// Calculates the Look At Matrix using the specified parameters.
		/// </summary>
		/// <param name="eye">
		/// The position of the eye in the world.
		/// </param>
		/// <param name="center">
		/// The position at which the eye is to look at.
		/// </param>
		/// <param name="gblUp">
		/// The global up, defaults to <see cref="Vector3f::getGlobalUp"/>.
		/// </param>
		/// <returns>
		/// The Look At Matrix.
		/// </returns>
		static Matrix4f getMatrixLookAt(const Vector3f &eye, 
				const Vector3f &center,
				const Vector3f &gblUp = Vector3f::getGlobalUp());

		/// <summary>
		/// Calculates an orthographic projection matrix using the specified
		/// parameters. This method assumes that the left view parameter is
		/// equivalent to the right view parameter and that the top view
		/// parameter is equivalent to the bottom view parameter.
		/// </summary>
		/// <param name="right">
		/// The right view parameter, equivalent to the left.
		/// </param>
		/// <param name="top">
		/// The top view parameter, equivalent to the bottom.
		/// </param>
		/// <param name="zNear">
		/// The near clipping plane value.
		/// </param>
		/// <param name="zFar">
		/// The far clipping plane value.
		/// </param>
		/// <returns>
		/// The Orthographic Projection Matrix.
		/// </returns>
		static Matrix4f getMatrixOrthographic(
				const float &right, const float &top,
				const float &zNear, const float &zFar);

		/// <summary>
		/// Calculates an orthographic projection matrix using the specified
		/// parameters.
		/// </summary>
		/// <param name="left">
		/// The left view parameter.
		/// </param>
		/// <param name="right">
		/// The right view parameter.
		/// </param>
		/// <param name="bottom">
		/// The bottom view parameter.
		/// </param>
		/// <param name="top">
		/// The top view parameter.
		/// </param>
		/// <param name="zNear">
		/// The near clipping plane value.
		/// </param>
		/// <param name="zFar">
		/// The far clipping plane value.
		/// </param>
		/// <returns>
		/// The Orthographic Projection Matrix.
		/// </returns>
		static Matrix4f getMatrixOrthographic(
				const float &left, const float &right,
				const float &bottom, const float &top, 
				const float &zNear, const float &zFar);

		/// <summary>
		/// Calculates a perspective projection matrix using the specified
		/// parameters.
		/// </summary>
		/// <param name="fov">
		/// The field of view, in radians.
		/// </param>
		/// <param name="aspect">
		/// The aspect ratio of the width to the height of the projection.
		/// </param>
		/// <param name="zNear">
		/// The near clipping plane value.
		/// </param>
		/// <param name="zFar">
		/// The far clipping plane value.
		/// </param>
		/// <returns>
		/// The Perspective Projection Matrix.
		/// </returns>
		static Matrix4f getMatrixPerspective(
				const float &fov, const float &aspect,
				const float &zNear, const float &zFar);

		/// <summary>
		/// Gets the Zeros Matrix. The Zeros Matrix has all zeros.
		/// </summary>
		/// <returns>
		/// The Zeros Matrix.
		/// </returns>
		static const Matrix4f& getMatrixZeros();

		/// <summary>
		/// Creates an empty 4x4 Matrix. All values of the Matrix will be
		/// initialized to zeros.
		/// </summary>
		Matrix4f();

		/// <summary>
		/// Creates a 4x4 Matrix with the specified values.
		/// </summary>
		/// <param name="m">
		/// The matrix 2D array to be placed into this Matrix.
		/// </param>
		Matrix4f(const float m[4][4]);

		/// <summary>
		/// Returns a Matrix which is initialized to the element by element sum
		/// of this Matrix and the specified constant.
		/// </summary>
		/// <param name="constant">
		/// The constant value.
		/// </param>
		/// <returns>
		/// The sum Matrix.
		/// </returns>
		Matrix4f add(const float &constant) const;

		/// <summary>
		/// Returns a Matrix which is initialized to the element by element sum
		/// of this Matrix and the specified matrix.
		/// </summary>
		/// <param name="m2">
		/// The other matrix.
		/// </param>
		/// <returns>
		/// The sum matrix.
		/// </returns>
		Matrix4f add(const Matrix4f &m2) const;

		/// <summary>
		/// Adds the specified constant element by element to this Matrix.
		/// </summary>
		/// <param name="constant">
		/// The constant to be added to each element of this Matrix.
		/// </param>
		/// <returns>
		/// This Matrix.
		/// </returns>
		Matrix4f& addTo(const float &constant);

		/// <summary>
		/// Adds the specified Matrix element by element to this Matrix.
		/// </summary>
		/// <param name="m2">
		/// The matrix to be added to this matrix.
		/// </param>
		/// <returns>
		/// This Matrix.
		/// </returns>
		Matrix4f& addTo(const Matrix4f &m2);

		/// <summary>
		/// Returns this Matrix as a 1D array in row-major order.
		/// </summary>
		/// <returns>
		/// The 1D array of the Matrix.
		/// </returns>
		std::array<float, 16> get() const;

		/// <summary>
		/// Gets the element of the Matrix at the specified row and column. An
		/// assertion checks that row and column are both in range [0, 3].
		/// </summary>
		/// <param name="r">
		/// The row of the Matrix.
		/// </param>
		/// <param name="c">
		/// The column of the Matrix.
		/// </param>
		/// <returns>
		/// The value at said row and column.
		/// </returns>
		const float& getAt(const int &r, const int &c) const;

		/// <summary>
		/// Returns the specified column of the Matrix as a four dimensional
		/// vector. An assertion checks that column argument is in range
		/// [0, 3].
		/// </summary>
		/// <param name="c">
		/// The column of the Matrix.
		/// </param>
		/// <returns>
		/// The column of the Matrix.
		/// </returns>
		Vector4f getColAt(const int &c) const;

		/// <summary>
		/// Returns the determinant value of this Matrix.
		/// </summary>
		/// <returns>
		/// The determinant value.
		/// </returns>
		const float& getDeterminant() const;

		/// <summary>
		/// Returns the inverse Matrix of this Matrix.
		/// </summary>
		/// <returns>
		/// The inverse matrix.
		/// </returns>
		Matrix4f getInverse() const;

		/// <summary>
		/// Returns the specified row of the Matrix as a four dimensional
		/// vector. An assertion checks that row argument is in range [0, 3].
		/// </summary>
		/// <param name="r">
		/// The row of the Matrix.
		/// </param>
		/// <returns>
		/// The row of the Matrix.
		/// </returns>
		Vector4f getRowAt(const int &r) const;

		/// <summary>
		/// Returns a Matrix which is initialized to the Matrix product of this
		/// and the specified Matrix.
		/// </summary>
		/// <param name="m2">
		/// The Matrix with which this Matrix is to be multiplied.
		/// </param>
		/// <returns>
		/// The multiplication matrix resultant.
		/// </returns>
		Matrix4f multiply(const Matrix4f& m2) const;

		/// <summary>
		/// Returns a Vector which is initialized to the Matrix product of this
		/// and the specified two dimensional vector. For this method, the
		/// vector is extended to a four dimensional vector with a 1.0F value
		/// for the Z and W components.
		/// </summary>
		/// <param name="v">
		/// The two dimensional vector.
		/// </param>
		/// <returns>
		/// The multiplation vector resultant.
		/// </returns>
		Vector2f multiply(const Vector2f &v) const;

		/// <summary>
		/// Returns a Vector which is initialized to the Matrix product of this
		/// and the specified three dimensional vector. For this method, the
		/// vector is extended to a four dimensional vector with a 1.0F value
		/// for the W component.
		/// </summary>
		/// <param name="v">
		/// The three dimensional vector.
		/// </param>
		/// <returns>
		/// The multiplication vector resultant.
		/// </returns>
		Vector3f multiply(const Vector3f &v) const;

		/// <summary>
		/// Returns a Vector which is initialized to the Matrix product of this
		/// and the specified four dimensional vector.
		/// </summary>
		/// <param name="v">
		/// The four dimensional vector.
		/// </param>
		/// <returns>
		/// The multiplication vector resultant.
		/// </returns>
		Vector4f multiply(const Vector4f &v) const;

		/// <summary>
		/// Multiplies the specified Matrix with this Matrix and stores the
		/// result in this Matrix.
		/// </summary>
		/// <param name="m2">
		/// The matrix to be multiplied with this.
		/// </param>
		/// <returns>
		/// This Matrix.
		/// </returns>
		Matrix4f& multiplyTo(const Matrix4f& m2);

		/// <summary>
		/// Returns a Matrix initialized to this Matrix scaled by the specified
		/// scalar value.
		/// </summary>
		/// <param name="scale">
		/// The scalar value.
		/// </param>
		/// <returns>
		/// This Matrix.
		/// </returns>
		Matrix4f scale(const float &scale) const;

		/// <summary>
		/// Scales this Matrix by the specified scalar value.
		/// </summary>
		/// <param name="scale">
		/// The scalar value.
		/// </param>
		/// <returns>
		/// This Matrix.
		/// </returns>
		Matrix4f& scaleTo(const float &scale);

		/// <summary>
		/// Sets the value at the specified Matrix coordinate. An assert checks
		/// that the row and column values are both in range [0, 3].
		/// </summary>
		/// <param name="r">
		/// The row value.
		/// </param>
		/// <param name="c">
		/// The column value.
		/// </param>
		/// <param name="val">
		/// The value to be written at [r, c].
		/// </param>
		void setAt(const int &r, const int &c, const float &val);

		/// <summary>
		/// Sets this Matrix to the specified 4x4 Matrix array.
		/// </summary>
		/// <param name="f">
		/// The new matrix array of this Matrix.
		/// </param>
		void setMatrix(float f[4][4]);

		/// <summary>
		/// Sets this Matrix to the specified 4x4 Matrix array.
		/// </summary>
		/// <param name="f">
		/// The new matrix array of this Matrix.
		/// </param>
		void setMatrix(const float f[4][4]);

		/// <summary>
		/// Sets the specified column of the Matrix. An assertion checks that
		/// the column index is in range [0, 3].
		/// </summary>
		/// <param name="c">
		/// The column index.
		/// </param>
		/// <param name="col">
		/// The new column to be written to the Matrix.
		/// </param>
		void setColAt(const int &c, const Vector4f &col);

		/// <summary>
		/// Sets the specified row of the Matrix. An assertion checks that
		/// the row index is in range [0, 3].
		/// </summary>
		/// <param name="r">
		/// The row index.
		/// </param>
		/// <param name="row">
		/// The new row to be written to the Matrix.
		/// </param>
		void setRowAt(const int &r, const Vector4f &row);

		/// <summary>
		/// Overloads the multiplication operator to return the Matrix 
		/// product of this matrix and the specified scalar value.
		/// </summary>
		/// <param name="scale">
		/// The scalar value.
		/// </param>
		/// <returns>
		/// The scaled Matrix.
		/// </returns>
		Matrix4f operator*(const float &scale) const;

		/// <summary>
		/// Overloads the multiplication operator to return the Matrix
		/// product of this matrix and the specified matrix.
		/// </summary>
		/// <param name="m2">
		/// The matrix to be multiplied with this.
		/// </param>
		/// <returns>
		/// The multiplication matrix resultant.
		/// </returns>
		Matrix4f operator*(const Matrix4f& m2) const;

		/// <summary>
		/// Overloads the multiplication operator to return the Vector
		/// product of this matrix and the specified two dimensional vector.
		/// For this operation, the two dimensional vector is extended to a
		/// four dimensional vector with 1.0F value for the Z and W components.
		/// </summary>
		/// <param name="v">
		/// The vector to be multiplied with this matrix.
		/// </param>
		/// <returns>
		/// The multiplication vector resultant.
		/// </returns>
		Vector2f operator*(const Vector2f &v) const;

		/// <summary>
		/// Overloads the multiplication operator to return the Vector
		/// product of this matrix and the specified three dimensional vector.
		/// For this operation, the three dimensional vector is extended to a
		/// four dimensional vector with 1.0F value for the W component.
		/// </summary>
		/// <param name="v">
		/// The vector to be multiplied with this matrix.
		/// </param>
		/// <returns>
		/// The multiplication vector resultant.
		/// </returns>
		Vector3f operator*(const Vector3f &v) const;

		/// <summary>
		/// Overloads the multiplication operator to return the Vector
		/// product of this matrix and the specified four dimensional vector.
		/// </summary>
		/// <param name="v">
		/// The vector to be multiplied with this matrix.
		/// </param>
		/// <returns>
		/// The multiplication vector resultant.
		/// </returns>
		Vector4f operator*(const Vector4f &v) const;

		/// <summary>
		/// Overloads the multiplication operator to multiply this Matrix by
		/// the specified scalar value and return this Matrix.
		/// </summary>
		/// <param name="scale">
		/// The scalar value.
		/// </param>
		/// <returns>
		/// This scaled Matrix.
		/// </returns>
		Matrix4f& operator*=(const float &scale);

		/// <summary>
		/// Overloads the multiplication operator to multiply this Matrix with
		/// the specified matrix and store the result in this matrix.
		/// </summary>
		/// <param name="m2">
		/// The matrix to be multiplied with this.
		/// </param>
		/// <returns>
		/// This matrix.
		/// </returns>
		Matrix4f& operator*=(const Matrix4f& m2);

		/// <summary>
		/// Overloads the division operator to divide this Matrix by the
		/// specified scalar value.
		/// </summary>
		/// <param name="scale">
		/// The scalar value.
		/// </param>
		/// <returns>
		/// The matrix containing the scaled values.
		/// </returns>
		Matrix4f operator/(const float &scale) const;

		/// <summary>
		/// Overloads the division operator to divide this Matrix by the
		/// specified scalar value and store the resultant matrix in this
		/// instance.
		/// </summary>
		/// <param name="scale">
		/// The scalar value.
		/// </param>
		/// <returns>
		/// This matrix.
		/// </returns>
		Matrix4f& operator/=(const float &scale);

		/// <summary>
		/// Overloads the addition operator to add the specified constant to
		/// each value of the Matrix and returns the result.
		/// </summary>
		/// <param name="constant">
		/// The constant to be added to each value of the matrix.
		/// </param>
		/// <returns>
		/// The resultant Matrix.
		/// </returns>
		Matrix4f operator+(const float &constant) const;

		/// <summary>
		/// Overloads the addition operator to add the specified Matrix's
		/// values to this Matrix's values and return the result.
		/// </summary>
		/// <param name="m2">
		/// The Matrix whose values are to be added.
		/// </param>
		/// <returns>
		/// The resultant Matrix.
		/// </returns>
		Matrix4f operator+(const Matrix4f& m2) const;

		/// <summary>
		/// Overloads the addition operator to add the specified constant to
		/// each value of the Matrix and store the result in this Matrix.
		/// </summary>
		/// <param name="constant">
		/// The constant to be added to each value of the matrix.
		/// </param>
		/// <returns>
		/// This matrix.
		/// </returns>
		Matrix4f& operator+=(const float &constant);

		/// <summary>
		/// Overloads the addition operator to add the specified Matrix's
		/// values to the values of this Matrix and store the resultant in this
		/// Matrix.
		/// </summary>
		/// <param name="m2">
		/// The matrix to be added to this.
		/// </param>
		/// <returns>
		/// This matrix.
		/// </returns>
		Matrix4f& operator+=(const Matrix4f& m2);

		/// <summary>
		/// Overloads the unary negation operator to negate each element of
		/// this Matrix and return the result.
		/// </summary>
		/// <returns>
		/// The negated matrix.
		/// </returns>
		Matrix4f operator-() const;

		/// <summary>
		/// Overloads the subtraction operator to subtract the specified 
		/// constant from each value of this Matrix and return the result.
		/// </summary>
		/// <param name="constant">
		/// The constant value.
		/// </param>
		/// <returns>
		/// The resultant matrix.
		/// </returns>
		Matrix4f operator-(const float &constant) const;

		/// <summary>
		/// Overloads the subtraction operator to subtract the values of the
		/// specified matrix from the values of this Matrix and return the
		/// result.
		/// </summary>
		/// <param name="m2">
		/// The matrix whose values are to be subtracted from this.
		/// </param>
		/// <returns>
		/// The resultant matrix.
		/// </returns>
		Matrix4f operator-(const Matrix4f& m2) const;

		/// <summary>
		/// Overloads the subtraction operator to subtract the specified 
		/// constant from each value of this Matrix and store the result in
		/// this.
		/// </summary>
		/// <param name="constant">
		/// The constant value.
		/// </param>
		/// <returns>
		/// This matrix.
		/// </returns>
		Matrix4f& operator-=(const float &constant);

		/// <summary>
		/// Overloads the subtraction operator to subtract the values of the
		/// specified matrix from the values of this Matrix and store the 
		/// result in this matrix.
		/// </summary>
		/// <param name="m2">
		/// The matrix whose values are to be subtracted from this.
		/// </param>
		/// <returns>
		/// This matrix.
		/// </returns>
		Matrix4f& operator-=(const Matrix4f& m2);
	private:
		float matrix[4][4];             // 4x4 representation of the Matrix
		
		mutable float inverse[4][4];    // The 4x4 array containing the inverse
		mutable float determinant;      // The determinant of this Matrix
		mutable bool isDirty;           // Was I modified since last recalc?

		/// <summary>
		/// Calculates the inverse matrix and determinant values of this 
		/// Matrix and updates them in this Matrix. This also resets the
		/// <see cref="isDirty"/> flag of the Matrix to false.
		/// </summary>
		void recalculateInternals() const;
	};
} }

#endif
