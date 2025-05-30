#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

enum param
{
	genre = 1,
	colvo,
	age
};
typedef struct
{
	unsigned long id;//6
	char title[40];
	char author[40];
	unsigned long year;//4
	unsigned long popularity;//9
	enum param type;
	union
	{
		char genre[15];			// жанр			жанр от руки
		unsigned long colvo;	// тираж		как попьюларити
		int age;				// возраст		от 0 до 100 возраст
	};
}BOOK;

typedef struct NODE
{
	BOOK data;
	struct NODE* prev;
	struct NODE* next;
} node;
node* head;		// указатель на голову
node* tail;		// указатель на хвост

enum perechen
{
	id = 1,
	title,
	author,
	year,
	popularity,
	characteristic		// 14 + 2 на края
};
struct division
{
	unsigned int divisor : 16;    // число, на которое нужно делить (максимум 65535)
	unsigned int remainder : 16;  // остаток (максимум 65535)
};

BOOK info();
void insertAtEnd();
void showList();
void deleteWholeList();
void deleteOneBook();
void delete();
void add(int* pupa);
void save(int ember);
void edit();
void sort();
void rec(int age);

