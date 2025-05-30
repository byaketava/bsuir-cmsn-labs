#include"Header.h"

void create (struct FIFO** head, struct FIFO** tail)
{
	int choose;
	puts("How do you want to add elements to the queue:\n1. By yourself\n2. Randomly");
	check(&choose, 1, 2);
	if (choose == 1)
	{
		printf("-----------------------------------------------------------------------\n");
		int size;
		puts("Enter the number of elements:");
		check(&size, 1, 15);
		for (int i = 0; i < size; i++)
		{
			indertAtEnd(head, tail, i);
		}
	}
	else
	{
		insertRandomly(head, tail);
	}
	printf("-----------------------------------------------------------------------\n");
}
void insertRandomly(struct FIFO** head, struct FIFO** tail)
{
	fifo* new;
	int size = rand() % 15 + 1;
	for (int i = 0; i < size; i++)
	{
		new = (struct FIFO*)malloc(sizeof(struct FIFO));
		new->next = NULL;
		new->prev = NULL;
		new->data = rand() % 100 + 1;
		if (*head == NULL)
		{
			*head = new;
		}
		else
		{
			new->prev = (*tail);
			(*tail)->next = new;
		}
		*tail = new;
	}
}
void indertAtEnd(struct FIFO** head, struct FIFO** tail, int posl)
{
	int num;
	fifo* new;
	printf("Enter the %i number: ", posl+1);
	check(&num, 1, 100);
	new = (struct FIFO*)malloc(sizeof(struct FIFO));
	new->next = NULL;
	new->prev = NULL;
	new->data = num;
	if (*head == NULL)
	{
		*head = new;
	}
	else
	{
		new->prev = (*tail);
		(*tail)->next = new;
	}
	*tail = new;
}
void check(int *pupa, int a, int b)	//проверка на ввод 
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
		printf("Aboba?..\n");
	}
}
void print(struct FIFO* head) 
{
	struct FIFO* p = head;
	puts("The queue:");
	while (p != NULL) 
	{       
		printf("%-4d", p->data);
		p = p->next;       
	}
	printf("\n-----------------------------------------------------------------------\n");
}
void sort(fifo** head, int a)    // 1 возрастание 2 убывание
{
	fifo* temp = *head;
	while (temp != NULL)
	{
		fifo* min = temp;
		fifo* pupa = temp->next;

		while (pupa != NULL) 
		{
			if (a == 1)
			{
				if (min->data > pupa->data)
				{
					min = pupa;
				}
			}
			if (a == 2)
			{
				if (min->data < pupa->data)
				{
					min = pupa;
				}
			}
			pupa = pupa->next;
		}
		if (min != temp) 
		{
			swap(&(min->data), &(temp->data));
		}
		temp = temp->next;
	}
}
void swap(int* a, int* b) 
{
	int temp = *a;
	*a = *b;
	*b = temp;
}
void pop(struct FIFO** head, struct FIFO** tail)
{
	if (*head != NULL)
	{
		*head = (*head)->next;
	}
	else
	{
		*tail = NULL;
	}
}
void delete()
{
	int num, ch;
	printf("Do you want to delete 1 element, or the whole queue:\n1. 1 element\n2. The whole queue\n");
	check(&ch, 1, 2);
	printf("-----------------------------------------------------------------------\n");
	printf("Enter the number of queue you want to cut\n");
	check(&num, 1, 3);
	printf("-----------------------------------------------------------------------\n");
	switch (num)
	{
	case 1:
		if (head1 != NULL)
		{
			if (ch == 1)
			{
				pop(&head1, &tail1);
				print(head1);
			}
			else
			{
				while (head1 != NULL)
					pop(&head1, &tail1);
			}
		}
		else
		{
			puts("What am I going to delete if you don't have a queue?\n");
			printf("-----------------------------------------------------------------------\n");
		}
		break;
	case 2:
		if (head2 != NULL)
		{
			if (ch == 1)
			{
				pop(&head2, &tail2);
				print(head2);
			}
			else
			{
				while (head2 != NULL)
					pop(&head2, &tail2);
			}
		}
		else
		{
			puts("What am I going to delete if you don't have a queue?\n");
			printf("-----------------------------------------------------------------------\n");
		}
		break;
	case 3:
		if (head3 != NULL)
		{
			if (ch == 1)
			{
				pop(&head3, &tail3);
				print(head3);
			}
			else
			{
				while (head3 != NULL)
					pop(&head3, &tail3);
			}
		}
		else
		{
			puts("What am I going to delete if you don't have a queue?\n");
			printf("-----------------------------------------------------------------------\n");
		}
		break;
	}
}
void push(struct FIFO** head, struct FIFO** tail, int num)
{
	fifo* new;
	new = (struct FIFO*)malloc(sizeof(struct FIFO));
	new->next = NULL;
	new->prev = NULL;
	new->data = num;
	if (*head == NULL)
	{
		*head = new;
	}
	else
	{
		new->prev = (*tail);
		(*tail)->next = new;
	}
	*tail = new;
}

void two_to_one(fifo** head1, fifo** tail1, fifo** head2, fifo** tail2, fifo** head3, fifo** tail3)
{
	print(*head1);
	print(*head2);
	fifo* p1 = *head1;
	fifo* p2 = *tail2;

	while (p1 != NULL && p2 != NULL)
	{
		if (p1->data <= p2->data)
		{
			push(head3, tail3, p1->data);
			p1 = p1->next;
			pop(head1, tail1);
		}
		else
		{
			push(head3, tail3, p2->data);
			p2 = p2->prev;
		}
		print(*head3);
	}

	if (p1 == NULL && p2 != NULL)
	{
		while (p2 != NULL)
		{
			push(head3, tail3, p2->data);
			p2 = p2->prev;
			print(*head3);
		}
	}

	if (p2 == NULL && p1 != NULL)
	{
		while (p1 != NULL)
		{
			push(head3, tail3, p1->data);
			p1 = p1->next;
			print(*head3);
		}
		pop(head1, tail1);
	}
	fifo* r = *head2;
	while (r->next != NULL)
		r = r->next;
	*tail2 = r;
	while (*head2 != NULL)
		pop(head2, tail2);
}
