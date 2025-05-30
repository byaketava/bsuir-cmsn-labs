#include "Header.h"

void begin() 
{
    int n, m;                                       // ���������� ��� �������� ������� �������� �������
    printf("������� ���������� �����: ");
    n = check(1, 50);                               // ���� � ��������� ���������� �����
    printf("������� ���������� ��������: ");
    m = check(1, 50);                               // ���� � ��������� ���������� ��������
    int** mass = createArr(n, m);                   // �������� �������
    printf("\n����������� ��������� ����������� ��� �����:\n'1' - ������\n'0' - ����\n'2' - ��� ����������� '-'\n");
    input(mass, n, m);                              // ���������� �������
   
    tree* head = (tree*)calloc(1, sizeof(tree));    // ��������� ������ ��� ������ ����
    int j = 0;
    int i = 0;                                      
    head = f1(head, mass, m, n, j);                 // ����� ������� ������ ���� ��������� ��������
    write(head, m);                                 // ����� ������ 
    j = 0;
    int** vec = createArr(1, m);                    // ������ ���� ��������� ��������
    int len = writeArr(head, &vec, m, i, j);        // ���-�� ����� � ������� ��������
    printf("\n\n");
    printf("�������������� �� ��������������� �������\n\n");
    printArr(vec, len, m);
    orrtogonal(vec, mass, n, m, len);
}
tree* f1(tree* head, int** a, int m, int n, int j)          // ����� ���� ��������� ��������
{
    tree* f = head;                                         // ����
    if (j <= m) 
    {
        f->left = f->right = f->mid = NULL;
        f->a = m + 2;
        if (Ret(a, j, n, 1))                                // ���� ���� �������� 1
        {
            f->left = (tree*)calloc(1, sizeof(tree));
            f->a = j + 1;                                   // � � ���������� ����� �������
            f->left = f1(f->left, a, m, n, j + 1);          // �������� ���������� ������� ��� �����
        }
        if (Ret(a, j, n, 0))                                // ���� ���� �������� 0
        {
            f->mid = (tree*)calloc(1, sizeof(tree));
            f->a = j + 1;
            f->mid = f1(f->mid, a, m, n, j + 1);
        }
        if (!Ret(a, j, n, 1) && !Ret(a, j, n, 0))           // ���� ��� �� 1, �� 0
        {
            f->right = (tree*)calloc(1, sizeof(tree));
            f->a = j + 1;
            f->right = f1(f->right, a, m, n, j + 1);
        }
        return f;
    }
}
int writeArr(tree* head, int*** vec, int m, int i, int j)               // ������������ ������ � ������
{
    if (j < m) 
    {
        if (head->left != NULL)                                         // ���� ����� ����� �� ������
        {
            (*vec)[i][j] = 0;                                           // ���������� 0
            i = writeArr(head->left, vec, m, i, j + 1);                 // ����������� �����
            if (j == m - 1)                                             // ���� ������� ���������
            {
                i++;                                                    //������� �� ����� ������
                *vec = (int**)realloc(*vec, (i + 1) * sizeof(int*));    //�������� ������ ��� ����� ������
                (*vec)[i] = (int*)calloc(m, sizeof(int));               // �������� ����� ��� �������
                for (int k = 0; k < j; k++)                             //����������� ���������� �����
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
int orrtogonal(int** vec, int** mass, int n, int m, int len)       //�������� ����������� �� ���� �� 
                                                            //���� ������ �� �������
{
    for (int i = 0; i < len; i++)                           //�� ����� ������� ��������       
    {
        int q = 0;                                          //���������� ������������� �����
        for (int j = 0; j < n; j++)                         //�� ����� �������
        {
            for (int k = 0; k < m; k++)                     //��� �� �������
            {
                if (vec[i][k] == 0 && mass[j][k] == 1 || vec[i][k] == 1 && mass[j][k] == 0) 
                {//�������� ������� ���������������
                    q++;
                    break;
                }
            }
        }
        if (q == n)                                         //���� ��� ������ ������������
        {
            printf("\n\nC��������� ��� ������� ���� ������������� ������:\n");
            for (int p = 0; p < m; p++) {
                printf("%d", vec[i][p]);
            }
            printf("\n\n������� �������������\n");
            return 0;
        }
    }
    printf("\n\n������� �����������\n");
}

int Ret(int** a, int j, int n, int x)           // ���������� 1 ���� ���� ����������� ��������
{                                               // 0 ���� ��� ���
    for (int i = 0; i < n; i++) {
        if (a[i][j] == x)
            return 1;
    }
    return 0;
}
void input_keybord(int n, int m, int** mass) //������ ����
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
            printf("������� %d ������� %d ������: ", j, i);
            mass[i][j] = check(0, 2);
        }
    }
}
void input_random(int n, int m, int** mass)         // ��������� ����
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
    printf("\n�������� ������ �����:\n1 - ������ ����\n2 - ��������� ����\n");
    int a = check(1, 2);                            // ����� ������� ����� (�������/��������)
    switch (a)
    {
    case 1:                                         // ��� ������ ������� �����
        input_keybord(n, m, mass);
        system("cls");                              // �������� �������
        printArr(mass, n, m);                       // ����� �������� ���������� �������
        printf("\n");
        break;
    case 2:                                         // ��� ������ ���������� �����
        input_random(n, m, mass);
        printArr(mass, n, m);                       // ����� �������� ���������� �������
        printf("\n");
        break;
    }
}
int** createArr(int n, int m)                       // ������� �������� ��������
{
    int** mass = (int**)calloc(n, sizeof(int*));    // ��������� ������ ��� ������
    for (int i = 0; i < n; i++)
    {
        mass[i] = (int*)calloc(m, sizeof(int));     // ��������� ������ ��� �������
    }
    return mass;                                    // ���������� �������..................
}
void printArr(int** mass, int n, int m)             // ����� ������� �� �����
{
    printf("        ");
    for (int j = 0; j < m; j++)
    {
        printf("\033[4;37m%7d\033[0m", j);          // ����� ������� ��������
    }
    for (int i = 0; i < n; i++)
    {
        printf("\n%7d|", i);                        // ����� ������� �����
        for (int j = 0; j < m; j++)
        {
            if(mass[i][j]==2)
                printf("%7c", '-');
            else
            printf("%7d", mass[i][j]);
        }
    }
}
int check(int x, int y)                             // ������� ��������� ������� ���������
{
    int a;                                          
    scanf_s("%d", &a);
    while (getchar() != '\n' || a < x || a > y)     // c�������� ������� �� ������ �����, ���������
    {                                               // ����� �� ���, �������������� ��� ��������� ���������
        rewind(stdin);
        printf("�������� ����\n");
        scanf_s("%d", &a);
    }
    return a;                                       // ���������� �������� ������������� �����
}