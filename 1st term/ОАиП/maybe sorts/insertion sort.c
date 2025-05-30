#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//по возрастанию одномерный
void insertion_sort(int n, int* mas)
{
    int i, j, temp;
    for (i = 1; i < n; i++)                         //запись элемента в память
    {
        temp = mas[i];
        for (j = i - 1; j >= 0 && temp < mas[j]; j--)
        {
            mas[j+1] = mas[j];                        //сдвиг
            //output_array(n, mas);                   //проверка каждого изменения массива
        }
        mas[j+1] = temp;                              //запись элемента из памяти
        /*for (int k = 0; k < n; k++)                 //проверка каждого изменения массива
        {
            if (k == j+1 || k == i)
                printf(" \033[1;32m%5i\033[0m", mas[k]);
            else
                printf(" %5i", mas[k]);
        }
        printf("\n");*/
    }
}
//строки по убыванию значения последнего элемента в строке
void insertion_sort_stroki(int n, int m, int** mas)
{
    int i, j;
    int* temp;
    int mem;
    for (i = 1; i < n; i++)
    {
        temp = *(mas + i);
        mem = mas[i][m];
        for (j = i - 1; j >= 0 && mem > mas[j][m]; j--)
        {
            *(mas + j + 1) = *(mas + j);//сдвиг        
        }
        *(mas + j + 1) = temp;//запись в освободившийся или в тот же элемент
    }
}