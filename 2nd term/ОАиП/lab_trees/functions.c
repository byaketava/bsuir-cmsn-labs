#include"Header.h"

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
node* create(int val)
{
	node* tmp = (node*)malloc(sizeof(node));
	tmp->data = val;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}
void insert(node** root, int val)
{
	if (*root == NULL)
	{
		*root = create(val);
		return;
	}
	if (val <  (* root)->data)
	{
		insert(&((*root)->left), val);
	}
	else if(val > (*root)->data)
	{
		insert(&((*root)->right), val);
	}
}
void buildTree(node** root)
{
	int n,a, val;
	printf("Enter number of nodes: \033[1;38;5;204m");
	check(&n, 1, 25);
	puts("\033[0mHow do you want to enter them: \n1. By hands\n2. Randomly\033[1;38;5;204m");
	check(&a, 1, 2);
	if (a == 2)
	{
		puts("\033[0m________________________________________________________________________________________");
		printf("Entered randomly values:\n\n");
		for (int i = 0; i < n; i++)
		{
			val = rand() % 101 - 50;
			insert(root, val);
		}
	}
	else
	{
		puts("\033[0m________________________________________________________________________________________");
		printf("Enter values: \033[1;38;5;204m");
		for (int i = 0; i < n; i++)
		{
			check(&val, -50, 50);
			insert(root, val);
		}
		fflush(stdin);
		printf("\033[0m ");
	}
}
void print_tree(node* tmp, int level, char branch)
{
	if (tmp == NULL)
		return;
	print_tree(tmp->right, level + 1, '/');
	for (int i = 0; i < level; i++)
		printf("	");
	if (level > 0)
		printf("%c------", branch);
	printf("<%d>\n", tmp->data);
	print_tree(tmp->left, level + 1, '\\');
}
void maxSum(node* temp,int*max, int*current, int**max_path, int**current_path, int *cnt)
{
	if (temp == NULL)
		return;
	(* current_path)[*cnt] = temp->data;
	(*current) = (*current) + temp->data;
	(*cnt)++;
	if (temp->left == NULL && temp->right == NULL)		// Если текущий узел является листом
	{

		if (*cnt > 1 && *current >= *max)
		{
			*max = *current;					// Обновить максимальную сумму и путь, если текущий путь имеет большую сумму
			for (int i = 0; i < *cnt; i++)
				(*max_path)[i] = (*current_path)[i];
		}
	}
	else 												// Рекурсивно искать путь с максимальной суммой в левом и правом поддеревьях
	{
		maxSum(temp->left, max, current, max_path, current_path, cnt);
		maxSum(temp->right, max, current, max_path, current_path, cnt);
	}
	
	(*cnt)--;	
	*current = (*current) - (*current_path)[*cnt];
}
node* search(node* root, int val) 
{
	if (root == NULL || root->data == val) 
	{
		return root;
	}
	if (root->data > val) 
	{
		printf("%i -> ", root->data);
		return search(root->left, val);
	}
	else 
	{
		printf("%i -> ", root->data);
		return search(root->right, val);
	}
}
node* delete(node* root, int val)
{
	if (root == NULL) 
	{
		return root;
	}
	
	if (val < root->data) 
	{
		root->left = delete(root->left, val);
	}
	else if (val > root->data) 
	{
		root->right = delete(root->right, val);
	}
	else 
	{
		if (root->left == NULL && root->right == NULL)
		{
			node* temp = NULL;
			free(root);
			return temp;
		}
		else if (root->left == NULL)
		{
			node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) 
		{
			node* temp = root->left;
			free(root);
			return temp;
		}
		else
		{
			node* temp = minValueNode(root->right);				// 1 раз вправо, до упора влево // минимальное знач пр поддерева
			root->data = temp->data;
			root->right = delete(root->right, temp->data);
		}
	}
	return root;
}
node* minValueNode(node* temp) 
{
	node* current = temp;
	while (current && current->left != NULL) 
	{
		current = current->left;
	}
	return current;
}
void freeTree(node* temp)
{
	if (temp == NULL)
		return;
	freeTree(temp->left);
	freeTree(temp->right);
	free(temp);
}
