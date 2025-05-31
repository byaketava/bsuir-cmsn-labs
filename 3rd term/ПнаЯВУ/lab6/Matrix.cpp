#include "Header.h"
#include "Matrix.h"
#include "queue.h"

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

//инициализация
void Matrix::setMatrix()
{
	for (int i = 0; i < rows * cols; i++)
		arr[i] = rand() % 40;
}

void Matrix::setAllMatrix()
{
	rows = rand() % 15;
	cols = rand() % 15;
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
		os << setw(5) << right << m.arr[i];
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
	m = Matrix(rand()%15+1, rand()%15+1);
	for (int i = 0; i < m.rows * m.cols; i++)
		m.arr[i] = rand() % 40;
		
	
	return is;
}