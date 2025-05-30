#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Enums.h"

class NextPieceBoard : public sf::Drawable, sf::Transformable
{
private:
    // указатель на фигуру
    Piece* piece;

    // размер одной плитки
    int tileSize;
public:
    // конструктор класса
    NextPieceBoard(Piece* piece, int tileSize);

    // устанавливает позицию следующей фигуры в окне NEXT
    void setPiece(Piece* piece);
protected:
    // отрисовка поля и фигуры
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};