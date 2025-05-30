#include"header.h"

int main(int argc, char* argv[])
{
	system("CLS");
	char s; //для хранения символа считанного
	int size = 0;
	FILE* fp;

	puts("________________________________________________________________");
	/* && (argv[1] == "CON" || argv[1] == "PRN" ||
	argv[1] == "AUX" || argv[1] == "NUL" || argv[1] == "COM1" ||
		argv[1] == "COM2" || argv[1] == "COM3" || argv[1] == "COM4" ||
		argv[1] == "COM5" || argv[1] == "COM6" || argv[1] == "COM7" ||
		argv[1] == "COM8" || argv[1] == "COM9" || argv[1] == "LPT1" ||
		argv[1] == "LPT2" || argv[1] == "LPT3" || argv[1] == "LPT4" ||
		argv[1] == "LPT5" || argv[1] == "LPT6" || argv[1] == "LPT7" ||
		argv[1] == "LPT8" || argv[1] == "LPT9")*/
	if (argc != 2)
	{
		printf("\033[1;35mUsage:\033[0m\n%s file_name\n\n", argv[0]); //add color to using and flashing for name
		puts("Try again ;)");
		puts("________________________________________________________________");
		exit(EXIT_FAILURE);
	}
	char* name = argv[1];
	if ((fp = fopen(argv[1], "wt")) == NULL)
	{
		printf("The file %s could not be opened!\n:(\n", argv[1]);
		puts("________________________________________________________________");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("The file \033[1;35m%s\033[0m was created successfully!\n:)\n", argv[1]);
	}
	puts("________________________________________________________________");
	puts("Use the \033[1;36mkeyboard\033[0m to fill in the file with \033[1;36mnumbers\033[0m");

	while (1)   //проверка на ввод
	{

		s = getchar();
		if (((s >= '0' && s <= '9') || s == ' ' || s == '\n'))
			fputc(s, fp);
		else if (s == EOF)
			break;
		else
		{
			printf("Don't do this, please don't break my file!\n");
			exit(EXIT_FAILURE);
		}
	}
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	fclose(fp);
	puts("________________________________________________________________");

	if ((fp = fopen(argv[1], "rt")) == NULL)
	{
		printf("The file %s could not be opened!\n:(\n", argv[1]);
		puts("________________________________________________________________");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("The file \033[1;35m%s\033[0m was opened for reading successfully!\n:)\n", argv[1]);
	}
	puts("________________________________________________________________");
	puts("The file \033[1;36mcontains\033[0m:");
	while ((s = getc(fp)) != EOF)
	{
		printf("%c", s);
	}
	fclose(fp);
	puts("________________________________________________________________");

	int task;
	do
	{
		puts("Select an option (\033[1;35m1\033[0m, \033[1;35m2\033[0m, \033[1;35m3\033[0m, \033[1;35m4\033[0m or \033[1;35m5\033[0m), or enter \033[1;35m0\033[0m to end the program");
		puts("1: \033[1;36mrewrite\033[0m  the data in the file");
		puts("2: \033[1;36madd\033[0m data to the file");
		puts("3: \033[1;36mshow\033[0m file data");
		puts("4: \033[1;36mdetermine the maximum number\033[0m recorded in the file");
		puts("5: \033[1;36mflip the number in the file\033[0m, the ordinal number of which is set from the keyboard");
		while (1)   //проверка на ввод только 1, 2 или 0 
		{
			int numread = scanf_s("%d", &task);
			char nextchar = getchar();
			if (numread == 1 && (task == 2 || task == 1 || task == 0 || task == 3 || task == 4 || task == 5) && (nextchar == '\n' || nextchar == ' '))
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
			option1(name, &size);
			option3(name, size);
			break;
		case 2:
			system("cls");  //чистим экран
			option2(name, &size);
			option3(name, size);
			break;
		case 3:
			system("cls");  //чистим экран
			option3(name, size);
			break;
		case 4:
			system("cls");  //чистим экран
			option4(name, size);
			break;
		case 5:
				system("cls");  //чистим экран
				char* str = readLine(name, size);

				puts("Enter the order of the number:");

				
				int k;
				 scanf_s("%d", &k);
				int space = 0, i = 0;
				while (space < k - 1)
				{
					if ((str[i] == ' ') || (str[i] == '\n'))
					{
						space++;
					}
					i++;
				}
				int j = i + 1;
				while ((str[j] != ' ') && (str[j] != '\n'))
					j++;
				j--;
				obmen(str, i, j);
				for (int q = 0; q < size; q++)
				{
					printf("%c", str[q]);
				}
				

				fopen_s(&fp, name, "w");
				fputs(str, fp);
				fclose(fp);
				puts("\n________________________________________________________________");

				break;
		case 0:
			exit(0);        //завершение программы
		}
	} while (task != 0);    //даёт возможность выбора другой задачи или завершения программы


	

	return 0;
}



