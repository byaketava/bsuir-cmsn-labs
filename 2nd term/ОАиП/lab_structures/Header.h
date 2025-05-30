#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	unsigned long id;//6
	char title[40];
	char author[40];
	unsigned int year;//4
	unsigned long popularity;//9
} BOOK;
enum perechen
{
	id = 1,
	title,
	author,
	year,
	popularity,
};
void option1(BOOK** pororo, int size);
void option2(BOOK** pororo, int size);
void option3(int size, BOOK** pororo, int (*comparator)(BOOK*, int, int));
void option4(BOOK *pororo, int i, int j);
void option5(int *size, BOOK**pororo, int* ember);
void option6(BOOK** pororo, int size);
void option7(int* size, BOOK** pororo);
void option0(int *size, BOOK**pororo, int ember);
int comparator(BOOK* pororo, int j, int pooopa);