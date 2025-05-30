#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "Resources.h"

class Piece : public sf::Drawable, public sf::Transformable 
{
private:
    // позиция фигуры на поле
    Cell piecePosition;

    // текущий поворот фигуры
    // у каждой фигуры есть 4 варианта вращения, каждый вариант описан в массиве shapes[4][4]
    int rotation = 0;

    // цвет текущей фигуры (число определяет смещение в tileset)
    // 0/9 - прозрачный, 1-7 - цветные блоки, 8 - тень
    int color = 0;

    // текущая фигура (её представление в перечислении pieceEnum)
    int currentPiece = 0;

    // текущая форма (поворот) описывается 4 клетками, каждый поворот определяетя одним из четырёх вариантов массива Cell shapes[4][4]
    Cell shape[4];

    // основной массив, хранящий положение всех клеток фигуры при разных вариантах вращений
    Cell shapes[4][4];

    // текстура (набор плиток)
    sf::Texture tiles = Resources::getTexture("res/tiles.png");

    // массив 4 спрайтов для представления одной фигуры
    sf::Sprite tileSprite[4];

    // устанавливает текущую форму фигуры (положение каждого из 4 блоков) в зависимости от поворота
    void setCurrentShape();

    // отрисовка фигуры
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    // конструктор класса
    // rotation      текущий поворот фигуры 0-3
    // currentPiece  номер фигуры согласно pieceEnum
    // Cell* shapes  повороты
    // spawnX        позиция появления фигуры
    Piece(int rotation, int currentPiece, Cell* shapes, int spawnX = 4);

    // копирует все формы фигуры в массив
    void setShapes(Cell* newShapes);

    // возвращает массив всех поворотов
    Cell* const getShapes() const;

    // возвращает текущий поворот фигуры (0-3)
    int getRotation() const;

    // устанавливает желаемый поворот фигуры
    void setRotation(int rotation);

    // возвращает текущий цвет фигуры
    int getCurrentColor() const;

    // возвращает текущий тип фигуры (согласно перечислению)
    int getCurrentShapeInt() const;

    // возвращает текущую позицию фигуры на поле
    const Cell getPiecePosition() const;

    // устанавливает позицию фигуры. Устанавливает 4 спрайта (блока) на желаемую позицию
    void setPiecePosition(int x, int y, bool fixedToBoard);
    void setPiecePosition(int x, int y);
    void setPiecePosition(Cell x);

    // поворот фигуры (изменение rotation)
    void rotate();

    // возвращает текущую форму фигуры
    Cell* getCurrentShape();

    // возвращает форму фигуры после поворота (для проверки столкновений)
    Cell* getRotationShape();
};