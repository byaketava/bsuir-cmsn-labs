#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void check(int* pupa, int a, int b);
char* setString();
char* findMaxCommonSubstring(char** strings, int n);
void option3();
void printMatrix(int** matrix, int M, int N);
void floodFill(int*** matrix, int M, int N, int i, int j, int color);
void option2();

int main()
{
	int task;
	do
	{
		puts("Choose:");
		puts("1. Option 2");
		puts("2. Option 3");

		check(&task, 0, 2);
		switch (task)
		{
		case 1:
			system("cls");
			option2();
			break;
		case 2:
			system("cls");
			option3();
			break;
		case 0:
			system("cls");
			puts("Bye-bye!");
			break;
		}
	} while (task != 0);
	return 0;
}