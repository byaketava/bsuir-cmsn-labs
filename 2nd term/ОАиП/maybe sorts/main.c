#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void input_array(int n, int* mas);
void output_array(int n, int* mas);
void sort1();
void shell_sort(int n, int* mas);
void insertion_sort(int n, int* mas); void insertion_sort_stroki(int n, int m, int** mas);
void sort2();
void sort(int* mas, int size);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  

int main()
{
    int task;
    srand((unsigned int)time(NULL));
    do
    {
        printf(" 1. Shell sort\n 2. Insertion sort\n 3. \n");
        printf(" Enter the number of the sort (\033[38;5;141m1\033[0m or \033[38;5;141m2\033[0m), or enter \033[38;5;141m0\033[0m to end the program\n ");
        while (1)   //проверка на ввод только 1, 2 или 0 
        {
            int numread = scanf_s("%d", &task);
            char nextchar = getchar();
            if (numread == 1 && (task == 1 || task == 2 || task == 0) && (nextchar == '\n' || nextchar == ' '))
                break;
            if (nextchar != '\n')
            {
                while (getchar() != '\n')
                    continue;
            }
            printf(" Incorrect input, try again\n");
        }
        switch (task)
        {
        case 1:
            system("cls");  //чистим экран
            sort1();
            break; 
        case 2:
            system("cls");  //чистим экран
            sort2();
            break;      
        case 0:
            exit(0);        //завершение программы
        }
    } while (task != 0);    //даёт возможность выбора другой задачи или завершения программы
}

void input_array(int n, int* mas)
{
    for (int i = 0; i < n; i++)
    {
        mas[i] = rand() % 101 - 50;
    }
}
void output_array(int n, int* mas)
{
    for (int i = 0; i < n; i++)
    {
        printf(" %5i", mas[i]);
    }
    printf("\n");
}

void sort1()
{
    int n = rand() % 25 + 1;
    int* mas = NULL;
    mas = (int*)calloc(n, sizeof(int));
    input_array(n, mas);
    printf(" The number of elements in the array is \033[38;5;141m%i\033[0m\n", n);
    printf(" _____________________________________________________________________\n");
    printf(" An array:\n");
    output_array(n, mas);
    printf(" _____________________________________________________________________\n");
    printf("\n Sorted array:\n");
    shell_sort(n, mas);
    output_array(n, mas);
    printf(" _____________________________________________________________________\n");
}
void sort2()
{
    int n = rand() % 25 + 1;
    int* mas = NULL;
    mas = (int*)calloc(n, sizeof(int));
    input_array(n, mas);
    printf(" The number of elements in the array is \033[38;5;141m%i\033[0m\n", n);
    printf(" _____________________________________________________________________\n");
    printf(" An array:\n");
    output_array(n, mas);
    printf(" _____________________________________________________________________\n");
    printf("\n Sorted array:\n");
    sort(mas, n);
    output_array(n, mas);
    printf(" _____________________________________________________________________\n");
}
