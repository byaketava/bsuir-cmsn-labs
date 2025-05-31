#include <iostream>
#include <string>

void checking(int& num, int x, int y);

int main()
{
    int start;
    do
    {
        std::cout << "1. Start\n2. Stop" << std::endl;
        checking(start, 1, 2);
        bool check = true;
        int count = 0, temp = 0;
        int size;
        std::string word;
        std::string final;

        std::cout << "\nEnter sentense or char combination:" << std::endl;
        getline(std::cin, word);                                                // ���� ������ ��� ����������
        size = word.size();                                                     // ����� ������
        std::cout << "\nEnter size of step:" << std::endl;                        // ����� ����
        int step;
        checking(step, 2, 10);
        char** shifr{ new char* [step] {} };                                    // ������ ��� ����������
        for (int i{}; i < step; i++)
        {
            shifr[i] = new char[size] {};
        }

        std::cout << "\nSelect option:" << std::endl;
        std::cout << "1. Shifr\n2. Deshifr" << std::endl;
        int task;
        checking(task, 1, 2);                                                   // �������� ��� ����������
        switch (task)
        {
        case 1:
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < step; j++)
                {
                    if (temp == j)
                    {
                        shifr[j][i] = word[count];                              // ���������� �������
                    }
                    else
                    {
                        shifr[j][i] = '*';
                    }
                }
                count++;                                                        // ����� �� �������
                if (temp == step - 1)
                {
                    check = false;
                }
                if (temp == 0)
                {
                    check = true;
                }
                if (check == true)                                              // ���� temp = 0
                {
                    temp++;
                }
                if (check == false)                                             // ���� ����� ���� ��������� temp
                {
                    temp--;
                }
            }
            // ����� ������������ �������
            std::cout << std::endl;
            for (int i = 0; i < step; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    std::cout << shifr[i][j];
                }
                std::cout << std::endl;
            }
            // ���������� ������ ������ ��������
            for (int i = 0; i < step; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (shifr[i][j] != '*')
                    {
                        final.append(1, shifr[i][j]);
                    }
                }
            }
            std::cout << std::endl << final << std::endl;
            std::cout << std::endl;
            break;
        case 2:
            // ���������� ������� �������� � ����������� �������
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < step; j++)
                {
                    if (temp == j)
                    {
                        shifr[j][i] = '-';
                    }
                    else
                    {
                        shifr[j][i] = '*';
                    }
                }
                if (temp == step - 1)
                {
                    check = false;
                }
                if (temp == 0)
                {
                    check = true;
                }
                if (check == true)
                {
                    temp++;
                }
                if (check == false)
                {
                    temp--;
                }
            }
            // ������� �� ����� ������ �����, ������������� �� �������, �������
            // �� �� �������, ��� ��� ��������
            for (int i = 0; i < step; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (shifr[i][j] == '-')
                    {
                        shifr[i][j] = word[count];
                        count++;
                    }
                }
            }
            // ����� ������������ �������
            std::cout << std::endl;
            for (int i = 0; i < step; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    std::cout << shifr[i][j];
                }
                std::cout << std::endl;
            }
            // ����������� ��������������� ������ ��������
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < step; j++)
                {
                    if (shifr[j][i] != '*')
                    {
                        final.append(1, shifr[j][i]);
                    }
                }
            }
            std::cout << std::endl << final << std::endl;
            std::cout << std::endl;
            break;
        }
    } while (start != 2);

    return 0;
}

void checking(int& num, int x, int y)
{
    while (1)
    {
        std::cin >> num;
        if (!std::cin.fail() && num >= x && num <= y && std::cin.get() == '\n')
            break;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ������� ������ �����
        std::cout << "��,��, ��... �������� ���� ��!\n� ������ ������� \033[1;5;35m���������\033[0m:" << std::endl;
    }
}