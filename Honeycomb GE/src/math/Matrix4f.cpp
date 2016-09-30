#include <iostream>

#include "..\..\include\math\Matrix4f.h"

namespace Honeycomb::Math {
	float Matrix4f::M_IDENTITY[4][4] = {
		{ 1, 0, 0, 0 },
		{ 0, 1, 0, 0 },
		{ 0, 0, 1, 0 },
		{ 0, 0, 0, 1 }
	};

	Matrix4f Matrix4f::IDENTITY = Matrix4f(Matrix4f::M_IDENTITY);

	Matrix4f::Matrix4f() {
		
	}

	Matrix4f::Matrix4f(float m[4][4]) {
		this->setMatrix(m);
	}

	Matrix4f::~Matrix4f() {

	}

	Matrix4f Matrix4f::add(Matrix4f m2) {
		Matrix4f sum;

		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				sum.matrix[r][c] = this->matrix[r][c] + m2.matrix[r][c];
			}
		}

		return sum;
	}

	Matrix4f Matrix4f::addTo(Matrix4f m2) {
		Matrix4f sum;

		sum.setMatrix(sum.matrix);
		return *this;
	}

	Matrix4f& Matrix4f::identity() {
		return Matrix4f::IDENTITY;
	}

	float* Matrix4f::get() {
		float* oneDim = new float[16]; // Create a 1D array of 16 values (4x4)

		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				// Convert the 2D index to 1D and write from the matrix to it
				oneDim[r * 4 + c] = this->getAt(r, c);
			}
		}

		return oneDim;
	}

	float Matrix4f::getAt(int r, int c) {
		return this->matrix[r][c];
	}

	Matrix4f Matrix4f::multiply(Matrix4f m2) {
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

	Matrix4f Matrix4f::multiplyTo(Matrix4f m2) {
		Matrix4f product;

		this->setMatrix(product.matrix);
		return *this;
	}

	Matrix4f Matrix4f::scale(float scale) {
		Matrix4f scaled;

		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				scaled.matrix[r][c] = this->matrix[r][c] * scale;
			}
		}

		return scaled;
	}

	Matrix4f Matrix4f::scaleTo(float scale) {
		Matrix4f scaled = this->scale(scale);

		this->setMatrix(scaled.matrix);
		return *this;
	}

	void Matrix4f::setAt(int r, int c, float val) {
		this->matrix[r][c] = val;
	}

	void Matrix4f::setMatrix(float f[4][4]) {
		// Copy the specified matrix array values into this matrix array, 
		// column by column.
		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				this->matrix[r][c] = f[r][c];
			}
		}
	}

	void Matrix4f::setMatrix(const float f[4][4]) {
		// Copy the specified matrix array values into this matrix array, 
		// column by column.
		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				this->matrix[r][c] = f[r][c];
			}
		}
	}

	Matrix4f Matrix4f::operator*(float scale) {
		return this->scale(scale);
	}

	Matrix4f Matrix4f::operator*=(float scale) {
		return this->scaleTo(scale);
	}

	Matrix4f Matrix4f::operator*(Matrix4f m2) {
		return this->multiply(m2);
	}

	Matrix4f Matrix4f::operator*=(Matrix4f m2) {
		return this->multiplyTo(m2);
	}

	Matrix4f Matrix4f::operator/(float scale) {
		return this->scale(1.0F / scale);
	}

	Matrix4f Matrix4f::operator/=(float scale) {
		return this->scaleTo(1.0F / scale);
	}

	Matrix4f Matrix4f::operator+(Matrix4f m2) {
		return this->add(m2);
	}

	Matrix4f Matrix4f::operator+=(Matrix4f m2) {
		return this->addTo(m2);
	}

	Matrix4f Matrix4f::operator-() {
		return this->scale(-1.0F);
	}

	Matrix4f Matrix4f::operator-(Matrix4f m2) {
		return this->add(-m2);
	}

	Matrix4f Matrix4f::operator-=(Matrix4f m2) {
		return this->addTo(-m2);
	}
}