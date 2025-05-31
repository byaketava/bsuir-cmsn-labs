#include"Header.h"

// конструкторы
Matrix::Matrix()
{
	rows = 0;
	cols = 0;
	for (int i = 0; i < rows * cols; i++)
		arr[i] = 0;
}
Matrix::Matrix(int rows_, int cols_) : rows(rows_), cols(cols_), arr(new int[rows_ * cols_])
{
	for (int i = 0; i < rows * cols; i++)
		arr[i] = 0;
}
//конструктор копирования
//Matrix::Matrix(const Matrix& obj)
//{
//	rows = obj.rows;
//	cols = obj.cols;
//	for (int i = 0; i < rows * cols; i++)
//		arr[i] = obj.arr[i];
//}
//инициализация
void Matrix::setMatrix()
{
	for (int i = 0; i < rows * cols; i++)
		arr[i] = rand() % 40;
}
//вывод на экран
void Matrix::printMatrix()
{
	cout << setw(14) << right;
	for (int i = 0; i < cols; i++)
		cout << "\033[1;36m" << setw(5) << right << i + 1 << "\033[0m";
	cout << "\n" << setw(7) << right << " ";
	for (int i = 0; i < cols; i++)
		cout << "\033[1;36m_____\033[0m";
	cout << "\033[1;36m__\033[0m";
	cout << "\n\033[1;36m" << setw(5) << right << 1 << " |\033[0m";
	for (int i = 0; i < rows * cols; i++)
	{
		if (i != 0 && i % cols == 0)
		{
			cout << "\033[1;36m";
			cout << setw(7) << right << " |\033[0m" << "\n\033[1;36m" << setw(5) << right << (i / cols) + 1 << " |\033[0m";
		}
		cout << setw(5) << right << arr[i];
	}
	cout << "\033[1;36m";
	cout << setw(3) << right << " |" << "\n" << setw(7) << right << " |";
	for (int i = 0; i < cols; i++)
		cout << "\033[1;36m_____\033[0m";
	cout << "\033[1;36m__|\033[0m";
	cout << endl;
}
//get
int Matrix::get(int row, int col) const
{
	return arr[row * cols + col];
}
//set
void Matrix::set(int row, int col, int value)
{
	arr[row * cols + col] = value;
}
//добавить строку
void Matrix::addRow(int row)
{
	rows++;
	// Создание нового массива для измененного размера матрицы
	int* newArr = new int[rows * cols];
	// Копирование элементов до указанной строки
	for (int i = 0; i < row * cols; i++)
		newArr[i] = arr[i];
	// Копирование элементов после указанной строки
	for (int i = row * cols; i < (rows - 1) * cols; i++)
		newArr[i + cols] = arr[i];
	delete[] arr;
	arr = newArr;
	for (int i = row * cols; i < (row + 1) * cols; i++)
		newArr[i] = 0;
}
//удалить строку
void Matrix::removeRow(int row)
{
	rows--;
	// Создание нового массива для измененного размера матрицы
	int* newArr = new int[rows * cols];
	// Копирование элементов до указанной строки
	for (int i = 0; i < row; i++)
		for (int j = 0; j < cols; j++)
			newArr[i * cols + j] = arr[i * cols + j];
	// Копирование элементов после указанной строки
	for (int i = row + 1; i <= rows; i++)
		for (int j = 0; j < cols; j++)
			newArr[(i - 1) * cols + j] = arr[i * cols + j];
	delete[] arr;
	arr = newArr;
}
//добавить столбец
void Matrix::addCol(int col)
{
	cols++;
	// Создание нового массива для измененного размера матрицы
	int* newArr = new int[rows * cols];
	// Копирование элементов до указанного столбца
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < col; j++)
			newArr[i * cols + j] = arr[i * (cols - 1) + j];
	// Копирование элементов после указанного столбца
	for (int i = 0; i < rows; i++)
		for (int j = col; j < cols - 1; j++)
			newArr[i * cols + j + 1] = arr[i * (cols - 1) + j];
	delete[] arr;
	arr = newArr;
	for (int i = 0; i < rows; i++)
		newArr[i * cols + col] = 0;
}
//удалить столбец
void Matrix::removeCol(int col)
{
	cols--;
	// Создание нового массива для измененного размера матрицы
	int* newArr = new int[rows * cols];
	// Копирование элементов до указанного столбца
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < col; j++)
			newArr[i * cols + j] = arr[i * (cols + 1) + j];
	// Копирование элементов после указанного столбца
	for (int i = 0; i < rows; i++)
		for (int j = col + 1; j <= cols; j++)
			newArr[i * cols + (j - 1)] = arr[i * (cols + 1) + j];
	delete[] arr;
	arr = newArr;
}
//транспонировать матрицу
void Matrix::transpose()
{
	// Создание нового массива для транспонированной матрицы
	int* newArr = new int[cols * rows];
	// Копирование элементов из старого массива в новый с измененными индексами
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			newArr[j * rows + i] = arr[i * cols + j];
	// Изменение размеров
	int temp = rows;
	rows = cols;
	cols = temp;

	delete[] arr;
	arr = newArr;
}

Matrix Matrix:: operator+(const Matrix& m) const
{
	Matrix result(rows, cols);

	for (int i = 0; i < rows * cols; i++)
		result.arr[i] = arr[i] + m.arr[i];

	return result;
}
Matrix Matrix:: operator-(const Matrix& m) const
{
	Matrix result(rows, cols);

	for (int i = 0; i < rows * cols; i++)
		result.arr[i] = arr[i] - m.arr[i];

	return result;
}
Matrix Matrix:: operator*(const Matrix& m) const
{
	Matrix result(rows, m.cols);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < m.cols; j++)
		{
			int sum = 0;
			for (int k = 0; k < cols; k++)
			{
				sum += arr[i * cols + k] * m.arr[k * m.cols + j];
			}
			result.arr[i * result.cols + j] = sum;
		}
	}

	return result;
}
Matrix& Matrix:: operator+=(const Matrix& m) 
{
	for (int i = 0; i < rows * cols; i++)
		arr[i] += m.arr[i];

	return *this;
}
Matrix& Matrix:: operator-=(const Matrix& m)
{
	for (int i = 0; i < rows * cols; i++)
		arr[i] -= m.arr[i];

	return *this;
}
Matrix& Matrix:: operator*=(int value)
{
	for (int i = 0; i < rows*cols; i++)
	{
		arr[i] *= value;
	}
	return *this;
}
Matrix& Matrix:: operator==(const Matrix& m)
{
	if (this != &m)
	{
		delete[] arr;
		rows = m.rows;
		cols = m.cols;
		arr = new int[rows * cols];
		for (int i = 0; i < rows * cols; i++)
		{
			arr[i] = m.arr[i];
		}
	}
	return *this;
}
void* Matrix:: operator new(size_t size) 
{
	void* m = ::new Matrix;
	return m;
}
void Matrix:: operator delete(void* m) 
{
	::delete (m);
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) 
{
	os << setw(14) << right;
	for (int i = 0; i < m.cols; i++)
		os << "\033[1;36m" << setw(5) << right << i + 1 << "\033[0m";
	os << "\n" << setw(7) << right << " ";
	for (int i = 0; i < m.cols; i++)
		os << "\033[1;36m_____\033[0m";
	os << "\033[1;36m__\033[0m";
	os << "\n\033[1;36m" << setw(5) << right << 1 << " |\033[0m";
	for (int i = 0; i < m.rows * m.cols; i++)
	{
		if (i != 0 && i % m.cols == 0)
		{
			os << "\033[1;36m";
			os << setw(7) << right << " |\033[0m" << "\n\033[1;36m" << setw(5) << right << (i / m.cols) + 1 << " |\033[0m";
		}
		os << setw(5) << right <<m.arr[i];
	}
	os << "\033[1;36m";
	os << setw(3) << right << " |" << "\n" << setw(7) << right << " |";
	for (int i = 0; i < m.cols; i++)
		os << "\033[1;36m_____\033[0m";
	os << "\033[1;36m__|\033[0m";
	os << endl;
	return os;
}
std::istream& operator>>(std::istream& is, Matrix& m)
{
	for (int i = 0; i < m.rows * m.cols; i++)
		is >> m.arr[i];
	return is;
}