#include "Cell.h"
#include <iostream>

Cell::Cell(int x, int y): x(x), y(y) {}
Cell::Cell()            : x(0), y(0) {}

int Cell::getX() const
{
    return x;
}
int Cell::getY() const
{
    return y;
}

void Cell::setX(int x)
{
    Cell::x = x;
}
void Cell::setY(int y)
{
    Cell::y = y;
}

void Cell::setPos(int x, int y)
{
    Cell::x = x;
    Cell::y = y;
}