#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void text_task_3(void);
char** input_strings(char** string, int n, int*m);
void output_strings(char** strings, int n, int* m);
void mas_sss(char** stroki, int n, int* m);

void task3()
{
	text_task_3();
	int n;
	char** strings = NULL;
	strings = (char**)calloc(51, sizeof(char*));
	for (int i = 0; i < 50; i++)
	{
		strings[i] = (char*)calloc(50, sizeof(char));
	}
	int* m = NULL;
	m = (int*)calloc(100, sizeof(int));
	printf(" How many strings do you want to input?\n ");
	while (1)   //проверка на ввод
	{
		int numread = scanf_s("%d", &n);
		char nextchar = getchar();
		if (numread == 1 && (n >= 1 && n <= 10) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf(" Don't do this, please don't break my code!\n");
	}
	printf(" _______________________________________________________________________\n ");
	printf("Input strings (from 1 to %i):\n ", n);
	strings = input_strings(strings, n, m);
	printf(" _______________________________________________________________________\n ");
	mas_sss(strings, n, m);
	output_strings(strings, n, m);
}