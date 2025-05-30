#include <stdio.h>
#include<math.h>

int main()
{
	int length, width;
	printf(" Enter X max (1-200): ");
	while (1)
	{
		int numread = scanf_s("%i", &length);
		char nextchar = getchar();
		if (numread == 1 && (length <= 200 && length >= 1) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf(" Incorrect input, try again\n ");
	}
	//200
	printf("\n Enter Y max (1-50): ");
	while (1)
	{
		int numread = scanf_s("%i", &width);
		char nextchar = getchar();
		if (numread == 1 && (width <= 50 && width >= 1) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf(" Incorrect input, try again\n ");
	}
	//50 (*2)
	char pole[200][100];

	for (int x = 0; x < length; x++)	//заполнение массива 
	{
		for (int y = 0; y < width * 2; y++)
		{
			pole[x][y] = ' ';
			pole[0][y] = '|';
		}
		pole[x][width] = '-';
	}


	double x = 0;
	for (int i = 0; x < length; i++)	//сама функция
	{
		double y = sqrt(x) * sin(x) / 2;
		if (abs(y) < width)	// чтобы за экран не вышло
		{
			pole[(int)x][(int)round(y - width)] = '.';
		}
		x = x + 0.1;
	}


	for (int y = width * 2 - 1; y >= 0; y--)	//вывод
	{
		for (int x = 0; x < length; x++)
		{
			if (pole[x][y]=='.')
				printf("\033[32m%c\033[0m", pole[x][y]);
			else
				printf("%c", pole[x][y]);
		}
		printf("\n");
	}
	return 0;
}