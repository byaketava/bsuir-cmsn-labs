#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//option 3		ƒан массив строк. Ќайти максимальную подстроку присутствующую в каждой строке.
//option 2		ƒана матрица MxN с нул€ми и единицами. Ќули Ч вода, единицы Ч суша. 
//				Ќайти и раскрасить в разные цвета острова.

void check(int* pupa, int a, int b)	//проверка на ввод 
{
	while (1)
	{
		int numread = scanf_s("%d", pupa);
		char nextchar = getchar();
		if (numread == 1 && (*pupa >= a && *pupa <= b) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf("\033[0mAboba?..\n");
	}
}
char* setString() 
{
	char* str = (char*)malloc(sizeof('\n'));
	int i = 1;
	char c;
	while ((c = getchar()) != EOF && c != '\n') 
	{
		i++;
		str = (char*)realloc(str, i * sizeof(char));
		if (str != NULL) 
		{
			str[i - 2] = c;							// сам символ
			str[i - 1] = '\0';
		}
	}
	return str;
}
char* findMaxCommonSubstring(char** strings, int n) 
{
	char* maxSubstring = NULL;
	int maxSubstringLen = 0;
	int str1Len = strlen(strings[0]);

	for (int start = 0; start < str1Len; start++) 
	{
		for (int end = start; end < str1Len; end++) 
		{
			int len = end - start + 1;							// длина текущей подстроки
			char* substring = (char*)malloc(len + 1);
			strncpy(substring, &strings[0][start], len);		// копируем текущую подстроку в выделенную пам€ть
			substring[len] = '\0';

			int commonSubstringFound = 1;

			for (int i = 1; i < n; i++)							// ищем в остальных строках
			{
				if (strstr(strings[i], substring) == NULL)		// возвращает указатель на первое вхождение в строку,
				{												// на которую указывает str1, строки, указанной в str2
					commonSubstringFound = 0;
					break;
				}
			}

			if (commonSubstringFound && len > maxSubstringLen)	// изменение макс значений если найдена больша€ строка
			{
				maxSubstring = substring;
				maxSubstringLen = len;
			}
			else
			{
				free(substring);
			}
		}
	}
	return maxSubstring;
}
void option3()
{
	int n;
	printf("Enter amount of strings: ");
	check(&n, 1, 10);
	char** strings = (char**)malloc(n * sizeof(char*));
	for (int i = 0; i < n; i++) 
	{
		printf("\nEnter %d string:\n", i + 1);
		strings[i] = setString();
		rewind(stdin);
	}
	char* maxSubstring = findMaxCommonSubstring(strings, n);
	if (maxSubstring != NULL) 
	{
		printf("\nMax common substring: %s\n\n", maxSubstring);
		free(maxSubstring);
	}
	else 
	{
		printf("\nCommon substring is not founded\n\n");
	}
}

void printMatrix(int** matrix, int M, int N)
{
	char c[4];
	printf("\nMatrix:\n");
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (matrix[i][j] == 1)
			{
				printf("%2d ", matrix[i][j]);
			}
			else if (matrix[i][j] == 0)
			{
				printf("\033[1;38;5;0m%2d \033[0m", matrix[i][j]);
			}
			else
			{
				_itoa(matrix[i][j] * 3, c, 10);//5 6 
				printf("\033[1;38;5;%sm1  \033[0m", c);
			}
		}
		printf("\n");
	}
}

void floodFill(int*** matrix, int M, int N, int i, int j, int color)
{
	if (i < 0 || i >= M || j < 0 || j >= N)
		return;
	if ((*matrix)[i][j] != 1)
		return;
	(*matrix)[i][j] = color;

	floodFill(matrix, M, N, i + 1, j, color);
	floodFill(matrix, M, N, i - 1, j, color);
	floodFill(matrix, M, N, i, j + 1, color);
	floodFill(matrix, M, N, i, j - 1, color);
}

void colorIslands(int*** matrix, int M, int N) 
{
	int color = 2;
	for (int i = 0; i < M; i++) 
	{
		for (int j = 0; j < N; j++) 
		{
			if ((*matrix)[i][j] == 1) 
			{
				floodFill(matrix, M, N, i, j, color);
				color++;
			}
		}
	}
}
void option2()
{
	srand((unsigned int)time(NULL));
	int M, N;
	printf("Enter M: ");
	check(&M, 1, 40);
	printf("\nEnter N: ");
	check(&N, 1, 40);
	
	int** matrix = (int**)calloc(M, sizeof(int*));
	for (int i = 0; i < M; i++)
	{
		matrix[i] = (int*)calloc(N, sizeof(int));
	}

	for (int i = 0; i < M; i++) 
	{
		for (int j = 0; j < N; j++) 
		{
			matrix[i][j] = rand() % 2;		// рандои 0\1
		}
	}

	printMatrix(matrix, M, N);
	colorIslands(&matrix, M, N);
	printMatrix(matrix, M, N);
	printf("\n");
}