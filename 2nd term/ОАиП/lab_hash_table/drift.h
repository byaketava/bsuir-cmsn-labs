#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>
#define size 50

typedef struct TABLE
{
                         //2+2
    char* key;            //20+2  // хранит указатель на ключ
    char* ip;             //15+2  // хранит ip
    unsigned int port;             // 5+2  // хранит port
    struct TABLE* next;   //  // хранит указатель на следующее поле (для обработки коллизий)
} table;

void check(int* pupa, int a, int b);
void print_table(table** hhh);
void read_N(table** hhh, int N);
int hash_fonk(char* key);
void add(table** hhh, table* tmp);
void hands(table** hhh);
void delete(table** hhh);
char* find(table** hhh);