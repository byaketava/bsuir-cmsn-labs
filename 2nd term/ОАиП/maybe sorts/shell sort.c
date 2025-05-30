#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//по возрастанию одномерный
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
                    /*for (int k = 0; k < n; k++)                   //проверка каждого изменения массива
                    {
                        if(k==j || k== j-step)
                        printf(" \033[1;32m%5i\033[0m", mas[k]);
                        else
                        printf(" %5i", mas[k]);
                    }
                    printf("\n");*/
                }
                else
                    break;
            }
        }
    }
}