#include"Header.h"

//option 1	самые попул€рные
//option 2	выбранного автора
//option 3	сортировка по каждому из полей структуры или по нескольким
//option 4	вывести все
//option 5	добавить книжку
//option 6	изменить существующую
//option 7	удалить книжку
//option 0	хотите сохранить?
/*  
	id
	title[40]
	author[40]
	year
	popularity
*/
//size - кол-во книг на данный момент

void option1(BOOK** pororo, int size)
{
	int N;
	BOOK tmp;
	for (int i = size-1; i>0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if ((*pororo)[j].popularity < (*pororo)[j + 1].popularity)
			{
				tmp = (*pororo)[j];
				(*pororo)[j] = (*pororo)[j + 1];
				(*pororo)[j + 1] = tmp;
			}
		}
	}
	puts("How many of the most popular books should be displayed on the screen?");
	while (1)   //проверка на ввод  
	{
		int numread = scanf_s("%d", &N);
		char nextchar = getchar();
		if (numread == 1 && (N >0 && N <= size) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf("Aboba?..\n");
	}
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	printf("The most popular %i books are:\n", N);
	option4(*pororo, 0, N);
}
void option2(BOOK** pororo, int size)
{
	char str[41];
	BOOK tmp;
	option4(*pororo, 0, size);


	puts("Choose the author by id of the book");
	int pupa;
	int k = 0;

	scanf_s("%lu", &pupa);
	for (int i = 0; i < size; i++)
	{
		if (pupa == (*pororo)[i].id)
		{
			strncpy(str, (*pororo)[i].author, 40);
			k++;

		}
	};
	if (k == 0)
	{
		rewind(stdin);
		puts("There are no books with such an id");
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		return;
	}

	for (int i = size - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (strcmp((*pororo)[j].author, (*pororo)[j + 1].author) > 0)
			{
				tmp = (*pororo)[j];
				(*pororo)[j] = (*pororo)[j + 1];
				(*pororo)[j + 1] = tmp;
			}
		}
	}
	int first = 0, last = 0;
	for (int i = 0; i < size; i++)
	{
		if (strcmp(str, (*pororo)[i].author) == 0 && ((strcmp(str, (*pororo)[i - 1].author) != 0) || i == 0))
		{
			first = i;
		}
		if (strcmp(str, (*pororo)[i].author) == 0 && ((strcmp(str, (*pororo)[i + 1].author) != 0) || i == size - 1))
		{
			last = i;
		}
	}
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	printf("The book(s) of the chosen author:\n");
	option4(*pororo, first, last + 1);
}
void option3(int size, BOOK** pororo, int (*comparator)(BOOK*, int,  int))
{
	BOOK tmp;
	int looopa, pooopa;
	enum perechen characteristic;
	puts("Choose the type of sort:\n1. By 1 characteristic\n2. By 2 and more characteristics");
	while (1)   //проверка на ввод  
	{
		int numread = scanf_s("%d", &looopa);
		char nextchar = getchar();
		if (numread == 1 && (looopa == 1 || looopa == 2) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf("Don't do this, please don't break my code!\n");
	}

	if (looopa == 1)
	{
		do
		{
			puts("By which characteristic do you want to sort? (choose an option (1 to 5) below)\n1. ID\n2. Title\n3. Author\n4. Year\n5. Popularity\n0 ->  back to the menu");
			while (1)   //проверка на ввод  
			{
				int numread = scanf_s("%d", &characteristic);
				char nextchar = getchar();
				if (numread == 1 && (characteristic >= 0 && characteristic < 6) && (nextchar == '\n' || nextchar == ' '))
					break;
				if (nextchar != '\n')
				{
					while (getchar() != '\n')
						continue;
				}
				printf(":(\n");
			}
			printf("--------------------------------------------------------------------------------------------------------------------\n");
			switch (characteristic)
			{
			case id:
				for (int i = size - 1; i > 0; i--)
				{
					for (int j = 0; j < i; j++)
					{
						if ((*pororo)[j].id > (*pororo)[j + 1].id)
						{
							tmp = (*pororo)[j];
							(*pororo)[j] = (*pororo)[j + 1];
							(*pororo)[j + 1] = tmp;
						}
					}
				}
				option4(*pororo, 0, size);
				break;
			case title:
				for (int i = size - 1; i > 0; i--)
				{
					for (int j = 0; j < i; j++)
					{
						if (strcmp((*pororo)[j].title, (*pororo)[j + 1].title) > 0)
						{
							tmp = (*pororo)[j];
							(*pororo)[j] = (*pororo)[j + 1];
							(*pororo)[j + 1] = tmp;
						}
					}
				}
				option4(*pororo, 0, size);
				break;
			case author:
				for (int i = size - 1; i > 0; i--)
				{
					for (int j = 0; j < i; j++)
					{
						if (strcmp((*pororo)[j].author, (*pororo)[j + 1].author) > 0)
						{
							tmp = (*pororo)[j];
							(*pororo)[j] = (*pororo)[j + 1];
							(*pororo)[j + 1] = tmp;
						}
					}
				}
				option4(*pororo, 0, size);
				break;
			case year:
				for (int i = size - 1; i > 0; i--)
				{
					for (int j = 0; j < i; j++)
					{
						if ((*pororo)[j].year > (*pororo)[j + 1].year)
						{
							tmp = (*pororo)[j];
							(*pororo)[j] = (*pororo)[j + 1];
							(*pororo)[j + 1] = tmp;
						}
					}
				}
				option4(*pororo, 0, size);
				break;
			case popularity:
				for (int i = size - 1; i > 0; i--)
				{
					for (int j = 0; j < i; j++)
					{
						if ((*pororo)[j].popularity > (*pororo)[j + 1].popularity)
						{
							tmp = (*pororo)[j];
							(*pororo)[j] = (*pororo)[j + 1];
							(*pororo)[j + 1] = tmp;
						}
					}
				}
				option4(*pororo, 0, size);
				break;
			case 0:
				system("cls");
				break;
			}
		} while (characteristic != 0);
	}
	else
	{
	printf("--------------------------------------------------------------------------------------------------------------------\n");
		puts("Choose the sort type:\n1. Author -> title\n2. Author -> year\n3. Author -> popularity\n4. Year -> popularity\n5. Author -> year -> popularity");
		while (1)   //проверка на ввод  
		{
			int numread = scanf_s("%d", &pooopa);
			char nextchar = getchar();
			if (numread == 1 && (pooopa > 0 && pooopa < 6) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf("Don't do this, please don't break my code!\n");
		}
		

		for (int i = size - 1; i > 0; i--)
		{
			for (int j = 0; j < i; j++)
			{
				if (comparator(*pororo, j, pooopa) > 0)
				{
					tmp = (*pororo)[j];
					(*pororo)[j] = (*pororo)[j + 1];
					(*pororo)[j + 1] = tmp;
				}

			}
		}

	}
	option4(*pororo, 0, size);
}
void option4(BOOK *pororo, int i, int j)
{
	printf(" __________________________________________________________________________________________________________________ \n");
	printf("|                                                                                                                  |\n");
	printf("|                                                  \033[1;5;38;5;204m%c\033[0m BOOK LIST \033[1;5;38;5;204m%c\033[0m                                                   |\n", 4, 4);
	printf("|__________________________________________________________________________________________________________________|\n");
	printf("|        |                                          |                                          |      |            |\n");
	printf("|   \033[1;38;5;204mid\033[0m   |                  \033[1;38;5;204mtitle\033[0m                   |                  \033[1;38;5;204mauthor\033[0m                  | \033[1;38;5;204myear\033[0m | \033[1;38;5;204mpopularity\033[0m |\n");
	printf("|________|__________________________________________|__________________________________________|______|____________|\n");
	for (i; i < j-1; i++)
	{
		printf("|        |                                          |                                          |      |            |\n");
		printf("| %06i | %-40s | %-40s | %-4i | %-10i |\n", pororo[i].id, pororo[i].title, pororo[i].author, pororo[i].year, pororo[i].popularity);
		printf("|________|__________________________________________|__________________________________________|______|____________|\n");
	};
	printf("|        |                                          |                                          |      |            |\n");
	printf("| %06i | %-40s | %-40s | %-4i | %-10lu |\n", pororo[j-1].id, pororo[j - 1].title, pororo[j - 1].author, pororo[j - 1].year, pororo[j - 1].popularity);
	printf("|________|__________________________________________|__________________________________________|______|____________|\n\n");
	printf("--------------------------------------------------------------------------------------------------------------------\n");
}
void option5(int* size, BOOK** pororo, int* ember)
{
	char strt[40];
	int size_struct = sizeof(BOOK);
	FILE* ptrbooks;
	int eu;
	puts("do you want to add books from a file or a book by yourself?\n1. File (^-^)\n2. Hands (o_O)");
	while (1)   //проверка на ввод  
	{
		int numread = scanf_s("%d", &eu);
		char nextchar = getchar();
		if (numread == 1 && (eu == 1 || eu == 2) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf("Aboba?..\n");
	}
	printf("--------------------------------------------------------------------------------------------------------------------\n");
	if (eu == 2)
	{
		(*size)++;
		//BOOK* library = (BOOK*)malloc(sizeof(BOOK) * SIZE)
		if ((*size) != 0)
		{
			*pororo = (BOOK*)realloc(*pororo, size_struct * (*size));
		}
		printf("Write down an id:\n");
		while (1)   //проверка на ввод  
		{
			int numread = scanf_s("%lu", &(*pororo)[(*size) - 1].id);
			char nextchar = getchar();
			if (numread == 1 && (*pororo)[(*size) - 1].id >= 0 && (*pororo)[(*size) - 1].id <= 999999 && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf(":(\n");
		}
		rewind(stdin);
		printf("--------------------------------------------------------------------------------------------------------------------\n");

		printf("Write down a title:\n");
		fgets(strt, 40, stdin);
		strt[strlen(strt) - 1] = 0;
		strncpy((*pororo)[(*size) - 1].title, strt, 40);
		rewind(stdin);
		printf("--------------------------------------------------------------------------------------------------------------------\n");

		printf("Write down an author:\n");
		fgets(strt, 40, stdin);
		strt[strlen(strt) - 1] = 0;
		strncpy((*pororo)[(*size) - 1].author, strt, 40);
		rewind(stdin);
		printf("--------------------------------------------------------------------------------------------------------------------\n");

		printf("Write down a year:\n");
		while (1)   //проверка на ввод  
		{
			int numread = scanf_s("%lu", &(*pororo)[(*size) - 1].year);
			char nextchar = getchar();
			if (numread == 1 && ((*pororo)[(*size) - 1].year <= 2023) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf(":(\n");
		}
		rewind(stdin);
		printf("--------------------------------------------------------------------------------------------------------------------\n");

		printf("Write down a popularity:\n");
		while (1)   //проверка на ввод  
		{
			int numread = scanf_s("%lu", &(*pororo)[(*size) - 1].popularity);
			char nextchar = getchar();
			if (numread == 1 && ((*pororo)[(*size) - 1].popularity <= 999999999 && (*pororo)[(*size) - 1].popularity >= 0) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf(":(\n");
		}
		rewind(stdin);
		printf("--------------------------------------------------------------------------------------------------------------------\n");
	}
	else
	{
		puts("Choose one of the files below:\n1. Test\n2. Trojan horse\n3. Nothing\n4. Your library");
		while (1)   //проверка на ввод  
		{
			int numread = scanf_s("%d", ember);
			char nextchar = getchar();
			if (numread == 1 && (eu >= 1 && eu <= 4) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf("Aboba?..\n");
		}
		int cntr = 0;int amount =0;
		switch (*ember)
		{
		case 1:
			system("cls");
			if ((ptrbooks = fopen("Test", "a+b")) == NULL)
			{
				puts("The file cannot be opened :(");
				exit(EXIT_FAILURE);
			}
			else
				puts("The file was opened successfully!");
			rewind(ptrbooks);
			fread(&amount, sizeof(int), 1, ptrbooks);//кол-во добавл€емых книг
			if (amount != 0)//если кол-во не равно 0
			{
				*pororo = (BOOK*)realloc(*pororo, size_struct * ((*size) + amount));//выдел€ем на старые+новые
			}
			while (cntr < (amount) && fread(&(*pororo)[(*size) + cntr], sizeof(BOOK), 1, ptrbooks) == 1)
			{
				cntr++;
			}
			fclose(ptrbooks);
			break;
		case 2:
			system("cls");
			if ((ptrbooks = fopen("Trojan horse", "a+b")) == NULL)
			{
				puts("The file cannot be opened :(");
				exit(EXIT_FAILURE);
			}
			else
				puts("The file was opened successfully!");
			rewind(ptrbooks);
			fread(&amount, sizeof(int), 1, ptrbooks);//кол-во добавл€емых книг
			if (amount != 0)//если кол-во не равно 0
			{
				*pororo = (BOOK*)realloc(*pororo, size_struct * ((*size) + amount));//выдел€ем на старые+новые
			}
			while (cntr < (amount) && fread(&(*pororo)[(*size) + cntr], sizeof(BOOK), 1, ptrbooks) == 1)
			{
				cntr++;
			}
			fclose(ptrbooks);
			break;
		case 3:
			system("cls");
			puts("I said N-O-T-H-I-N-G, why don't you understand?..");
			break;
		case 4:
			system("cls");
			if ((ptrbooks = fopen("library", "a+b")) == NULL)
			{
				puts("The file cannot be opened :(");
				exit(EXIT_FAILURE);
			}
			else
				puts("The file was opened successfully!");
			rewind(ptrbooks);
			fread(&amount, sizeof(int), 1, ptrbooks);//кол-во добавл€емых книг
			if (amount != 0)//если кол-во не равно 0
			{
				*pororo = (BOOK*)realloc(*pororo, size_struct * ((*size) + amount));//выдел€ем на старые+новые
			}
			while (cntr < (amount) && fread(&(*pororo)[(*size) + cntr], sizeof(BOOK), 1, ptrbooks) == 1)
			{
				cntr++;
			}
			fclose(ptrbooks);
			break;
		}
		if ((*size)+amount!=0)
		option4(*pororo, 0, (*size) + amount);
		else
		{
			puts("There are no books");
			printf("--------------------------------------------------------------------------------------------------------------------\n");
		}
		(*size) = (*size) + amount;
	}
	
}
void option6(BOOK**pororo, int size)
{
	char strt[41];
	enum perechen characteristic;
	option4(*pororo, 0, size);
	int k = -1;
	int cntr = 0;
	unsigned long pupa;
	puts("Which book do you want to edit? (write an id below)");//id цветом
	while (1)
	{
		scanf_s("%lu", &pupa);
		for (int i = 0; i < size; i++)
		{
			if (pupa == (*pororo)[i].id)
			{
				k = i;
				break;
			}
		};
		if (k == -1)
		{
			rewind(stdin);
			puts("Wrong input, try again");
		}
		else
		{
			printf("--------------------------------------------------------------------------------------------------------------------\n");
			option4(*pororo, k, k + 1);
			break;
		}
	}
	do
	{
		puts("Which characteristic do you want to edit? (choose an option (1 to 5) below)\n1. ID\n2. Title\n3. Author\n4. Year\n5. Popularity\n0 ->  back to the menu");//id цветом
		while (1)   //проверка на ввод  
		{
			int numread = scanf_s("%d", &characteristic);
			char nextchar = getchar();
			if (numread == 1 && (characteristic >= 0 && characteristic < 6) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf(":(\n");
		}
		printf("--------------------------------------------------------------------------------------------------------------------\n");
		switch (characteristic)
		{
		case id:
			printf("Write down a new id:\n");
			while (1)   //проверка на ввод  
			{
				int numread = scanf_s("%lu", &(*pororo)[k].id);
				char nextchar = getchar();
				if (numread == 1 && (*pororo)[k].id>=0 && (*pororo)[k].id <= 999999 && (nextchar == '\n' || nextchar == ' '))
					break;
				if (nextchar != '\n')
				{
					while (getchar() != '\n')
						continue;
				}
				printf(":(\n");
			}
			rewind(stdin);
			printf("--------------------------------------------------------------------------------------------------------------------\n");
			option4(*pororo, k, k + 1);
			break;
		case title:
			printf("Write down a new title:\n");
			gets_s(strt, 40);
			strncpy((*pororo)[k].title, strt, 40);
			rewind(stdin);
			printf("--------------------------------------------------------------------------------------------------------------------\n");
			option4(*pororo, k, k + 1);
			break;
		case author:
			printf("Write down a new author:\n");
			gets_s(strt, 40);
			strncpy((*pororo)[k].author, strt, 40);
			rewind(stdin);
			printf("--------------------------------------------------------------------------------------------------------------------\n");
			option4(*pororo, k, k + 1);
			break;
		case year:
			printf("Write down a new year:\n");
			while (1)   //проверка на ввод  
			{
				int numread = scanf_s("%lu", &(*pororo)[k].year);
				char nextchar = getchar();
				if (numread == 1 && ((*pororo)[k].year <=2023) && (nextchar == '\n' || nextchar == ' '))
					break;
				if (nextchar != '\n')
				{
					while (getchar() != '\n')
						continue;
				}
				printf(":(\n");
			}
			rewind(stdin);
			printf("--------------------------------------------------------------------------------------------------------------------\n");
			option4(*pororo, k, k + 1);
			break;
		case popularity:
			printf("Write down a new popularity:\n");
			while (1)   //проверка на ввод  
			{
				int numread = scanf_s("%lu", &(*pororo)[k].popularity);
				char nextchar = getchar();
				if (numread == 1 && ((*pororo)[k].popularity <= 999999999 && (*pororo)[k].popularity >=0) && (nextchar == '\n' || nextchar == ' '))
					break;
				if (nextchar != '\n')
				{
					while (getchar() != '\n')
						continue;
				}
				printf(":(\n");
			}
			rewind(stdin);
			printf("--------------------------------------------------------------------------------------------------------------------\n");
			option4(*pororo, k, k + 1);
			break;
		case 0:
			system("cls");
			break;
		}
	} while (characteristic != 0);
}
void option7(int* size, BOOK** pororo)
{
	int pupa;
	int k = 0;
	if ((*size) == 0)
		puts("You don't have any books yet, what are you going to delete?\n");
	else
	{
		option4(*pororo, 0, (*size));
		puts("Enter the id of the book you want to delete");
		while (1)
		{
			scanf_s("%lu", &pupa);
			for (int i = 0; i < (*size); i++)
			{
				if (pupa == (*pororo)[i].id)
				{
					for (int j = i; j < (*size) - 1; j++)
					{
						(*pororo)[j] = (*pororo)[j + 1];
					}
					(*size)--;
					if ((*size) != 0)//если кол-во не равно 0
					{
						*pororo = (BOOK*)realloc(*pororo, sizeof(BOOK) * (*size));//обрезаем конец
					}
					k++;
				}
			};
			if (k == 0)
			{
				rewind(stdin);
				puts("There are no books with such an id\n");
			}
			break;
		}
		if((* size)!=0)
		option4(*pororo, 0, (*size));
		else
		{
			puts("There no more books");
			printf("--------------------------------------------------------------------------------------------------------------------\n");
		}
	}
}
void option0(int *size, BOOK ** pororo, int ember)
{
	int size_struct = sizeof(BOOK);
	FILE* ptrbooks;
	int eu;
	int count = 0;
	puts("Do yo want to save your books?\n1. YES!\n2. nope (>_<)");
	while (1)   //проверка на ввод  
	{
		int numread = scanf_s("%d", &eu);
		char nextchar = getchar();
		if (numread == 1 && (eu == 1 || eu == 2) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf("Aboba?..\n");
	}
	if (eu == 2)
		puts("\n-----------\n  oboltus  \n-----------");
	else
	{
		if (ember == 4)
		{
			if ((ptrbooks = fopen("library", "w+b")) == NULL)
			{
				puts("The file cannot be opened :(");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if ((ptrbooks = fopen("library", "a+b")) == NULL)
			{
				puts("The file cannot be opened :(");
				exit(EXIT_FAILURE);
			}
		}
		rewind(ptrbooks);
		fwrite(size, sizeof(int), 1, ptrbooks);
		while (count < (* size) && fwrite(&(*pororo)[count], sizeof(BOOK), 1, ptrbooks) == 1)
		{
			count++;
		}
		puts("\n-----------------------------------");
		puts("  Your library is safe now, enjoy  ");
		puts("-----------------------------------");
		fclose(ptrbooks);
	}
}
int comparator(BOOK* pororo, int j, int pooopa)
{
	int a = strcmp(pororo[j].author, pororo[j + 1].author);
	int b = strcmp(pororo[j].title, pororo[j + 1].title);
	int c = pororo[j].year - pororo[j + 1].year;
	int d = pororo[j].popularity - pororo[j + 1].popularity;
	switch (pooopa)
	{
	case 1:						//автор - название
		if (a == 0)
		{
			if (b == 0)
			{

				return 0;
			}
			else
				return b;
		}
		else
			return a;
		break;
	case 2:
		if (a == 0)
		{
			if (c == 0)
			{

				return 0;
			}
			else
				return c;
		}
		else
			return a;
		break;
	case 3:
		if (a == 0)
		{
			if (d == 0)
			{

				return 0;
			}
			else
				return d;
		}
		else
			return a;
		break;
	case 4:
		if (c == 0)
		{
			if (d == 0)
			{

				return 0;
			}
			else
				return d;
		}
		else
			return c;
		break;
	case 5:						//автор - год - попул€рность
		if (a == 0)
		{
			if (c == 0)
			{
				if (d == 0)
				{

					return 0;
				}
				else
					return d;
			}
			else
				return c;
		}
		else
			return a;
		break;
	}
}