#include"Header.h"

int main(int argc, char** argv)
{
	FILE* fp = fopen("console.log", "w+");
	if (fp == NULL)
	{
		printf("The .log file could not be opened!\n:(\n\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("The .log file was opened succesfully!\n:)\n\n");
	}
	
				time_t current_time = time(NULL);
				char* current_time_str = ctime(&current_time);

	fprintf(fp, "[Start the program]:[Successful]:%s \n", current_time_str); // Вывод начальной информации

	int age, task;
	int ember = 0;
	head = NULL;		// указатель на голову на 0
	tail = NULL;		// указатель на хвост на 0
	puts("How old are you O_o ?");
	while (1)   //проверка на ввод  
	{
		int numread = scanf_s("%d", &age);
		char nextchar = getchar();
		if (numread == 1 && (age >= 0 && age <=100) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf("You don't know your age? Really?!\n");
	}
	if (age == 22)
		puts("\033[1;5;38;5;204m* HAPPY BIRTHDAY, BROOO *\033[0m");
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	fprintf(fp, "[Get the age]:[Successful]:%s \n", current_time_str);
	do
	{
		puts("Select an option \033[1;35m1 - 7\033[0m, or enter \033[1;35m0\033[0m to end the program");
		puts("1: \033[1;36mthe remainder\033[0m of the division operation");
		puts("2: \033[1;36mrecommended\033[0m books to read");
		puts("3: \033[1;36msort\033[0m books");
		puts("4: \033[1;36mshow\033[0m all books");
		puts("5: \033[1;36madd\033[0m a new book");
		puts("6: \033[1;36medit\033[0m an existing book");
		puts("7: \033[1;36mdelete\033[0m an existing book");

		while (1)   //проверка на ввод  
		{
			int numread = scanf_s("%d", &task);
			char nextchar = getchar();
			if (numread == 1 && (task >= 0 && task <= 7) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf("Don't do this, please don't break my code!\n");
		}
		fprintf(fp, "[Choose the task]:[Successful]:%s \n", current_time_str);
		switch (task)
		{
		case 1:
			system("cls");  //чистим экран
			if (argc != 3)
			{
				printf("Usage: %s <dividend> <divisor>\n", argv[0]);
				return;
			}

			int dividend = atoi(argv[1]);
			int divisor = atoi(argv[2]);
			if (divisor == 0) 
			{
				printf("Error: division by zero.\n");
				return 1;
			}
			struct division div;
			div.divisor = divisor;
			div.remainder = dividend % divisor;

			printf("%d %% %d = %d\n", dividend, divisor, div.remainder);
			printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
			
			fprintf(fp, "[Division]:[Successful]:%s \n", current_time_str);
			break;
			case 2:
				system("cls");  //чистим экран
				if (head != NULL)
				{
					rec(age);
					fprintf(fp, "[Recommendations]:[Successful]:%s \n", current_time_str);
				}
				else
				{
					fprintf(fp, "[Recommendations]:[Unsuccessful]:%s \n", current_time_str);
					puts("What am I going to show  if you don't have any books?\n");
					printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
				}
				break;
			case 3:
				system("cls");  //чистим экран
				if (head != NULL)
				{
					sort();
					fprintf(fp, "[Sorting]:[Successful]:%s \n", current_time_str);
				}
				else
				{
					puts("What am I going to show  if you don't have any books?\n");
					printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
					fprintf(fp, "[Sorting]:[Unsuccessful]:%s \n", current_time_str);
				}
				break;
			case 4:
				system("cls");  //чистим экран
				showList();		//вывести список книг
				fprintf(fp, "[Show the list]:[Successful]:%s \n", current_time_str);
				break;
			case 5:
				system("cls");  //чистим экран
				add(&ember);
				fprintf(fp, "[Adding the books]:[Successful]:%s \n", current_time_str);
				if (head != NULL)
				{
					showList();
					fprintf(fp, "[Show the list]:[Successful]:%s \n", current_time_str);
				}
				else
				{
					puts("There are no books");
					printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
					fprintf(fp, "[Show the list]:[Unsuccessful]:%s \n", current_time_str);
				}
				break;
			case 6:
				system("cls");  //чистим экран
				if (head != NULL)
				{
					edit();
					fprintf(fp, "[Edit the book]:[Successful]:%s \n", current_time_str);
				}
				else
				{
					puts("What am I going to edit if you don't have any books?\n");
					printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
					fprintf(fp, "[Edit the book]:[Unsuccessful]:%s \n", current_time_str);
				}
				break;
			case 7:
				system("cls");  //чистим экран
				delete();
				showList();
				fprintf(fp, "[Delete the book]:[Successful]:%s \n", current_time_str);
				break;
		case 0:
			system("cls");
			save(ember);
			fprintf(fp, "[Saving]:[Unsuccessful]:%s \n", current_time_str);
			exit(0);        //завершение программы
		}
	} while (task != 0);    //даёт возможность выбора другой задачи или завершения программы
	fprintf(fp, "[End the program]:[Successful]:%s \n", current_time_str);
	fclose(fp); // Закрыть файл после записи
	return 0;
}