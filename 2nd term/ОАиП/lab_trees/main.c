#include"Header.h"

int main()

{
	srand((unsigned int)time(NULL));
	node* root = NULL;
	int task;
	do
	{
		puts("\033[0m________________________________________________________________________________________");
		puts("Select an option \033[1;35m1 - 6\033[0m, or enter \033[1;35m0\033[0m to end the program");
		puts("1: \033[1;36msearching\033[0m for a specific number");
		puts("2: \033[1;36madd\033[0m a node");
		puts("3: \033[1;36mdelete\033[0m a node");
		puts("4: \033[1;36medit\033[0m a node");
		puts("5: \033[1;36mshow\033[0m the tree");
		puts("6: \033[1;36mfind\033[0m the path with the max sum between two nodes");
		check(&task, 0, 6);
		switch (task)
		{
		case 1:
			system("cls");
			int b;
			node* ch;
			puts("________________________________________________________________________________________");
			printf("Enter the value you want to find: \033[1;38;5;204m");
			check(&b, -50, 50);
			printf("\033[0m");
			puts("________________________________________________________________________________________");
			ch = search(root, b);
			if (ch == NULL)
			{
				printf("\033[1;38;5;204mError\033[0m\nThere is no such node in the tree\n");
			}
			else
			{
				printf("\033[1;38;5;204m%i\033[0m\nYou can see the path above\n", ch->data);
				puts("________________________________________________________________________________________");
				puts("\033[1;38;5;204mThe tree:\033[0m");
				print_tree(root, 0, '-');
			}
			break;
		case 2:
			system("cls");
			puts("________________________________________________________________________________________");
			if (root != NULL)
			{
				puts("\033[1;38;5;204mThe tree:\033[0m");
				print_tree(root, 0, '-');
			}
			else
			{
				puts("The tree doesn't exist yet :(");
			}
			puts("________________________________________________________________________________________");
			buildTree(&root);
			print_tree(root, 0, '-');
			break;
		case 3:
			system("cls");
			int c;
			puts("________________________________________________________________________________________");
			puts("\033[1;38;5;204mThe tree:\033[0m");
			print_tree(root, 0, '-');
			puts("________________________________________________________________________________________");
			printf("Enter the value you want to delete: \033[1;38;5;204m");
			check(&c, -50, 50);
			printf("\033[0m");
			puts("________________________________________________________________________________________");
			root = delete(root, c);
			puts("\033[1;38;5;204mThe tree:\033[0m");
			print_tree(root, 0, '-');
			break;
		case 4:
			system("cls");
			int d;
			node* ed;
			if (root == NULL)
			{
				puts("________________________________________________________________________________________");
				puts("The tree doesn't exist yet :(");
				break;
			}
			puts("________________________________________________________________________________________");
			puts("\033[1;38;5;204mThe tree:\033[0m");
			print_tree(root, 0, '-');
			puts("________________________________________________________________________________________");
			printf("Enter the value you want to edit: \033[1;38;5;204m");
			check(&d, -50, 50);
			printf("\033[0m");
			puts("________________________________________________________________________________________");
			ed = search(root, d);
			if (ed == NULL)
			{
				printf("\033[1;38;5;204mError\033[0m\nThere is no such node in the tree\n");
			}
			else
			{
				printf("\033[1;38;5;204m%i\033[0m\nYou can see the path to the value above\n", ed->data);
				puts("________________________________________________________________________________________");
				printf("Enter the the new value: \033[1;38;5;204m");
				if (ed->left != NULL && ed->right != NULL)
					check(&d, ed->left->data, ed->right->data);
				else if (ed->left == NULL)
					check(&d, -50, ed->right->data);
				else if (ed->right == NULL)
					check(&d, ed->left->data, 50);
				else if (ed->left == NULL && ed->right == NULL)
					check(&d, -50, ed->data);
				printf("\033[0m");
				ed->data = d;
				puts("________________________________________________________________________________________");
				puts("\033[1;38;5;204mThe tree:\033[0m");
				print_tree(root, 0, '-');
			}
			break;
		case 5:
			system("cls");
			puts("________________________________________________________________________________________");
			puts("\033[1;38;5;204mThe tree:\033[0m");
			print_tree(root, 0, '-');
			break;
		case 6:
			system("cls");
			puts("________________________________________________________________________________________");
			puts("\033[1;38;5;204mThe tree:\033[0m");
			print_tree(root, 0, '-');
			int max = 0, current = 0, cnt = 0;
			int* max_path = (int*)calloc(50, sizeof(int));
			int* current_path = (int*)calloc(50, sizeof(int));
			node* lupa = root;
			while (1)
			{
				if (lupa->data < 0 && lupa->right != NULL)
					lupa = lupa->right;
				else if (lupa->data < 0 && lupa->left != NULL)
					lupa = lupa->left;
				else break;
			}
			maxSum(lupa, &max, &current, &max_path, &current_path, &cnt);
			maxSum(root, &max, &current, &max_path, &current_path, &cnt);
			int summ = 0;
			puts("________________________________________________________________________________________");
			printf("\033[1;38;5;204mMax sum:\033[0m %d\n", max);
			printf("\033[1;38;5;204mPath: \033[0m");
			for (int i = 0; summ < max; i++)
			{
				summ += max_path[i];
				printf("%d -> ", max_path[i]);
			}
			printf("NULL\n");
			break;
		case 0:
			system("cls");
			print_tree(root, 0, '-');
			freeTree(root);
			print_tree(root, 0, '-');
			puts("Bye-bye!");
			exit(0);        //завершение программы
		}
	} while (task != 0);    //даёт возможность выбора другой задачи или завершения программы
	return 0;
}