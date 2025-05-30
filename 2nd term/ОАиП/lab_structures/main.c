#include"Header.h"

int main()
{
	int ember=0;
	int size = 0;
	BOOK* library = NULL;
	//(BOOK*)malloc(sizeof(BOOK) * size);
	int task;
	do
	{
		puts("Select an option \033[1;35m1 - 7\033[0m, or enter \033[1;35m0\033[0m to end the program");
		puts("1: \033[1;36mfind\033[0m N the most popular books");
		puts("2: \033[1;36mfind all books\033[0m of the selected author");
		puts("3: \033[1;36msort\033[0m books");
		puts("4: \033[1;36mshow\033[0m all books");
		puts("5: \033[1;36madd\033[0m a new book");
		puts("6: \033[1;36medit\033[0m an existing book");
		puts("7: \033[1;36mdelete\033[0m an existing book");

		while (1)   //ïğîâåğêà íà ââîä  
		{
			int numread = scanf_s("%d", &task);
			char nextchar = getchar();
			if (numread == 1 && (task >=0 && task <= 7) && (nextchar == '\n' || nextchar == ' '))
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
			system("cls");  //÷èñòèì ıêğàí
			if (size != 0)
				option1(&library, size);
			else
			{
				puts("What am I going to show you if you don't have any books?\n");
				printf("--------------------------------------------------------------------------------------------------------------------\n");
			}
			break;
		case 2:
			system("cls");  //÷èñòèì ıêğàí
			if (size != 0)
				option2(&library, size);
			else
			{
				puts("What am I going to show you if you don't have any books?\n");
				printf("--------------------------------------------------------------------------------------------------------------------\n");
			}
			break;
		case 3:
			system("cls");  //÷èñòèì ıêğàí

			if (size != 0)
				option3(size, &library, comparator);
			else
			{
				puts("What am I going to show you if you don't have any books?\n");
				printf("--------------------------------------------------------------------------------------------------------------------\n");
			}
			break;
		case 4:
			system("cls");  //÷èñòèì ıêğàí
			if (size != 0)
				option4(library, 0, size);
			else
			{
				puts("What am I going to show you if you don't have any books?\n");
				printf("--------------------------------------------------------------------------------------------------------------------\n");
			}
			break;
		case 5:
			system("cls");  //÷èñòèì ıêğàí
			option5(&size, &library, &ember);
			break;
		case 6:
			system("cls");  //÷èñòèì ıêğàí
			if (size != 0)
				option6(&library, size);
			else
			{
				puts("What am I going to edit you if you don't have any books?\n");
				printf("--------------------------------------------------------------------------------------------------------------------\n");
			}
			break;
		case 7:
			system("cls");  //÷èñòèì ıêğàí
			option7(&size, &library);
			break;
		case 0:
			system("cls");
			option0(&size, &library, ember);
			exit(0);        //çàâåğøåíèå ïğîãğàììû
		}
	} while (task != 0);    //äà¸ò âîçìîæíîñòü âûáîğà äğóãîé çàäà÷è èëè çàâåğøåíèÿ ïğîãğàììû
	return 0;
}