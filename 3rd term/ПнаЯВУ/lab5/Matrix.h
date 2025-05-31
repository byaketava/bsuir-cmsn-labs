#pragma once
class Matrix
{
	int* arr;
	int rows;
	int cols;
public:
	Matrix();
	Matrix(int rows_, int cols_);
	~Matrix() 	
	{
		delete[] arr;
	}
	void setMatrix();
	void printMatrix();
	int get(int row, int col) const;
	void set(int row, int col, int value);
	void addRow(int row);
	void removeRow(int row);
	void addCol(int col);
	void removeCol(int col);
	void transpose();

	int get_rows()
	{
		return this->rows;
	}
	int get_cols()
	{
		return this->cols;
	}
};