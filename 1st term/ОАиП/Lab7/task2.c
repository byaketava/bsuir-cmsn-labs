#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void text_task_2(void);
char* input_string(char** stroka, int* size);
char* word_in_S0(char* word, int size_S0, char* stroka, int* m);
void find_and_delete_word(char* S, char* word, int m, int* size_S);
void output_string(char* stroka, int size);

int task2()
{
	text_task_2();
	int size_S = 0;
	int size_S0 = 0;
	char* S = NULL;
	char* S0 = NULL;
	char* word = NULL;
	word = (char*)calloc(100, sizeof(char));
	printf(" Enter the string S:\n ");
	S = input_string(&S, &size_S);
	printf(" _______________________________________________________________________\n");
	printf(" Enter the string S0:\n ");
	S0 = input_string(&S0, &size_S0);
	printf(" _______________________________________________________________________\n");
	if (S == 0 || S0 == 0)
	{
		return 0;
	}
	int m=0; //длина слова, потом изменяется
	word = word_in_S0(word, size_S0, S0, &m);//само слово
	if (m == 0)
		return 0;
	find_and_delete_word(S, word, m, &size_S);
	printf(" New string:\n");
	output_string(S, size_S);
	printf(" _______________________________________________________________________\n");
	return 0;
}