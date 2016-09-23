#pragma once
#ifndef MATRIX_4F
#define MATRIX_4f

namespace Honeycomb::Math {
	class Matrix4f {
	public:
		/// Returns an instancce of the Matrix class initialized to the matrix
		/// sum of this and the specified second matrix. Neither matrix is 
		/// modified in the process.
		/// Matrix4f m2 : The second matrix.
		/// return : The summation matrix.
		Matrix4f add(Matrix4f m2);

		/// Adds the specified second matrix to this current matrix.
		/// Matrix4f m2 : The second matrix.
		/// return : This matrix, post addition.
		Matrix4f addTo(Matrix4f m2);

		/// Returns an instance of the Matrix class which is initialized to a 
		/// 4x4 identity matrix.
		/// return : The 4x4 identity matrix.
		static Matrix4f identity();

		/// Gets the value in the 4x4 Matrix at the specified row and column.
		/// int r : The row position.
		/// int c : The column position.
		/// return : The value at the position.
		float getAt(int r, int c);

		/// Returns an instance of the Matrix equal to the product of this 
		/// matrix and the specified other matrix.
		/// Matrix4f m2 : The second matrix.
		/// return : The product of the two matricies.
		Matrix4f multiply(Matrix4f m2);

		/// Multiplies this and the specified matrix and stores the result in 
		/// this matrix instance.
		/// Matrix4f m2 : The second matrix.
		/// return : This product of the two matricies.
		Matrix4f multiplyTo(Matrix4f m2);

		/// Returns an instance of the Matrix class initialized to this matrix
		/// scaled by the scalar quantity specified. The contents of this 
		/// matrix are not changed.
		/// scale : The scale by which to scale the matrix.
		/// return : The scaled copy of this Matrix.
		Matrix4f scale(float scale);

		/// Scales this matrix by specified scalar factor.
		/// float scale : The constant by which to scale the matrix.
		/// return : This scaled matrix.
		Matrix4f scaleTo(float scale);

		/// Sets the value in the 4x4 Matrix at the specified row and column 
		/// position to the specified value.
		/// int r : The row position.
		/// int c : The column position.
		/// return : The value at the position.
		void setAt(int r, int c, float val);

		/// Overloads the mulitplication operator to return a matrix instance
		/// which is equivalent to this matrix, scaled by the specified amount.
		/// This matrix instance is not modified.
		/// const float &scale : The constant by which to scale the matrix.
		/// return : The scaled matrix.
		Matrix4f operator*(float scale);

		/// Overloads the mulitplication set operator to set this matrix 
		/// instance equal to this matrix scaled by the specified constant.
		/// const float &scale : The constant by which to scale the matrix.
		/// return : The scaled matrix.
		Matrix4f operator*=(float scale);

		/// Overloads the mulitplication operator to return a matrix instance
		/// which is equivalent to this matrix, multiplied by the specified 
		/// matrix. Neither this or the specified matrix's values are modified.
		/// Matrix4f m2 : The second matrix.
		/// return : The product of the matricies.
		Matrix4f operator*(Matrix4f m2);

		/// Overloads the multiplication set operator to set this matrix equal 
		/// to the product of this matrix and the specified matrix.
		/// Matrix4f m2 : The second matrix.
		/// return : This product of the matricies.
		Matrix4f operator*=(Matrix4f m2);

		/// Overloads the division operator to return a matrix instance which 
		/// is equivalent to this matrix, divided by the specified scalar.
		/// This matrix instance is not modified.
		/// Matrix4f m2 : The second matrix.
		/// return : The scaled matrix.
		Matrix4f operator/(float scale);

		/// Overloads the division set operator to set this matrix equal to the
		/// original matrix divided by the scaling factor.
		/// float scale : The scale.
		/// return : This scaled matrix.
		Matrix4f operator/=(float scale);

		/// Overloads the addition operator to return a matrix instance
		/// which is equivalent to the sum of this matrix and the specified
		/// matrix. Neither this or the specified matrix's values are modified.
		/// const Matrix4f &m2 : Reference to the second matrix.
		/// return : The sum matrix.
		Matrix4f operator+(Matrix4f m2);

		/// Overloads the addition set operator to set this matrix equal to the
		/// resultant of this and the specified matrix, and return it.
		/// Matrix4f v2 : Reference to the second matrix.
		/// return : This resultant matrix.
		Matrix4f operator+=(Matrix4f m2);

		/// Unary operator overload which returns a matrix instance which is
		/// equivalent to this matrix, negated. This matrix is not modified.
		/// return : The negated copy of this matrix.
		Matrix4f operator-();

		/// Overloads the subtraction operator to return a matrix instance
		/// which is equivalent to the difference of this matrix and the 
		/// specified matrix. Neither this nor the specified matrix's values 
		/// are modified.
		/// const Matrix4f &m2 : Reference to the second matrix.
		/// return : The difference matrix.
		Matrix4f operator-(Matrix4f m2);

		/// Overloads the subtraction set operator to set this matrix equal to 
		/// the difference of this and the specified matrix, and return it.
		/// Matrix4f v2 : Reference to the second matrix.
		/// return : This difference matrix.
		Matrix4f operator-=(Matrix4f m2);
	private:
		const static float IDENTITY[4][4]; // Stores the identity matrix

		float matrix[4][4]; // Stores the 4x4 array which represents the matrix

		/// Sets the entire matrix to the specified 2D 4x4 array.
		/// float f[4][4] : The 4x4 array to override this matrix.
		void setMatrix(float f[4][4]);

		/// Sets the entire matrix to the specified 2D 4x4 array.
		/// float f[4][4] : The 4x4 array to override this matrix.
		void setMatrix(const float f[4][4]);
	};
}

#endif