#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//�� ����������� ����������
void insertion_sort(int n, int* mas)
{
    int i, j, temp;
    for (i = 1; i < n; i++)                         //������ �������� � ������
    {
        temp = mas[i];
        for (j = i - 1; j >= 0 && temp < mas[j]; j--)
        {
            mas[j+1] = mas[j];                        //�����
            //output_array(n, mas);                   //�������� ������� ��������� �������
        }
        mas[j+1] = temp;                              //������ �������� �� ������
        /*for (int k = 0; k < n; k++)                 //�������� ������� ��������� �������
        {
            if (k == j+1 || k == i)
                printf(" \033[1;32m%5i\033[0m", mas[k]);
            else
                printf(" %5i", mas[k]);
        }
        printf("\n");*/
    }
}
//������ �� �������� �������� ���������� �������� � ������
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
            *(mas + j + 1) = *(mas + j);//�����        
        }
        *(mas + j + 1) = temp;//������ � �������������� ��� � ��� �� �������
    }
}