#include "Piece.h"
#include "Board.h"
#include <random>
#include <chrono>

// ���������� ��������� ����� �� 1 �� 7
int getRandomNumber()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::uniform_int_distribution<int> dis(1, 7);
    return dis(gen);
}

Piece::Piece(int rotation, int currentPiece, Cell* shapes, int spawnX) : rotation(rotation), currentPiece(currentPiece)
{
    // ����������� ��������� ��������� ������������ ������ � ������
    setShapes(shapes);

    // ������������� ��������� �������
    this->piecePosition.setPos(spawnX, 0);

    int random = getRandomNumber();

    // ������������� ������ �������� ���������
    for (int i = 0; i < 4; i++) 
    {
        // ���� ������ ��� ����
        if (currentPiece == 8)
        {
            // ���������� �������� ����� ����
            tileSprite[i].setTextureRect(sf::IntRect(40 * currentPiece, 0, 40, 40));
            this->color = 8;
        }
        else
        {
            // ���������� �������� ���������� �����
            tileSprite[i].setTextureRect(sf::IntRect(40 * random, 0, 40, 40));
            this->color = random;
        }
        tileSprite[i].setTexture(tiles);
        // ���������� ������� ������� �� ������
        tileSprite[i].setPosition((piecePosition.getX() + shape[i].getX()) * 40 + X_OFFSET,
                                  (piecePosition.getY() + shape[i].getY()) * 40 + Y_OFFSET);
    }
}

void Piece::setShapes(Cell* newShapes) 
{
    // ����������� � ���� ������ ��������� ������������ ������
    for (int i = 0; i < 4; i++) 
    {
        for (int j = 0; j < 4; j++) 
        {
            this->shapes[i][j] = newShapes[i * 4 + j];
        }
    }
    setCurrentShape();
}

void Piece::setCurrentShape() 
{
    // ������������� 4 ������� � �������, ������������� ������� ��������� ������
    for (int i = 0; i < 4; i++) 
    {
        this->shape[i] = shapes[rotation][i];
    }
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    // ��� ������� �� ������ ��������
    for (int i = 0; i < 4; i++)
    {
        target.draw(tileSprite[i], states);
    }
}

const Cell Piece::getPiecePosition() const 
{
    return piecePosition;
}
// ���������� ��� ��������� ����/���� � ���� ��������� ������
void Piece::setPiecePosition(int x, int y, bool fixedToBoard) 
{
    piecePosition.setX(x);
    piecePosition.setY(y);

    for (int i = 0; i < 4; i++) 
    {
        // ���� ���������� � ����� ������� + ������ � ����������� ���������� ��������
        // + ������ �� ���� �������� �� Y
        if (fixedToBoard)
            tileSprite[i].setPosition((piecePosition.getX() + shape[i].getX()) * 40 + X_OFFSET,
                                      (piecePosition.getY() + shape[i].getY()) * 40 + Y_OFFSET);
        // � ���� �� ��������� ������ � ���� next, ��� ������ ����� ������ �������
        else
        {
            if (currentPiece == 4)
                tileSprite[i].setPosition((piecePosition.getX() + shape[i].getX()) * 40 + 30,
                                          (piecePosition.getY() + shape[i].getY()) * 40 + 30);
            else if (currentPiece == 1)
                tileSprite[i].setPosition((piecePosition.getX() + shape[i].getX()) * 40 + 10,
                                          (piecePosition.getY() + shape[i].getY()) * 40 + 30);
            else 
                tileSprite[i].setPosition((piecePosition.getX() + shape[i].getX()) * 40 + 30,
                                          (piecePosition.getY() + shape[i].getY()) * 40 + 10);
        }
    }
}
// ��� ��������� ����
void Piece::setPiecePosition(int x, int y) 
{
    setPiecePosition(x, y, true);
}
// ���������� ��� ����
void Piece::setPiecePosition(Cell x) 
{
    setPiecePosition(x.getX(), x.getY(), true);
    setCurrentShape();
}

void Piece::rotate() 
{
    int nextRotation = (this->rotation + 1) % 4;
    setRotation(nextRotation);
    setCurrentShape();
    setPiecePosition(this->getPiecePosition());
}

int Piece::getRotation() const
{
    return rotation;
}

void Piece::setRotation(int rotation) 
{
    if (rotation >= 0 && rotation < 4)
        Piece::rotation = rotation;
    else
        Piece::rotation = 0;
}

Cell* Piece::getCurrentShape() 
{
    return this->shape;
}

Cell* Piece::getRotationShape() 
{
    int nextRotation = this->rotation - 1;
    if (nextRotation < 0) 
    {
        nextRotation = 3;
    }
    return this->shapes[nextRotation];
}

int Piece::getCurrentColor() const
{
    return color;
}

int Piece::getCurrentShapeInt() const 
{
    return currentPiece;
}

Cell* const Piece::getShapes() const 
{
    return (Cell*)shapes;
}