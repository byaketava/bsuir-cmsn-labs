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
			// Расширение массива
			sizeForPtr = sizeForPtr * 3;
			unique_ptr<Matrix[]> newArray = make_unique<Matrix[]>(sizeForPtr);
			for (int i = 0; i < size; i++)
				newArray[i] = move(Array[i]);
		}
		cout << "Выберите действие \033[1;35m1 - 4\033[0m, или введите \033[1;35m0\033[0m для завершения программы" << endl;
		cout << "1: \033[1;36mсоздать\033[0m новую матрицу" << endl;
		cout << "2: \033[1;36mудалить\033[0m существующую матрицу" << endl;
		cout << "3: \033[1;36mвыбрать\033[0m матрицу для работы" << endl;
		cout << "4: \033[1;36mпросмотреть\033[0m все матрицы" << endl;
		cout << "_______________________________________________________________" << endl;
		check(task, 0, 4);
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
				cout << "Введите номер матрицы, которую хотите удалить:" << endl;
				int forDel;
				check(forDel, 1, size);
				cout << "Запускаю процесс удаления..." << endl;
				cout << "_______________________________________________________________" << endl;
				for (int i = forDel - 1; i < size; i++)
					Array[i] = move(Array[i + 1]);
				size--;
				option4(size, Array.get());
				cout << "Удаление завершено." << endl;
				cout << "_______________________________________________________________" << endl;
			}
			break;
		case 3:
			system("cls");
			option4(size, Array.get());
			if (size != 0)
			{
				cout << "Выберите матрицу для дальнейшей работы:" << endl;
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
					cout << "Выберите действие \033[1;35m1 - 7\033[0m, или введите \033[1;35m0\033[0m для выхода в меню" << endl;
					cout << "1: \033[1;36mполучить\033[0m элемент" << endl;
					cout << "2: \033[1;36mизменить\033[0m элемент" << endl;
					cout << "3: \033[1;36mдобавить\033[0m строку" << endl;
					cout << "4: \033[1;36mудалить\033[0m строку" << endl;
					cout << "5: \033[1;36mдобавить\033[0m столбец" << endl;
					cout << "6: \033[1;36mудалить\033[0m столбец" << endl;
					cout << "7: \033[1;36mтранспонировать\033[0m матрицу" << endl;
					cout << "_______________________________________________________________" << endl;
					check(option, 0, 7);
					switch (option)
					{
					case 1:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "Введите номер строки:" << endl;
						int r1;
						num_of_rows = Array[numOfMatrix - 1].get_rows();
						check(r1, 1, num_of_rows);
						cout << "Введите номер столбца:" << endl;
						int c1;
						num_of_cols = Array[numOfMatrix - 1].get_cols();
						check(c1, 1, num_of_cols);
						cout << "Значение в ячейке (" << r1 << ", " << c1 << ") = " << Array[numOfMatrix - 1].get(r1 - 1, c1 - 1) << endl;
						cout << "_______________________________________________________________" << endl;
						break;
					case 2:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "Введите номер строки:" << endl;
						int r2;
						num_of_rows = Array[numOfMatrix - 1].get_rows();
						check(r2, 1, num_of_rows);
						cout << "Введите номер столбца:" << endl;
						int c2;
						num_of_cols = Array[numOfMatrix - 1].get_cols();
						check(c2, 1, num_of_cols);
						cout << "Введите новое значение:" << endl;
						int val;
						check(val, 1, 100);
						Array[numOfMatrix - 1].set(r2 - 1, c2 - 1, val);
						cout << "Новое значение в ячейке (" << r2 << ", " << c2 << ") = " << Array[numOfMatrix - 1].get(r2 - 1, c2 - 1) << endl;
						cout << "_______________________________________________________________" << endl;
						break;
					case 3:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "Введите номер строки,после которой требуется вставить новую:" << endl;
						int r3;
						num_of_rows = Array[numOfMatrix - 1].get_rows();
						check(r3, 1, num_of_rows);
						cout << "Добавление строки..." << endl;
						Array[numOfMatrix - 1].addRow(r3);
						cout << "_______________________________________________________________" << endl;
						break;
					case 4:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "Введите номер строки, которую требуется удалить:" << endl;
						int r4;
						num_of_rows = Array[numOfMatrix - 1].get_rows();
						check(r4, 1, num_of_rows);
						cout << "Удаление строки..." << endl;
						Array[numOfMatrix - 1].removeRow(r4 - 1);
						cout << "_______________________________________________________________" << endl;
						break;
					case 5:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "Введите номер столбца,после которого требуется вставить новый:" << endl;
						int c5;
						num_of_cols = Array[numOfMatrix - 1].get_cols();
						check(c5, 1, num_of_cols);
						cout << "Добавление столбца..." << endl;
						Array[numOfMatrix - 1].addCol(c5);
						cout << "_______________________________________________________________" << endl;
						break;
					case 6:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "Введите номер столбца, который требуется удалить:" << endl;
						int c6;
						num_of_cols = Array[numOfMatrix - 1].get_cols();
						check(c6, 1, num_of_cols);
						cout << "Удаление столбца..." << endl;
						Array[numOfMatrix - 1].removeCol(c6 - 1);
						cout << "_______________________________________________________________" << endl;
						break;
					case 7:
						system("cls");
						showOne(Array.get(), numOfMatrix);
						cout << "Транспонирование матрицы..." << endl;
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
		case 0:
			system("cls");
			char a = 2;
			char b = 4;
			cout << "_______________________________________________________________" << endl;
			cout << "\t\t\t\033[1;5;35mРеЗюМе\033[0m\nЛабораторная работа выполнена в соответствии со всеми \nтребованиями (и за короткий срок!).\nДополнительное задание также выполнено." << endl;
			cout << "\nНо если это \033[1;5;35m" << b << "\033[0m not enought \033[1;5;35m" << b << "\033[0m , то я готова взять ещё доп.задание!" << endl;
			cout << "\n\n\t" << a << " Надеюсь мы всё еще не бывшие лучшие друзья " << a << endl;
			cout << "_______________________________________________________________" << endl;
			exit(0);        //завершение программы
		}
	} while (task != 0);
}
void showOne(Matrix* arr, int number)
{
	cout << "\033[1;35m" << number << " матрица\033[0m:\n" << endl;
	arr[number - 1].printMatrix();
	cout << "_______________________________________________________________" << endl;
}
void option1(int& size, unique_ptr<Matrix[]>& Array)
{
	if (size == 30)
	{
		cout << "У вас уже есть 30 матриц, разберитесь с ними, а потом создавайте" << endl;
		cout << "_______________________________________________________________" << endl;
	}
	else
	{
		cout << "Создание новой матрицы" << endl;
		cout << "_______________________________________________________________" << endl;
		cout << "Введите количество строк:" << endl;
		int rows;
		check(rows, 1, 25);
		cout << "Введите количество столбцов:" << endl;
		int cols;
		check(cols, 1, 25);

		size++;
		Array[size - 1] = Matrix(rows, cols);

		cout << "_______________________________________________________________" << endl;
		cout << "Выберите действие:\n1. Инициализировать матрицу \033[1;35mвручную\033[0m...\n2. Инициализировать матрицу \033[1;35mслучайным\033[0m образом" << endl;
		int boop;
		check(boop, 1, 2);
		cout << "_______________________________________________________________" << endl;
		if (boop == 1)
			cout << "Оно конечно можно вручную, но я это вводить не хочу.\nЗапускаю инициализацию случайным образом..." << endl;
		Array[size - 1].setMatrix();
		cout << "Инициализация завершена." << endl;
		cout << "_______________________________________________________________" << endl;
	}
}
void option4(int size, Matrix*arr) 
{
	if (size == 0)
		cout << "Вы ещё не создали ни одной матрицы. Будьте внимательнее!!!\n(а еще внимательно относитесь к выбору друзей)" << endl;
	else
	{
		for (int i = 0; i < size; i++) 
		{
			cout << "\033[1;35m" << i + 1 << " матрица\033[0m:\n" << endl;
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
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
		cout << "Да,да, да... Проверки наше всё!\nА теперь введите \033[1;5;35mАдЕкВаТнО\033[0m:" << endl;
	}
}