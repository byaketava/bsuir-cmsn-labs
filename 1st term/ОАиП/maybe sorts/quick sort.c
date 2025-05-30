#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void sort(int* mas, int size) 
{
    //��������� � ������ � � ����� �������
    int i = 0;
    int j = size - 1;
    //����������� ������� �������
    int mid = mas[size / 2];
    //����� ������
    do
    {
        //��������� ��������, ���� ��, ������� ����� ���������� � ������ �����
        //� ����� ����� ������� ����������(��������� �� �����) ��������, ������� ������ ������������
        while (mas[i] < mid) {
            i++;
        }
        //� ������ ����� ���������� ��������, ������� ������ ������������
        while (mas[j] > mid) {
            j--;
        }
        //������ �������� �������
        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    }
    while (i <= j);

    if (j > 0) {
        //"����� �����"
        sort(mas, j + 1);
    }
    if (i < size) {
        //"����� �����"
        sort(&mas[i], size - i);
    }
}




/*void quickSort(int* numbers, int left, int right)
{
    int pivot; // ����������� �������
    int l_hold = left; //����� �������
    int r_hold = right; // ������ �������
    pivot = numbers[left];
    while (left < right) // ���� ������� �� ���������
    {
        while ((numbers[right] >= pivot) && (left < right))
            right--; // �������� ������ ������� ���� ������� [right] ������ [pivot]
        if (left != right) // ���� ������� �� ����������
        {
            numbers[left] = numbers[right]; // ���������� ������� [right] �� ����� ������������
            left++; // �������� ����� ������� ������
        }
        while ((numbers[left] <= pivot) && (left < right))
            left++; // �������� ����� ������� ���� ������� [left] ������ [pivot]
        if (left != right) // ���� ������� �� ����������
        {
            numbers[right] = numbers[left]; // ���������� ������� [left] �� ����� [right]
            right--; // �������� ������ ������� �����
        }
    }
    numbers[left] = pivot; // ������ ����������� ������� �� �����
    pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot) // ���������� �������� ���������� ��� ����� � ������ ����� �������
        quickSort(numbers, left, pivot - 1);
    if (right > pivot)
        quickSort(numbers, pivot + 1, right);
}
int main()
{
    int a[SIZE];
    // ���������� ������� ���������� �������
   
    // ����� ��������� ������� �� ����������
    quickSort(a, 0, SIZE - 1); // ����� ������� ����������
    // ����� ��������� ������� ����� ����������
    for (int i = 0; i < SIZE; i++)
        printf("%4d ", a[i]);
    printf("\n");
    getchar();
    return 0;
}*/