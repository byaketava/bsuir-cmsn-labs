#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
#include <algorithm>

using namespace std;

class Point
{
public:
    int n, m;
    int color;
    int state;
    Point(int _n, int _m, int clr, int st)  : n(_n), m(_m), color(clr), state(st) {};
    Point()                                 : n(0), m(0), color(0), state(0) {};
};

void check(int& num, int x, int y)
{
    while (1)
    {
        cin >> num;
        if (!cin.fail() && num >= x && num <= y && cin.get() == '\n')
            break;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очистка буфера ввода
        cout << "Да,да, да... Проверки наше всё!\nА теперь введите \033[1;5;35mАдЕкВаТнО\033[0m:" << endl;
    }
}
int getRandomNumber(int n, int m)
{
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine gen(seed);
    uniform_int_distribution<int> dis(n, m);
    return dis(gen);
}
// евклидово расстояние в двумерном пространстве
double distance(int x, int y, int n, int m)
{
    int xD = n - x;
    int yD = m - y;
    return sqrt(xD * xD + yD * yD);
}

vector <vector<Point>> createRegionsAndVote(int n, int m, int regs, int candys)
{
    vector<Point> points;
    vector <vector<Point>> regions(n, vector<Point>(m));
    points.resize(regs);
    
    // генерация точки начала каждого региона
    for (int i = 0; i < regs; i++)
    {
        points[i].n = getRandomNumber(0, n - 1);
        points[i].m = getRandomNumber(0, m - 1);
        for (int j = i - 1; j >= 0; j--)
        {
            if (points[i].n == points[j].n && points[i].m == points[j].m)
                i--;
        }
        points[i].state = i + 1;
    }
    // изменение значений в векторе точек
    for (int i = 0; i < regs; i++)
        regions[points[i].n][points[i].m].state = points[i].state;
    // распределение точек между регионами
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            double minDist = distance(i, j, points[0].n, points[0].m);
            double tmp = 0;
            regions[i][j].state = points[0].state;
            for (int k = 1; k < regs; k++)
            {
                tmp = distance(i, j, points[k].n, points[k].m);
                if (tmp < minDist)
                {
                    minDist = tmp;
                    regions[i][j].state = points[k].state;
                }
            }
        }
    // голосование
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            regions[i][j].color = getRandomNumber(1, candys);
        }
    }
    // вывод
    char c[4];

    for (int j = 0; j < candys; j++)
    {
        _itoa(j + 1, c, 10);
        printf("\033[1;38;5;%sm%4i\033[0m", c, j + 1);
    }
    cout << endl << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            _itoa(regions[i][j].color, c, 10);
            printf("\033[1;38;5;%sm%4i\033[0m", c, regions[i][j].state);
        }
        cout << endl;
    }
    cout << endl;
    return regions;
}

vector<int> winners(vector <vector<Point>> regions, int n, int m, int regs, int k)
{
    vector<vector<int>> regWin(regs, vector<int>(k));
    vector<int> totalWin(k, 0);
    // сколько за кого голосов в каждом регионе
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            regWin[regions[i][j].state-1][regions[i][j].color - 1]++;

    for (int i = 0; i < regs; i++)
    {
        auto maximum = max_element(regWin[i].begin(), regWin[i].end());
        int cnt = 0;
        int c = 0;
        for (int f = 0; f < k; f++)
        {
            if (regWin[i][f] == *maximum)
            {
                cnt++;
                c = f;
            }
            if (f == k - 1 && cnt == 1)
                totalWin[c]++;
        }
    }
    return totalWin;
}

int main()
{
	setlocale(0, "");

	int n, m, k;
	cout << "Введите размеры матрицы (n, m):\nn: ";
	check(n, 6, 50);
	cout << "m: ";
	check(m, 6, 50);

	cout << "Введите количество кандидатов (k):\nk: ";
	check(k, 2, 12);

    int regions = getRandomNumber(5, (n * m) / 5);
    cout << "Количество регионов: " << regions << endl << endl;
	
    vector <vector<Point>> states = createRegionsAndVote(n, m, regions, k);
    vector<int> votes = winners(states, n, m, regions, k);

    for (int i = 0; i < k; i++)
    {
        cout << i + 1 << "  кандидат: " << votes[i] << endl;
    }
}