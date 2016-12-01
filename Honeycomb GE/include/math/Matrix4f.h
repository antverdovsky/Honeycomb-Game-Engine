#pragma once
#ifndef MATRIX_4F
#define MATRIX_4f

namespace Honeycomb::Math {
	class Matrix4f {
	public:
		/// Creates an empty 4x4 Matrix. The values of the matrix will be set
		/// to whatever is the default float value of the computer on which
		/// the engine is running.
		Matrix4f();

		/// Creaates a 4x4 Matrix initialized to the specified 2D 4x4 array.
		/// float m[4][4] : The 2D 4x4 Matrix array.
		Matrix4f(float m[4][4]);

		/// Default Destructor.
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

		/// Returns an instance of the Matrix class which is initialized to a 
		/// 4x4 identity matrix.
		/// return : The 4x4 identity matrix.
		static const Matrix4f& identity();

		/// Gets a 1D array of all of the values stored by this Matrix class.
		/// The values are ordered by row major order (All column values of 
		/// row 1 precede all column values of row 2, etc).
		/// return : The array pointer.
		float* get() const;

		/// Gets the value in the 4x4 Matrix at the specified row and column.
		/// const int &r : The row position.
		/// const int &c : The column position.
		/// return : The value at the position.
		const float& getAt(const int &r, const int &c) const;

		/// Returns an instance of the Matrix equal to the product of this 
		/// matrix and the specified other matrix.
		/// const Matrix4f &m2 : The second matrix.
		/// return : The product of the two matricies.
		Matrix4f multiply(const Matrix4f& m2) const;

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
		float matrix[4][4]; // Stores the 4x4 array which represents the matrix

		static float M_IDENTITY[4][4];
		static Matrix4f IDENTITY;
	};
}

#endif