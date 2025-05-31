#pragma once
#include <iostream>
#include <new>

class Matrix
{
	int* arr;
	int rows;
	int cols;
public:
	Matrix();
	Matrix(int rows_, int cols_);
	~Matrix() {}

	void setMatrix();
	void setAllMatrix();
	void printMatrix();

	int get_rows()
	{
		return this->rows;
	}
	int get_cols()
	{
		return this->cols;
	}

	friend std::ostream& operator<< (std::ostream& os, const Matrix& m);
	friend std::istream& operator>>(std::istream& is, Matrix& m);
};