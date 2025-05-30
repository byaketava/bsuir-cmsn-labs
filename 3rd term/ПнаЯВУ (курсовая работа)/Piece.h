#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "Resources.h"

class Piece : public sf::Drawable, public sf::Transformable 
{
private:
    // ������� ������ �� ����
    Cell piecePosition;

    // ������� ������� ������
    // � ������ ������ ���� 4 �������� ��������, ������ ������� ������ � ������� shapes[4][4]
    int rotation = 0;

    // ���� ������� ������ (����� ���������� �������� � tileset)
    // 0/9 - ����������, 1-7 - ������� �����, 8 - ����
    int color = 0;

    // ������� ������ (� ������������� � ������������ pieceEnum)
    int currentPiece = 0;

    // ������� ����� (�������) ����������� 4 ��������, ������ ������� ����������� ����� �� ������ ��������� ������� Cell shapes[4][4]
    Cell shape[4];

    // �������� ������, �������� ��������� ���� ������ ������ ��� ������ ��������� ��������
    Cell shapes[4][4];

    // �������� (����� ������)
    sf::Texture tiles = Resources::getTexture("res/tiles.png");

    // ������ 4 �������� ��� ������������� ����� ������
    sf::Sprite tileSprite[4];

    // ������������� ������� ����� ������ (��������� ������� �� 4 ������) � ����������� �� ��������
    void setCurrentShape();

    // ��������� ������
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    // ����������� ������
    // rotation      ������� ������� ������ 0-3
    // currentPiece  ����� ������ �������� pieceEnum
    // Cell* shapes  ��������
    // spawnX        ������� ��������� ������
    Piece(int rotation, int currentPiece, Cell* shapes, int spawnX = 4);

    // �������� ��� ����� ������ � ������
    void setShapes(Cell* newShapes);

    // ���������� ������ ���� ���������
    Cell* const getShapes() const;

    // ���������� ������� ������� ������ (0-3)
    int getRotation() const;

    // ������������� �������� ������� ������
    void setRotation(int rotation);

    // ���������� ������� ���� ������
    int getCurrentColor() const;

    // ���������� ������� ��� ������ (�������� ������������)
    int getCurrentShapeInt() const;

    // ���������� ������� ������� ������ �� ����
    const Cell getPiecePosition() const;

    // ������������� ������� ������. ������������� 4 ������� (�����) �� �������� �������
    void setPiecePosition(int x, int y, bool fixedToBoard);
    void setPiecePosition(int x, int y);
    void setPiecePosition(Cell x);

    // ������� ������ (��������� rotation)
    void rotate();

    // ���������� ������� ����� ������
    Cell* getCurrentShape();

    // ���������� ����� ������ ����� �������� (��� �������� ������������)
    Cell* getRotationShape();
};