#include"Header.h"

// ������������
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
//�������������
void Matrix:: setMatrix()
{
	for (int i = 0; i < rows * cols; i++)
		arr[i] = rand() % 40;
}
//����� �� �����
void Matrix:: printMatrix()
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
//�������� ������
void Matrix::addRow(int row)
{
	rows++;
	// �������� ������ ������� ��� ����������� ������� �������
	int* newArr = new int[rows * cols];
	// ����������� ��������� �� ��������� ������
	for (int i = 0; i < row * cols; i++)
		newArr[i] = arr[i];
	// ����������� ��������� ����� ��������� ������
	for (int i = row * cols; i < (rows - 1) * cols; i++)
		newArr[i + cols] = arr[i];
	delete[] arr;
	arr = newArr;
	for (int i = row * cols; i < (row + 1) * cols; i++)
		newArr[i] = 0;
}
//������� ������
void Matrix::removeRow(int row)
{
	rows--;
	// �������� ������ ������� ��� ����������� ������� �������
	int* newArr = new int[rows * cols];
	// ����������� ��������� �� ��������� ������
	for (int i = 0; i < row; i++)
		for (int j = 0; j < cols; j++)
			newArr[i * cols + j] = arr[i * cols + j];
	// ����������� ��������� ����� ��������� ������
	for (int i = row + 1; i <= rows; i++)
		for (int j = 0; j < cols; j++)
			newArr[(i - 1) * cols + j] = arr[i * cols + j];
	delete[] arr;
	arr = newArr;
}
//�������� �������
void Matrix::addCol(int col)
{
	cols++;
	// �������� ������ ������� ��� ����������� ������� �������
	int* newArr = new int[rows * cols];
	// ����������� ��������� �� ���������� �������
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < col; j++)
			newArr[i * cols + j] = arr[i * (cols - 1) + j];
	// ����������� ��������� ����� ���������� �������
	for (int i = 0; i < rows; i++)
		for (int j = col; j < cols - 1; j++)
			newArr[i * cols + j + 1] = arr[i * (cols - 1) + j];
	delete[] arr;
	arr = newArr;
	for (int i = 0; i < rows; i++)
		newArr[i * cols + col] = 0;
}
//������� �������
void Matrix::removeCol(int col)
{
	cols--;
	// �������� ������ ������� ��� ����������� ������� �������
	int* newArr = new int[rows * cols];
	// ����������� ��������� �� ���������� �������
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < col; j++)
			newArr[i * cols + j] = arr[i * (cols + 1) + j];
	// ����������� ��������� ����� ���������� �������
	for (int i = 0; i < rows; i++)
		for (int j = col + 1; j <= cols; j++)
			newArr[i * cols + (j - 1)] = arr[i * (cols + 1) + j];
	delete[] arr;
	arr = newArr;
}
//��������������� �������
void Matrix::transpose()
{
	// �������� ������ ������� ��� ����������������� �������
	int* newArr = new int[cols * rows];
	// ����������� ��������� �� ������� ������� � ����� � ����������� ���������
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			newArr[j * rows + i] = arr[i * cols + j];
	// ��������� ��������
	int temp = rows;
	rows = cols;
	cols = temp;

	delete[] arr;
	arr = newArr;
}