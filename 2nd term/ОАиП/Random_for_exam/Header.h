#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

typedef struct T3
{
	int value;
	struct T3* next;
	struct T3* prev;
}s3;

void t1();
void input_num_txt(FILE* fp);
void sort_vybor_file(FILE* fp);
void swap_numbers(FILE* file, int pos1, int pos2);

void t2();
void input_num_bin(FILE* fp);
void sort_vstavki_file(FILE* fp);
void swap_bin(FILE* fp, int j, int i, int temp1, int temp2);

void t3();
void delete_node_ring(s3** head);

void t4();
void insert_in_bin(FILE* fp);

void t8();
void input_words_txt(FILE* fp);
void words_reverse_shifr(FILE* fp);

void shell_sort(int n, int* mas);

void words_change_1and2(FILE* fp);
void taska_kati();

