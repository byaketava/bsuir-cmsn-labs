#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void sort(char** words, int* size, int f);

void text_task_1(void)
{
    printf(" Task 1:\n");
    printf(" _______________________________________________________________________\n");
    printf(" A string is given. Find the \033[38;5;141mlongest\033[0m word.\n");
    printf(" _______________________________________________________________________\n ");
}
char* input_string(char** string, int* size)
{
    int c;
    while ((c = getchar()) != EOF && c != '\n')
    {
        (*size)++;
        char* copy = (char*)realloc((*string), ((*size)+1) * sizeof(char));
        if (copy != NULL)
        {
            *string = copy;
        }
        (*string)[(*size) - 1] = c;        
    }    
    if ( c == '\n')
    {
        if ((*size) == 0)
        {
            printf(" Are you serious?! ENTER???\n\n");
            return 0;
        }
    }
    (*string)[(*size)] = '\0';
    return *string;
}
void output_string(char*stroka, int size)
{    
    printf(" ");
    for (int i = 0; i < size; i++)
    {
        printf("%c", stroka[i]);
    }
    printf("\n");
}
char** mas_slov(char** slova, int* n, int size, char* stroka, int* m, int* j)
{
    if (((stroka[0] >= 65 && stroka[0] <= 90) || (stroka[0] >= 97 && stroka[0] <= 122)) && (stroka[1] < 65 || (stroka[1] > 90 && stroka[1] < 97) || stroka[1]>122))
    {
        m[*j] = 2;
        (*n)++;
        slova[*n][m[*j] - 1] = stroka[0];
        (*j)++;
        m[*j] = 0;
    }
    for (int i = 1; i < size; i++)
    {        
        if ((stroka[i] >= 65 && stroka[i] <= 90) || (stroka[i] >= 97 && stroka[i] <= 122))
        {
            if ((stroka[i - 1] < 65 || (stroka[i - 1] > 90 && stroka[i - 1] < 97) || stroka[i - 1]>122))
            {
                m[*j] = 1;
                (*n)++;
                slova[*n][m[*j] - 1] = stroka[i];
            }
            //начало слова не с первого символа
            if ((stroka[i - 1] >= 65 && stroka[i - 1] <= 90) || (stroka[i - 1] >= 97 && stroka[i - 1] <= 122))
            {
                if (i - 1 == 0)
                {
                    (*n)++;
                    m[*j] = 2;
                    slova[* n][0] = *(stroka + i - 1);
                    slova[*n][1] = *(stroka + i);
                }
                //начало слова с самого первого символа
                else
                {
                    m[*j]++;
                    slova[*n][m[*j] - 1] = stroka[i];
                }
                //просто продолжение слова
            }
            if ((stroka[i+1]<65 || (stroka[i+1]>90 && stroka[i+1]<97) || stroka[i+1]>122) || i== size-1)
            {
                m[*j]++;                
                (*j)++;
                m[*j] = 0;
            }
        }
    }
    if ((*n) == -1)
    {
        printf(" _______________________________________________________________________\n");
        printf(" I don't work with this, you knowww...\n Next time think about WHAT you are typing, okey?\n");
        printf(" _______________________________________________________________________\n\n");
        return 0;
    }
    printf(" _______________________________________________________________________\n");
    printf(" String words:\n ");
    
    int* memory = NULL;
    memory = (int*)calloc((*n) + 1, sizeof(int));
    for (int i = 0; i < (*n) + 1; i++)
    {
        memory[i] = m[i]-1;
    }
    int step, l, o, temp;
    for (step = (*n) / 2; step > 0; step /= 2)
    {
        for (l = step; l < ((*n)+1); l++)
        {
            for (o = l; o >= step; o -= step)
            {
                if (memory[o] < memory[o - step])
                {
                    temp = memory[o];
                    memory[o] = memory[o - step];
                    memory[o - step] = temp;
                }
                else
                    break;
            }
        }
    }
    int* maxi = NULL;
    maxi = (int*)calloc((*n) + 1, sizeof(int));
    int max = memory[*n];
    int d = 0;
    for (int i = 0; i < (* n)+1; i++)
    {
        for (int k = 0; k < m[i]; k++)
        {
            printf("%c", slova[i][k]);
        }
        if ((m[i] - 1) == max)
        {
            printf("\t(\033[38;5;043mlength\033[0m = \033[38;5;141m%i\033[0m)     \033[38;5;043mthe longest one\033[0m\n ", m[i] - 1);
        }
        else
        {
            printf("\t(\033[38;5;043mlength\033[0m = \033[38;5;141m%i\033[0m)\n ", m[i] - 1);
        }
    }   
    printf("_______________________________________________________________________\n"); 
    printf("\n");
    return slova;
}

void text_task_2(void)
{
    printf(" Task 2:\n");
    printf(" _______________________________________________________________________\n");
    printf(" The strings S and S0 are given. Delete the \033[38;5;141mfirst word from S0\033[0m from\n the string \033[38;5;141mS\033[0m.\n");
    printf(" _______________________________________________________________________\n");
}
char* word_in_S0(char* word, int size_S0, char* stroka, int* m)
{
    if (((stroka[0] >= 65 && stroka[0] <= 90) || (stroka[0] >= 97 && stroka[0] <= 122)) && (stroka[1] < 65 || (stroka[1] > 90 && stroka[1] < 97) || stroka[1]>122))
    {
        *m = 1;//m длина слова
        word[(*m) - 1] = stroka[0];
        return word;
    }
    for (int i = 1; i < size_S0; i++)
    {
        if ((stroka[i] >= 65 && stroka[i] <= 90) || (stroka[i] >= 97 && stroka[i] <= 122))
        {
            if ((stroka[i - 1] < 65 || (stroka[i - 1] > 90 && stroka[i - 1] < 97) || stroka[i - 1]>122))
            {
                (*m) = 1;
                word[(*m) - 1] = stroka[i];
            }
            //начало слова не с первого символа
            if ((stroka[i - 1] >= 65 && stroka[i - 1] <= 90) || (stroka[i - 1] >= 97 && stroka[i - 1] <= 122))
            {
                if (i - 1 == 0)
                {
                    (*m) = 2;
                    word[0] = stroka[i - 1];
                    word[1] = stroka[i];
                }
                //начало слова с самого первого символа
                else
                {
                    (*m)++;
                    word[(*m) - 1] = stroka[i];
                }
                //просто продолжение слова
            }
            if ((stroka[i + 1] < 65 || (stroka[i + 1] > 90 && stroka[i + 1] < 97) || stroka[i + 1]>122) || i == size_S0 - 1)
            {
                break;
            }
        }
    }
    if ((*m) == 0)
    {
        printf(" I don't work with this, you knowww...\n I need at least one word in S0.\n Next time think about WHAT you are typing, okey?\n");
        printf(" _______________________________________________________________________\n\n");
        return 0;
    }
    printf(" The first word in S0:\n ");
    for (int i = 0; i < (*m); i++)
    {
        printf("%c", word[i]);
    }
    printf("\n _______________________________________________________________________\n");
    return word;
}
void find_and_delete_word(char*S, char*word, int m,int* size_S)
{
    int j = 0; 
    int flag = 0;
    for (int i = 0; i <= (*size_S) - m; i++)
    {
        if (S[i] == word[j]) 
        {
            flag++;
            j++;
        }
        else 
        {
            flag = 0;
            j = 0;
        }

        if (flag == m)
        {
            for(int k = i-m+1; k<(*size_S)-m; k++)
            {
                S[k] = S[k + m];
            }
            *size_S = (*size_S) - m;
            flag = 0;
            j = 0;
        }
    }
}

void text_task_3(void)
{
    printf(" Task 3:\n");
    printf(" _______________________________________________________________________\n");
    printf(" Sort the array of strings by the \033[38;5;141mHoare method\033[0m in \033[38;5;141mascending\033[0m order of the\n length of the \033[38;5;141mshortest\033[0m word in each line.\n");
    printf(" _______________________________________________________________________\n");
}
char** input_strings(char** string, int n, int *m)//n кол-во строк
{
    int c; int j=0;
    for (int i = 0; i < n; i++)
    {
        while ((c = getchar()) != EOF && c != '\n')
        {
            string[i][j] = c;
            j++;
            (m)[i]++;
        }
        if (c == EOF || c == '\n')
        {
            if ((m[i]) == 0)
            {
                printf(" Are you serious?! ENTER???\n\n");
                return 0;
            }
        }
        string[i][j] = '\0';
        j = 0;
        printf(" ");
    }
    return string;
}
void output_strings(char** strings, int n, int*m)
{
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < m[i]; k++)
        {
            printf("%c", strings[i][k]);
        }
        printf("\n ");
    }
    printf("\n");
}
void mas_sss(char** stroki, int n, int *m)
{
    int k = 0;
    int f = -1;
    int x = 0;
    int* itog = NULL;
    itog = (int*)calloc(100, sizeof(int));
    char** words = NULL;
    words = (char**)calloc(50, sizeof(char*));
    for (int i = 0; i < 50; i++)
    {
        words[i] = (char*)calloc(50, sizeof(char));
    }
    int* size = NULL;
    size = (int*)calloc(100, sizeof(int));
    for (int l = 0; l < n; l++)//по строкам
    {
        if (((stroki[l][0] >= 65 && stroki[l][0] <= 90) || (stroki[l][0] >= 97 && stroki[l][0] <= 122)) 
            && (stroki[l][1] < 65 || (stroki[l][1] > 90 && stroki[l][1] < 97) || stroki[l][1]>122))
        {
            f++;//1 слово уже есть
            size[f] = 1;//размер слова 1
            words[f-1][size[f] - 1] = stroki[l][0];// первый символ и единственный тут слова 
        }
        for (int i = 1; i < m[l]; i++)
        {
            if ((stroki[l][i] >= 65 && stroki[l][i] <= 90) || (stroki[l][i] >= 97 && stroki[l][i] <= 122))
            {
                if ((stroki[l][i - 1] < 65 || (stroki[l][i - 1] > 90 && stroki[l][i - 1] < 97) || stroki[l][i - 1]>122))
                {
                    f++;
                    size[f] = 1;
                    words[f][size[f] - 1] = stroki[l][i];
                }
                //начало слова не с первого символа
                if ((stroki[l][i - 1] >= 65 && stroki[l][i - 1] <= 90) || (stroki[l][i - 1] >= 97 && stroki[l][i - 1] <= 122))
                {
                    if (i - 1 == 0)
                    {
                        f++;
                        size[f] = 2;//размер слова 2
                        words[f][0] = stroki[l][0];
                        words[f][1] = stroki[l][1];
                    }
                    //начало слова с самого первого символа
                    else
                    {
                        size[k]++;
                        words[f][size[f] - 1] = stroki[l][i];
                    }
                    //просто продолжение слова
                }
                if ((stroki[l][i + 1] < 65 || (stroki[l][i + 1] > 90 && stroki[l][i + 1] < 97) || stroki[l][i + 1]>122) || i == m[l] - 1)
                {
                    f++;
                }
            }
        }
        if (f == -1)
        {
            printf(" _______________________________________________________________________\n");
            printf(" I don't work with this, you knowww...\n Next time think about WHAT you are typing, okey?\n");
            printf(" _______________________________________________________________________\n\n");
            return 0;////////////////
        }
        else
        {//сортировочка
            output_strings(words, n, size);
            sort(words, size, f);
            output_strings(words, n, size);
            printf(" in %i string the shortest one is\n ", l + 1);
            for (int y = 0; y < size[0]; y++)
            {
                printf("%c", words[0][y]);
            }
            printf("\n dlina = %i", size[0]);
            itog[x] = size[0];
            x++;
        }
    }

    

    
   
}

void sort(char**words, int*size,int f)
{
    int w = 0;
    int v = f - 1;
    int mid = size[f / 2];
    do
    {
        while (size[w] < mid)
        {
            w++;
        }
        while (size[v] > mid)
        {
            v--;
        }
        if (w <= v)
        {
            int tmp = size[w];
            char* lol;
            lol = *(words + w);
            size[w] = size[v];
            *(words + w) = *(words + v);
            size[v] = tmp;
            *(words + v) = lol;
            w++;
            v--;
        }
    } while (w <= v);
    if (v > 0)
    {
        sort(words, size, v + 1);
    }
    if (w < f)
    {
        sort(&words[w], &size[w], f - w);
    }
}