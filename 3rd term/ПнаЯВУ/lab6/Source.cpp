#include "Header.h"
#include "Matrix.h"
#include "queue.h"

void menu()
{
	Queue<Matrix> MQ;
	int task;
	do
	{
		cout << "�������� �������� \033[1;35m1 - 4\033[0m, ��� ������� \033[1;35m0\033[0m ��� ���������� ���������" << endl;
		cout << "1: \033[1;36m�������\033[0m ����� ������� � �������� � �������" << endl;
		cout << "2: \033[1;36m�������\033[0m ������ � ������� �������" << endl;
		cout << "3: \033[1;36m�����������\033[0m ��� ������� � �������" << endl;
		cout << "4: \033[1;36m��������\033[0m ������ � ������� �������" << endl;
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
				cout << "�������� ������� ��������..." << endl;
				MQ.dequeue();
				cout << "�������� ���������." << endl;
				cout << "_______________________________________________________________" << endl;
			}
			else
			{
				cout << "������� �����" << endl;
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
				cout << "������� �����" << endl;
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
				cout << "������� �����" << endl;
			}
			break;
		}
		case 0:
		{
			system("cls");
			char a = 2;
			char b = 4;
			cout << "_______________________________________________________________" << endl;
			cout << "\t\t\t\033[1;5;35m������\033[0m\n������������ ������ ��������� � ������������ �� ����� \n������������ (� �� �������� ����!).\n�������������� ������� ����� ���������." << endl;
			cout << "\n�� ���� ��� \033[1;5;35m" << b << "\033[0m not enought \033[1;5;35m" << b << "\033[0m , �� ��� ����� \033[1; 5; 35m" << b << "\033[0m enought \033[1; 5; 35m" << b << "\033[0m " << endl;
			cout << "\n\n\t" << a << " �� ����� ������ ������! " << a << endl;
			cout << "_______________________________________________________________" << endl;
			return;        //���������� ���������
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
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ������� ������ �����
		cout << "��,��, ��... �������� ���� ��!\n� ������ ������� \033[1;5;35m���������\033[0m:" << endl;
	}
}