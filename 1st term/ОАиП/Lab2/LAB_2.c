#include<stdio.h>
#include<stdlib.h>
void task1();// —колько слагаемых должно быть  в  сумме  1+1/2+1/3+1/4+...+1/n, 
             // чтобы эта сумма оказалась больше 5 ?

void task2();// —оставить алгоритм,  определ€ющий  количество способов,  
             // какими   задуманное число n>1 можно представить в виде  суммы  n=i3+j3,  
             // счита€, что перестановка слагаемых нового способа не даЄт.

void task3();// ѕроверить €вл€ютс€ ли числа P и Q взаимнопростыми.

int main()
{
    int task;
    do {
        printf("Enter the number of the task (from 1 to 3), or enter '0' to end the program\n");
        scanf_s("%d", &task);

        switch (task)
        {
        case 1:
            system("cls");  //чистим экран
            task1();
            break;
        case 2:
            system("cls");
            task2();
            break;
        case 3:
            system("cls");
            task3();
            break;
        case 0:
            exit(0);
        }
    } while (task != 0);  //даЄт возможность выбора другой задачи или завершени€ программы
}

void task1()
{
    float sum = 0;
    float n;
    for (n = 1; sum<=5; n++)
    {
         sum = sum + (1 / n); 
         printf("n = %.f sum=%f\n", n, sum); 
    }
    n--;
    printf("\n The number of elements of the sum is equal to the value of the last divisor\nSo n = %.f\n", n);
}

void task2()
{
    int n, i, j;
    int cnt = 0;
    printf("Enter the number n>1\n");
    while (scanf_s("%i", &n) != 1)  //проверка  на ввод
    {
        while (getchar() != '\n')
            continue;
        printf("Just enter the number higher then 1\n ");
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            if (i * i * i + j * j * j == n)
                cnt++;
    }
    printf("Ways to represent a number: %i\v", cnt/2);
}

void task3()
{
    int P, Q, n, BigOne;
    int cnt = 0;
    printf("Enter P, Q\n");

    while (scanf_s("%d%d", &P, &Q) != 2) // проверка на ввод
    {
        while (getchar() != '\n')
            continue;
        printf("Incorrect input\n");
    }

    if (P >= Q)
        BigOne = P;
    else
        BigOne = Q;
    for (n = 2; n <= BigOne; n++)
    {
        if (P % n == 0 && Q % n == 0) 
            cnt++; 
    }
    if (P == Q)
    {
        printf("Numbers are the same\v");
    }
    else if (cnt == 0 || P == 1 || Q == 1 || P == -1 || Q == -1)
    {
        printf("Numbers are mutually prime\v");
    }
    else
    {
        printf("Numbers are not mutually prime\v");
    }
}