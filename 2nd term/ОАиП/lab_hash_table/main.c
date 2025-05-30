#include"drift.h"

int main()
{
	srand(time(NULL));
	int task;
	table** hhh = (table**)calloc(size, sizeof(table*));
	do
	{
		puts("\033[0m________________________________________________________________________________________");
		puts("Select an option \033[1;35m1 - 5\033[0m, or enter \033[1;35m0\033[0m to end the program");
		puts("1: \033[1;36mupload\033[0m N strings");
		puts("2: \033[1;36madd\033[0m a string");
		puts("3: \033[1;36mdelete\033[0m a string by its entry");
		puts("4: \033[1;36mfind\033[0m ip by entered string");
		puts("5: \033[1;36mshow\033[0m table");
		check(&task, 0, 5);
		switch (task)
		{
		case 1:
			system("cls");
			int N;
			puts("________________________________________________________________________________________");
			puts("How many strings do you want to upload?");
			check(&N,1,size);
			read_N(hhh, N);
			puts("________________________________________________________________________________________");
			print_table(hhh);
			break;
		case 2:
			system("cls");
			puts("________________________________________________________________________________________");
			hands(hhh);
			print_table(hhh);
			break;
		case 3:
			system("cls");
			puts("________________________________________________________________________________________");
			print_table(hhh);
			puts("________________________________________________________________________________________");
			delete(hhh);
			puts("________________________________________________________________________________________");
			print_table(hhh);
			break;
		case 4:
			system("cls");
			puts("________________________________________________________________________________________");
			print_table(hhh);
			puts("________________________________________________________________________________________");
			printf("\nip: %s\n", find(hhh));
			break;
		case 5:
			system("cls");
			puts("________________________________________________________________________________________");
			print_table(hhh);
			break;
		case 0:
			system("cls");
			puts("Bye-bye!");
			exit(0);        //завершение программы
		}
	} while (task != 0);    //даёт возможность выбора другой задачи или завершения программы

	return 0;
}