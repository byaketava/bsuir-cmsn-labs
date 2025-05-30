#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void text_task_2(void);
void input_array2(int n, int m, int** mas);
void output_array2(int n, int m, int** mas);
void insertion_sort(int n, int m, int** mas);


void task2()
{
    int n = rand() % 25 + 1;
    int m = rand() % 25 + 1;
    int** mas = NULL; 
    text_task_2();
    mas = (int**)calloc(n, sizeof(int*));
    for (int k = 0; k < n; k++)
    {
        mas[k] = (int*)calloc((m+1), sizeof(int));
    }
    input_array2(n, m, mas);
    printf(" The size of matrix is \033[38;5;141m%i\033[0mx\033[38;5;141m%i\033[0m\n", n, m);
    printf(" _____________________________________________________________________\n");
    printf(" An array:\n");
    output_array2(n, m, mas);
    printf(" _____________________________________________________________________\n");
    printf(" The array with sorted rows:\n");
    insertion_sort(n, m, mas);
    output_array2(n, m, mas);
    printf(" _____________________________________________________________________\n");
}


void text_task_2(void)
{
    printf(" Task 1:\n");
    printf(" _____________________________________________________________________\n");
    printf(" In a matrix of size \033[38;5;141mN\033[0mx\033[38;5;141mM\033[0m, sort the rows in \033[38;5;141mdescending order\033[0m of the\n \033[38;5;141mvalue\033[0m of the \033[38;5;141mminimum\033[0m element by the \033[38;5;141minsertion\033[0m sort.\n");
    printf(" _____________________________________________________________________\n");
}
void input_array2(int n, int m, int** mas)
{
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mas[i][j] = rand() % 101 - 50;
        }
    }
    int min;
    for (int i = 0; i < n; i++)
    {
        min = mas[i][0];
        for (int j = 0; j < m; j++)
        {
            if (mas[i][j] < min)
                min = mas[i][j];
        }
        mas[i][m] = min;
    }
}
void output_array2(int n, int m, int** mas)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= m; j++)
        {
            if (j == m)
                printf("   \033[38;5;043mminimum element is \033[0m %3i", mas[i][j]);
            else
            {
                if(mas[i][j]==mas[i][m])
                    printf(" \033[38;5;141m%5i\033[0m", mas[i][j]);
                else
                    printf(" %5i", mas[i][j]);
            }
        }
        printf("\n\n");
    }
}
void insertion_sort(int n, int m, int** mas)
{
    int i, j;
    int *temp;
    int mem;
    for (i = 1; i < n; i++)
    {
        temp = *(mas + i);
        mem = mas[i][m];
        for (j = i - 1; j >= 0 && mem > mas[j][m]; j--)
        {
            *(mas + j + 1) = *(mas + j);//сдвиг        
        }
        *(mas + j + 1) = temp;//запись в освободившийс€ или в тот же элемент
    }
}