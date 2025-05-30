#include<stdio.h>
#include<stdlib.h>

void task1();// Ввести радиус и высоту цилиндра.Найти площадь боковой поверхности,
                // площадь полной поверхности и объем цилиндра.
                // Точность до двух знаков после запятой

void task2();// Даны два числа a и b.Определите, равны или не равны эти числа

void task3();//Если среди чисел a, b и c есть пара взаимно противоположных,
                //вывести третье(оставшееся) число, в противоположном случае
                //вывести сообщение "нет"

void task4();//По номеру месяца вывести его название

int main() 
{
   int task;
   do {
       printf("Enter the number of task (from 1 to 4), or enter '0' to end the program\n");
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
    case 4:
        system("cls");
        task4();
        break;
    default:
    {
        system("cls");
        printf("Omg, can you just put 1, 2, 3, 4 or 0 here, try again\v");
        break;
    }
    case 0:
       exit(0);
    }
   } while (task !=0);  //даёт возможность выбора другой задачи или завершения программы

}

void task1()
{
    int r, h;
    double pi = 3.14159265; //задание числа пи без использования мат.библиотеки
    printf("Enter r, h\n");

    while (scanf_s("%i%i", &r, &h) != 2)  //проверка  на ввод
    {
        while (getchar() != '\n')
            continue;
        printf("Oops... Wrong input, try again\n");
    }

    if ((r == 0) || (h == 0))  //при равенстве одной из переменных нулю
    {
        printf("Are you sure?.. Figure does not exist\v");
        return;
    }
    else if (r > 0 && h > 0)
    {
        double S_side = 2 * pi * r * h;
        double S_total = S_side + 2 * pi * r * r;
        double V = pi * r * r * h;
        printf("S(side)=%.2lf, S(total)=%.2lf, V=%.2lf\n", S_side, S_total, V);
        return;
    }
    else  //при вводе 1 или 2 отрицательных чисел
    {
        printf("Oops... 1 or 2 of the numbers are negative\n");
        return;
    }

}

void task2()
{
    float a, b;
    printf("Enter a, b\n");

    while (scanf_s("%f%f", &a, &b) != 2)  //проверка  на ввод
    {
        while (getchar() != '\n')
            continue;
        printf("Just.enter.2.numbers...\n ");
    }

    if (a == b)
        printf("Numbers are the same\v");
    else
        printf("Oh, numbers are not the same, bye-bye!\v");
}

void task3()
{
    float a, b, c;
    printf("Enter a, b, c\n");

    while (scanf_s("%f%f%f", &a, &b, &c) != 3)  //проверка  на ввод
    {
        while (getchar() != '\n')
            continue;
        printf("Is it so hard to enter just numbers? Try again, now.\n");
    }

    if (a + b == 0)
        printf("Those two (a and b) turned into 0, so only c=%f survived\v", c);
    else if (a + c == 0)
        printf("Those two (a and c) turned into 0, so only b=%f survived\v", b);
    else  if (b + c == 0)
        printf("Those two (b and c) turned into 0, so only a=%f survived\v", a);
    else
        printf("No. None of the pairs of numbers is mutually opposite\v");
}

void task4()
{
    int a;
    printf("Enter the month number in the form '1', '5', '11' etc.\n");

    while (!scanf_s("%d", &a) || a < 1 || a >12)  //проверка  на ввод
    {
        while (getchar() != '\n')
            continue;
        printf("Again, put the month number here\n");
    }

    if (a == 1)
        printf("Month: January (Winter) P.S. Happy New Year!!!\v");
    if (a == 2)
        printf("Month: February (Winter)\v");
    if (a == 3)
        printf("Month: March (Spring)\v");
    if (a == 4)
        printf("Month: April (Spring)\v");
    if (a == 5)
        printf("Month: May (Spring)\v");
    if (a == 6)
        printf("Month: June (Summer)\v");
    if (a == 7)
        printf("Month: July (Summer)\v");
    if (a == 8)
        printf("Month: August (Summer)\v");
    if (a == 9)
        printf("Month: September (Autumn)\v");
    if (a == 10)
        printf("Month: October (Autumn)\v");
    if (a == 11)
        printf("Month: November (Autumn)\v");
    if (a == 12)
        printf("Month: December (Autumn)\v");
}