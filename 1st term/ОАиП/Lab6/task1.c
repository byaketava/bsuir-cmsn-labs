#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void text_task_1(void);
void input_array1(int n, int*mas);
void output_array1(int n, int* mas);
void extra_array(int n, int* mas, int** dop_array, int*size);
void shell_sort(int n, int* mas);
void sort_elements(int n, int* mas, int* dop_mas);


void task1()
{
    int n = rand() % 25 + 1;
    int size;
    int* mas = NULL; 
    int* dop_mas = NULL;
    text_task_1();
    mas = (int*)calloc(n,sizeof(int));
    input_array1(n, mas);
    printf(" The number of elements in the array is \033[38;5;141m%i\033[0m\n", n);
    printf(" _____________________________________________________________________\n");
    printf(" An array:\n");
    output_array1(n, mas);
    printf(" _____________________________________________________________________\n");
    extra_array(n, mas, &dop_mas, &size);
    if (size != 0)
    {
        printf(" An extra array consisting of even positive elements:\n");
        output_array1(size, dop_mas);
        printf("\n Sorted extra array:\n");
        shell_sort(size, dop_mas);
        output_array1(size, dop_mas);
        printf(" _____________________________________________________________________\n");
    }
    else
    {
        printf(" There are \033[38;5;141mno\033[0m even positive elements in the array\n");
        printf(" _____________________________________________________________________\n");
    }
    printf(" The array with sorted even positive elements:\n");
    sort_elements(n, mas, dop_mas);
    output_array1(n, mas);
    printf(" _____________________________________________________________________\n");
}


void text_task_1(void)
{
    printf(" Task 1:\n");
    printf(" _____________________________________________________________________\n");
    printf(" In a one-dimensional array, sort even positive elements by\n");
    printf(" the \033[38;5;141mShell\033[0m method.\n");
    printf(" _____________________________________________________________________\n");
}
void input_array1(int n, int* mas)
{
    for (int i = 0; i < n; i++)
    {
        mas[i] = rand() % 101 - 50;
    }
}
void output_array1(int n, int* mas)
{
    for (int i = 0; i < n; i++)
    {
        if ((mas[i] > 0) && (mas[i] % 2 == 0))
            printf(" \033[38;5;043m%3i\033[0m", mas[i]);
        else
            printf(" %3i", mas[i]);
    }
    printf("\n");
}
void extra_array(int n, int* mas, int **dop_array, int*size)
{
    (* size) = 1;
    for (int i = 0; i < n; i++)
    {
        if (mas[i] > 0 && mas[i] % 2 == 0)
            (* size)++;
    }
    if ((*size) != 1)
    {
        int* copy = (int*)realloc(*dop_array, (*size) * sizeof(int));
        if (copy != NULL)
        {
            *dop_array = copy;
        }
        int p = 0;
        for (int i = 0; i < n; i++)
        {
            if (mas[i] > 0 && mas[i] % 2 == 0)
            {
                (* dop_array)[p] = mas[i];
                p++;
            }
        }
    }
    (*size)--;
}
void shell_sort(int n, int* mas)
{
    int step, i, j, temp;
    for (step = n / 2; step > 0; step /= 2)
    {
        for (i = step; i < n; i++)
        {
            for (j = i; j >= step; j -= step)
            {
                if (mas[j] < mas[j - step])
                {
                    temp = mas[j];
                    mas[j] = mas[j - step];
                    mas[j - step] = temp;
                }
                else
                    break;
            }
        }
    }
}
void sort_elements(int n, int* mas, int* dop_mas)
{
    int p = 0;
    for (int i = 0; i < n; i++)
    {
        if (mas[i] > 0 && mas[i] % 2 == 0)
        {
            mas[i] = dop_mas[p];
            p++;
        }
    }
}