#include <iostream>
#include <cmath>
using namespace std;                                    // пространство имен

struct Vector2f 
{
    float x, y;
                                                        // Конструкторы
    Vector2f() : x(0.0f), y(0.0f) {}
    Vector2f(float x, float y) : x(x), y(y) {}
                                                        // Переопределение операторов
    Vector2f operator+(const Vector2f& other) const     // Сложение x и y текущей структуры с соотв компонентами другой структуры
    {
        return Vector2f(x + other.x, y + other.y);
    }

    Vector2f operator-(const Vector2f& other) const 
    {
        return Vector2f(x - other.x, y - other.y);
    }

    Vector2f operator*(float scalar) const 
    {
        return Vector2f(x * scalar, y * scalar);
    }

    Vector2f operator/(float scalar) const 
    {
        return Vector2f(x / scalar, y / scalar);
    }

    Vector2f& operator+=(const Vector2f& other) 
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2f& operator-=(const Vector2f& other) 
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2f& operator*=(float scalar) 
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2f& operator/=(float scalar) 
    {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    // Вывод в консоль
    friend ostream& operator<<(ostream& os, const Vector2f& vec)    //  ссылка на поток вывода и Vector2f
    {
        os << "(" << vec.x << ", " << vec.y << ")";
        return os;
    }
};  

float length(float a, float b)
{
    float len = sqrt(pow(a, 2) + pow(b, 2));
    return len;
}

int main() 
{

    float a1;
    cout << "Enter a1:";
    cin >> a1;
    float b1;
    cout << "Enter b1:";
    cin >> b1;
    Vector2f v1(a1, b1);

    float a2;
    cout << "\nEnter a2:";
    cin >> a2;
    float b2;
    cout << "Enter b2:";
    cin >> b2;
    Vector2f v2(a2, b2);

    float scalar;
    cout << "\nEnter scalar:";
    cin >> scalar;
    cout << "\nv1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;

    Vector2f v3 = v1 + v2;
    cout << "\nv3 = v1 + v2 = " << v3 << endl;

    Vector2f v4 = v1 - v2;
    cout << "v4 = v1 - v2 = " << v4 << endl;

    Vector2f v5 = v1 * scalar;
    cout << "v1 *   " << scalar << " =  " << v5 << endl;

    Vector2f v6 = v2 / scalar;
    cout << "v2 /  " << scalar << " =  " << v6 << endl;

    v1 += v2;
    cout << "\nv1 += v2, v1 = " << v1 << endl;

    v2 -= v1;
    cout << "v2 -= v1, v2 = " << v2 << endl;

    v3 *= scalar;
    cout << "v3 *= " << scalar << ", v3 = " << v3 << endl;

    v4 /= scalar;
    cout << "v4 /= " << scalar << ", v4 = " << v4 << endl;

    cout << "v1 * v2 = " << (length(a1, b1) * length(a2, b2)) << endl;

    return 0;
}