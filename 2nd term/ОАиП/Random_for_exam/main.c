#include"Header.h"

int main()
{
	srand((unsigned int)time(NULL));
	int task;
	do
	{
		puts("______________________________________");
		scanf("%i", &task);
		switch (task)
		{
		case 1:
			system("cls");
			t1();
			break;
		case 2:
			system("cls");
			t2();
			break;
		case 3:
			system("cls");
			t3();
			break;
		case 111:
			system("cls");
			taska_kati();
			break;
		case 4:
			system("cls");
			t4();
			break;
		case 8:
			system("cls");
			t8();
			break;
		case 9:
			system("cls");
			int n = 12;
			int mas[12];
			for (int k = 0; k < 12; k++)
			{
				mas[k] = rand() % 21;
				printf("%-3i ", mas[k]);
			}
			printf("\n\n");
			shell_sort(n, mas);
			printf("\n\n");
			for (int k = 0; k < 12; k++)
			{
				printf("%-3i ", mas[k]);
			}
			printf("\n");
			break;
		case 0:
			return 0;
		default:
			break;
		}
	} while (task != 0);
}