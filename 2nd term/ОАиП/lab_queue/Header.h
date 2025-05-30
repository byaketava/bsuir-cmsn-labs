#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct FIFO 
{
	int data;
	struct FIFO* next;
	struct FIFO* prev;
}fifo;

fifo* head1, * tail1,* head2, * tail2, * head3, * tail3;

void indertAtEnd(struct FIFO** head, struct FIFO** tail, int posl);
void insertRandomly(struct FIFO** head, struct FIFO** tail);
void create(struct FIFO** head, struct FIFO** tail);
void check(int* pupa, int a, int b);
void print(struct FIFO* head);
void pop(struct FIFO** head, struct FIFO** tail);
void delete();
void sort(fifo** head, int a);
void swap(int* a, int* b);
void push(struct FIFO** head, struct FIFO** tail, int num);
void two_to_one(fifo** head1, fifo** tail1, fifo** head2, fifo** tail2, fifo** head3, fifo** tail3);
