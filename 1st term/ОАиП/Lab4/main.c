#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void task1();
void task2();
void task3();
void text_task_1(void); 
void text_task_2(void); 
void text_task_3(void);
int check();
void rand_1_to_100(int *size);
void prompt_1_or_0(int *vvod);
void entering_an_array(int vvod, int n, int m, int* arr);
void show_the_array(int n, int m, int* arr);
void task_1_1(int n, int m, int* array);
void task_1_2(int n, int m, int* array);
void task_2(int n, int m, int* array);
void task_3(int n, int* array);

int main()
{
    srand((unsigned int)time(NULL));
    int task;
    do
    {
        printf(" Enter the number of the task (from 1 to 3), or enter '0' to end the program\n");
        while (1)   //проверка на ввод только 1, 2, 3 или 0 
        {
            int numread = scanf_s("%d", &task);
            char nextchar = getchar();
            if (numread == 1 && (task == 3 || task == 2 || task == 1 || task == 0) && (nextchar == '\n' || nextchar == ' '))
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
            task1();
            break;
        case 2:
            system("cls");  //чистим экран
            task2();
            break;
        case 3:
            system("cls");  //чистим экран
            task3();
            break;
        case 0:
            exit(0);        //завершение программы
        }
    } while (task != 0);    //даёт возможность выбора другой задачи или завершения программы
}

void task1()
{
    int arr[100][100];
    int n, m, vvod;
    text_task_1();
    n = check();
    printf(" m: ");
    m = check();
    rand_1_to_100(&n);
    rand_1_to_100(&m);
    printf("\n n = %i\n", n);
    printf(" m = %i\n", m);
    prompt_1_or_0(&vvod);
    entering_an_array(vvod, n, m, &arr[0][0]);
    show_the_array(n, m, &arr[0][0]);
    task_1_1(n, m, &arr[0][0]);
    task_1_2(n, m, &arr[0][0]);
}
void task2()
{
    int arr[100][100];
    int n, m, vvod;
    
    text_task_2();
    n = check();
    printf(" m: ");
    m = check();
    rand_1_to_100(&n);
    rand_1_to_100(&m);
    printf("\n n = %i\n", n);
    printf(" m = %i\n", m);
    prompt_1_or_0(&vvod);
    entering_an_array(vvod, n, m, &arr[0][0]);
    show_the_array(n, m, &arr[0][0]);
    task_2(n, m, &arr[0][0]);
}
void task3()
{
    int arr[100][100];
    int n, vvod;
    text_task_3();
    n = check();
    rand_1_to_100(&n);
    printf("\n n = %i\n", n);
    prompt_1_or_0(&vvod);
    entering_an_array(vvod, n, n, &arr[0][0]);
    show_the_array(n, n, &arr[0][0]);
    task_3(n, &arr[0][0]);
}

void text_task_1(void)
{
    printf(" Task 1:\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" An integer rectangular matrix is given. Determine:\n");
    printf("  - the number of columns containing at least one null element;\n");
    printf("  - the number of the row containing the longest series of\n");
    printf("    identical elements.\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" Enter the size n and m (from 1 to 100) of elements in the array n x m,\n");// сделать чтобы при n равном нулю обрывалось
    printf(" or enter '0' to initialize the number randomly:\n");
    printf(" n: ");
}
void text_task_2(void)
{
    printf(" Task 2:\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" Check if there is at least one row in the matrix containing an element\n");
    printf(" equal to zero and find its number.\n");
    printf(" Reduce all elements of the matrix by the value of the first element\n");
    printf(" of the found row.\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" Enter the size n and m (from 1 to 100) of elements in the array n x m,\n");// сделать чтобы при n равном нулю обрывалось
    printf(" or enter '0' to initialize the number randomly:\n");
    printf(" n: ");
}
void text_task_3(void)
{
    printf(" Task 3:\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" In a square matrix of size NxN, find the minimum even element\n");
    printf(" in the 3rd region.\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" Enter the size n (from 1 to 100) of elements in the array n x n,\n");// сделать чтобы при n равном нулю обрывалось
    printf(" or enter '0' to initialize the number randomly: ");
}
int check()
{
    int size;
    while (1)
    {
        int numread = scanf_s("%i", &size);
        char nextchar = getchar();
        if (numread == 1 && (size <= 100 && size >= 0) && (nextchar == '\n' || nextchar == ' '))
            break;
        if (nextchar != '\n')
        {
            while (getchar() != '\n')
                continue;
        }
        printf(" Incorrect input, try again\n");
    }
    return size;
}
void prompt_1_or_0(int *vvod)
{
    printf(" ---------------------------------------------------------------------\n");
    printf(" '1' if you want to enter the array by yourself\n");
    printf(" '0' if you want to initialize the array randomly\n");
    printf(" Select the action: ");
    while (1)   //проверка на ввод только 1 или 0 (для рандома)
    {
        int numread = scanf_s("%i", &*vvod);
        char nextchar = getchar();
        if (numread == 1 && (*vvod == 1 || *vvod == 0) && (nextchar == '\n' || nextchar == ' '))
            break;
        if (nextchar != '\n')
        {
            while (getchar() != '\n')
                continue;
        }
        printf(" Incorrect input, try again\n");
    }
    printf(" ---------------------------------------------------------------------\n");
}
void rand_1_to_100(int *size)
{
    if (*size == 0)
    {
        *size = rand() % 100 + 1;
    }
}
void entering_an_array(int vvod, int n, int m, int* array)
{
    if (vvod == 1)  //ввод массива с клавиатуры
    {
        printf(" Enter the elements of the array:\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf(" [%i][%i] element: ", i + 1, j + 1);
                while (1)   //проверка ввода с клавиатуры
                {
                    int numread = scanf_s("%i", &array[i * m + j]);
                    char nextchar = getchar();
                    if (numread == 1 && (nextchar == '\n' || nextchar == ' '))
                        break;
                    if (nextchar != '\n')
                    {
                        while (getchar() != '\n')
                            continue;
                    }
                    printf(" Incorrect input, try again\n");
                    printf(" [%i][%i] element: ", i + 1, j + 1);
                }
            }
            printf("\n");
        }
        printf(" ---------------------------------------------------------------------\n");
    }
    else   //второй и единственный вариант рандомный ввод
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                array[i * m + j] = rand() % 201 - 100;
            }
        }
    }
}
void show_the_array(int n, int m, int *array)
{
    printf(" The elements of the array:\n");    //вывод всех элементов массива на экран
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (array[i*m+j] >= 0)
                printf("  %i\t", array[i * m + j]);
            else
                printf(" %i\t", array[i * m + j]);
        }
        printf("\n\n");
    }
    printf(" ---------------------------------------------------------------------\n");
}
void task_1_1(int n, int m, int*array)
{
    int num_of_columns = 0, memo, column[100], k = 0;
    for (int j = 0; j < m; j++)
    {
        memo = num_of_columns;//memo для сравнения, чтобы количество строк считалось через нам оф каломнс
        for (int i = 0; i < n; i++)
        {
            if (array[i*m+j] == 0)
            {
                num_of_columns++;
                column[k] = j;
                k;
            }
            if (memo != num_of_columns)
                break;
        }
    }
    printf(" The null elements of the array:\n");    //вывод всех элементов массива на экран с выделением нуля
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (array[i * m + j] > 0)
                printf("  %i\t", array[i * m + j]);
            else if (array[i * m + j] == 0)
                printf("  \033[1;35;5m%i\033[0m\t", array[i * m + j]);   //выделить цветом нули
            else
                - printf(" %i\t", array[i * m + j]);
        }
        printf("\n\n");
    }
    if (num_of_columns == 0)
    {
        printf(" There are %i column(-s) containing at least one null element:\n", num_of_columns);
        for (int i = 0; i < k; i++)
            printf(" %i ", column[i] + 1);
    }
    else
    {
        printf(" There are %i column(-s) containing at least one null element:\n", num_of_columns); //вывести номера колонок
        for (int i = 0; i < k; i++)
            printf(" %i ", column[i] + 1);
        printf(" column(-s)\n");
    }
    printf(" ---------------------------------------------------------------------\n");
}
void task_1_2(int n, int m, int*array)
{
    int dlina, memory = 1, row = 0;
    for (int i = 0; i < n; i++)
    {
        dlina = 1;
        for (int j = 1; j < m; j++)
        {
            if (array[i*m+j] == array[i*m+j-1])
            {
                dlina++;
                if (dlina > memory)
                {
                    memory = dlina;
                    row = i;
                }
            }
            else
            {
                dlina = 1;
            }
        }
    }
    if (memory == 1)
        printf(" There are no series longer than 1 element in it.\n");
    else
        printf(" The %i row containing the longest series of identical elements.\n", row + 1);
}
void task_2 (int n, int m, int*array)
{
    int num_of_row = 0, row = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (array[i*m+j] == 0)
            {
                num_of_row++;
                row = i;
            }
        }
        if (num_of_row == 1)
            break;
    }

    if (num_of_row != 0)
    {
        printf(" The row with the null element:\n");    //вывод строки массива на экран с выделением нуля
        for (int j = 0; j < m; j++)
        {
            if (array[row*m+j] > 0)
                printf("  %i\t", array[row*m+j]);
            else if (array[row*m+j] == 0)
                printf("  \033[1;35;5m%i\033[0m\t", array[row*m+j]);   //выделить цветом нули
            else
                printf(" %i\t", array[row * m + j]);
        }
        printf("\n There is at least 1 row containing at least 1 null element: %i row\n", row + 1); //вывести номер строки
        printf(" ---------------------------------------------------------------------\n");
        printf(" The elements of the array:\n");    //вывод новых элементов массива на экран
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (array[i*m+j] >= 0)
                    printf(" %3i\t", array[i * m + j] - array[row*m]);
                else
                    printf(" %3i\t", array[i * m + j] - array[row*m]);
            }
            printf("\n\n");
        }
    }
    if (num_of_row == 0)
    {
        printf(" There are no rows containing at least one null element\n\n");
    }
}
void task_3(int n, int* array)
{
    int min_even = 101;
    for (int i = n / 2; i < n; i++)
    {
        for (int j = i; j >= n - i - 1; j--)
        {
            if ((array[i*n+j] % 2 == 0) && (array[i * n + j] <= min_even))
            {
                min_even = array[i * n + j];
            }
        }
    }

    printf(" The elements of the array:\n");    //вывод всех элементов массива с областью на экран
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i >= n / 2 && i < n && j <= i && j >= n - i - 1)
            {
                if (array[i * n + j] >= 0)
                {
                    if (array[i * n + j] == min_even)
                        printf("  \033[1;5;32m%i\033[0m\t", array[i * n + j]);
                    else
                        printf("  \033[1;35m%i\033[0m\t", array[i * n + j]);
                }
                else
                {
                    if (array[i * n + j] == min_even)
                        printf(" \033[1;5;32m%i\033[0m\t", array[i * n + j]);
                    else
                        printf(" \033[1;35m%i\033[0m\t", array[i * n + j]);
                }
            }
            else
            {
                if (array[i * n + j] >= 0)
                    printf("  %i\t", array[i * n + j]);
                else
                    printf(" %i\t", array[i * n + j]);
            }
        }
        printf("\n\n");
    }

    if (min_even == 101)
    {
        printf(" There is no even elements in the 3rd region\n");
    }
    else
    {
        printf(" The minimum even element in the 3rd region is %i\n", min_even);
    }
}