#pragma once
class Matrix
{
	int* arr;
	int rows;
	int cols;
public:
	Matrix();
	Matrix(int rows_, int cols_);
	//Matrix(const Matrix& obj);
	~Matrix() {}

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

	Matrix operator+(const Matrix& m) const;
	Matrix operator-(const Matrix& m) const;
	Matrix operator*(const Matrix& m) const;
	Matrix& operator+=(const Matrix& m);
	Matrix& operator-=(const Matrix& m);
	Matrix& operator*=(int value);
	Matrix& operator==(const Matrix& m);
	void* operator new(size_t size);
	void operator delete(void* m);

	friend std::ostream& operator<< (std::ostream& os, const Matrix& m);
	friend std::istream& operator>>(std::istream& is, Matrix& m);
};