#include "Header.h"

void begin() 
{
    int n, m;                                       // переменные для хранения размера троичной матрицы
    printf("Введите количество строк: ");
    n = check(1, 50);                               // ввод с проверкой количества строк
    printf("Введите количество столбцов: ");
    m = check(1, 50);                               // ввод с проверкой количества столбцов
    int** mass = createArr(n, m);                   // создание матрицы
    printf("\nИспользуйте следующие обозначения для ввода:\n'1' - истина\n'0' - ложь\n'2' - для обозначения '-'\n");
    input(mass, n, m);                              // заполнение матрицы
   
    tree* head = (tree*)calloc(1, sizeof(tree));    // выделение памяти под первый узел
    int j = 0;
    int i = 0;                                      
    head = f1(head, mass, m, n, j);                 // вызов функции поиска всех возможных векторов
    write(head, m);                                 // обход дерева 
    j = 0;
    int** vec = createArr(1, m);                    // массив всех возможных векторов
    int len = writeArr(head, &vec, m, i, j);        // кол-во строк в массиве векторов
    printf("\n\n");
    printf("Подозрительные на ортогональность вектора\n\n");
    printArr(vec, len, m);
    orrtogonal(vec, mass, n, m, len);
}
tree* f1(tree* head, int** a, int m, int n, int j)          // поиск всех возможных векторов
{
    tree* f = head;                                         // узел
    if (j <= m) 
    {
        f->left = f->right = f->mid = NULL;
        f->a = m + 2;
        if (Ret(a, j, n, 1))                                // если есть значение 1
        {
            f->left = (tree*)calloc(1, sizeof(tree));
            f->a = j + 1;                                   // в а записываем номер столбца
            f->left = f1(f->left, a, m, n, j + 1);          // вызываем рекурсивно функцию для ветки
        }
        if (Ret(a, j, n, 0))                                // если есть значение 0
        {
            f->mid = (tree*)calloc(1, sizeof(tree));
            f->a = j + 1;
            f->mid = f1(f->mid, a, m, n, j + 1);
        }
        if (!Ret(a, j, n, 1) && !Ret(a, j, n, 0))           // если нет ни 1, ни 0
        {
            f->right = (tree*)calloc(1, sizeof(tree));
            f->a = j + 1;
            f->right = f1(f->right, a, m, n, j + 1);
        }
        return f;
    }
}
int writeArr(tree* head, int*** vec, int m, int i, int j)               // переписываем дерево в массив
{
    if (j < m) 
    {
        if (head->left != NULL)                                         // если левая ветка не пустая
        {
            (*vec)[i][j] = 0;                                           // записываем 0
            i = writeArr(head->left, vec, m, i, j + 1);                 // рекурсивный вызов
            if (j == m - 1)                                             // если столбец последний
            {
                i++;                                                    //переход на новую строку
                *vec = (int**)realloc(*vec, (i + 1) * sizeof(int*));    //выделяем память под новую строку
                (*vec)[i] = (int*)calloc(m, sizeof(int));               // выделяет место под столбцы
                for (int k = 0; k < j; k++)                             //копирование одинаковой части
                {
                    (*vec)[i][k] = (*vec)[i - 1][k];
                }
            }
        }
        if (head->mid != NULL)
        {
            (*vec)[i][j] = 1;
            i = writeArr(head->mid, vec, m, i, j + 1);
            if (j == m - 1) 
            {
                i++;
                *vec = (int**)realloc(*vec, (i + 1) * sizeof(int*));
                (*vec)[i] = (int*)calloc(m, sizeof(int));
                for (int k = 0; k < j; k++) 
                {
                    (*vec)[i][k] = (*vec)[i - 1][k];
                }
            }
        }
        if (head->right != NULL) {
            (*vec)[i][j] = 2;
            i = writeArr(head->right, vec, m, i, j + 1);
            if (j == m - 1) {
                i++;
                *vec = (int**)realloc(*vec, (i + 1) * sizeof(int*));
                (*vec)[i] = (int*)calloc(m, sizeof(int));
                for (int k = 0; k < j; k++) {
                    (*vec)[i][k] = (*vec)[i - 1][k];
                }
            }
        }



    }

    return i;
}
void write(tree* tree, int n) 
{
    if (tree != NULL && tree->a <= n) {

        if (tree->left != NULL) {
            //printf("0");
            write(tree->left, n);
        }
        if (tree->mid != NULL) {
            //printf("1");
            write(tree->mid, n);
        }
        if (tree->right != NULL) {
            //printf("2");
            write(tree->right, n);
        }
    }
}
int orrtogonal(int** vec, int** mass, int n, int m, int len)       //проверка ортогонален ли хотя бы 
                                                            //один вектор из массива
{
    for (int i = 0; i < len; i++)                           //до конца массива векторов       
    {
        int q = 0;                                          //количество ортогональных строк
        for (int j = 0; j < n; j++)                         //до конца матрицы
        {
            for (int k = 0; k < m; k++)                     //идём по стобцам
            {
                if (vec[i][k] == 0 && mass[j][k] == 1 || vec[i][k] == 1 && mass[j][k] == 0) 
                {//проверка условий ортогональности
                    q++;
                    break;
                }
            }
        }
        if (q == n)                                         //если все строки ортогональны
        {
            printf("\n\nCуществует как минимум один ортогональный вектор:\n");
            for (int p = 0; p < m; p++) {
                printf("%d", vec[i][p]);
            }
            printf("\n\nМатрица невырожденная\n");
            return 0;
        }
    }
    printf("\n\nМатрица вырожденная\n");
}

int Ret(int** a, int j, int n, int x)           // возвращает 1 если есть необходимое значение
{                                               // 0 если его нет
    for (int i = 0; i < n; i++) {
        if (a[i][j] == x)
            return 1;
    }
    return 0;
}
void input_keybord(int n, int m, int** mass) //ручной ввод
{
    system("cls");
    for (int i = 0; i < n; i++)
    {
        if (i != 0 )
        {
            system("cls");
            printArr(mass, i, m);
            printf("\n\n");
        }
        for (int j = 0; j < m; j++)
        {
            printf("Введите %d элемент %d строки: ", j, i);
            mass[i][j] = check(0, 2);
        }
    }
}
void input_random(int n, int m, int** mass)         // случайный ввод
{
    system("cls");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            mass[i][j] = rand() % 3;
        }
    }
}
void input(int** mass, int n, int m)
{ 
    printf("\nВыберите формат ввода:\n1 - ручной ввод\n2 - случайный ввод\n");
    int a = check(1, 2);                            // выбор способа ввода (вручную/случайно)
    switch (a)
    {
    case 1:                                         // при выборе ручного ввода
        input_keybord(n, m, mass);
        system("cls");                              // очищение консоли
        printArr(mass, n, m);                       // вывод текущего содержания матрицы
        printf("\n");
        break;
    case 2:                                         // при выборе случайного ввода
        input_random(n, m, mass);
        printArr(mass, n, m);                       // вывод текущего содержания матрицы
        printf("\n");
        break;
    }
}
int** createArr(int n, int m)                       // функция создания массиваа
{
    int** mass = (int**)calloc(n, sizeof(int*));    // выделение памяти под строки
    for (int i = 0; i < n; i++)
    {
        mass[i] = (int*)calloc(m, sizeof(int));     // выделение памяти под столбцы
    }
    return mass;                                    // возвращает матрицу..................
}
void printArr(int** mass, int n, int m)             // вывод массива на экран
{
    printf("        ");
    for (int j = 0; j < m; j++)
    {
        printf("\033[4;37m%7d\033[0m", j);          // вывод номеров столбцов
    }
    for (int i = 0; i < n; i++)
    {
        printf("\n%7d|", i);                        // вывод номеров строк
        for (int j = 0; j < m; j++)
        {
            if(mass[i][j]==2)
                printf("%7c", '-');
            else
            printf("%7d", mass[i][j]);
        }
    }
}
int check(int x, int y)                             // функция принимает границы диапазона
{
    int a;                                          
    scanf_s("%d", &a);
    while (getchar() != '\n' || a < x || a > y)     // cчитывает символы из потока ввода, проверяет
    {                                               // число ли это, принадлежность его заданному диапазону
        rewind(stdin);
        printf("Неверный ввод\n");
        scanf_s("%d", &a);
    }
    return a;                                       // возвращает введённое пользователем число
}