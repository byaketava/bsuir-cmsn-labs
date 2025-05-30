#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void task1(); 
void task2(); 
void dialog_box();

int main()
{
    int task;
    srand((unsigned int)time(NULL));
    do
    {
        printf(" Enter the number of the task (\033[38;5;141m1\033[0m or \033[38;5;141m2\033[0m), or enter \033[38;5;141m0\033[0m to end the program\n");
        printf(" You can also enter \033[38;5;141m10\033[0m after checking the lab to open the \033[38;5;141mdialog box\033[0m\n ");
        while (1)   //проверка на ввод только 1, 2 или 0 
        {
            int numread = scanf_s("%d", &task);
            char nextchar = getchar();
            if (numread == 1 && (task == 2 || task == 1 || task == 0 || task == 10) && (nextchar == '\n' || nextchar == ' '))
                break;
            if (nextchar != '\n')
            {
                while (getchar() != '\n')
                    continue;
            }
            printf(" Don't do this, please don't break my code!\n ");
        }
        switch (task)
        {
        case 1:
            system("cls");  //чистим экран
            task1();
            break;
        case 2:
            system("cls");  //чистим экран
            task2();
            break; 
        case 10:
            system("cls");  //чистим экран
            dialog_box();
            break;
        case 0:
            exit(0);        //завершение программы
        }
    } while (task != 0);    //даёт возможность выбора другой задачи или завершения программы
}
