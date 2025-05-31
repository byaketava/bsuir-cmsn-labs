#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <stdlib.h>
#include <windows.h>
#include <iostream>
 
 
class point
{
public:
    double x;
    double y;
    double z;
    void set(double a, double b, double c)
    {
        x = a;
        y = b;
        z = c;
    }
    point operator + (point A)
    {
        point abc;
        abc.x = x + A.x;
        abc.y = y + A.y;
        abc.z = z + A.z;
        return abc;
    }
    point operator - (point A)
    {
        point abc;
        abc.x = x - A.x;
        abc.y = y - A.y;
        abc.z = z - A.z;
        return abc;
    }
    point operator *(double A)
    {
        point abc;
        abc.x = x * A;
        abc.y = y * A;
        abc.z = z * A;
        return abc;
    }
    point operator -()
    {
        point abc;
        abc.x =x * -1;
        abc.y =y* -1;
        abc.z = z * -1;
        return abc;
    }
    point normalized()
    {
        point abc;
        int length = sqrt(x *x + y *y + z *z);
        abc.x = x / length;
        abc.y = y / length;
        abc.z = z / length;
        return abc;
    }
    double Magnitude()
    {
        return sqrt(x *x + y *y + z *z);
    }
}; 
class box
{
public:
    point A, B, C, D, A1, B1, C1, D1;
    box(point p11, point p22, point p33, point p44) 
    {
         A = p11;
         B = p22;
         C = p33;
         D1 = p44;
         D = C - B + A;
         A1 = D1 - D + A;
         B1 = D1 - D + B;
         C1 = D1 - D + C;
    }
};

 point Collision(box n1, box n2)
{
    //получаем позицию центра кубов
    point a[8];
    point b[8];
    a[0] = n1.D;
    a[1] = n1.C;
    a[2] = n1.D1;
    a[3] = n1.A;
    a[4] = n1.B1;
    a[5] = n1.A1;
    a[6] = n1.B;
    a[7] = n1.C1;
    b[0] = n2.D;
    b[1] = n2.C;
    b[2] = n2.D1;
    b[4] = n2.B1;
    b[3] = n2.A;
    b[5] = n2.A1;
    b[6] = n2.B;
    b[7] = n2.C1;
 
    std::vector<point> axis = GetAxis(n1, n2);
    return IntersectionOfProj(a, b, axis);
}

point IntersectionOfProj(point* a, point* b, std::vector<point> Axis)
{
    point norm;
    norm.x = 1000;
    norm.y = 1000;
    norm.z = 1000;
    //простым нахождение мин. и макс. точек куба по заданной оси
    for (int j = 0; j < Axis.size(); j++)
    {
        //проекции куба a
        float max_a = 0;
        float min_a = 0;
        ProjAxis(min_a, max_a, a, Axis[j]);
 
        //проекции куба b
        float max_b;
        float min_b;
        ProjAxis(min_b, max_b, b, Axis[j]);
 
        float points[4] = { min_a, max_a, min_b, max_b };
        std::sort(points, points + 4);
 
        float sum = (max_b - min_b) + (max_a - min_a);
        float len = abs(points[3] - points[0]);
 
        if (sum <= len)
        {
            point x;
            x.x = 0;
            x.y = 0;
            x.z = 0;
            //разделяющая ось существует
            // объекты не пересекаются
            return x;
        }
        float dl = abs(points[2] - points[1]);
        if (dl < norm.Magnitude())
        {
            norm = Axis[j] * dl;
            //ориентация нормы
            if (points[0] != min_a)
                norm = -norm;
        }
 
    }
    return norm;
}
void ProjAxis(float& min, float& max, point* &points, point Axis)
{
    max = ProjVector3(points[0], Axis);
    min = ProjVector3(points[0], Axis);
    for (int i = 0; i < 8; i++)
    {
        float tmp = ProjVector3(points[i], Axis);
        if (tmp > max)
        {
            max = tmp;
        }
 
        if (tmp < min)
        {
            min = tmp;
        }
    }
 
}
std::vector<point> GetAxis(box n1, box n2)
{
    point A;
    point B;
    point a[8];
    point b[8];
    a[0] = n1.D;
    a[1] = n1.C;
    a[2] = n1.D1;
    a[3] = n1.A;
    a[4] = n1.B1;
    a[5] = n1.A1;
    a[6] = n1.B;
    a[7] = n1.C1;
    b[0] = n2.D;
    b[1] = n2.C;
    b[2] = n2.D1;
    b[4] = n2.B1;
    b[3] = n2.A;
    b[5] = n2.A1;
    b[6] = n2.B;
    b[7] = n2.C1;
    //потенциальные разделяющие оси
    std::vector<point> Axis;
 
    //нормали плоскостей первого куба
    for (int i = 1; i < 4; i++)
    {
        A = a[i] - a[0];
        B = a[(i + 1) % 3 + 1] - a[0];
        //Axis.Add(Vector3.Cross(A, B).normalized);
        Axis.push_back(Cross(A, B).normalized());
    }
 
    for (int i = 1; i < 4; i++)
    {
        A = b[i] - b[0];
        B = b[(i + 1) % 3 + 1] - b[0];
        Axis.push_back(Cross(A, B).normalized());
    }
 
    for (int i = 1; i < 4; i++)
    {
        A = a[i] - a[0];
        for (int j = 1; j < 4; j++)
        {
            B = b[j] - b[0];
            if (Cross(A, B).Magnitude() != 0)
            {
                Axis.push_back(Cross(A, B).normalized());
            }
        }
    }
    return Axis;
}
float ProjVector3(point v, point a)
{
    a = a.normalized();
    return dot(v, a) / a.Magnitude();
 
}
point Cross(point A, point B)
{
    point C;
    C.x = A.y * B.z - A.z * B.y;
    C.y = A.x * B.z - A.z * B.x;
    C.z = A.x * B.y - A.y * B.x;
    return C;
}
double dot(point A, point B)
{
    return A.x * B.x + A.y * B.y + A.z * B.z;
}
 
int main() 
{
    srand(time(0));
    setlocale(LC_ALL, "Rus");
	point a[4];
	point b[4];
	std::cout << "Введите координаты для точек первого параллелепипеда" << std::endl;
	
	int x, y, z;
	for (int i = 0; i < 4; i++)
	{
		std::cin >> x >> y >> z;
		a[i].set(x, y, z);
	}
	std::cout << "Введите координаты для точек второго параллелепипеда" << std::endl;
	for (int i = 0; i < 4; i++)
	{
		std::cin >> x >> y >> z;
		b[i].set(x, y, z);
	}
	box n1(a[0], a[1], a[2], a[3]), n2(b[0], b[1], b[2], b[3]);

	point res = Collision(n1, n2);
	if (res.x == 0 && res.y == 0 && res.z == 0)
		std::cout << "Параллелепипеды НЕ пересекаются^^" << std::endl;
	else
		std::cout << "Пересекаются по плоскости, нормальный вектор которой: " << res.x << " " << res.y << " " << res.z << std::endl;   
}