#include"Header.h"

//option 1	������� �� �������
	//option 2	������������
	//option 3	���������� �� ������� �� ����� ���������
	//option 4	�������� ������ ����
	//option 5	��������  �����
	//option 6	�������� ������������
	//option 7	������� ������
	//option 0	������ ���������?
// 
//showList			������� ���
//info				���������� ���������
//insertAtEnd		�������� 1 �����
//add(int* pupa)	�������� ����� �� ����� ��� ������ � �����
//deleteWholeList	������� ��� �����	
//deleteOneBook		������� 1 �����
//save(int pupa)	��������� �����
//edit				�������� ����������

/*
	id
	title[40]
	author[40]
	year
	popularity
	param
		 genre[15];			// ����			���� �� ����
		 colvo;				// �����		��� �����������
		 age;
*/
//size - ���-�� ���� �� ������ ������

BOOK info()
{
	char strt[41];
	BOOK book;
	rewind(stdin);
	printf("Write down an id:\n");
	while (1)   //�������� �� ����  
	{
		int numread = scanf_s("%lu", &book.id);
		char nextchar = getchar();
		if (numread == 1 && book.id >= 0 && book.id <= 999999 && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf(":(\n");
	}
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	rewind(stdin);
	printf("Write down a title:\n");
	gets_s(strt, 40);
	strncpy(book.title, strt, 40);
	rewind(stdin);
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Write down an author:\n");
	gets_s(strt, 40);
	strncpy(book.author, strt, 40);
	rewind(stdin);
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Write down a year:\n");
	while (1)   //�������� �� ����  
	{
		int numread = scanf_s("%lu", &book.year);
		char nextchar = getchar();
		if (numread == 1 && book.year <= 2023 && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf(":(\n");
	}
	rewind(stdin);
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Write down a popularity:\n");
	while (1)   //�������� �� ����  
	{
		int numread = scanf_s("%lu", &book.popularity);
		char nextchar = getchar();
		if (numread == 1 && (book.popularity <= 999999999 && book.popularity >= 0) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf(":(\n");
	}
	rewind(stdin);
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("Select the characteristic you want to add:\n1. Genre\n2. Circulation\n3. Recommended age\n");
	while (1)   //�������� �� ����  
	{
		int numread = scanf_s("%d", &book.type);
		char nextchar = getchar();
		if (numread == 1 && (book.type <= 3 && book.type >= 1) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf(":(\n");
	}
	switch (book.type)
	{
	case genre:
		printf("Write down a genre:\n");
		rewind(stdin);
		gets_s(strt, 15);
		strncpy(book.genre, strt, 15);
		break;
	case colvo:
		printf("Write down a circulation:\n");
		rewind(stdin);
		while (1)   //�������� �� ����  
		{
			int numread = scanf_s("%lu", &book.colvo);
			char nextchar = getchar();
			if (numread == 1 && (book.colvo <= 999999999 && book.colvo > 0) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf(":(\n");
		}
		break;
	case age:
		printf("Write down an age:\n");
		rewind(stdin);
		while (1)   //�������� �� ����  
		{
			int numread = scanf_s("%i", &book.age);
			char nextchar = getchar();
			if (numread == 1 && (book.age < 100 && book.age >= 0) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf(":(\n");
		}
		break;
	default:
		printf(":(\n");
		break;
	}
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	return book;
}
void insertAtEnd()									//�������� � ����� ������
{
	BOOK new_book = info();								// � ����� ������ ���������� ��������
	node* newone = (node*)malloc(sizeof(node));			// ��������� ������ ��� ������ �������� ������
	node* current = head;								// �������� ��������� ����, ���� � ������
	newone->data = new_book;							// � ���� ������ ���� ��������� �� ����� �����
	newone->next = NULL;								// ��������� ��� �� 0 ������
	if (head == NULL)
	{													// ���� ��� ������ �����
		newone->prev = NULL;							// �� �� ���������� ������ ��� �� 0 ������
		head = newone;									// ������ �� ����� �����
		tail = newone;									// ����� �� ����� �����
	}
	else
	{
		while (current->next != NULL)					// ���� ��������� ����� �������� �� �� 0 ���������
			current = current->next;					// ��������� � ���������� ����
		current->next = newone;							// ��������� ��������� �� �������� ����
		newone->prev = current;							// ���������� ��������� �� ��������
		tail = newone;									// ����� �� ����� ����
	}
}
void add(int* pupa)										// ��������� ����� ��� �������� ������ ����������
{
	FILE* ptrbooks;
	int a;
	BOOK new_book;
	int count = 0;										// ��� log �����
	puts("Do you want to add books from a file or a book by yourself?\n1. File (^-^)\n2. Hands (o_O)");
	while (1)   //�������� �� ����  
	{
		int numread = scanf_s("%d", &a);
		char nextchar = getchar();
		if (numread == 1 && (a == 1 || a == 2) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf("Aboba?..\n");
	}
	printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	if (a == 2)
	{
		insertAtEnd();
	}
	else
	{
		puts("Choose one of the files below:\n1. Test\n2. Trojan horse\n3. Nothing\n4. Your library");
		while (1)   //�������� �� ����  
		{
			int numread = scanf_s("%d", pupa);
			char nextchar = getchar();
			if (numread == 1 && (*pupa >= 1 && *pupa <= 4) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf("Aboba?..\n");
		}
		switch (*pupa)
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
			while (fread(&new_book, sizeof(BOOK), 1, ptrbooks) == 1)
			{
				node* newone = (node*)malloc(sizeof(node));
				newone->data = new_book;
				newone->next = NULL;
				node* last = head;
				if (head == NULL)
				{
					head = newone;
					newone->prev = NULL;
				}
				else
				{
					while (last->next != NULL)
					{
						last = last->next;
					}
					last->next = newone;
					newone->prev = last;
				}
				tail = newone;
				count++;
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
			while (fread(&new_book, sizeof(BOOK), 1, ptrbooks) == 1)
			{
				node* newone = (node*)malloc(sizeof(node));
				newone->data = new_book;
				newone->next = NULL;
				node* last = head;
				if (head == NULL)
				{
					head = newone;
					newone->prev = NULL;
				}
				else
				{
					while (last->next != NULL)
					{
						last = last->next;
					}
					last->next = newone;
					newone->prev = last;
				}
				tail = newone;
				count++;
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
			while (fread(&new_book, sizeof(BOOK), 1, ptrbooks) == 1)
			{
				node* newone = (node*)malloc(sizeof(node));
				newone->data = new_book;
				newone->next = NULL;
				node* last = head;
				if (head == NULL)
				{
					head = newone;
					newone->prev = NULL;
				}
				else
				{
					while (last->next != NULL)
					{
						last = last->next;
					}
					last->next = newone;
					newone->prev = last;
				}
				tail = newone;
				count++;
			}
			fclose(ptrbooks);
			break;
		}
	}
}
void showList()		
{
	node* current = head;
	if (current == NULL)
	{
		printf("There are no books, what should i show you?\n");
	}
	else 
	{
		printf(" ___________________________________________________________________________________________________________________________________ \n");
		printf("|                                                                                                                                   |\n");
		printf("|                                                          \033[1;5;38;5;204m%c\033[0m BOOK LIST \033[1;5;38;5;204m%c\033[0m                                                            |\n", 4, 4);
		printf("|___________________________________________________________________________________________________________________________________|\n");
		printf("|        |                                          |                                          |      |            |                |\n");
		printf("|   \033[1;38;5;204mid\033[0m   |                  \033[1;38;5;204mtitle\033[0m                   |                  \033[1;38;5;204mauthor\033[0m                  | \033[1;38;5;204myear\033[0m | \033[1;38;5;204mpopularity\033[0m | \033[1;38;5;204mcharacteristic\033[0m |\n");
		printf("|________|__________________________________________|__________________________________________|______|____________|________________|\n");
		while (current != NULL) 
		{
			printf("|        |                                          |                                          |      |            |                |\n");
			switch (current->data.type)
			{
			case genre:
				printf("| %06i | %-40s | %-40s | %-4i | %-10i | %-14s |\n", current->data.id, current->data.title, current->data.author, current->data.year, current->data.popularity, current->data.genre);
				break;
			case colvo:
				printf("| %06i | %-40s | %-40s | %-4i | %-10i | pcs. %-9i |\n", current->data.id, current->data.title, current->data.author, current->data.year, current->data.popularity, current->data.colvo);
				break;
			case age:
				printf("| %06i | %-40s | %-40s | %-4i | %-10i | %-2i+            |\n", current->data.id, current->data.title, current->data.author, current->data.year, current->data.popularity, current->data.age);
				break;
			default:
				printf("Error :(\n");
				break;
			}
			printf("|________|__________________________________________|__________________________________________|______|____________|________________|\n");
			current = current->next;
		}
	}
	printf("\n-------------------------------------------------------------------------------------------------------------------------------------\n");
}
void deleteWholeList()
{
	node* tmp = head;
	node* next = NULL;
	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	head = NULL;
}
void deleteOneBook()
{
	showList();
	int pop;
	node* current = head;
	puts("Enter the id of the book you want to delete");
	scanf_s("%lu", &pop);
	while (current != NULL && current->data.id != pop)
		current = current->next;
	if (current == NULL)
		puts("There are no books with such an id\n");
	else
	{
		if (current->prev)							// ���� ����� ��� ���� �����, ��
			current->prev->next = current->next;	// ���������� ����� ��������� �� ��������� ����� ��������
		if (current->next)							// ���� ����� ���� ���� �����, ��
			current->next->prev = current->prev;	// ��������� ����� ��������� �� ����� ����� ��������
		if (head == current)
			head = current->next;
		if (tail == current)
			tail = current->prev;
		free(current);
	}
	if (head == NULL)
	{
		puts("There no more books");
		printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	else
		showList();
}
void delete()
{
	if (head == NULL)
		puts("You don't have any books yet, what are you going to delete?\n");
	else
	{
		int a;
		puts("Choose the option:\n1. Delete one book\n2. Delete the whole library");
		scanf_s("%i", &a);
		if (a == 1)
			deleteOneBook();
		if (a == 2)
			deleteWholeList();
	}
}
void save(int pupa)
{
	FILE* ptrbooks;
	int a;
	puts("Do yo want to save your books?\n1. YES!\n2. nope (>_<)");
	while (1)   //�������� �� ����  
	{
		int numread = scanf_s("%d", &a);
		char nextchar = getchar();
		if (numread == 1 && (a == 1 || a == 2) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf("Aboba?..\n");
	}
	if (a == 2)
		puts("\n-----------\n  oboltus  \n-----------");
	else
	{
		node* current = head;
		if (pupa == 4)
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
		while (current != NULL && fwrite(&current->data, sizeof(BOOK), 1, ptrbooks) == 1)
		{
			current = current->next;
		}
		puts("\n-----------------------------------");
		puts("  Your library is safe now, enjoy  ");
		puts("-----------------------------------");
		fclose(ptrbooks);
	}
}
void edit()
{
	char strt[41];
	int edt;
	enum perechen choose;
	node* current = head;
	showList();
	puts("Enter the id of the book you want to edit");
	scanf_s("%lu", &edt);
	while (current != NULL && current->data.id != edt)
		current = current->next;
	if (current == NULL)
	{
		puts("There are no books with such an id\n");
		printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	else
	{
		do
		{
			showList();
			puts("Which characteristic do you want to edit? (choose an option (1 to 6) below)\n1. ID\n2. Title\n3. Author\n4. Year\n5. Popularity\n6. Characteristic\n0 ->  back to the menu");
			while (1)   //�������� �� ����  
			{
				int numread = scanf_s("%d", &choose);
				char nextchar = getchar();
				if (numread == 1 && (choose >= 0 && choose < 7) && (nextchar == '\n' || nextchar == ' '))
					break;
				if (nextchar != '\n')
				{
					while (getchar() != '\n')
						continue;
				}
				printf(":(\n");
			}
			printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
			switch (choose)
			{
			case id:
				printf("Write down a new id:\n");
				while (1)   //�������� �� ����  
				{
					int numread = scanf_s("%lu", &current->data.id);
					char nextchar = getchar();
					if (numread == 1 && current->data.id >= 0 && current->data.id <= 999999 && (nextchar == '\n' || nextchar == ' '))
						break;
					if (nextchar != '\n')
					{
						while (getchar() != '\n')
							continue;
					}
					printf(":(\n");
				}
				rewind(stdin);
				printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
				break;
			case title:
				printf("Write down a new title:\n");
				gets_s(strt, 40);
				strncpy(current->data.title, strt, 40);
				rewind(stdin);
				printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
				break;
			case author:
				printf("Write down a new author:\n");
				gets_s(strt, 40);
				strncpy(current->data.author, strt, 40);
				rewind(stdin);
				printf("-------------------------------------------------------------------------------------------------------------------------------------\n");				
				break;
			case year:
				printf("Write down a new year:\n");
				while (1)   //�������� �� ����  
				{
					int numread = scanf_s("%lu", &current->data.year);
					char nextchar = getchar();
					if (numread == 1 && (current->data.year <= 2023) && (nextchar == '\n' || nextchar == ' '))
						break;
					if (nextchar != '\n')
					{
						while (getchar() != '\n')
							continue;
					}
					printf(":(\n");
				}
				rewind(stdin);
				printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
				break;
			case popularity:
				printf("Write down a new popularity:\n");
				while (1)   //�������� �� ����  
				{
					int numread = scanf_s("%lu", &current->data.popularity);
					char nextchar = getchar();
					if (numread == 1 && (current->data.popularity <= 999999999 && current->data.popularity >= 0) && (nextchar == '\n' || nextchar == ' '))
						break;
					if (nextchar != '\n')
					{
						while (getchar() != '\n')
							continue;
					}
					printf(":(\n");
				}
				rewind(stdin);
				printf("-------------------------------------------------------------------------------------------------------------------------------------\n");				
				break;
			case characteristic:
				printf("Select the new characteristic you want to add:\n1. Genre\n2. Circulation\n3. Recommended age\n");
				while (1)   //�������� �� ����  
				{
					int numread = scanf_s("%d", &current->data.type);
					char nextchar = getchar();
					if (numread == 1 && (current->data.type <= 3 && current->data.type >= 1) && (nextchar == '\n' || nextchar == ' '))
						break;
					if (nextchar != '\n')
					{
						while (getchar() != '\n')
							continue;
					}
					printf(":(\n");
				}
				switch (current->data.type)
				{
				case genre:
					printf("Write down a genre:\n");
					rewind(stdin);
					gets_s(strt, 15);
					strncpy(current->data.genre, strt, 15);
					break;
				case colvo:
					printf("Write down a circulation:\n");
					rewind(stdin);
					while (1)   //�������� �� ����  
					{
						int numread = scanf_s("%lu", &current->data.colvo);
						char nextchar = getchar();
						if (numread == 1 && (current->data.colvo <= 999999999 && current->data.colvo > 0) && (nextchar == '\n' || nextchar == ' '))
							break;
						if (nextchar != '\n')
						{
							while (getchar() != '\n')
								continue;
						}
						printf(":(\n");
					}
					break;
				case age:
					printf("Write down an age:\n");
					rewind(stdin);
					while (1)   //�������� �� ����  
					{
						int numread = scanf_s("%i", &current->data.age);
						char nextchar = getchar();
						if (numread == 1 && (current->data.age < 100 && current->data.age >= 0) && (nextchar == '\n' || nextchar == ' '))
							break;
						if (nextchar != '\n')
						{
							while (getchar() != '\n')
								continue;
						}
						printf(":(\n");
					}
					break;
				default:
					printf(":(\n");
					break;
				}
				printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
				break;
			case 0:
				system("cls");
				showList();
				break;
			}
		} while (choose != 0);
	}
}
void sort()
{
	enum perechen num;
	enum param a;
	do
	{
		node* sorted = NULL, * current = head;
		puts("By which characteristic do you want to sort? (choose an option (1 to 5) below)\n1. ID\n2. Title\n3. Author\n4. Year\n5. Popularity\n6. Characteristic\n0 ->  back to the menu");
		while (1)   //�������� �� ����  
		{
			int numread = scanf_s("%d", &num);
			char nextchar = getchar();
			if (numread == 1 && (num >= 0 && num < 7) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf(":(\n");
		}
		printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
		switch (num)	//���������� ���������
		{
		case id:
			while (current != NULL)											// ���� �� ����� ������� ���� ������
			{
				node* next = current->next;
				if (sorted == NULL || sorted->data.id >= current->data.id)		// ���� ��������������� ���� ��� ��, ��� ������
				{															// � �� ������ ���� ��� � ��������
					current->next = sorted;									// �� �� ���� ����� ��� �� ������
					if (sorted != NULL)										// ���� ������ �� ����, ��
					{
						sorted->prev = current;								// �� �� ���� ����� ������ �� ���
					}
					sorted = current;										// �������� � ������ �������� ����
				}
				else															// �����
				{
					node* temp = sorted;									// ���� �� ������
					while (temp->next != NULL && temp->next->data.id < current->data.id)// ���� �� ��������� � ������ � ���� <
					{
						temp = temp->next;									// ������� � ���� � ������
					}
					current->next = temp->next;								// �� �� ���� ����� ��� �� ���� ����� ���� � ������
					if (temp->next != NULL)									// ���� ���� �� ��������� � ������
					{
						temp->next->prev = current;							// �� �� ���� ����� ���� ������ �� ���
					}
					temp->next = current;									// �� �� ���� ����� ����� �� ���
					current->prev = temp;									// �� �� ���� ����� ��� �� ����
				}
				current = next;												// ������� � ���� ����
			}
			head = sorted;
			showList();
			break;
		case title:
			while (current != NULL)											// ���� �� ����� ������� ���� ������
			{
				node* next = current->next;
				if (sorted == NULL || strcmp(sorted->data.title, current->data.title) >= 0)		// ���� ��������������� ���� ��� ��, ��� ������
				{															// � �� ������ ���� ��� � ��������
					current->next = sorted;									// �� �� ���� ����� ��� �� ������
					if (sorted != NULL)										// ���� ������ �� ����, ��
					{
						sorted->prev = current;								// �� �� ���� ����� ������ �� ���
					}
					sorted = current;										// �������� � ������ �������� ����
				}
				else															// �����
				{
					node* temp = sorted;									// ���� �� ������
					while (temp->next != NULL && strcmp(temp->next->data.title, current->data.title) < 0)// ���� �� ��������� � ������ � ���� <
					{
						temp = temp->next;									// ������� � ���� � ������
					}
					current->next = temp->next;								// �� �� ���� ����� ��� �� ���� ����� ���� � ������
					if (temp->next != NULL)									// ���� ���� �� ��������� � ������
					{
						temp->next->prev = current;							// �� �� ���� ����� ���� ������ �� ���
					}
					temp->next = current;									// �� �� ���� ����� ����� �� ���
					current->prev = temp;									// �� �� ���� ����� ��� �� ����
				}
				current = next;												// ������� � ���� ����
			}
			head = sorted;
			showList();
			break;
		case author:
			while (current != NULL)											// ���� �� ����� ������� ���� ������
			{
				node* next = current->next;
				if (sorted == NULL || strcmp(sorted->data.author, current->data.author) >= 0)		// ���� ��������������� ���� ��� ��, ��� ������
				{															// � �� ������ ���� ��� � ��������
					current->next = sorted;									// �� �� ���� ����� ��� �� ������
					if (sorted != NULL)										// ���� ������ �� ����, ��
					{
						sorted->prev = current;								// �� �� ���� ����� ������ �� ���
					}
					sorted = current;										// �������� � ������ �������� ����
				}
				else															// �����
				{
					node* temp = sorted;									// ���� �� ������
					while (temp->next != NULL && strcmp(sorted->data.author, current->data.author) < 0)// ���� �� ��������� � ������ � ���� <
					{
						temp = temp->next;									// ������� � ���� � ������
					}
					current->next = temp->next;								// �� �� ���� ����� ��� �� ���� ����� ���� � ������
					if (temp->next != NULL)									// ���� ���� �� ��������� � ������
					{
						temp->next->prev = current;							// �� �� ���� ����� ���� ������ �� ���
					}
					temp->next = current;									// �� �� ���� ����� ����� �� ���
					current->prev = temp;									// �� �� ���� ����� ��� �� ����
				}
				current = next;												// ������� � ���� ����
			}
			head = sorted;
			showList();
			break;
		case year:
			while (current != NULL)											// ���� �� ����� ������� ���� ������
			{
				node* next = current->next;
				if (sorted == NULL || sorted->data.year >= current->data.year)		// ���� ��������������� ���� ��� ��, ��� ������
				{															// � �� ������ ���� ��� � ��������
					current->next = sorted;									// �� �� ���� ����� ��� �� ������
					if (sorted != NULL)										// ���� ������ �� ����, ��
					{
						sorted->prev = current;								// �� �� ���� ����� ������ �� ���
					}
					sorted = current;										// �������� � ������ �������� ����
				}
				else															// �����
				{
					node* temp = sorted;									// ���� �� ������
					while (temp->next != NULL && temp->next->data.year < current->data.year)// ���� �� ��������� � ������ � ���� <
					{
						temp = temp->next;									// ������� � ���� � ������
					}
					current->next = temp->next;								// �� �� ���� ����� ��� �� ���� ����� ���� � ������
					if (temp->next != NULL)									// ���� ���� �� ��������� � ������
					{
						temp->next->prev = current;							// �� �� ���� ����� ���� ������ �� ���
					}
					temp->next = current;									// �� �� ���� ����� ����� �� ���
					current->prev = temp;									// �� �� ���� ����� ��� �� ����
				}
				current = next;												// ������� � ���� ����
			}
			head = sorted;
			showList();
			break;
		case popularity:
			while (current != NULL)											// ���� �� ����� ������� ���� ������
			{
				node* next = current->next;
				if (sorted == NULL || sorted->data.popularity >= current->data.popularity)		// ���� ��������������� ���� ��� ��, ��� ������
				{															// � �� ������ ���� ��� � ��������
					current->next = sorted;									// �� �� ���� ����� ��� �� ������
					if (sorted != NULL)										// ���� ������ �� ����, ��
					{
						sorted->prev = current;								// �� �� ���� ����� ������ �� ���
					}
					sorted = current;										// �������� � ������ �������� ����
				}
				else															// �����
				{
					node* temp = sorted;									// ���� �� ������
					while (temp->next != NULL && temp->next->data.popularity < current->data.popularity)// ���� �� ��������� � ������ � ���� <
					{
						temp = temp->next;									// ������� � ���� � ������
					}
					current->next = temp->next;								// �� �� ���� ����� ��� �� ���� ����� ���� � ������
					if (temp->next != NULL)									// ���� ���� �� ��������� � ������
					{
						temp->next->prev = current;							// �� �� ���� ����� ���� ������ �� ���
					}
					temp->next = current;									// �� �� ���� ����� ����� �� ���
					current->prev = temp;									// �� �� ���� ����� ��� �� ����
				}
				current = next;												// ������� � ���� ����
			}
			head = sorted;
			showList();
			break;
		case characteristic:
			puts("By which characteristic do you want to sort? \n1. Genre\n2. Circulation\n3. Recommended age");
			while (1)   //�������� �� ����  
			{
				int numread = scanf_s("%d", &a);
				char nextchar = getchar();
				if (numread == 1 && (a > 0 && a < 4) && (nextchar == '\n' || nextchar == ' '))
					break;
				if (nextchar != '\n')
				{
					while (getchar() != '\n')
						continue;
				}
				printf(":(\n");
			}
			printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
			while (current != NULL)											// ���� �� ����� ������� ���� ������
			{
				node* next = current->next;
				if (sorted == NULL || sorted->data.type >= current->data.type)		// ���� ��������������� ���� ��� ��, ��� ������
				{															// � �� ������ ���� ��� � ��������
					current->next = sorted;									// �� �� ���� ����� ��� �� ������
					if (sorted != NULL)										// ���� ������ �� ����, ��
					{
						sorted->prev = current;								// �� �� ���� ����� ������ �� ���
					}
					sorted = current;										// �������� � ������ �������� ����
				}
				else															// �����
				{
					node* temp = sorted;									// ���� �� ������
					while (temp->next != NULL && temp->next->data.type < current->data.type)// ���� �� ��������� � ������ � ���� <
					{
						temp = temp->next;									// ������� � ���� � ������
					}
					current->next = temp->next;								// �� �� ���� ����� ��� �� ���� ����� ���� � ������
					if (temp->next != NULL)									// ���� ���� �� ��������� � ������
					{
						temp->next->prev = current;							// �� �� ���� ����� ���� ������ �� ���
					}
					temp->next = current;									// �� �� ���� ����� ����� �� ���
					current->prev = temp;									// �� �� ���� ����� ��� �� ����
				}
				current = next;												// ������� � ���� ����
			}
			head = sorted;
			current = head;
			sorted = NULL;
			switch (a)
			{
			case genre:
				while (current->data.type == 1)											// ���� �� ����� ������� ���� ������
				{
					node* next = current->next;

					if (sorted == NULL || strcmp(sorted->data.genre, current->data.genre) >= 0)		// ���� ��������������� ���� ��� ��, ��� ������
					{															// � �� ������ ���� ��� � ��������
						current->next = sorted;									// �� �� ���� ����� ��� �� ������
						if (sorted != NULL)										// ���� ������ �� ����, ��
						{
							sorted->prev = current;								// �� �� ���� ����� ������ �� ���
						}
						sorted = current;										// �������� � ������ �������� ����
					}
					else															// �����
					{
						node* temp = sorted;									// ���� �� ������
						while (temp->next != NULL && strcmp(sorted->data.genre, current->data.genre) < 0)// ���� �� ��������� � ������ � ���� <
						{
							temp = temp->next;									// ������� � ���� � ������
						}
						current->next = temp->next;								// �� �� ���� ����� ��� �� ���� ����� ���� � ������
						if (temp->next != NULL)									// ���� ���� �� ��������� � ������
						{
							temp->next->prev = current;							// �� �� ���� ����� ���� ������ �� ���
						}
						temp->next = current;									// �� �� ���� ����� ����� �� ���
						current->prev = temp;									// �� �� ���� ����� ��� �� ����
					}
					current = next;												// ������� � ���� ����
				}
				head = sorted;
				node* lupa = head;
				while (lupa->next != NULL)
				{
					lupa = lupa->next;
				}
				if (current->data.type != 1)
				{
					lupa->next = current;
					current->prev = lupa;
				}
				break;
			case colvo:
				while (current->data.type != 2)
					current = current->next;
				while (current->data.type == 2)											// ���� �� ����� ������� ���� ������
				{
					node* next = current->next;
					if (sorted == NULL || sorted->data.colvo >= current->data.colvo)		// ���� ��������������� ���� ��� ��, ��� ������
					{															// � �� ������ ���� ��� � ��������
						current->next = sorted;									// �� �� ���� ����� ��� �� ������
						if (sorted != NULL)										// ���� ������ �� ����, ��
						{
							sorted->prev = current;								// �� �� ���� ����� ������ �� ���
						}
						sorted = current;										// �������� � ������ �������� ����
					}
					else															// �����
					{
						node* temp = sorted;									// ���� �� ������
						while (temp->next != NULL && temp->next->data.colvo < current->data.colvo)// ���� �� ��������� � ������ � ���� <
						{
							temp = temp->next;									// ������� � ���� � ������
						}
						current->next = temp->next;								// �� �� ���� ����� ��� �� ���� ����� ���� � ������
						if (temp->next != NULL)									// ���� ���� �� ��������� � ������
						{
							temp->next->prev = current;							// �� �� ���� ����� ���� ������ �� ���
						}
						temp->next = current;									// �� �� ���� ����� ����� �� ���
						current->prev = temp;									// �� �� ���� ����� ��� �� ����
					}
					current = next;												// ������� � ���� ����
				}
				node* blaa = head;
				while (blaa->next->data.type != 2)
					blaa = blaa->next;
				blaa->next = NULL;
				while (blaa != head)
					blaa = blaa->prev;
				lupa = sorted;
				while (lupa->next != NULL)
				{
					lupa = lupa->next;
				}
				if (current->data.type != 2)
				{
					lupa->next = blaa;//head
					blaa->prev = lupa;
				}

				head = sorted;
				lupa = head;
				while (lupa->next != NULL)
				{
					lupa = lupa->next;
				}
				if (current->data.type != 1 && current->data.type != 2)
				{
					lupa->next = current;
					current->prev = lupa;
				}
				break;
			case age:
				while (current->data.type != 3)
					current = current->next;
				while (current != NULL&&current->data.type == 3)									// ���� �� ����� ������� ���� ������
				{
					node* next = current->next;
					if (sorted == NULL || sorted->data.age >= current->data.age)		// ���� ��������������� ���� ��� ��, ��� ������
					{															// � �� ������ ���� ��� � ��������
						current->next = sorted;									// �� �� ���� ����� ��� �� ������
						if (sorted != NULL)										// ���� ������ �� ����, ��
						{
							sorted->prev = current;								// �� �� ���� ����� ������ �� ���
						}
						sorted = current;										// �������� � ������ �������� ����
					}
					else															// �����
					{
						node* temp = sorted;									// ���� �� ������
						while (temp->next != NULL && temp->next->data.age < current->data.age)// ���� �� ��������� � ������ � ���� <
						{
							temp = temp->next;									// ������� � ���� � ������
						}
						current->next = temp->next;								// �� �� ���� ����� ��� �� ���� ����� ���� � ������
						if (temp->next != NULL)									// ���� ���� �� ��������� � ������
						{
							temp->next->prev = current;							// �� �� ���� ����� ���� ������ �� ���
						}
						temp->next = current;									// �� �� ���� ����� ����� �� ���
						current->prev = temp;									// �� �� ���� ����� ��� �� ����
					}
					current = next;												// ������� � ���� ����
				}
				
				blaa = head;
				while (blaa->next->data.type != 3)
					blaa = blaa->next;
				blaa->next = NULL;
				while (blaa != head)
					blaa = blaa->prev;
				lupa = sorted;
				while (lupa->next != NULL)
				{
					lupa = lupa->next;
				}
					lupa->next = blaa;//head
					blaa->prev = lupa;
				head = sorted;
				break;
			}
			showList();
			break;
		case 0:
			system("cls");
			break;
		}
	} while (num != 0);
}
void rec(int age)
{
	node* sorted = NULL, * current = head;
	
	printf("Recommended books based on your age (%i):\n", age);
	while (current != NULL)											// ���� �� ����� ������� ���� ������
	{
		node* next = current->next;
		if (sorted == NULL || sorted->data.type >= current->data.type)		// ���� ��������������� ���� ��� ��, ��� ������
		{															// � �� ������ ���� ��� � ��������
			current->next = sorted;									// �� �� ���� ����� ��� �� ������
			if (sorted != NULL)										// ���� ������ �� ����, ��
			{
				sorted->prev = current;								// �� �� ���� ����� ������ �� ���
			}
			sorted = current;										// �������� � ������ �������� ����
		}
		else															// �����
		{
			node* temp = sorted;									// ���� �� ������
			while (temp->next != NULL && temp->next->data.type < current->data.type)// ���� �� ��������� � ������ � ���� <
			{
				temp = temp->next;									// ������� � ���� � ������
			}
			current->next = temp->next;								// �� �� ���� ����� ��� �� ���� ����� ���� � ������
			if (temp->next != NULL)									// ���� ���� �� ��������� � ������
			{
				temp->next->prev = current;							// �� �� ���� ����� ���� ������ �� ���
			}
			temp->next = current;									// �� �� ���� ����� ����� �� ���
			current->prev = temp;									// �� �� ���� ����� ��� �� ����
		}
		current = next;												// ������� � ���� ����
	}
	head = sorted;
	current = head;
	sorted = NULL;
	node* pupa = NULL;
	while (current->data.type != 3)
		current = current->next;
	while (current != NULL && current->data.type == 3)									// ���� �� ����� ������� ���� ������
	{
		node* next = current->next;
		if ((sorted == NULL || sorted->data.age >= current->data.age) && current->data.age <= age)		// ���� ��������������� ���� ��� ��, ��� ������
		{															// � �� ������ ���� ��� � ��������
			current->next = sorted;									// �� �� ���� ����� ��� �� ������
			if (sorted != NULL)										// ���� ������ �� ����, ��
			{
				sorted->prev = current;								// �� �� ���� ����� ������ �� ���
			}
			sorted = current;										// �������� � ������ �������� ����
		}
		else if (current->data.age <= age)															// �����
		{
			node* temp = sorted;									// ���� �� ������
			while (temp->next != NULL && temp->next->data.age < current->data.age)// ���� �� ��������� � ������ � ���� <
			{
				temp = temp->next;									// ������� � ���� � ������
			}
			current->next = temp->next;								// �� �� ���� ����� ��� �� ���� ����� ���� � ������
			if (temp->next != NULL)									// ���� ���� �� ��������� � ������
			{
				temp->next->prev = current;							// �� �� ���� ����� ���� ������ �� ���
			}
			temp->next = current;									// �� �� ���� ����� ����� �� ���
			current->prev = temp;									// �� �� ���� ����� ��� �� ����
		}
		
		current = next;												// ������� � ���� ����
	}
	

	node* blaa = head;
	while (blaa->next->data.type != 3)
		blaa = blaa->next;
	blaa->next = NULL;
	while (blaa != head)
		blaa = blaa->prev;
	node* lupa = sorted;
	while (lupa->next != NULL)
	{
		lupa = lupa->next;
	}
	lupa->next = blaa;//head
	blaa->prev = lupa;
	head = sorted;
	showList();	
}