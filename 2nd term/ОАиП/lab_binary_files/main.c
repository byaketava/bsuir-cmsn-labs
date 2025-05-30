#include"Header.h"

int main(int argc, char* argv[])
{
	system("CLS");
	int size = 0;
	puts("________________________________________________________________");
	if (argc != 2)
	{
		printf("\033[1;35mUsage:\033[0m\n%s file_name\n\n", argv[0]); 
		puts("Try again ;)");
		puts("________________________________________________________________");
		exit(EXIT_FAILURE);
	}
	//имя файла сохранить в name 
	char* name = argv[1];
	option4(name, &size);
	//вывод содержимого файла
	int* numbers = (int*)malloc(size * sizeof(int));
	option5(name, size, numbers);

	int task;
	do
	{
		puts("Select an option (\033[1;35m1\033[0m, \033[1;35m2\033[0m, \033[1;35m3\033[0m, \033[1;35m4\033[0m, \033[1;35m5\033[0m, \033[1;35m6\033[0m or enter \033[1;35m0\033[0m to end the program");
		puts("1: \033[1;36mfind the longest sequence\033[0m of equal elements");
		puts("2: \033[1;36mturn to zero\033[0m the elements standing in positions with \033[1;36meven\033[0m numbers");
		puts("   (starting from 0, starting from the left)");
		puts("3: \033[1;36msort the file\033[0m this way - even ones on the left, zeros in the middle,");
		puts("   odd ones on the right. Do not change the order of the elements");
		puts("4: \033[1;36mrewrite\033[0m the data in the file");
		puts("5: \033[1;36madd\033[0m data to the file");
		puts("6: \033[1;36mshow\033[0m file data");

		while (1)   //проверка на ввод  
		{
			int numread = scanf_s("%d", &task);
			char nextchar = getchar();
			if (numread == 1 && (task == 2 || task == 1 || task == 0 || task == 3 || task == 4 || task == 5 || task == 6) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf("Don't do this, please don't break my code!\n");
		}
		switch (task)
		{
		case 1:
			system("cls");  //чистим экран
			option5(name, size, numbers);
			option1(name, size, numbers);
			break;
		case 2:
			system("cls");  //чистим экран
			option5(name, size, numbers);
			option2(name, size, numbers);
			option5(name, size, numbers);
			break;
		case 3:
			system("cls");  //чистим экран
			option5(name, size, numbers);
			option3(name, size);
			option5(name, size, numbers);
			break;
		case 4:
			system("cls");  //чистим экран
			option4(name, &size);
			option5(name, size, numbers);
			break;
		case 5:
			system("cls");  //чистим экран
			option6(name, &size);
			option5(name, size, numbers);
			break;
		case 6:
			system("cls");  //чистим экран
			option5(name, size, numbers);
			break;
		case 0:
			exit(0);        //завершение программы
		}
	} while (task != 0);    //даёт возможность выбора другой задачи или завершения программы
	return 0;
}