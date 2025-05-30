#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void text_task_1(void);
char* input_string(char** stroka, int* size);
char** mas_slov(char** slova, int* n, int size, char* stroka, int* m, int* j);

void task1()
{
	int size = 0;
	int j = 0;
	int n = -1;
	char** slova = NULL;
	slova = (char**)calloc(51, sizeof(char*)); 
	for (int i = 0; i < 51; i++)
	{
		slova[i] = (char*)calloc(50, sizeof(char));
	}
	char *stroka=NULL;
	int* m = NULL;
	m = (int*)calloc(100, sizeof(int));
	text_task_1();
	stroka = input_string(&stroka, &size);
	if (stroka == 0)
	{
		return 0;
	}
	slova = mas_slov(slova, &n, size, stroka, m, &j);
}