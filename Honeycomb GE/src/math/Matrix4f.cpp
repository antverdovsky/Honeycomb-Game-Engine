#include "..\..\include\math\Matrix4f.h"

namespace Honeycomb::Math {
	float Matrix4f::M_IDENTITY[4][4] = {
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};

	float Matrix4f::M_ZERO[4][4] = {
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	};

	Matrix4f Matrix4f::IDENTITY = Matrix4f(Matrix4f::M_IDENTITY);
	Matrix4f Matrix4f::ZERO = Matrix4f(Matrix4f::M_ZERO);

	const Matrix4f& Matrix4f::identity() {
		return Matrix4f::IDENTITY;
	}

	const Matrix4f& Matrix4f::zero() {
		return Matrix4f::ZERO;
	}

	Matrix4f::Matrix4f() : Matrix4f(M_ZERO) {

	}

	Matrix4f::Matrix4f(const Matrix4f &matrix) : Matrix4f(matrix.matrix) {

	}

	Matrix4f::Matrix4f(const float m[4][4]) {
		this->isInverse = false;

		this->inverse = new Matrix4f(this);
		this->setMatrix(m);
	}

	Matrix4f::~Matrix4f() {
		// Only delete the inverse if this is not an inverse (otherwise, the
		// inverse will delete the actual Matrix!)
		if (!this->isInverse) 
			delete this->inverse;
	}

	Matrix4f Matrix4f::add(const Matrix4f& m2) const {
		Matrix4f sum;

		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				sum.matrix[r][c] = this->matrix[r][c] + m2.matrix[r][c];
			}
		}

		return sum;
	}

	Matrix4f& Matrix4f::addTo(const Matrix4f& m2) {
		Matrix4f sum = this->add(m2);

		this->setMatrix(sum.matrix);
		return *this;
	}

	std::array<float, 16> Matrix4f::get() const {
		std::array<float, 16> array;

		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				// Convert the 2D index to 1D and write from the matrix to it
				array[r * 4 + c] = this->getAt(r, c);
			}
		}

		return array;
	}

	const float& Matrix4f::getAt(const int &r, const int &c) const {
		return this->matrix[r][c];
	}

	Vector4f Matrix4f::getColAt(const int &c) const {
		float colArray[4]; // Stores the column in an Array

		// Get each row of the column, and put it into the column array
		for (int i = 0; i < 3; ++i) colArray[i] = this->matrix[i][c];

		// Construct a Vector out of all the column's elements and return
		return Vector4f(colArray[0], colArray[1], colArray[2], colArray[3]);
	}

	const float& Matrix4f::getDeterminant() const {
		return this->determinant;
	}

	const Matrix4f& Matrix4f::getInverse() const {
		return *(this->inverse);
	}

	Vector4f Matrix4f::getRowAt(const int &r) const {
		float rowArray[4]; // Stores the row in an Array

		// Get each column of the row, and put it into the row array
		for (int i = 0; i < 3; ++i) rowArray[i] = this->matrix[r][i];

		// Construct a Vector out of all the row's elements and return
		return Vector4f(rowArray[0], rowArray[1], rowArray[2], rowArray[3]);
	}

	Matrix4f Matrix4f::multiply(const Matrix4f& m2) const {
		Matrix4f product;

		for (int r = 0; r < 4; r++) { // Go through all points on the matrix
			for (int c = 0; c < 4; c++) {
				// The new value in the matrix will be equal to the dot product
				// of the row and column vectors.
				float dot = 0;
				for (int j = 0; j < 4; j++)
					dot += this->matrix[r][j] * m2.matrix[j][c];

				product.matrix[r][c] = dot;
			}
		}

		return product;
	}

	Vector2f Matrix4f::multiply(const Vector2f &v) const {
		// Convert the specified Vector2 to a Vector4 with zero Z, W components
		// and compute the product of this matrix with the Vector4.
		Vector4f v4 = Vector4f(v.getX(), v.getY(), 0.0F, 0.0F);
		Vector4f prod = this->multiply(v4);

		// Truncate the Z, W component, return the remaining Vector2
		return Vector2f(prod.getX(), prod.getY());
	}

	Vector3f Matrix4f::multiply(const Vector3f &v) const {
		// Convert the specified Vector3 to a Vector4 with a zero W component
		// and compute the product of this matrix with the Vector4.
		Vector4f v4 = Vector4f(v.getX(), v.getY(), v.getZ(), 0.0F);
		Vector4f prod = this->multiply(v4);

		// Truncate the W component, return the remaining Vector3
		return Vector3f(prod.getX(), prod.getY(), prod.getZ());
	}

	Vector4f Matrix4f::multiply(const Vector4f &v) const {
		float result[4]; // The resulting Vector4f

		for (int i = 0; i < 3; ++i) { // Go through first 3 rows of matrix
			// Get the current row
			Vector4f row = this->getRowAt(i);

			result[i] = row.dot(v); // Get dot product or row and v
		}

		// Convert the result array into a Vector3f
		return Vector4f(result[0], result[1], result[2], result[3]);
	}

	Matrix4f& Matrix4f::multiplyTo(const Matrix4f& m2) {
		Matrix4f product = this->multiply(m2);

		this->setMatrix(product.matrix);
		return *this;
	}

	Matrix4f Matrix4f::scale(const float &scale) const {
		Matrix4f scaled;

		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				scaled.matrix[r][c] = this->matrix[r][c] * scale;
			}
		}

		return scaled;
	}

	Matrix4f& Matrix4f::scaleTo(const float &scale) {
		Matrix4f scaled = this->scale(scale);

		this->setMatrix(scaled.matrix);
		return *this;
	}

	void Matrix4f::setAt(const int &r, const int &c, const float &val) {
		this->matrix[r][c] = val;
		
		this->update();
	}

	void Matrix4f::setMatrix(float f[4][4]) {
		// Copy the specified matrix array values into this matrix array, 
		// column by column.
		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				this->matrix[r][c] = f[r][c];
			}
		}

		this->update();
	}

	void Matrix4f::setMatrix(const float f[4][4]) {
		// Copy the specified matrix array values into this matrix array, 
		// column by column.
		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				this->matrix[r][c] = f[r][c];
			}
		}

		this->update();
	}

	Matrix4f& Matrix4f::operator=(const Matrix4f &matrix) {
		this->isInverse = matrix.isInverse;

		this->inverse = !this->isInverse ? new Matrix4f(this) : matrix.inverse;
		this->setMatrix(matrix.matrix);

		return *this;
	}

	Matrix4f Matrix4f::operator*(const float &scale) const {
		return this->scale(scale);
	}

	Matrix4f& Matrix4f::operator*=(const float &scale) {
		return this->scaleTo(scale);
	}

	Matrix4f Matrix4f::operator*(const Matrix4f& m2) const {
		return this->multiply(m2);
	}

	Vector2f Matrix4f::operator*(const Vector2f &v) const {
		return this->multiply(v);
	}

	Vector3f Matrix4f::operator*(const Vector3f &v) const {
		return this->multiply(v);
	}

	Vector4f Matrix4f::operator*(const Vector4f &v) const {
		return this->multiply(v);
	}

	Matrix4f& Matrix4f::operator*=(const Matrix4f& m2) {
		return this->multiplyTo(m2);
	}

	Matrix4f Matrix4f::operator/(const float &scale) const {
		return this->scale(1.0F / scale);
	}

	Matrix4f& Matrix4f::operator/=(const float &scale) {
		return this->scaleTo(1.0F / scale);
	}

	Matrix4f Matrix4f::operator+(const Matrix4f& m2) const {
		return this->add(m2);
	}

	Matrix4f& Matrix4f::operator+=(const Matrix4f& m2) {
		return this->addTo(m2);
	}

	Matrix4f Matrix4f::operator-() const {
		Matrix4f neg = Matrix4f(*this);
		neg.scaleTo(-1.0F);

		return neg;
	}

	Matrix4f Matrix4f::operator-(const Matrix4f& m2) const {
		return this->add(-m2);
	}

	Matrix4f& Matrix4f::operator-=(const Matrix4f& m2) {
		return this->addTo(-m2);
	}

	Matrix4f::Matrix4f(Matrix4f *orig) {
		this->isInverse = true;

		this->inverse = orig;
		this->setMatrix(Matrix4f::M_ZERO);
	}

	void Matrix4f::update() {
		// Note: This method should NEVER be called for a matrix which is an
		//		 inverse matrix since the inverse matrix will recalculate the
		//		 original matrix which will in turn recalculate the inverse, 
		//		 etc.
		if (this->isInverse) return;

		// 1D Array Representations of this Matrix and the Inverse
		std::array<float, 16> m = this->get();
		std::array<float, 16> inv;

		// Algorithm from: http://stackoverflow.com/questions/1148309/
		inv[0] =   m[ 5] * m[10] * m[15] - m[ 5] * m[11] * m[14] -
				   m[ 9] * m[ 6] * m[15] + m[ 9] * m[ 7] * m[14] +
				   m[13] * m[ 6] * m[11] - m[13] * m[ 7] * m[10];
		inv[4] =  -m[ 4] * m[10] * m[15] + m[ 4] * m[11] * m[14] +
				   m[ 8] * m[ 6] * m[15] - m[ 8] * m[ 7] * m[14] -
				   m[12] * m[ 6] * m[11] + m[12] * m[ 7] * m[10];
		inv[8] =   m[ 4] * m[ 9] * m[15] - m[ 4] * m[11] * m[13] -
				   m[ 8] * m[ 5] * m[15] + m[ 8] * m[ 7] * m[13] +
		   		   m[12] * m[ 5] * m[11] - m[12] * m[ 7] * m[ 9];
		inv[12] = -m[ 4] * m[ 9] * m[14] + m[ 4] * m[10] * m[13] +
				   m[ 8] * m[ 5] * m[14] - m[ 8] * m[ 6] * m[13] -
				   m[12] * m[ 5] * m[10] + m[12] * m[ 6] * m[ 9];

		// Calculate the Determinant. If the determinant is zero, we cannot
		// calculate the Inverse, so set the inverse to zero and return.
		this->determinant = 
			m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
		this->inverse->determinant = 1.0F / this->determinant;
		if (abs(this->determinant) <= 0.000001F) {
			this->inverse->setMatrix(M_ZERO);
			return;
		}

		inv[1] =  -m[ 1] * m[10] * m[15] + m[ 1] * m[11] * m[14] +
				   m[ 9] * m[ 2] * m[15] - m[ 9] * m[ 3] * m[14] -
			       m[13] * m[ 2] * m[11] + m[13] * m[ 3] * m[10];
		inv[2] =   m[ 1] * m[ 6] * m[15] - m[ 1] * m[ 7] * m[14] -
				   m[ 5] * m[ 2] * m[15] + m[ 5] * m[ 3] * m[14] +
				   m[13] * m[ 2] * m[ 7] - m[13] * m[ 3] * m[ 6];
		inv[3] =  -m[ 1] * m[ 6] * m[11] + m[ 1] * m[ 7] * m[10] +
				   m[ 5] * m[ 2] * m[11] - m[ 5] * m[ 3] * m[10] -
				   m[ 9] * m[ 2] * m[ 7] + m[ 9] * m[ 3] * m[ 6];
		inv[5] =   m[ 0] * m[10] * m[15] - m[ 0] * m[11] * m[14] -
				   m[ 8] * m[ 2] * m[15] + m[ 8] * m[ 3] * m[14] +
				   m[12] * m[ 2] * m[11] - m[12] * m[ 3] * m[10];
		inv[6] =  -m[ 0] * m[ 6] * m[15] + m[ 0] * m[ 7] * m[14] +
				   m[ 4] * m[ 2] * m[15] - m[ 4] * m[ 3] * m[14] -
				   m[12] * m[ 2] * m[ 7] + m[12] * m[ 3] * m[ 6];
		inv[7] =   m[ 0] * m[ 6] * m[11] - m[ 0] * m[ 7] * m[10] -
				   m[ 4] * m[ 2] * m[11] + m[ 4] * m[ 3] * m[10] +
				   m[ 8] * m[ 2] * m[ 7] - m[ 8] * m[ 3] * m[ 6];
		inv[9] =  -m[ 0] * m[ 9] * m[15] + m[ 0] * m[11] * m[13] +
				   m[ 8] * m[ 1] * m[15] - m[ 8] * m[ 3] * m[13] -
				   m[12] * m[ 1] * m[11] + m[12] * m[ 3] * m[ 9];
		inv[10] =  m[ 0] * m[ 5] * m[15] - m[ 0] * m[ 7] * m[13] -
				   m[ 4] * m[ 1] * m[15] + m[ 4] * m[ 3] * m[13] +
				   m[12] * m[ 1] * m[ 7] - m[12] * m[ 3] * m[ 5];
		inv[11] = -m[ 0] * m[ 5] * m[11] + m[ 0] * m[ 7] * m[ 9] +
				   m[ 4] * m[ 1] * m[11] - m[ 4] * m[ 3] * m[ 9] -
				   m[ 8] * m[ 1] * m[ 7] + m[ 8] * m[ 3] * m[ 5];
		inv[13] =  m[ 0] * m[ 9] * m[14] - m[ 0] * m[10] * m[13] -
				   m[ 8] * m[ 1] * m[14] + m[ 8] * m[ 2] * m[13] +
				   m[12] * m[ 1] * m[10] - m[12] * m[ 2] * m[ 9];
		inv[14] = -m[ 0] * m[ 5] * m[14] + m[ 0] * m[ 6] * m[13] +
				   m[ 4] * m[ 1] * m[14] - m[ 4] * m[ 2] * m[13] -
				   m[12] * m[ 1] * m[ 6] + m[12] * m[ 2] * m[ 5];
		inv[15] =  m[ 0] * m[ 5] * m[10] - m[ 0] * m[ 6] * m[ 9] -
				   m[ 4] * m[ 1] * m[10] + m[ 4] * m[ 2] * m[ 9] +
				   m[ 8] * m[ 1] * m[ 6] - m[ 8] * m[ 2] * m[ 5];

		// Divide each element by the determinant to get the inverse
		for (float &elem : inv) elem *= (1.0F / this->determinant);

		// Construct the Inverse Matrix and write it to the Inverse Pointer
		float invMatrix[4][4] = {
			{ inv[ 0], inv[ 1], inv[ 2], inv[3] },
			{ inv[ 4], inv[ 5], inv[ 6], inv[7] },
			{ inv[ 8], inv[ 9], inv[10], inv[11] },
			{ inv[12], inv[13], inv[14], inv[15] },
		};
		this->inverse->setMatrix(invMatrix);
	}
}