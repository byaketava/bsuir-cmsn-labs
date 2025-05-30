#include <stdio.h>
#include <stdlib.h>
struct FILO 
{
	char data;
	struct FILO* next;
};
struct FILO* push(struct FILO*, char);
void f1(struct FILO**head, double b, int t);
void f2(struct FILO**head, int a, int t);
void show(struct FILO** head);

int main()
{
	do {
		system("cls");
		struct FILO* head;
		head = NULL;
		double f, b;
		int a, t, poopa;
		puts("Enter a number:\033[01;38;05;218m");
		while (1)
		{
			int numread = scanf_s("%lf", &f);
			char nextchar = getchar();
			if (numread == 1 && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf("\033[0mDon't do this, please don't break my code!\n");
		}
		puts("\033[0mEnter a base of a new system:\033[01;38;05;218m");
		while (1)   //проверка на ввод  
		{
			int numread = scanf_s("%d", &t);
			char nextchar = getchar();
			if (numread == 1 && (t > 1 && t < 33) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf("\033[0mDon't do this, please don't break my code!\n");
		}
		puts("\n\033[0mProcess:");
		a = (int)f;
		b = f - a;
		f1(&head, b, t);
		head = push(head, '.');
		f2(&head, a, t);
		show(&head);
		puts("___________________________________________");
		puts("If you want to quit, put '0'");
		scanf_s("%i", &poopa);
		if (poopa == 0)
			break;
		rewind(stdin);
	} while (1);
}

struct FILO* push(struct FILO* head, char x)
{
	struct FILO* n;
	n = (struct FILO*)malloc(sizeof(struct FILO));
	n->next = NULL;
	n->data = x;
	if (head == NULL)
		head = n;
	else
	{
		n->next = head;
		head = n;
	}
	return head;
}
void f1(struct FILO** head, double b, int t)
{
	char str[10];
	int c;
	printf("\033[01;38;05;117m");
	for (int i = 9; i >= 0; i--)
	{
		printf("%lf * %i ",b,t);
		b = b * t;
		c = (int)b;
		printf("= %lf, i = %i\n", b, c);
		if (c < 10)
			str[i] = ((c)+48);
		else
			str[i] = ((c)+55);
		b = b - c;
	}
	for (int j = 0; j < 10; j++)
	{
		(*head) = push((* head), str[j]);
	}
}
void f2(struct FILO** head, int a, int t)
{
	do
	{
		printf("\033[01;38;05;218m%i mod %i = %i\n",a,t,a%t);
		if (a % t < 10)
			(* head) = push((*head), (a % t) + 48);
		else
			(*head) = push((*head), (a % t) + 55);
		a = a / t;
	} while (a > 0);
	printf("\n");
}
void show(struct FILO** head)
{
	puts("\033[0mThe number in new system:\033[01;38;05;218m");
	struct FILO* p = (*head);
	while (p != NULL)
	{
		printf("%c", p->data);
		p = p->next;
	}
	puts("\033[0m");
}