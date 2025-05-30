#include"Header.h"

int main()
{
	srand((unsigned int)time(NULL));		// рандом псевдослучайный
	head1 = tail1 = head2 = tail2 = head3 = tail3 = NULL;
	int task;
	do
	{
		puts("Select an option \033[1;35m1 - 4\033[0m, or enter \033[1;35m0\033[0m to end the program");
			puts("1: \033[1;36mcreate\033[0m a third queue sorted in ascending order");
			puts("2: \033[1;36madd\033[0m elements to 1 and 2 queues");
			puts("3: \033[1;36mdelete\033[0m an element of queue");
			puts("4: \033[1;36mshow\033[0m the queues");
		check(&task, 0, 4);
		switch (task)
		{
		case 1:
			system("cls");  //чистим экран
			two_to_one(&head1, &tail1, &head2, &tail2, &head3, &tail3);
			print(head3);
			break;
		case 2:
			system("cls");  //чистим экран
			puts("The first queue:\n");
			create(&head1, &tail1);
			if (head1 != NULL)
			{
				sort(&head1, 1);
				print(head1);
			}
			else
			{
				puts("What am I going to show if you don't have any books?\n");
				printf("-----------------------------------------------------------------------\n");
			}
			puts("The second queue:\n");
			create(&head2, &tail2);
			if (head2 != NULL)
			{
				sort(&head2,2);
				print(head2);
			}
			else
			{
				puts("What am I going to show if you don't have any books?\n");
				printf("-----------------------------------------------------------------------\n");
			}
			break;
		case 3:
			system("cls");  //чистим экран
			delete();
			break;
		case 4:
			system("cls");  //чистим экран
			if (head1 != NULL)
			{
				printf("1 ");
				print(head1);
			}
			else
			{
				printf("The 1 queue is empty\n");
				printf("-----------------------------------------------------------------------\n");
			}
			if (head2 != NULL)
			{
				printf("2 ");
				print(head2);
			}
			else
			{
				printf("The 2 queue is empty\n");
				printf("-----------------------------------------------------------------------\n");
			}
			if (head3 != NULL)
			{
				printf("3 ");
				print(head3);
			}
			else
			{
				printf("The 3 queue is empty\n");
				printf("-----------------------------------------------------------------------\n");
			}
			break;
		case 0:
			system("cls");
			exit(0);        //завершение программы
		}
	} while (task != 0);    //даёт возможность выбора другой задачи или завершения программы
	return 0;
}