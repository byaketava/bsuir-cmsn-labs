#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void task1()
{
    double arr[100];
    int n, vvod;
    srand((unsigned int)time(NULL));
    printf(" Task 1:\n");
    printf(" ---------------------------------------------------------------------\n ");
    printf(" In a one-dimensional array consisting of n real elements, calculate:\n");
    printf("  - the sum of the negative elements of the array;\n");
    printf("  - the product of the array elements located between\n");
    printf("    the maximum and minimum elements.\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" Enter the number n (from 1 to 100) of elements in the array,\n");
    printf(" or enter '0' to initialize the number randomly: ");
    while (1)   
    {
        int numread = scanf_s("%i", &n);
        char nextchar = getchar();
        if (numread == 1 && (n <=100 && n >= 0) && (nextchar == '\n' || nextchar == ' '))
            break;
        if (nextchar != '\n')
        {
            while (getchar() != '\n')
                continue;
        }
        printf(" Incorrect input, try again\n");
    }
    if (n == 0)
    {
        n = rand() % 100 + 1;
    }
    printf(" n = %i\n", n);
    printf(" ---------------------------------------------------------------------\n");
    printf(" '1' if you want to enter the array by yourself\n");
    printf(" '0' if you want to initialize the array randomly\n");
    printf(" Select the action: ");
    while (1)   //проверка на ввод только 1 или 0 (для рандома)
    {
        int numread = scanf_s("%i", &vvod);
        char nextchar = getchar();
        if (numread == 1 && (vvod == 1 || vvod == 0) && (nextchar == '\n' || nextchar == ' '))
            break;
        if (nextchar != '\n')
        {
            while (getchar() != '\n')
                continue;
        }
        printf(" Incorrect input, try again\n");
    }
    printf(" ---------------------------------------------------------------------\n");
    if (vvod == 1)  //ввод массива с клавиатуры
    {
        printf(" Enter the elements of the array:\n");
        for (int i = 0; i < n; i++)
        {
            printf(" %i element: ", i+1);
            while (1)   //проверка ввода с клавиатуры
            {
                int numread = scanf_s("%lf", &arr[i]);
                char nextchar = getchar();
                if (numread == 1 && (nextchar == '\n' || nextchar == ' '))
                    break;
                if (nextchar != '\n')
                {
                    while (getchar() != '\n')
                        continue;
                }
                printf(" Incorrect input, try again\n");
                printf(" %i element: ", i+1);
            }
        }
        printf(" ---------------------------------------------------------------------\n");
    }
    else   //второй и единственный вариант рандомный ввод
    {
        for (int i = 0; i < n; i++)
        {
            arr[i] = (double) rand()/RAND_MAX * 20 - 10;
        }
    }
    printf(" The elements of the array:\n");    //вывод всех элементов массива на экран
    for (int i = 0; i < n; i++)
    {
        printf(" %i element = %.3lf\n", i+1, arr[i]);
    }
    printf(" ---------------------------------------------------------------------\n");
    double sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < 0)
            sum = sum + arr[i];
    } 
    printf(" The sum of the negative elements of the array is %.3lf\n", sum);
    printf(" ---------------------------------------------------------------------\n");
    int lmin=0;
    double min_start = arr[0];
    for (int i = 0; i < n; i++) //находим последний минимум
    {   
        if (arr[i] <= min_start)
        {
            min_start = arr[i];
            lmin = i;
        }
    }
    int fmax = 0;
    double max_start = arr[0];
    for (int i = 0; i < n; i++) //находим первый максимум
    {
        if (arr[i] > max_start)
        {
            max_start = arr[i];
            fmax = i;
        }
    }
    printf(" First maximum element is %d element: %.3f\n", fmax+1, arr[fmax]);
    printf(" Last minimum element is %d element: %.3f\n", lmin+1, arr[lmin]);
    printf("\n");
    double product = 1;
    if (fmax<lmin && (lmin-fmax)>1) 
    {
        int start = fmax + 1;
        for (int i = 1; i < lmin-fmax; i++)
        {
            printf(" %.3f * %.3f = ", product, arr[start]);
            product = product * arr[start];
            printf("%.3f\n", product);
            start = start + 1;
        }
        printf("\n The product of the array elements located between the maximum\n and minimum elements is: %.3f\v", product);
    }
    else if (fmax>lmin && (fmax-lmin)>1)
    {
        int start = fmax - 1;
        for (int i = 1; i < fmax-lmin; i++)
        {
            printf(" %.3f * %.3f = ", product, arr[start]);
            product = product * arr[start];
            printf("%.3f\n", product);
            start = start - 1;
        }
        printf("\n The product of the array elements located between the maximum\n and minimum elements is: %.3lf\v", product);
    }
    else
    {
        printf(" There are no elements between the first maximum and\n the last minimum elements\n");
    }
    printf(" ---------------------------------------------------------------------\n ");
}

void task2()
{
    int arr[100];
    int n, vvod;
    srand((unsigned int)time(NULL));
    printf(" Task 2:\n");
    printf(" ---------------------------------------------------------------------\n ");
    printf(" In an array of n elements, delete all even elements.\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" Enter the number n (from 1 to 100) of elements in the array,\n");
    printf(" or enter '0' to initialize the number randomly: ");
    while (1)   
    {
        int numread = scanf_s("%i", &n);
        char nextchar = getchar();
        if (numread == 1 && (n <= 100 && n >= 0) && (nextchar == '\n' || nextchar == ' '))
            break;
        if (nextchar != '\n')
        {
            while (getchar() != '\n')
                continue;
        }
        printf(" Incorrect input, try again\n");
    }
    if (n == 0)
    {
        n = rand() % 100 + 1;
    }
    printf(" n = %i\n", n);
    printf(" ---------------------------------------------------------------------\n");
    printf(" '1' if you want to enter the array by yourself\n");
    printf(" '0' if you want to initialize the array randomly\n");
    printf(" Select the action: ");
    while (1)   //проверка на ввод только 1 или 0 (для рандома)
    {
        int numread = scanf_s("%i", &vvod);
        char nextchar = getchar();
        if (numread == 1 && (vvod == 1 || vvod == 0) && (nextchar == '\n' || nextchar == ' '))
            break;
        if (nextchar != '\n')
        {
            while (getchar() != '\n')
                continue;
        }
        printf(" Incorrect input, try again\n");
    }
    printf(" ---------------------------------------------------------------------\n");
    if (vvod == 1)  //ввод массива с клавиатуры
    {
        printf(" Enter the elements of the array:\n");
        for (int i = 0; i < n; i++)
        {
            printf(" %i element: ", i + 1);
            while (1)   //проверка ввода с клавиатуры
            {
                int numread = scanf_s("%i", &arr[i]);
                char nextchar = getchar();
                if (numread == 1 && (nextchar == '\n' || nextchar == ' '))
                    break;
                if (nextchar != '\n')
                {
                    while (getchar() != '\n')
                        continue;
                }
                printf(" Incorrect input, try again\n");
                printf(" %i element: ", i + 1);
            }
        }
        printf(" ---------------------------------------------------------------------\n");
    }
    else   //второй и единственный вариант рандомный ввод
    {
        for (int i = 0; i < n; i++)
        {
            arr[i] = rand() % 201 - 100;
        }
    }
    printf(" The elements of the array:\n");    //вывод всех элементов массива на экран
    for (int i = 0; i < n; i++)
    {
        printf(" %i element = %i\n", i + 1, arr[i]);
    }
    printf(" ---------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        if (arr[i] % 2 == 0)
        {
            n--;
            for (int j = i; j < n; j++)
            {
                arr[j] = arr[j+1];
            }
            i--;
        }
    }
    printf(" New array:\n");
    if (n == 0)
    {
        printf(" An empty array.\n");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            printf(" %i element = %i\n", i + 1, arr[i]);
        }
    }
    printf(" ---------------------------------------------------------------------\n");
}

void task3()
{
    int arr[100];
    int n, vvod;
    srand((unsigned int)time(NULL));
    printf(" Task 3:\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" Given an array A of size n that does not contain zero elements. It is\n");
    printf(" necessary to get an array A, in which there are positive elements\n");
    printf(" first, and then negative ones. Do not use additional arrays.\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" Enter the number n (from 1 to 99) of elements in the array,\n");
    printf(" or enter '0' to initialize the number randomly: ");
    while (1)   
    {
        int numread = scanf_s("%i", &n);
        char nextchar = getchar();
        if (numread == 1 && (n <= 99 && n >= 0) && (nextchar == '\n' || nextchar == ' '))
            break;
        if (nextchar != '\n')
        {
            while (getchar() != '\n')
                continue;
        }
        printf(" Incorrect input, try again\n");
    }
    if (n == 0)
        n = rand() % 99 + 1;
    printf(" n = %i\n", n);
    printf(" ---------------------------------------------------------------------\n");
    printf(" '1' if you want to enter the array by yourself\n");
    printf(" '0' if you want to initialize the array randomly\n");
    printf(" Select the action: ");
    while (1)   //проверка на ввод только 1 или 0 (для рандома)
    {
        int numread = scanf_s("%i", &vvod);
        char nextchar = getchar();
        if (numread == 1 && (vvod == 1 || vvod == 0) && (nextchar == '\n' || nextchar == ' '))
            break;
        if (nextchar != '\n')
        {
            while (getchar() != '\n')
                continue;
        }
        printf(" Incorrect input, try again\n");
    }
    printf(" ---------------------------------------------------------------------\n");
    if (vvod == 1)  //ввод массива с клавиатуры
    {
        printf(" Enter the elements of the array:\n");
        for (int i = 0; i < n; i++)
        {
            printf(" %i element: ", i + 1);
            while (1)   //проверка ввода с клавиатуры
            {
                int numread = scanf_s("%i", &arr[i]);
                char nextchar = getchar();
                if (numread == 1 && arr[i]!=0 && (nextchar == '\n' || nextchar == ' '))
                    break;
                if (nextchar != '\n')
                {
                    while (getchar() != '\n')
                        continue;
                }
                printf(" Incorrect input, try again\n");
                printf(" %i element: ", i + 1);
            }
        }
        printf(" ---------------------------------------------------------------------\n");
    }
    else   //инициализация случайным образом от -100 до 100 не включая 0 
    {
        for (int i = 0; i < n; i++)
        {
            arr[i] = -100 + 101 * (rand() % 2) + rand() % 100;
        }
    }   
    printf(" The elements of the array:\n");    //вывод всех элементов массива на экран
    for (int i = 0; i < n; i++)
    {
        printf(" %i element = %i\n", i + 1, arr[i]);
    }
    printf(" ---------------------------------------------------------------------\n");
    int cnt=n;
    for (int i = 0; i < cnt; i++)
    {
        if (arr[i] < 0)
        {
            arr[n] = arr[i];
            for (int j = i; j < n; j++)
            {
                arr[j] = arr[j + 1];
            }
            i--;
            cnt--;
        }
    }
    printf(" New array:\n");
    for (int i = 0; i < n; i++)
    {
        printf(" %i element = %i\n", i + 1, arr[i]);
    }
    printf(" ---------------------------------------------------------------------\n");
}

int main()
{
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
