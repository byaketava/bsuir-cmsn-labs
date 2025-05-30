#include"drift.h"

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
void print_table(table** hhh)
{
	table** temp = hhh;
	printf("Current table:\n");
	printf(" _____________________________________________________ \n");
	printf("|                                                     |\n");
	printf("|                      \033[1;5;38;5;204m%c\033[0m TABLE \033[1;5;38;5;204m%c\033[0m                      |\n", 4, 4);
	printf("|_____________________________________________________|\n");
	printf("|    |                      |                 |       |\n");
	printf("| \033[1;38;5;204mid\033[0m |         \033[1;38;5;204mname\033[0m         |       \033[1;38;5;204mip\033[0m        |  \033[1;38;5;204mport\033[0m |\n");
	printf("|____|______________________|_________________|_______|\n");
	for (int i = 0; i < size; i++) 
	{
		table* t = hhh[i];
		while (t != NULL) 
		{
			printf("|    |                      |                 |       |\n");
			printf("| %-2i | %-20s | %-15s | %-5i |\n",i,t->key, t->ip, t->port);
			printf("|____|______________________|_________________|_______|\n");
			t = t->next;
		}
	}
}
void read_N(table** hhh, int N)
{
	FILE* fp = fopen("file.txt", "r+");
	puts("________________________________________________________________________________________");
	if (fp == NULL)
	{
		printf("Error\n");
		puts("________________________________________________________________________________________");
		return;
	}
	printf("The file was opened successfully\n");
	int pupa = 0;
	char name[20];
	char ip[20];
	while (pupa < N)
	{
		if (fscanf(fp, "%s", name) != EOF)
		{
			table* t = (table*)calloc(1, sizeof(table));
			if (name[strlen(name) - 1] == '\n')
			{
				name[strlen(name) - 1] = '\0';
			}
			int ind = hash_fonk(name);
			t->key = _strdup(name);
			sprintf(ip, "%d.%d.%d.%d", rand() % 256, rand() % 256, rand() % 256, rand() % 256);
			t->ip = _strdup(ip);
			t->port = rand() % 65536;
			t->next = NULL;
			add(&hhh[ind], t);
			pupa++;
		}
	}
	fclose(fp);

}
int hash_fonk(char*key)
{
	double A = (sqrt(5) - 1) / 2;
	double k = 0;
	int ind=0,lupa=0;
	double gg;
	for (int i = 0; key[i] != '\0'; i++) 
	{
		k = k + key[i];
	}
	k = k * A;
	int a = (int)k;
	gg = k - a;
	gg = gg * size;
	
	return (int)gg;
}
void add(table** hhh, table* tmp)
{
	if (*hhh == NULL) 
	{
		*hhh = tmp;
	}
	else 
	{
		table* cur = *hhh;
		while (cur->next != NULL) 
		{
			cur = cur->next;
		}
		cur->next = tmp;
		(*hhh) = cur;
	}
}
void hands(table** hhh)
{
	char name[20];
	char ip[20];
	table* t = (table*)calloc(1, sizeof(table));
	puts("Input name:");
	scanf("%s", &name);
	t->key = _strdup(name);
	puts("\nInput ip (123.123.123.123):");
	scanf("%s", &ip);
	t->ip = _strdup(ip);
	puts("\nInput port:");
	check(&(t->port), 0, 65535);
	int ind = hash_fonk(name);
	add(&hhh[ind], t);
}
void delete(table** hhh)
{
	char key[20];
	printf("Enter the name: ");
	scanf("%s", &key);
	int ind = hash_fonk(key);
	
	table* prev = NULL;
	table* curr = hhh[ind];
	while (curr != NULL) 
	{
		if (strcmp(curr->key, key) == 0) 
		{											// если найден элемент с заданным ключом
			if (prev == NULL) 
			{										// если элемент первый в списке
				hhh[ind] = curr->next;
			}
			else 
			{										// если элемент не первый в списке
				prev->next = curr->next;
			}
			free(curr);								// освобождение памяти, занятой элементом
			return;
		}
		prev = curr;
		curr = curr->next;
	}

}
char* find(table** hhh)
{
	char key[20];
	printf("Enter the name: ");
	scanf("%s", &key);
	int ind = hash_fonk(key);
	table* prev = NULL;
	table* curr = hhh[ind];
	while (curr != NULL)
	{
		if (strcmp(curr->key, key) == 0)
		{											// если найден элемент с заданным ключом
			return curr->ip;						// освобождение памяти, занятой элементом
		}
		prev = curr;
		curr = curr->next;
	}
}