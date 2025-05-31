#include "Header.h"
#include "Matrix.h"
#include "queue.h"

void menu()
{
	Queue<Matrix> MQ;
	int task;
	do
	{
		cout << "Выберите действие \033[1;35m1 - 4\033[0m, или введите \033[1;35m0\033[0m для завершения программы" << endl;
		cout << "1: \033[1;36mсоздать\033[0m новую матрицу и добавить в очередь" << endl;
		cout << "2: \033[1;36mудалить\033[0m первую в очереди матрицу" << endl;
		cout << "3: \033[1;36mпросмотреть\033[0m все матрицы в очереди" << endl;
		cout << "4: \033[1;36mполучить\033[0m первую в очереди матрицу" << endl;
		cout << "_______________________________________________________________" << endl;
		check(task, 0, 4);
		switch (task)
		{
		case 1:
		{
			system("cls");
			cin >> MQ;
			break;
		}
		case 2:
		{
			system("cls");
			if (!MQ.isEmpty())
			{
				cout << "Запускаю процесс удаления..." << endl;
				MQ.dequeue();
				cout << "Удаление завершено." << endl;
				cout << "_______________________________________________________________" << endl;
			}
			else
			{
				cout << "Очередь пуста" << endl;
			}
			break;
		}
		case 3:
		{
			system("cls");
			if (!MQ.isEmpty())
			{
				cout << MQ << endl;
			}
			else
			{
				cout << "Очередь пуста" << endl;
			}
			break;
		}
		case 4:
		{
			system("cls");
			cout << endl;
			if (!MQ.isEmpty())
			{
				cout << MQ;
			}
			else
			{
				cout << "Очередь пуста" << endl;
			}
			break;
		}
		case 0:
		{
			system("cls");
			char a = 2;
			char b = 4;
			cout << "_______________________________________________________________" << endl;
			cout << "\t\t\t\033[1;5;35mРеЗюМе\033[0m\nЛабораторная работа выполнена в соответствии со всеми \nтребованиями (и за короткий срок!).\nДополнительное задание также выполнено." << endl;
			cout << "\nНо если это \033[1;5;35m" << b << "\033[0m not enought \033[1;5;35m" << b << "\033[0m , то что тогда \033[1; 5; 35m" << b << "\033[0m enought \033[1; 5; 35m" << b << "\033[0m " << endl;
			cout << "\n\n\t" << a << " Вы самый лучший лабник! " << a << endl;
			cout << "_______________________________________________________________" << endl;
			return;        //завершение программы
		}
		}
	} while (task != 0);
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