#include"Header.h"

void t1()
{
	char temp;
	FILE* fp = fopen("1.txt", "w+");
	if (fp == NULL)
		return;
	input_num_txt(fp);
	rewind(fp);
	while ((temp = fgetc(fp)) != EOF)
	{
		printf("%c", temp);
	}
	rewind(fp);
	printf("\n");
	sort_vybor_file(fp);
	rewind(fp);
	while ((temp = fgetc(fp)) != EOF)
	{
		printf("%c", temp);
	}
	rewind(fp);
	fclose(fp);
}
void sort_vybor_file(FILE* fp)
{
	int len = 0;
	int num1, num2, num0;
	char temp;
	int min;
	rewind(fp);
	while (fscanf(fp, "%d", &min) == 1)
	{
		len++;
	}
	rewind(fp);
	for (int i = 0; i < len - 1; i++)
	{
		for (int k = 0; k <= i; k++)
			fscanf(fp, "%d", &num0);
		rewind(fp);
		min = i;
		for (int j = i+1; j < len; j++)
		{
			// Считывание двух чисел из файла
			for (int m = 0; m <= min; m++)
				fscanf(fp, "%d", &num1);
			rewind(fp);
			for (int n = 0; n <= j; n++)
				fscanf(fp, "%d", &num2);
			rewind(fp);

			if (num2 < num1)
			{
				min = j;
			}
		}

		if (min != i)
		{
			rewind(fp);
			swap_numbers(fp, i, min);
			rewind(fp);
			while ((temp = fgetc(fp)) != EOF)
			{
				printf("%c", temp);
			}
			rewind(fp);
			printf("\n");
		}
	}

}
void swap_numbers(FILE* file, int pos1, int pos2) 
{
	int z;
	int num1;
	for (int i = 0; i <= pos1; i++)
		fscanf(file, "%d", &num1);
	rewind(file);
	
	int num2=0;
	for (int i = 0; i <= pos2; i++)
		fscanf(file, "%d", &num2);
	rewind(file);
	
	for (int i = 0; i < pos1; i++)
		fscanf(file, "%d", &z);
	if (pos1 == 0)
		fseek(file, 0, SEEK_CUR);
	else
		fseek(file, 1, SEEK_CUR);
	fprintf(file, "%02d", num2);
	rewind(file);

	for (int i = 0; i < pos2; i++)
		fscanf(file, "%d", &z);
	if (pos2 == 0)
		fseek(file, 0, SEEK_CUR);
	else
		fseek(file, 1, SEEK_CUR);
	fprintf(file, "%02d", num1);
	rewind(file);
}
void input_num_txt(FILE*fp)
{
	int num;
	puts("how many nums");
	scanf("%i", &num);
	for (int i = 0; i < num; i++)
	{
		int t = rand() % 100;
		fprintf(fp, "%02d ", t);
	}
	/*puts("Input numbers");
	while (1)
	{
		char s = getchar();
		if (s >= '0' && s <= '9' || s == ' ' || s == '\n')
		{
			fputc(s, fp);
		}
		else if (s == EOF)
			break;
		else
		{
			puts("Incorrect");
			exit(EXIT_FAILURE);
		}
	}*/
}

void t2()
{
	int t;
	FILE* fp = fopen("2.bin", "w+b");
	if (fp == NULL)
		return;
	input_num_bin(fp);
	sort_vstavki_file(fp);
	rewind(fp);
	while (fread(&t, sizeof(int), 1, fp) == 1)
	{
		printf("%d ", t);
	}
	printf("\n");
	fclose(fp);
}
void input_num_bin(FILE* fp)
{
	int num;
	puts("how many nums");
	scanf("%i", &num);
	int t;
	for (int i = 0; i < num; i++)
	{
		t = rand() % 100;
		fwrite(&t, sizeof(int), 1, fp);
	}
	rewind(fp);
	while (fread(&t, sizeof(int), 1, fp) == 1)
	{
		printf("%d ", t);
	}
	printf("\n");
}
void sort_vstavki_file(FILE* fp)
{
	int len = 0;
	int t;
	int temp1, temp2, temp;
	rewind(fp);
	while (fread(&t, sizeof(int), 1, fp) == 1)
	{
		len++;
	}
	
	for (int i = 1; i < len; i++)
	{
		rewind(fp);
		fseek(fp, i * sizeof(int), SEEK_SET);
		fread(&temp1, sizeof(int), 1, fp);
		temp = i;
		for (int j = i - 1; j >= 0; j--)
		{
			rewind(fp);
			fseek(fp, j * sizeof(int), SEEK_SET);
			fread(&temp2, sizeof(int), 1, fp);
			if (temp2 < temp1)
				break;
			else
			{
				swap_bin(fp, j, temp, temp1, temp2);
				temp--;
				rewind(fp);
				fseek(fp, temp * sizeof(int), SEEK_SET);
				fread(&temp1, sizeof(int), 1, fp);
			}
		}
	}
}
void swap_bin(FILE* fp, int j, int i, int temp1, int temp2)
{
	int t;
	rewind(fp);
	fseek(fp, i * sizeof(int), SEEK_SET);
	fwrite(&temp2, sizeof(int), 1, fp);

	rewind(fp);
	while (fread(&t, sizeof(int), 1, fp) == 1)
	{
		printf("%d ", t);
	}
	printf("\n");

	rewind(fp);
	fseek(fp, j * sizeof(int), SEEK_SET);
	fwrite(&temp1, sizeof(int), 1, fp);
	rewind(fp);
	while (fread(&t, sizeof(int), 1, fp) == 1)
	{
		printf("%d ", t);
	}
	printf("\n\n");
}

void t3()
{
	int num;
	s3* head = NULL;
	puts("how many nums");
	scanf("%i", &num);
	int t;
	s3* pred = NULL;
	for (int i = 0; i < num; i++)
	{
		s3* current = (s3*)malloc(sizeof(s3));
		current->value = rand() % 100;
		
		if (head == NULL) 
		{
			// Если список пуст, создаем новый узел и делаем его первым узлом, все указатели на него
			head = current;
			current->next = current;
			current->prev = current;
		}
		else 
		{
			// Иначе добавляем новый узел после последнего узла
			s3* last = head->prev;
			last->next = current;
			current->prev = last;
			current->next = head;
			head->prev = current;
		}
	}
	s3* temp = head;
	do
	{
		printf("%i ", temp->value);
		temp = temp->next;
	} while (temp != head);
	printf("\n");
	delete_node_ring(&head);
	temp = head;
	do
	{
		printf("%i ", temp->value);
		temp = temp->next;
	} while (temp != head);
	printf("\n");
}
void delete_node_ring(s3** head) 
{
	int t;
	s3* current = *head;
	s3* previous = NULL;
	
	puts("what element");
	scanf("%i", &t);

	while (current->value != t) 
	{
		previous = current;
		current = current->next;
		if (current == *head) 
		{
			printf("Элемент не найден в списке\n");
			return;
		}
	}
	previous = current->prev;
	previous->next = current->next;
	current->next->prev = previous;

	if (current == *head) 
	{
		*head = current->next;
	}
	free(current);
}

void t4()
{
	int t;
	FILE* fp = fopen("4.bin", "w+b");
	if (fp == NULL)
		return;
	input_num_bin(fp);
	sort_vstavki_file(fp);
	rewind(fp);
	while (fread(&t, sizeof(int), 1, fp) == 1)
	{
		printf("%d ", t);
	}
	printf("\n");
	insert_in_bin(fp);
	rewind(fp);
	while (fread(&t, sizeof(int), 1, fp) == 1)
	{
		printf("%d ", t);
	}
	printf("\n");
	fclose(fp);
}
void insert_in_bin(FILE*fp)
{
	int t;
	puts("What num?");
	scanf("%i", &t);
	rewind(fp);
	int pos = 0;
	int cur;
	while (fread(&cur, sizeof(int), 1, fp) == 1)
	{
		if (t < cur)
			break;
		else
			pos++;
	}

	int end_pos = pos;
	int next;
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);

	fseek(fp, end_pos * sizeof(int), SEEK_SET);
	fread(&cur, sizeof(int), 1, fp);

	while (end_pos * sizeof(int) < size) 
	{
		
		fseek(fp, (end_pos + 1) * sizeof(int), SEEK_SET);
		fread(&next, sizeof(int), 1, fp);
		fseek(fp, (end_pos + 1) * sizeof(int), SEEK_SET);
		fwrite(&cur, sizeof(int), 1, fp);
		cur = next;
		end_pos++;
	}
	fseek(fp, pos * sizeof(int), SEEK_SET);
	fwrite(&t, sizeof(int), 1, fp);

}

void t8 ()
{
	char temp;
	FILE* fp = fopen("8.txt", "w+");
	if (fp == NULL)
		return;
	input_words_txt(fp);
	rewind(fp);
	while ((temp = fgetc(fp)) != EOF)
	{
		printf("%c", temp);
	}
	printf("\n");
	rewind(fp);
	
	words_reverse_shifr(fp);

	rewind(fp);
	while ((temp = fgetc(fp)) != EOF)
	{
		printf("%c", temp);
	}
	printf("\n");
	rewind(fp);
	fclose(fp);
}
void input_words_txt(FILE* fp)
{
	int num;
	char w[20];
	puts("how many words");
	scanf("%i", &num);
	for (int i = 0; i < num; i++)
	{
		scanf("%s",w);    
		fputs(w, fp);  
		fputc(' ',fp);
	}
}
void words_reverse_shifr(FILE* fp)
{
	char s[20];
	char c1, c2;
	int beg = 0;
	int end = 0;
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	rewind(fp);
	while (end < size)
	{
		fseek(fp, beg, SEEK_SET);
		fscanf(fp,"%s",&s);
		fseek(fp, -1, SEEK_CUR);
		end = ftell(fp);
		int kkk = ((end - beg+1) / 2)+beg;
		for (int i = beg, j = end;i<kkk;i++,j--)
		{
			fseek(fp, i, SEEK_SET);
			fscanf(fp, "%c", &c1);
			fseek(fp, j, SEEK_SET);
			fscanf(fp, "%c", &c2);
			fseek(fp, i, SEEK_SET);
			fprintf(fp, "%c", c2);
			fseek(fp, j, SEEK_SET);
			fprintf(fp, "%c", c1);
		}
		beg = end + 2;
	};
}

void shell_sort(int n, int* mas)
{
	int step, i, j, temp;
	for (step = n / 2; step > 0; step /= 2)
	{
		for (i = step; i < n; i++)
		{
			for (j = i; j >= step; j -= step)
			{
				if (mas[j] < mas[j - step])   // 4765  5<7, поэтому нынешнее (5)  
				{                             // запомнили, присвоили ему 7,            
					temp = mas[j];            // а на место 7 поставили темп
					mas[j] = mas[j - step];   // получили 4567
					mas[j - step] = temp;
					for (int k = 0; k < 12; k++)
					{
						printf("%-3i ", mas[k]);
					}
					printf("\n");
				}
				else
					break;
			}
		}
	}
}

void taska_kati()
{
	char temp;								// для вывода содержимого файла
	FILE* fp = fopen("8.txt", "w+");		// открытие файла для записи и чтения
	if (fp == NULL)							// проверка открылся ли файл
		return;
	input_words_txt(fp);					// ввод слов в файл
	rewind(fp);								// перемещение указателя в начало файла

	while ((temp = fgetc(fp)) != EOF)		// вывод содержимого файла
	{
		printf("%c", temp);
	}
	printf("\n");
	
	rewind(fp);								// переход в начало файла
	words_change_1and2(fp);

	rewind(fp);
	while ((temp = fgetc(fp)) != EOF)
	{
		printf("%c", temp);
	}
	printf("\n");
	rewind(fp);
	fclose(fp);
}
void words_change_1and2(FILE* fp)
{
	char c;											// для поиска позиций конца слов
	char c1, c2;									// для свапа хранить два символа									
	int end = 0;
	int count = 0;									// для запоминания количества пробелов
	while (count < 2 && (c = fgetc(fp)) != EOF)		// пока не достигнут конец файла
	{
		if (c == ' ')								// если пробел, то выходим из цикла
		{
			count++;
		}
	}												// с помощью этого нашли где второе слоово заканчивается

	fseek(fp, -2, SEEK_CUR);						// мы стоим после пробела, поэтому -2,  чтобы стать после
	end = ftell(fp);								// предпоследнего и считать последний для свапа
													// запоминаем позицию эту 

	rewind(fp);
	int mid = ((end - 0 + 1) / 2);					// середина символов между началом и концом 2 слова
	for (int i = 0, j = end; i < mid; i++, j--)		// идём с двух концов до середины и меняем символы местами
	{
		fseek(fp, i, SEEK_SET);
		fscanf(fp, "%c", &c1);
		fseek(fp, j, SEEK_SET);
		fscanf(fp, "%c", &c2);
		fseek(fp, i, SEEK_SET);
		fprintf(fp, "%c", c2);
		fseek(fp, j, SEEK_SET);
		fprintf(fp, "%c", c1);
	}

	// дальше реверс отдельно 1 и отдельно 2 слов

	int beg = 0;										// наччало 1\2 слова в цикле меняется
	int temp = 0;										// для запоминания конца 1 слова
	rewind(fp);
	while (temp < end)									// пока не достигнут конец 2 слова
	{
		fseek(fp, beg, SEEK_SET);						// перемещаемся на нач 1 слова, в след итерации 2 слова
		while ((c = fgetc(fp)) != EOF)					// пока не достигнут конец файла
		{
			if (c == ' ')								// если пробел, то выходим из цикла
				break;
		}
		fseek(fp, -2, SEEK_CUR);						// смещаемся на конец слова
		temp = ftell(fp);								// запоминаем позицию
		mid = ((temp - beg+1) / 2)+beg;					// середина слова (сначала первого, потом второго,
														// поэтому в конце есть +beg
		for (int i = beg, j = temp; i < mid; i++, j--)
		{
			fseek(fp, i, SEEK_SET);
			fscanf(fp, "%c", &c1);
			fseek(fp, j, SEEK_SET);
			fscanf(fp, "%c", &c2);
			fseek(fp, i, SEEK_SET);
			fprintf(fp, "%c", c2);
			fseek(fp, j, SEEK_SET);
			fprintf(fp, "%c", c1);
		}
		beg = temp + 2;
	}
}