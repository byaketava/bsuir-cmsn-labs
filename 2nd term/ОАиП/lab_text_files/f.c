#include"header.h"

void option3(char* name, int size)
{
	FILE* fp;
	char s;
	int new_size;
	puts("________________________________________________________________");
	if ((fp = fopen(name, "rt")) == NULL)
	{
		printf("The file %s could not be opened!\n:(\n", name);
		puts("________________________________________________________________");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("The file \033[1;35m%s\033[0m was opened for reading successfully!\n:)\n", name);
	}
	puts("________________________________________________________________");
	fseek(fp, 0, SEEK_END);
	new_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (size != new_size)
	{
		puts("The file \033[1;5;35mwas corrupted\033[0m, bye-bye!");
		exit(EXIT_FAILURE);
	}
	puts("The file \033[1;36mcontains\033[0m:");
	while ((s = getc(fp)) != EOF)
	{
		printf("%c", s);
	}
	fclose(fp);
	puts("________________________________________________________________");
	
}

void option1(char* name, int* size)
{
	char s; //для хранения символа считанного
	FILE* fp;
	puts("________________________________________________________________");
	if ((fp = fopen(name, "wt")) == NULL)
	{
		printf("The file %s could not be opened!\n:(\n", name);
		puts("________________________________________________________________");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("The file \033[1;35m%s\033[0m was opened for reading successfully!\n:)\n", name);
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
	*size = ftell(fp);
	fclose(fp);
}

void option2(char* name, int* size)
{
	char s; //для хранения символа считанного
	FILE* fp;
	int new_size;
	puts("________________________________________________________________");
	if ((fp = fopen(name, "at")) == NULL)
	{
		printf("The file %s could not be opened!\n:(\n", name);
		puts("________________________________________________________________");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("The file \033[1;35m%s\033[0m was opened for reading successfully!\n:)\n", name);
	}
	fseek(fp, 0, SEEK_END);
	new_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if ((* size) != new_size)
	{
		puts("The file \033[1;5;35mwas corrupted\033[0m, bye-bye!");
		exit(EXIT_FAILURE);
	}

	puts("________________________________________________________________");
	puts("Use the \033[1;36mkeyboard\033[0m to \033[1;36madd\033[0m data to the file");
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
	*size = ftell(fp);
	fclose(fp);
}

void option4(char* name, int size)
{
	
	FILE* fp;
	int new_size;
	char s;
	puts("________________________________________________________________");
	if ((fp = fopen(name, "rt")) == NULL)
	{
		printf("The file %s could not be opened!\n:(\n", name);
		puts("________________________________________________________________");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("The file \033[1;35m%s\033[0m was opened for reading successfully!\n:)\n", name);
	}
	puts("________________________________________________________________");
	fseek(fp, 0, SEEK_END);
	new_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (size != new_size)
	{
		puts("The file \033[1;5;35mwas corrupted\033[0m, bye-bye!");
		exit(EXIT_FAILURE);
		puts("________________________________________________________________");

	}
	puts("The file \033[1;36mcontains\033[0m:");
	while ((s = getc(fp)) != EOF)
	{
		printf("%c", s);
	}
	fseek(fp, 0, SEEK_SET);
	puts("________________________________________________________________");
	
	double x = 0;
	int count = 0;
	fscanf_s(fp, "%lf", &x);
	double max = x;
	do
	{
		fscanf_s(fp, "%lf", &x);
		if (x >= max)
		{
			if (x == max)
			{
				count++;
			}
			else
			{
				count = 0;
			}
			max = x;
		}
		if (feof(fp))
			break;
	} while (1);
	
	printf("The maximum number is \033[1;36m%.0lf\033[0m\n\n", max);
	printf("The number was caught \033[1;36m%i\033[0m times\n", count);
	fclose(fp);
	puts("________________________________________________________________");
	
}

char* readLine(char* name, int size)
{
	FILE* fp = NULL;
	char s;           
	int count = 0;         
	char* str = (char*)calloc(size, sizeof(char));
	int new_size;
	
	puts("________________________________________________________________");
	if ((fp = fopen(name, "r+")) == NULL)
	{
		printf("The file %s could not be opened!\n:(\n", name);
		puts("________________________________________________________________");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("The file \033[1;35m%s\033[0m was opened successfully!\n:)\n", name);
	}
	puts("\n________________________________________________________________");
	fseek(fp, 0, SEEK_END);
	new_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	if (size != new_size)
	{
		puts("The file \033[1;5;35mwas corrupted\033[0m, bye-bye!");
		exit(EXIT_FAILURE);
	}



	s = getc(fp);        //считываем символ
	if (str != NULL)
	{
		while (s != EOF)      //пока не конец файла
		{
			str[count] = s;      //записываем символ в массив
			count++;       //увеличиваем значение параметра на единицу
			s = getc(fp);      //cчитываем следующий символ
		}
	}
	fclose(fp);
	return str;
}

void obmen(char* mas, int i, int j)
{
	if (i <= j)
	{
		int tmp = mas[i];
		mas[i] = mas[j];
		mas[j] = tmp;
		obmen(mas, i + 1, j - 1);
	}
}

