#include"Header.h"

void menu()
{
	int task;
	int sizeForPtr = 10;
	unique_ptr<Matrix[]> Array = make_unique<Matrix[]>(sizeForPtr);
	int size = 0;
	do
	{
		if (size == sizeForPtr)
		{
			// ���������� �������
			sizeForPtr = sizeForPtr * 3;
			unique_ptr<Matrix[]> newArray = make_unique<Matrix[]>(sizeForPtr);
			for (int i = 0; i < size; i++)
				newArray[i] = move(Array[i]);
		}
		cout << "�������� �������� \033[1;35m1 - 4\033[0m, ��� ������� \033[1;35m0\033[0m ��� ���������� ���������" << endl;
		cout << "1: \033[1;36m�������\033[0m ����� �������" << endl;
		cout << "2: \033[1;36m�������\033[0m ������������ �������" << endl;
		cout << "3: \033[1;36m�������\033[0m ������� ��� ������" << endl;
		cout << "4: \033[1;36m�����������\033[0m ��� �������" << endl;
		cout << "5: \033[1;36m����������\033[0m ����������" << endl;
		cout << "_______________________________________________________________" << endl;
		check(task, 0, 5);
		switch (task)
		{
		case 1:
			system("cls");
			option1(size, Array);
			break;
		case 2:
			system("cls");
			option4(size, Array.get());
			if (size != 0)
			{
				cout << "������� ����� �������, ������� ������ �������:" << endl;
				int forDel;
				check(forDel, 1, size);
				cout << "�������� ������� ��������..." << endl;
				cout << "_______________________________________________________________" << endl;
				for (int i = forDel - 1; i < size; i++)
					Array[i] = move(Array[i + 1]);
				size--;
				option4(size, Array.get());
				cout << "�������� ���������." << endl;
				cout << "_______________________________________________________________" << endl;
			}
			break;
		case 3:
			system("cls");
			option4(size, Array.get());
			if (size != 0)
			{
				cout << "�������� ������� ��� ���������� ������:" << endl;
				int numOfMatrix;
				check(numOfMatrix, 1, size);
				cout << "_______________________________________________________________" << endl;
				int option;
				int num_of_rows = 0;
				int num_of_cols = 0;
				system("cls");
				do
				{
					showOne(Array.get(), numOfMatrix);
					cout << "�������� �������� \033[1;35m1 - 7\033[0m, ��� ������� \033[1;35m0\033[0m ��� ������ � ����" << endl;
					cout << "1: \033[1;36m��������\033[0m �������" << endl;
					cout << "2: \033[1;36m��������\033[0m �������" << endl;
					cout << "3: \033[1;36m��������\033[0m ������" << endl;
					cout << "4: \033[1;36m�������\033[0m ������" << endl;
					cout << "5: \033[1;36m��������\033[0m �������" << endl;
					cout << "6: \033[1;36m�������\033[0m �������" << endl;
					cout << "7: \033[1;36m���������������\033[0m �������" << endl;
					cout << "_______________________________________________________________" << endl;
					check(option, 0, 7);
					switch (option)
					{
					case 1:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "������� ����� ������:" << endl;
						int r1;
						num_of_rows = Array[numOfMatrix - 1].get_rows();
						check(r1, 1, num_of_rows);
						cout << "������� ����� �������:" << endl;
						int c1;
						num_of_cols = Array[numOfMatrix - 1].get_cols();
						check(c1, 1, num_of_cols);
						cout << "�������� � ������ (" << r1 << ", " << c1 << ") = " << Array[numOfMatrix - 1].get(r1 - 1, c1 - 1) << endl;
						cout << "_______________________________________________________________" << endl;
						break;
					case 2:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "������� ����� ������:" << endl;
						int r2;
						num_of_rows = Array[numOfMatrix - 1].get_rows();
						check(r2, 1, num_of_rows);
						cout << "������� ����� �������:" << endl;
						int c2;
						num_of_cols = Array[numOfMatrix - 1].get_cols();
						check(c2, 1, num_of_cols);
						cout << "������� ����� ��������:" << endl;
						int val;
						check(val, 1, 100);
						Array[numOfMatrix - 1].set(r2 - 1, c2 - 1, val);
						cout << "����� �������� � ������ (" << r2 << ", " << c2 << ") = " << Array[numOfMatrix - 1].get(r2 - 1, c2 - 1) << endl;
						cout << "_______________________________________________________________" << endl;
						break;
					case 3:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "������� ����� ������,����� ������� ��������� �������� �����:" << endl;
						int r3;
						num_of_rows = Array[numOfMatrix - 1].get_rows();
						check(r3, 1, num_of_rows);
						cout << "���������� ������..." << endl;
						Array[numOfMatrix - 1].addRow(r3);
						cout << "_______________________________________________________________" << endl;
						break;
					case 4:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "������� ����� ������, ������� ��������� �������:" << endl;
						int r4;
						num_of_rows = Array[numOfMatrix - 1].get_rows();
						check(r4, 1, num_of_rows);
						cout << "�������� ������..." << endl;
						Array[numOfMatrix - 1].removeRow(r4 - 1);
						cout << "_______________________________________________________________" << endl;
						break;
					case 5:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "������� ����� �������,����� �������� ��������� �������� �����:" << endl;
						int c5;
						num_of_cols = Array[numOfMatrix - 1].get_cols();
						check(c5, 1, num_of_cols);
						cout << "���������� �������..." << endl;
						Array[numOfMatrix - 1].addCol(c5);
						cout << "_______________________________________________________________" << endl;
						break;
					case 6:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "������� ����� �������, ������� ��������� �������:" << endl;
						int c6;
						num_of_cols = Array[numOfMatrix - 1].get_cols();
						check(c6, 1, num_of_cols);
						cout << "�������� �������..." << endl;
						Array[numOfMatrix - 1].removeCol(c6 - 1);
						cout << "_______________________________________________________________" << endl;
						break;
					case 7:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "���������������� �������..." << endl;
						Array[numOfMatrix - 1].transpose();
						cout << "_______________________________________________________________" << endl;
						break;
					case 0:
						system("cls");
						break;
					}
				} while (option != 0);
			}
			break;
		case 4:
			system("cls");
			option4(size, Array.get());
			break;
		case 5:
			system("cls");
			if (size != 0)
			{
				int option;
				do
				{
					cout << "�������� �������� \033[1;35m1 - 9\033[0m, ��� ������� \033[1;35m0\033[0m ��� ������ � ����" << endl;
					cout << "1: \033[1;36m+\033[0m" << endl;
					cout << "2: \033[1;36m-\033[0m" << endl;
					cout << "3: \033[1;36m*\033[0m" << endl;
					cout << "4: \033[1;36m+=\033[0m" << endl;
					cout << "5: \033[1;36m-=\033[0m" << endl;
					cout << "6: \033[1;36m*=\033[0m" << endl;
					cout << "7: \033[1;36m=\033[0m" << endl;
					cout << "8: \033[1;36mnew � delete\033[0m (�������� ��������� ������� � ���������)" << endl;
					cout << "9: \033[1;36m����\033[0m �������" << endl;
					cout << "10: \033[1;36m�����\033[0m �������" << endl;
					cout << "_______________________________________________________________" << endl;
					check(option, 0, 10);
					int Matrix1;
					int Matrix2;
					switch (option)
					{
					case 1:
						system("cls");
						option4(size, Array.get());
						cout << "�������� ������ �������:" << endl;
						check(Matrix1, 1, size);
						cout << "_______________________________________________________________" << endl;

						cout << "�������� ������ �������:" << endl;
						check(Matrix2, 1, size);
						cout << "_______________________________________________________________" << endl;
						showOne(Array.get(), Matrix1);
						showOne(Array.get(), Matrix2);

						if (Array[Matrix1 - 1].get_rows() != Array[Matrix2 - 1].get_rows() || Array[Matrix1 - 1].get_cols() != Array[Matrix2 - 1].get_cols())
						{
							cout << "�������� ����������\n" << endl;
						}
						else
						{
							size++;
							Array[size - 1] = Array[Matrix1 - 1] + Array[Matrix2 - 1];
							cout << "\033[1;5m����� \033[0m";
							showOne(Array.get(), size);
						}
						break;
					case 2:
						system("cls");
						option4(size, Array.get());
						cout << "�������� ������ �������:" << endl;
						check(Matrix1, 1, size);
						cout << "_______________________________________________________________" << endl;

						cout << "�������� ������ �������:" << endl;
						check(Matrix2, 1, size);
						cout << "_______________________________________________________________" << endl;
						showOne(Array.get(), Matrix1);
						showOne(Array.get(), Matrix2);

						if (Array[Matrix1 - 1].get_rows() != Array[Matrix2 - 1].get_rows() || Array[Matrix1 - 1].get_cols() != Array[Matrix2 - 1].get_cols())
						{
							cout << "��������� ����������\n" << endl;
						}
						else
						{
							size++;
							Array[size - 1] = Array[Matrix1 - 1] - Array[Matrix2 - 1];
							cout << "\033[1;5m����� \033[0m";
							showOne(Array.get(), size);
						}
						break;
					case 3:
						system("cls");
						option4(size, Array.get());
						cout << "�������� ������ �������:" << endl;
						check(Matrix1, 1, size);
						cout << "_______________________________________________________________" << endl;

						cout << "�������� ������ �������:" << endl;
						check(Matrix2, 1, size);
						cout << "_______________________________________________________________" << endl;
						showOne(Array.get(), Matrix1);
						showOne(Array.get(), Matrix2);

						if (Array[Matrix1 - 1].get_cols() != Array[Matrix2 - 1].get_rows())
						{
							cout << "��������� ����������\n" << endl;
						}
						else
						{
							size++;
							Array[size - 1] = Array[Matrix1 - 1] * Array[Matrix2 - 1];
							cout << "\033[1;5m����� \033[0m";
							showOne(Array.get(), size);
						}
						break;
					case 4:
						system("cls");
						option4(size, Array.get());
						cout << "�������� ������ �������:" << endl;
						check(Matrix1, 1, size);
						cout << "_______________________________________________________________" << endl;

						cout << "�������� ������ �������:" << endl;
						check(Matrix2, 1, size);
						cout << "_______________________________________________________________" << endl;
						showOne(Array.get(), Matrix1);
						showOne(Array.get(), Matrix2);

						if (Array[Matrix1 - 1].get_rows() != Array[Matrix2 - 1].get_rows() || Array[Matrix1 - 1].get_cols() != Array[Matrix2 - 1].get_cols())
						{
							cout << "�������� ����������\n" << endl;
						}
						else
						{
							Array[Matrix1 - 1] += Array[Matrix2 - 1];
							cout << "\033[1;5m���������� \033[0m";
							showOne(Array.get(), Matrix1);
						}
						break;
					case 5:
						system("cls");
						option4(size, Array.get());
						cout << "�������� ������ �������:" << endl;
						check(Matrix1, 1, size);
						cout << "_______________________________________________________________" << endl;

						cout << "�������� ������ �������:" << endl;
						check(Matrix2, 1, size);
						cout << "_______________________________________________________________" << endl;
						showOne(Array.get(), Matrix1);
						showOne(Array.get(), Matrix2);

						if (Array[Matrix1 - 1].get_rows() != Array[Matrix2 - 1].get_rows() || Array[Matrix1 - 1].get_cols() != Array[Matrix2 - 1].get_cols())
						{
							cout << "��������� ����������\n" << endl;
						}
						else
						{
							Array[Matrix1 - 1] -= Array[Matrix2 - 1];
							cout << "\033[1;5m���������� \033[0m";
							showOne(Array.get(), Matrix1);
						}
						break;
					case 6:
						system("cls");
						option4(size, Array.get());
						cout << "�������� �������, ������� ������ ��������:" << endl;
						check(Matrix1, 1, size);
						cout << "_______________________________________________________________" << endl;
						int val;
						cout << "������� ���������:" << endl;
						check(val, -25, 25);
						cout << "_______________________________________________________________" << endl;
						showOne(Array.get(), Matrix1);

						Array[Matrix1 - 1] *= val;
						cout << "\033[1;5m���������� \033[0m";
						showOne(Array.get(), Matrix1);
						break;
					case 7:
						system("cls");
						option4(size, Array.get());
						cout << "�������� ������ �������:" << endl;
						check(Matrix1, 1, size);
						cout << "_______________________________________________________________" << endl;

						cout << "�������� ������ �������:" << endl;
						check(Matrix2, 1, size);
						cout << "_______________________________________________________________" << endl;
						showOne(Array.get(), Matrix1);
						showOne(Array.get(), Matrix2);

						if (Matrix1 == Matrix2)
						{
							cout << "��������� ����������\n" << endl;
						}
						else
						{
							Array[Matrix1 - 1] == Array[Matrix2 - 1];
							cout << "\033[1;5m���������� \033[0m";
							showOne(Array.get(), Matrix1);
						}
						break;
					case 8:
						system("cls");
						if (size == 30)
						{
							cout << "� ��� ��� ���� 30 ������, ����������� � ����, � ����� ����������" << endl;
							cout << "_______________________________________________________________" << endl;
						}
						else
						{
							cout << "�������� ������� �������� ����� �������..." << endl;
							size++;
							Matrix* m = new Matrix(rand() % 15 + 1, rand() % 15 + 1);
							(*m).setMatrix();
							Array[size - 1] = *m;
							cout << "�������� ���������." << endl;
							cout << "_______________________________________________________________" << endl;
							cout << "\033[1;5m����� \033[0m";
							showOne(Array.get(), size);
							option4(size, Array.get());
							cout << "�������� ������� �������� ����� �������..." << endl;
							cout << "_______________________________________________________________" << endl;
							delete m;
							size--;
							cout << "�������� ���������." << endl;
							cout << "_______________________________________________________________" << endl;
							option4(size, Array.get());
						}
						break;
					case 9:
						system("cls");
						if (size == 30)
						{
							cout << "� ��� ��� ���� 30 ������, ����������� � ����, � ����� ����������" << endl;
							cout << "_______________________________________________________________" << endl;
						}
						else
						{
							cout << "�������� ����� �������" << endl;
							cout << "_______________________________________________________________" << endl;
							cout << "������� ���������� �����:" << endl;
							int rows;
							check(rows, 1, 5);
							cout << "������� ���������� ��������:" << endl;
							int cols;
							check(cols, 1, 5);
							size++;
							Array[size - 1] = Matrix(rows, cols);
							cout << "_______________________________________________________________" << endl;
							cout << "������� ��������:" << endl;
							cin >> Array[size - 1];
							cout << "_______________________________________________________________" << endl;
							cout << "\033[1;35m" << size << " �������\033[0m:\n" << endl;
							cout << Array[size - 1] << endl;
							cout << "_______________________________________________________________" << endl;
							//showOne(Array.get(), Matrix1);
						}
						break;
					case 10:
						system("cls");
						cout << "�������� �������, ������� ������ ������� �� �����:" << endl;
						check(Matrix1, 1, size);
						cout << "_______________________________________________________________" << endl;
						cout << "\033[1;35m" << Matrix1 << " �������\033[0m:\n" << endl;
						cout << Array[Matrix1-1] << endl;
						cout << "_______________________________________________________________" << endl;
						break;
					case 0:
						system("cls");
						break;
					}
				} while (option != 0);
			}

			else
			{
				cout << "������������ �������� ������ ��� ��������� ��������!" << endl;
			}
			break;
		case 0:
			system("cls");
			char a = 2;
			char b = 4;
			cout << "_______________________________________________________________" << endl;
			cout << "\t\t\t\033[1;5;35m������\033[0m\n������������ ������ ��������� � ������������ �� ����� \n������������ (� �� �������� ����!).\n�������������� ������� ����� ���������." << endl;
			cout << "\n�� ���� ��� \033[1;5;35m" << b << "\033[0m not enought \033[1;5;35m" << b << "\033[0m , �� � ������ ����� ��� ���.�������!" << endl;
			cout << "\n\n\t" << a << " ������� �� �� ��� �� ������ ������ ������ " << a << endl;
			cout << "_______________________________________________________________" << endl;
			exit(0);        //���������� ���������
		}
	} while (task != 0);
}
void showOne(Matrix* arr, int number)
{
	cout << "\033[1;35m" << number << " �������\033[0m:\n" << endl;
	arr[number - 1].printMatrix();
	cout << "_______________________________________________________________" << endl;
}
void option1(int& size, unique_ptr<Matrix[]>& Array)
{
	if (size == 30)
	{
		cout << "� ��� ��� ���� 30 ������, ����������� � ����, � ����� ����������" << endl;
		cout << "_______________________________________________________________" << endl;
	}
	else
	{
		cout << "�������� ����� �������" << endl;
		cout << "_______________________________________________________________" << endl;
		cout << "������� ���������� �����:" << endl;
		int rows;
		check(rows, 1, 25);
		cout << "������� ���������� ��������:" << endl;
		int cols;
		check(cols, 1, 25);

		size++;
		Array[size - 1] = Matrix(rows, cols);

		cout << "_______________________________________________________________" << endl;
		cout << "�������� ��������:\n1. ���������������� ������� \033[1;35m�������\033[0m...\n2. ���������������� ������� \033[1;35m���������\033[0m �������" << endl;
		int boop;
		check(boop, 1, 2);
		cout << "_______________________________________________________________" << endl;
		if (boop == 1)
			cout << "��� ������� ����� �������, �� � ��� ������� �� ����.\n�������� ������������� ��������� �������..." << endl;
		Array[size - 1].setMatrix();
		cout << "������������� ���������." << endl;
		cout << "_______________________________________________________________" << endl;
	}
}
void option4(int size, Matrix* arr)
{
	if (size == 0)
		cout << "�� ��� �� ������� �� ����� �������. ������ ������������!!!\n(� ��� ����������� ���������� � ������ ������)" << endl;
	else
	{
		for (int i = 0; i < size; i++)
		{
			cout << "\033[1;35m" << i + 1 << " �������\033[0m:\n" << endl;
			arr[i].printMatrix();
			cout << endl;
		}
	}
	cout << "_______________________________________________________________" << endl;
}
void check(int& num, int x, int y)
{
	while (1)
	{
		cin >> num;
		if (!cin.fail() && num >= x && num <= y && cin.get() == '\n')
			break;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������� ������ �����
		cout << "��,��, ��... �������� ���� ��!\n� ������ ������� \033[1;5;35m���������\033[0m:" << endl;
	}
}