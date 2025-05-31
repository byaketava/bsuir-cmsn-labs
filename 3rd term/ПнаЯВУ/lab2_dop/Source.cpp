#include <iostream>
#include <vector>
//#include <algorithm>

class Point
{
public:
	double x, y, z;
    Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
    Point() : x(0), y(0), z(0) {}
    Point operator + (Point B)
    {
        Point ab;
        ab.x = x + B.x;
        ab.y = y + B.y;
        ab.z = z + B.z;
        return ab;
    }
    Point operator - (Point B)
    {
        Point ab;
        ab.x = x - B.x;
        ab.y = y - B.y;
        ab.z = z - B.z;
        return ab;
    }
};

std::vector<Point> Box(Point _p1, Point _p2, Point _p3, Point _p4)
{
    // входные данные
    Point p1 = _p1;
    Point p2 = _p2;
    Point p3 = _p3;
    Point p44 = _p4;
    // остальные углы
    Point p4 = p3 - p2 + p1;
    Point p11 = p44 - p4 + p1;
    Point p22 = p44 - p4 + p2;
    Point p33 = p44 - p4 + p3;

    std::vector<Point> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p11);
    points.push_back(p22);
    points.push_back(p33);
    points.push_back(p44);

    std::cout << "A: " << p1.x << " " << p1.y << " " << p1.z << std::endl;
    std::cout << "B: " << p2.x << " " << p2.y << " " << p2.z << std::endl;
    std::cout << "C: " << p3.x << " " << p3.y << " " << p3.z << std::endl;
    std::cout << "D: " << p4.x << " " << p4.y << " " << p4.z << std::endl;
    std::cout << "A1: " << p11.x << " " << p11.y << " " << p11.z << std::endl;
    std::cout << "B1: " << p22.x << " " << p22.y << " " << p22.z << std::endl;
    std::cout << "C1: " << p33.x << " " << p33.y << " " << p33.z << std::endl;
    std::cout << "D1: " << p44.x << " " << p44.y << " " << p44.z << std::endl << std::endl;

    return points;
}

bool Intersection(std::vector<Point> b1, std::vector<Point> b2)
{
    bool X = false;
    bool Y = false;
    bool Z = false;

    // пересечение по X и минимальные и максимальные значения для параллелепипедов по Х
    double minb1 = b1[0].x;
    double maxb1 = b1[0].x;
    double minb2 = b2[0].x;
    double maxb2 = b2[0].x;
    for (int i = 1; i < 8; ++i)
    {
        minb1 = std::min(minb1, b1[i].x);
        maxb1 = std::max(maxb1, b1[i].x);
        minb2 = std::min(minb2, b2[i].x);
        maxb2 = std::max(maxb2, b2[i].x);
    }
    if (maxb1 < minb2 || maxb2 < minb1) // параллелепипеды один выше другого
        X = true;

    // пересечение по Y и значения мин макс
    minb1 = b1[0].y;
    maxb1 = b1[0].y;
    minb2 = b2[0].y;
    maxb2 = b2[0].y;
    for (int i = 1; i < 8; ++i)
    {
        minb1 = std::min(minb1, b1[i].y);
        maxb1 = std::max(maxb1, b1[i].y);
        minb2 = std::min(minb2, b2[i].y);
        maxb2 = std::max(maxb2, b2[i].y);
    }
    if (maxb1 < minb2 || maxb2 < minb1) // параллелепипеды один ближе другой дальше
        Y = true;

    // пересечение по Z и значения мин макс
    minb1 = b1[0].z;
    maxb1 = b1[0].z;
    minb2 = b2[0].z;
    maxb2 = b2[0].z;
    for (int i = 1; i < 8; ++i)
    {
        minb1 = std::min(minb1, b1[i].z);
        maxb1 = std::max(maxb1, b1[i].z);
        minb2 = std::min(minb2, b2[i].z);
        maxb2 = std::max(maxb2, b2[i].z);
    }
    if (maxb1 < minb2 || maxb2 < minb1) // параллелепипеды один левее/правее другого
        Z = true;

    // пересечение по X, Y или Z
    if (X && Y && Z)
        return false;   // не пересекаются
    return true;        // пересекаются
}

int main() 
{
    setlocale(0, "");
    double x, y, z;
    // координаты углов первого параллелепипеда
    std::cout << "Введите координаты 1-го угла первого параллелепипеда (x y z): ";
    std::cin >> x >> y >> z;
    Point p1(x, y, z);

    std::cout << "Введите координаты 2-го угла первого параллелепипеда (x y z): ";
    std::cin >> x >> y >> z;
    Point p2(x, y, z);

    std::cout << "Введите координаты 3-го угла первого параллелепипеда (x y z): ";
    std::cin >> x >> y >> z;
    Point p3(x, y, z);

    std::cout << "Введите координаты 4-го угла первого параллелепипеда (x y z): ";
    std::cin >> x >> y >> z;
    Point p4(x, y, z);

    // первый параллелепипед
    std::vector<Point> box1 = Box(p1, p2, p3, p4);

    // координаты углов второго параллелепипеда
    std::cout << "Введите координаты 1-го угла второго параллелепипеда (x y z): ";
    std::cin >> x >> y >> z;
    Point p5(x, y, z);

    std::cout << "Введите координаты 2-го угла второго параллелепипеда (x y z): ";
    std::cin >> x >> y >> z;
    Point p6(x, y, z);

    std::cout << "Введите координаты 3-го угла второго параллелепипеда (x y z): ";
    std::cin >> x >> y >> z;
    Point p7(x, y, z);

    std::cout << "Введите координаты 4-го угла второго параллелепипеда (x y z): ";
    std::cin >> x >> y >> z;
    Point p8(x, y, z);

    // второй параллелепипед
    std::vector<Point> box2 = Box(p5, p6, p7, p8);

    if (Intersection(box1, box2)) 
        std::cout << "Параллелепипеды пересекаются" << std::endl;
    else 
        std::cout << "Параллелепипеды не пересекаются" << std::endl;
    return 0;
}