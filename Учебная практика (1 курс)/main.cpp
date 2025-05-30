#include "Header.h"

int main() 
{
    setlocale(LC_ALL, "rus");       // подключить русский язык
    srand(time(NULL));              // нициализирующее значение зависит от системного времени
    begin();                        // вызов основной функции
}