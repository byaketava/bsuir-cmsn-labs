#pragma once

class Cell
{
private:
    int x;
    int y;
public:
    Cell();
    Cell(int x, int y);
    int getX() const;
    int getY() const;

    void setX(int x);
    void setY(int y);
    void setPos(int x, int y);
};