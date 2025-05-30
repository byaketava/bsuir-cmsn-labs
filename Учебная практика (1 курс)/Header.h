#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct tree                    // структура содержащая в себе 
{                                      // возможные компоненты вектора
    int a;                             // номера вершин
    struct tree* left;          //0
    struct tree* right;         //2
    struct tree* mid;           //1

}tree;

void begin();
void printArr(int** mass, int n, int m);
void input_random(int n, int m, int** mass);
int check(int x, int y);                                    
void input_keybord(int n, int m, int** mass);
void input(int** mass, int n, int m);
int** createArr(int n, int m);
tree* f1(tree* head, int** a, int m, int n, int j);
int Ret(int** a, int j, int n, int x);
void write(tree* tree, int n);
int orrtogonal(int** vec, int** mass, int n, int m, int len);
int writeArr(tree* head, int*** vec, int m, int i, int j);