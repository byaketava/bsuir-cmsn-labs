#pragma once
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Cell.h"
#include "Piece.h"
#define X_OFFSET 210
#define Y_OFFSET 50

class Board : public sf::Drawable, sf::Transformable 
{
private:
    int boardWidth;     // ������ ����
    int boardHeight;    // ������ ����
    int** board;        // ������ ����

    // �������� ������
    sf::Texture tileset;

    // ������ ������ ���� ����� ������������ 4 ���������
    sf::VertexArray vertices;

    // ��������� �������� ����� ������ ����
    void updateTexture(Cell piecePos, Cell shapeCell, int color, int tileSize);

    // ��������� ��� ������
    void updateAllTextures(int tileSize);
public:
    // ����������� ������
    Board(int boardWidth, int boardHeight);
    // ���������� ������
    ~Board();

    // ������� ������ ������, �������������� ����
    // ������������� ������� ����
    // ��������� �������� ��������� ����� updateAllTextures()
    void initialization(int tileSize);

    // �������� ������������ � ������� ��������/��������� �����
    // ���������� false, ���� ������������ �� ����������
    // ���������� true, ���� ����� �� ������ ������ ����������� � ���-����
    bool collidesWith(int x, int y, Cell* shape);
    
    // ��������� ������ �� ���� � ��������� �������� ����
    // ���������� false, ���� ���� �������� (������ ���� ��������� � ����������� ����)
    // ���������� true, ���� ������ ���� ��������� �������
    bool add(Piece* piece);

    // ������� ����������� �����, ���������� ����� �������� �� ��� �����
    int updateBoard();

    // �������� ��� ����� ���� ��������� ����, ��������� ��������
    void pushRowDown(int row);
protected:
    // ������������ ����
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};