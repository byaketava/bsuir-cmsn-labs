#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct TREE
{
	int data;
	struct TREE* left;
	struct TREE* right;
}node;

void check(int* pupa, int a, int b);
node* create(int val);
void insert(node** root, int val);
void buildTree(node**root);
void print_tree(node* tmp, int level, char branch);
void maxSum(node* temp, int* max, int* current, int** max_path, int** current_path, int*cnt);
node* search(node* root, int val);
node* delete(node* root, int val);
node* minValueNode(node* temp);
void freeTree(node* temp);