#include "Header.h"
#include "Matrix.h"
#include "queue.h"
#include "Files.h"
#include <sstream>

void menu()
{
	Queue<Matrix> MQ;
	File<Matrix> file("info.txt");
	File<Matrix> text("text.txt");
	int task;
	do
	{
		cout << "�������� �������� \033[1;35m1 - 4\033[0m, ��� ������� \033[1;35m0\033[0m ��� ���������� ���������" << endl;
		cout << "1: \033[1;36m�������\033[0m ������� � �������� � ������� (� � ����)" << endl;
		cout << "2: \033[1;36m�������\033[0m ������ � ������� �������" << endl;
		cout << "3: \033[1;36m�����������\033[0m ��� ������� � �������" << endl;
		cout << "4: \033[1;36m���������\033[0m ���������� �����" << endl;
		cout << "5: \033[1;36m�������\033[0m k-��� ������� � �����" << endl;
		cout << "6: \033[1;36m��������������\033[0m ������" << endl;
		cout << "_______________________________________________________________" << endl;
		check(task, 0, 6);
		switch (task)
		{
		case 1:
		{
			system("cls");
			cin >> MQ;
			int a = 0;
			cout << "������ �������� ������� ������� � ����?\n1: ��\n2: ���" << endl;
			check(a, 1, 2);
			if (a == 1)
			{
				file >> MQ;
				cout << "������� �������� � ����!\n" << endl;
			}
			else
			{
				cout << "�����.\n" << endl;
			}
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
			cout << file << endl;
			cout << "������� �� ����� ���������!\n" << endl;
			break;
		}
		case 5:
		{
			system("cls");
			cout << file << endl;
			int k;
			cout << "\n������� ����� k �������, ������� ������ ������� �� �����:\n" << endl;
			check(k, 0, 50);
			file.RemoveKMatrix(k);
			cout << file << endl;
			break;
		}
		case 6:
		{
			system("cls");
			
			std::string tempFilename = "textTmp.txt";
			std::string Filename = "text.txt";

			std::ifstream inputFile(Filename);
			if (!inputFile.is_open())
			{
				cout << "������ �������� �����" << endl;
				return;
			}
			std::ofstream tempFile(tempFilename);
			if (!tempFile.is_open())
			{
				inputFile.close();
				cout << "������ �������� �����" << endl;
				return;
			}

			std::string line;

			while (std::getline(inputFile, line)) 
			{
				std::string resultLine;
				int currLength = 0;
				std::string word;

				std::istringstream iss(line);
				char c;
				iss.get(c);
				if (c == '\t')
				{
					resultLine = c;
					currLength += 8;
				}
				else
				{
					iss.putback(c);
				}

				while (iss >> word) 
				{
					if (resultLine.empty()) 
					{
						resultLine = word;
						currLength = word.length();
					}
					else if (currLength + word.length() + 1 <= 80) 
					{
						resultLine += " " + word;
						currLength += word.length() + 1;
					}
					else 
					{
						tempFile << resultLine << std::endl;
						resultLine = word;
						currLength = word.length();
					}
				}

				if (!resultLine.empty()) 
				{
					tempFile << resultLine << std::endl;
				}
				else 
				{
					tempFile << std::endl;
				}
			}

			inputFile.close();
			tempFile.close();

			if (std::remove(Filename.c_str()) != 0)
			{
				cout << "������ �������� ����� " << Filename << endl;
				return;
			}
			if (std::rename(tempFilename.c_str(), Filename.c_str()) != 0)
			{
				cout << "������ ���������������� ����� " << endl;
			}
			
			cout << "\n����� ������� ��������������!\n" << endl;
			
			cout << text << endl;
			break;
		}
		case 0:
		{
			system("cls");
			char a = 2;
			char b = 4;
			cout << "_______________________________________________________________" << endl;
			cout << "\t\t\t\033[1;5;35m������\033[0m\n������������ ������ ��������� � ������������ �� ����� \n������������.\n" << endl;
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