#include"Header.h"

//option 1	найти самую длинную последовательность равных элементов
//option 2	занулить элементы, стоящие на позициях с четными номерами (начиная от 0, слева)
//option 3	Отсортировать файл таким образом – четные слева, нули посередине,
//			нечетные справа.Порядок следования элементов не изменять. Доп массивов
//			не использовать
//option 5	показать содержимое
//option 4	переписать файл
//option 6	дописать файл	

void swap(FILE* fp, int i, int j) 
{
	int x, y;
	fseek(fp, i * sizeof(int), SEEK_SET);	// Перемещаем указатель на i-й элемент
	fread(&x, sizeof(int), 1, fp);			// Считываем i-й элемент в переменную x
	fseek(fp, j * sizeof(int), SEEK_SET);	// Перемещаем указатель на j-й элемент
	fread(&y, sizeof(int), 1, fp);			// Считываем j-й элемент в переменную y
	fseek(fp, i * sizeof(int), SEEK_SET);	// Перемещаем указатель на i-й элемент
	fwrite(&y, sizeof(int), 1, fp);			// Записываем y вместо i-го элемента
	fseek(fp, j * sizeof(int), SEEK_SET);	// Перемещаем указатель на j-й элемент
	fwrite(&x, sizeof(int), 1, fp);			// Записываем x вместо j-го элемента
}

void option1(char* name, int size, int* numbers)
{
	int dlina = 1;
	int memory = 1;
	int lastpos = 0;
	for (int i = 1; i < size; i++)
	{
		if (numbers[i] == numbers[i - 1])
		{
			dlina++;
			if (dlina >= memory)
			{
				memory = dlina;
				lastpos = i;
			}
		}
		else
		{
			dlina = 1;
		}
	}
	if (memory == size)
	{
		puts("All numbers are equal");
	}
	else if (memory == 1)
	{
		puts("There are no sequences longer than 1 element in it");
	}
	else
	{
		puts("\033[1;36mThe longest sequence\033[0m of equal elements is:");
		for (int j = lastpos - memory + 1; j <= lastpos; j++)
		{
			printf("%d ", numbers[j]);
		}
		printf("\n");
	}
	puts("________________________________________________________________");
}

void option2(char* name, int size, int* numbers)
{
	FILE* fp;
	for (int j = 0; j < size; j++)
	{
		if (j % 2 == 0)
		{
			numbers[j] = 0;
		}
	}
	if ((fp = fopen(name, "wb")) == NULL)
	{
		printf("The file %s could not be opened!\n:(\n", name);
		puts("________________________________________________________________");
		exit(EXIT_FAILURE);
	}
	fwrite(numbers, sizeof(int), size, fp);
	fclose(fp);
}

void option3(char* name, int size)
{
	FILE* f;
	int n = size; //кол-во элементов
	int right = size-1;
	int left = 0;
	int zero = n/2;
	if ((f = fopen(name, "r+b")) == NULL)
	{
		printf("The file %s could not be opened!\n:(\n", name);
		puts("________________________________________________________________");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) {
			int num1, num2;
			fread(&num1, sizeof(int), 1, f);
			fread(&num2, sizeof(int), 1, f);
			//printf("num1 : %i\t num2 : %i\n", num1, num2);
			if ((num2 % 2 == 0 && num1 % 2 != 0) /*&& (num2 != 0 && num1 != 0)*/) {
				fseek(f, -2 * sizeof(int), 1);
				fwrite(&num2, sizeof(int), 1, f);
				fwrite(&num1, sizeof(int), 1, f);
			}
			fseek(f, -1 * sizeof(int), 1);
		}
		fseek(f, 0, 0);
	}
	fseek(f, 0, 0);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) {
			int num1, num2;
			fread(&num1, sizeof(int), 1, f);
			fread(&num2, sizeof(int), 1, f);
			//printf("num1 : %i\t num2 : %i\n", num1, num2);
			if ( !(num2 == 0 && num1 != 0)) {
				fseek(f, -2 * sizeof(int), 1);
				fwrite(&num2, sizeof(int), 1, f);
				fwrite(&num1, sizeof(int), 1, f);
			}
			fseek(f, -1 * sizeof(int), 1);
		}
		fseek(f, 0, 0);
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++) {
			int num1, num2;
			fread(&num1, sizeof(int), 1, f);
			fread(&num2, sizeof(int), 1, f);
			//printf("num1 : %i\t num2 : %i\n", num1, num2);
			if (!(num2 % 2 != 0 && num1 % 2 == 0)) {
				fseek(f, -2 * sizeof(int), 1);
				fwrite(&num2, sizeof(int), 1, f);
				fwrite(&num1, sizeof(int), 1, f);
			}
			fseek(f, -1 * sizeof(int), 1);
		}
		fseek(f, 0, 0);
	}
	fclose(f);
}

void option4(char* name, int *size)
{
	FILE* fp;
	if ((fp = fopen(name, "wb")) == NULL)
	{
		printf("The file %s could not be opened!\n:(\n", name);
		puts("________________________________________________________________");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("The file \033[1;35m%s\033[0m was created successfully!\n:)\n", name);
	}
	//как много чисел
	int colvo;
	puts("________________________________________________________________");
	puts("How many numbers do ypu want to enter?");
	while (1)   //проверка на ввод только 1-25 
	{
		int numread = scanf_s("%d", &colvo);
		char nextchar = getchar();
		if (numread == 1 && (colvo >= 1 && colvo <= 25) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf("WHY..?\n");
	}
	puts("________________________________________________________________");
	printf("Use the \033[1;36mkeyboard\033[0m to fill in the file with \033[1;36m %d numbers\033[0m\n", colvo);
	int k;
	for (int i = 0; i < colvo; i++)
	{
		while (1)   //проверка на ввод чисел
		{
			int numread = scanf_s("%i", &k);
			char nextchar = getchar();
			if (numread == 1 && (k > -32767 && k < 32767) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf("For what..?\n");
		}
		fwrite(&k, sizeof(k), 1, fp);
		
	}
	(* size)=colvo;
	fclose(fp);
	puts("________________________________________________________________");
}

void option5(char*name, int size, int * numbers)
{
	FILE* fp;
	if (numbers == NULL)
	{
		printf("Something went wrong... hm......\n");
		exit(EXIT_FAILURE);
	}
	if ((fp = fopen(name, "rb")) == NULL)
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
	puts("The file \033[1;36mcontains\033[0m:");
	int kurlyk = fread(numbers, sizeof(int), size, fp);
	if (kurlyk != size) // проверяем, что считали нужное количество элементов
	{
		printf("Something went wrong... hm......\n");
		exit(EXIT_FAILURE);
	}
	fclose(fp);
	for (int i = 0; i < size; i++)
	{
		printf("%d ", numbers[i]);
	}
	printf("\n");
	puts("________________________________________________________________");
}

void option6(char* name, int* size)
{
	FILE* fp;
	if ((fp = fopen(name, "ab")) == NULL)
	{
		printf("The file %s could not be opened!\n:(\n", name);
		puts("________________________________________________________________");
		exit(EXIT_FAILURE);
	}
	else
	{
		printf("The file \033[1;35m%s\033[0m was created successfully!\n:)\n", name);
	}
	//как много чисел
	int colvo;
	puts("________________________________________________________________");
	puts("How many numbers do ypu want to add?");
	while (1)   //проверка на ввод только 1-25 
	{
		int numread = scanf_s("%d", &colvo);
		char nextchar = getchar();
		if (numread == 1 && (colvo >= 1 && colvo <= 25) && (nextchar == '\n' || nextchar == ' '))
			break;
		if (nextchar != '\n')
		{
			while (getchar() != '\n')
				continue;
		}
		printf("WHY..?\n");
	}
	puts("________________________________________________________________");
	printf("Use the \033[1;36mkeyboard\033[0m to fill in the file with \033[1;36m %d new numbers\033[0m\n", colvo);
	int k;
	for (int i = 0; i < colvo; i++)
	{
		while (1)   //проверка на ввод чисел
		{
			int numread = scanf_s("%i", &k);
			char nextchar = getchar();
			if (numread == 1 && (k > -32767 && k < 32767) && (nextchar == '\n' || nextchar == ' '))
				break;
			if (nextchar != '\n')
			{
				while (getchar() != '\n')
					continue;
			}
			printf("For what..?\n");
		}
		fwrite(&k, sizeof(k), 1, fp);	
	}
	(*size)=(*size)+colvo;
	fclose(fp);
	puts("________________________________________________________________");
}