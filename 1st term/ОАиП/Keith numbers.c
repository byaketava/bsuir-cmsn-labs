Keith numbers
#include<stdio.h>

int length(int inputNum);

int main()
{
    int number, numberCopy;
    int array[10];
    int complete = 0;
    int sum = 0;
    int YorN, i;
    printf("Enter the number: ");
    scanf_s("%d", &number);
    numberCopy = number;
    for (i = length(numberCopy) - 1; i >= 0; i--)
    {
        array[i] = number % 10;
        number /= 10;
        // сюда после фора еще один фор для вывода чисел на экран
    }
    while (complete == 0)
    {
        for (i = 0; i < length(numberCopy); i++)
        {
            sum += array[i];
        }
        if (sum == numberCopy)
        {
            complete = 1;
            YorN = 1;
        }
        else if (sum > numberCopy)
        {
            complete = 1;
            YorN = 0;
        }
        for (i = 0; i < length(numberCopy); i++)
        {
            printf("%d", array[i]);
            if (i != length(numberCopy) - 1)
            {
                array[i] = array[i + 1];
                printf(" + ");
            }
            else
            {
                array[i] = sum;
                printf(" = %d", array[i]);
            }
        }
        sum = 0;
        printf("\n");
    }
    if (YorN == 1)
    {
        printf("The number is a Keith number\n");
    }
    else
    {
        printf("The number is not a Keith number\n");
    }
    return 0;
}


int length(int inputNum)
{
    int counter = 0;
    while (inputNum > 0)
    {
        inputNum = inputNum / 10;
        counter++;
    }
    return counter;
}