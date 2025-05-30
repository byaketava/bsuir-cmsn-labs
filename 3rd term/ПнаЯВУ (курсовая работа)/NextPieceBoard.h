#pragma once
#include <SFML/Graphics.hpp>
#include "Piece.h"
#include "Enums.h"

class NextPieceBoard : public sf::Drawable, sf::Transformable
{
private:
    // ��������� �� ������
    Piece* piece;

    // ������ ����� ������
    int tileSize;
public:
    // ����������� ������
    NextPieceBoard(Piece* piece, int tileSize);

    // ������������� ������� ��������� ������ � ���� NEXT
    void setPiece(Piece* piece);
protected:
    // ��������� ���� � ������
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};