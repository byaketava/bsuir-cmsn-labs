#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//общие
void task1();
void task2();
void task3();

void text_task_1(int n); 
void text_task_2(void); 
void text_task_3(void);

void check(int* num); 

void rand_1_to_100(int* size); 
void rand_1_to_25(int* size);

//1 задача
void input_array_1(int n, int *arr);
void output_array_1(int n, int* arr);
void task_1(int* n, int*arr);

//2 задача
int** vyd_pam(int n);
void vood(int** mas, int n);
void vyvod(int** mas, int n);
void searchLine(int** mas, int n, int* min_ind);
int** deleteLine(int** mas, int* n, int k);

//3 задача и костыль в виде доп задания по раскраске
int** vydelenie_pamyati(int* n, int* dlina_strok);
void vvod_mas(int** mas, int n, int* dlina_strok);
void vyvod_massiva(int** mas, int n, int* dlina_strok, int end_i, int end_j, int begin_i, int begin_j, int memory);
void kostyl(int flag, int *end_i, int *end_j, int memory, int* begin_i, int* begin_j, int* dlina_strok, int *temp);
void task_3(int n, int** mas, int* memory, int* dlina_strok, int* end_i, int* end_j, int* flag);

//ещё доп...
void HB();

int main()
{
    int task;
    srand((unsigned int)time(NULL));

    do
    {
        printf(" Enter the number of the task (from 1 to 3), or enter '0' to end the program\n");
        while (1)   //проверка на ввод только 1, 2, 3 или 0 
        {
            int numread = scanf_s("%d", &task);
            char nextchar = getchar();
            if (numread == 1 && (task == 3 || task == 2 || task == 1 || task == 0 || task == 22) && (nextchar == '\n' || nextchar == ' '))
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
        case 22:
            system("cls");  //чистим экран
            HB();
            break;
        }
    } while (task != 0);    //даёт возможность выбора другой задачи или завершения программы
}
void task1()
{
    int* array = NULL;
    int n; 
    rand_1_to_25(&n);
    text_task_1(n);
    array = (int*)malloc(n * sizeof(int));
    input_array_1(n, array);
    output_array_1(n, array);
    task_1(&n, array);
}
void task2()
{
    int** mas = NULL;
    int min_ind = 0;
    int  n;
    rand_1_to_25(&n);
    text_task_2();
    mas = vyd_pam(n);
    vood(mas, n);
    printf(" The array:\n\n");
    vyvod(mas,  n);
    printf(" ---------------------------------------------------------------------\n");
    searchLine(mas, n, &min_ind);
    mas = deleteLine(mas, &n, min_ind);
    printf(" ---------------------------------------------------------------------\n");
    if(n==1)
        printf(" The new array:\n\n");
    else
        printf(" There are no more rows in the array:\n\n");
    vyvod(mas, n);
    
}
void task3()
{
    int flag=0;
    int begin_j=0;
    int end_i = 0, end_j = 0;
    int memory = 0;
    int n;
    rand_1_to_25(&n);
    int * dlina_strok = (int*)calloc(n, sizeof(int));
    text_task_3();
    int** mas = NULL;
    mas=vydelenie_pamyati(&n, dlina_strok);
    vvod_mas(mas, n, dlina_strok);
    task_3( n,  mas, &memory, dlina_strok, &end_i,&end_j, &flag);
    int temp = end_j;
    int begin_i = end_i;
    kostyl(flag, &end_i, &end_j, memory, &begin_i, &begin_j, dlina_strok, &temp);
    vyvod_massiva(mas, n, dlina_strok, end_i, end_j, begin_i, begin_j, memory);
    printf(" ---------------------------------------------------------------------\n");
    if (memory == 1)
        printf(" There are no series longer than 1 element in it.\n\n");
    else
        printf(" The longest possible sequence of positive numbers includes %i elements\n\n", memory);
}

void text_task_1(int n)
{
    printf(" Task 1:\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" -Fill the array with random numbers;\n");
    printf(" -Remove all elements with an even value from the array.\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" The number of elements in the array is: %i\n", n);
}
void text_task_2(void)
{
    printf(" Task 2:\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" In a two - dimensional array of natural numbers (the number of numbers\n");
    printf(" in a row can be different, the last number is 0)\n");
    printf("  - delete the row with the minimum sum of elements\n");
    printf("   (do not change the order of the remaining rows).\n");
    printf(" ---------------------------------------------------------------------\n");
}
void text_task_3(void)
{
    printf(" Task 3:\n");
    printf(" ---------------------------------------------------------------------\n");
    printf(" A two-dimensional array of nonzero integers is given:\n");
    printf("  - determine the longest possible sequence of positive numbers.\n");
    printf(" The array is viewed line by line from top to bottom, and in each\n");
    printf(" row - from left to right. Saving the sign when switching to a new\n");
    printf(" line is also taken into account.\n");
    printf(" ---------------------------------------------------------------------\n");
}
void check(int*num)
{
    while (1)
    {
        int numread = scanf_s("%i", num);
        char nextchar = getchar();
        if (numread == 1 && (*num <= 100 && *num >= 0) && (nextchar == '\n' || nextchar == ' '))
            break;
        if (nextchar != '\n')
        {
            while (getchar() != '\n')
                continue;
        }
        printf(" Incorrect input, try again\n");
    }
}
void rand_1_to_100(int* size)
{
    if (*size == 0)
    {
        *size = rand() % 100 + 1;
    }
}
void rand_1_to_25(int* size)
{
        *size = rand() % 25 + 1;
}
void input_array_1(int n,int *arr)

{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 201 -100;
    }
}
void output_array_1(int n, int* arr)
{
    printf(" ---------------------------------------------------------------------\n");
    printf(" Elements of the array:\n");
    for (int i = 0; i < n; i++)
    {
        if (arr[i]%2==0)
        printf(" \033[1;32;5m%i\033[0m", arr[i]);
        else
        printf(" %i", arr[i]);
    }
    printf("\n");
}
void task_1(int *n, int*arr)
{
    int flag = 0;
    for (int i = 0; i < *n; i++)
    {
        if (arr[i] % 2 == 0)
        {
            flag++;
            for (int k = i; k < *n - 1; k++)
            {
                arr[k] = arr[k + 1];
            }
            (*n)--;
            if (arr != NULL)
            {
                int* copy = (int*)realloc(arr, *n*sizeof(int));
                if (copy != NULL)
                {
                    arr = copy;
                }
            }
            i--;
        } 
    }
    printf(" ---------------------------------------------------------------------\n");
    if (*n == 0)
    {
        printf(" An array containing no elements was received\n");
    }
    else
    {
        if (flag == 0)
            printf(" There are no even elements in the array\n");
        printf(" Elements of the array after deleting elements:\n");
        for (int i = 0; i < *n; i++)
        {
            printf(" %i", arr[i]);
        }
        printf("\n\n");
    }
}




int** vyd_pam(int n)
{
    int m;
    int** mas = (int**)calloc(n, sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        rand_1_to_25(&m);
        mas[i] = (int*)malloc((m+1) * sizeof(int));
        mas[i][m] = '\0';
    }
    return mas;
}
void vood(int ** mas, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; mas[i][j] != '\0'; j++)
        {
            mas[i][j] = rand() % 100 + 1;
        }
    }
}
void vyvod(int** mas, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(" \033[3;32m%i row:\033[0m   ", i+1);
        for (int j = 0; mas[i][j] != '\0'; j++)
            printf(" %i\t", mas[i][j]);
        printf("\n\n");
    }
}


void vyvod_massiva(int** mas, int n, int* dlina_strok, int end_i, int end_j, int begin_i, int begin_j, int memory)
{
    printf(" The array:\n\n");
    for (int i = 0; i < n; i++)                             
    {
        printf(" \033[32;3m%i row:\033[0m   ", i + 1);
        for (int j = 0; j < *(dlina_strok + i); j++)        
        {
            if (((i >= begin_i) && (j >= begin_j) && (i <= end_i) && (j <= end_j) && (memory != 1)) ||
                (i == begin_i && j == begin_j && (memory != 1)) || (i == end_i && j == end_j && (memory != 1)))
                printf(" \033[1;35m%3d\033[0m\t", mas[i][j]);
            else
                printf(" %3d\t", mas[i][j]);
        }
        printf("\n\n");
    }
}
int** vydelenie_pamyati(int* n, int* dlina_strok)
{
    int m;                                                  
    int** mas = (int**)calloc((*n), sizeof(int*));
    for (int i = 0; i < *n; i++)                           
    {
        rand_1_to_25(&m);
        mas[i] = (int*)calloc(m, sizeof(int));              //выделение памяти на строку
        *(dlina_strok + i) = m;                             //занесение длины i-ой строки в массив длин строк
    }
    return mas;
}
void vvod_mas(int** mas, int n, int* dlina_strok)          
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < *(dlina_strok + i); j++)
        {
            mas[i][j] = -100 + 101 * (rand() % 2) + rand() % 100;
        }
    }
}
void task_3(int n, int** mas, int* memory, int* dlina_strok,int*end_i, int*end_j, int * flag)
{
    int dlina;
    *memory = 1; dlina = 1;
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < dlina_strok[i]; j++)
        {
            if ((mas[i][j] == mas[i][j - 1]) && (mas[i][j]>0))
            {
                dlina++;
                if (dlina > *memory)
                {
                    *memory = dlina; 
                    *end_i = i;
                    *end_j = j;
                }
            }
            else
            {
                dlina = 1;
            }
            if (j == (dlina_strok[i] - 1) && (i != (n - 1)))
            {
                if ((mas[i][dlina_strok[i] - 1] == mas[i + 1][0]) && (mas[i+1][0] > 0))
                {
                    dlina++;
                    if (dlina > *memory)
                    {
                        *memory = dlina;
                        *end_i = i+1;
                        *end_j = 0;
                        (* flag)++;
                    }
                }
                else
                {
                    dlina = 1;
                }
            }
            
        }
    }
     (* end_j)++;
     (* end_i)++;
   
}
void kostyl(int flag,int *end_i, int *end_j, int memory, int* begin_i, int* begin_j, int* dlina_strok, int*temp)
{
    if (memory > *temp)
    {
        (*begin_i)--;
        memory = memory - *temp;
        *temp = dlina_strok[(*begin_i) - 1];
        kostyl(flag, end_i, end_j, memory, begin_i, begin_j, dlina_strok, temp);
    }
    else
    {
        (*begin_i) --;
        if (flag != 0)
            (*begin_j) = dlina_strok[(*begin_i)] - memory;
        else
            (*begin_j) = (*end_j) - memory;
        (*end_i)--;
        (*end_j)--;
    }
}



void searchLine(int** mas, int n, int* min_ind)
{
    int sum = 0, min_sum = 5000;
    printf(" The sum of elements:\n\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; mas[i][j] != 0; j++)
        {
            sum += mas[i][j];
            
        }
        printf(" in the \033[1;32m%i\033[0m row is \033[1;35m%i\033[0m\n", i+1, sum);
        if (sum < min_sum)
        {
            min_sum = sum;
            *min_ind = i;
        }
        sum = 0;
    }
    printf(" ---------------------------------------------------------------------\n");
    printf(" The \033[1;32m%i\033[0m row has the minimum sum of the elements:\n", (* min_ind)+1);
    int flag = 0;
    for (int j = 0; mas[*min_ind][j+1] != 0; j++)
    {
        printf(" %i +", mas[*min_ind][j]);
        flag++;
    }
    printf(" %i = \033[1;35m%i\033[0m\n", mas[*min_ind][flag], min_sum);
}
int** deleteLine(int** mas, int* n, int k)
{
    for (int i = k; i < *n - 1 ; i++)
    {
        *(mas + i) = *(mas + i + 1);
    }
    (*n)--;
    return mas;
}

void HB()
{
    char mas[17][40] =
    {
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ','*',' ',' ','*',' ',' ','*','*',' ',' ','*','*',' ',' ','*',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ','*',' ','*',' ','*',' ','*',' ','*',' ','*',' ','*',' ','*',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*','*','*',' ','*','*','*',' ','*','*','*',' ','*','*','*',' ','*','*','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ','*',' ','*',' ','*',' ','*',' ',' ',' ','*',' ',' ',' ',' ',' ','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','*',' ','*',' ','*',' ','*',' ','*',' ',' ',' ','*',' ',' ',' ','*','*',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ','*','*',' ',' ','*','*','*',' ','*','*',' ',' ','*','*','*',' ','*',' ','*',' ','*','*',' ',' ',' ','*',' ',' ','*',' ','*',' ',' ','*',' ',' ',' '},
        {' ',' ',' ','*',' ','*',' ',' ','*',' ',' ','*',' ','*',' ',' ','*',' ',' ','*',' ','*',' ','*',' ','*',' ','*',' ','*',' ','*',' ','*',' ',' ','*',' ',' ',' '},
        {' ',' ',' ','*','*',' ',' ',' ','*',' ',' ','*','*',' ',' ',' ','*',' ',' ','*','*','*',' ','*',' ','*',' ','*','*','*',' ','*','*','*',' ',' ','*',' ',' ',' '},
        {' ',' ',' ','*',' ','*',' ',' ','*',' ',' ','*',' ','*',' ',' ','*',' ',' ','*',' ','*',' ','*',' ','*',' ','*',' ','*',' ',' ',' ','*',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ','*','*','*',' ','*','*','*',' ','*',' ','*',' ',' ','*',' ',' ','*',' ','*',' ','*','*',' ',' ','*',' ','*',' ','*','*',' ',' ',' ','*',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
        {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '}
    };


    for (int i = 0; i < 14; i++)
    {
        mas[rand() % 2][rand() % 40] = 4;
    }
    for (int i = 0; i < 14; i++)
    {
        mas[rand() % 2+15][rand() % 40] = 4;
    }
    for (int i = 0; i < 5; i++)
    {
        mas[rand() % 6 + 2][rand() % 9] = 4;
    }
    for (int i = 0; i < 5; i++)
    {
        mas[rand() % 6 + 2][rand() % 9 + 30] = 4;
    }
    for (int i = 0; i < 4; i++)
    {
        mas[rand() % 7 + 8][rand() % 2] = 4;
    }
    for (int i = 0; i < 4; i++)
    {
        mas[rand() % 7 + 8][rand() % 2 + 38] = 4;
    }


    for (int i = 0; i < 17; i++)
    {
        for (int j = 0; j < 40; j++)
        {
            if (mas[i][j] == 4)//zvezdy
            {
                printf("\033[1;5;38;5;227m%c\033[0m ", mas[i][j]);
            }
            else
            {
                if(j==0 || j == 7 || j == 14 || j == 21 || j == 28 || j == 35)
                    printf("\033[38;5;196m%c\033[0m ", mas[i][j]);//krasniy
                if (j == 1 || j == 8 || j == 15 || j == 22 || j == 29 || j == 36)
                    printf("\033[38;5;202m%c\033[0m ", mas[i][j]);//orangeviy
                if (j == 2 || j == 9 || j == 16 || j == 23 || j == 30 || j == 37)
                        printf("\033[38;5;220m%c\033[0m ", mas[i][j]);//geltiy
                if (j == 3 || j == 10 || j == 17 || j == 24 || j == 31 || j == 38)
                        printf("\033[38;5;154m%c\033[0m ", mas[i][j]);//zeleniy
                if (j == 4 || j == 11 || j == 18 || j == 25 || j == 32 || j == 39)
                        printf("\033[38;5;051m%c\033[0m ", mas[i][j]);//goluboy
                if (j == 5 || j == 12 || j == 19 || j == 26 || j == 33)
                        printf("\033[38;5;021m%c\033[0m ", mas[i][j]);//siniy
                if (j == 6 || j == 13 || j == 20 || j == 27 || j == 34)
                        printf("\033[38;5;141m%c\033[0m ", mas[i][j]);//fioletoviy
            }
        }
        printf("\n");
    }
    printf("\n\n");

}