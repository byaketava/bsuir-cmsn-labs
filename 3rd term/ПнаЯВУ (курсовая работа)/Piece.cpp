#include "Piece.h"
#include "Board.h"
#include <random>
#include <chrono>

// генерирует случайное число от 1 до 7
int getRandomNumber()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine gen(seed);
    std::uniform_int_distribution<int> dis(1, 7);
    return dis(gen);
}

Piece::Piece(int rotation, int currentPiece, Cell* shapes, int spawnX) : rotation(rotation), currentPiece(currentPiece)
{
    // копирование возможных вариантов расположения фигуры в массив
    setShapes(shapes);

    // устанавливаем стартовую позицию
    this->piecePosition.setPos(spawnX, 0);

    int random = getRandomNumber();

    // представление фигуры четырьмя спрайтами
    for (int i = 0; i < 4; i++) 
    {
        // если фигура это тень
        if (currentPiece == 8)
        {
            // установить текстуру цвета тени
            tileSprite[i].setTextureRect(sf::IntRect(40 * currentPiece, 0, 40, 40));
            this->color = 8;
        }
        else
        {
            // установить текстуру случайного цвета
            tileSprite[i].setTextureRect(sf::IntRect(40 * random, 0, 40, 40));
            this->color = random;
        }
        tileSprite[i].setTexture(tiles);
        // установить позицию спрайта на экране
        tileSprite[i].setPosition((piecePosition.getX() + shape[i].getX()) * 40 + X_OFFSET,
                                  (piecePosition.getY() + shape[i].getY()) * 40 + Y_OFFSET);
    }
}

void Piece::setShapes(Cell* newShapes) 
{
    // копирование в поле класса вариантов расположения фигуры
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
    // устанавливаем 4 спрайта в порядке, установленном текущим поворотом фигуры
    for (int i = 0; i < 4; i++) 
    {
        this->shape[i] = shapes[rotation][i];
    }
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    // для каждого из четырёх спрайтов
    for (int i = 0; i < 4; i++)
    {
        target.draw(tileSprite[i], states);
    }
}

const Cell Piece::getPiecePosition() const 
{
    return piecePosition;
}
// перегрузка для основного поля/тени и окна следующей фигуры
void Piece::setPiecePosition(int x, int y, bool fixedToBoard) 
{
    piecePosition.setX(x);
    piecePosition.setY(y);

    for (int i = 0; i < 4; i++) 
    {
        // поле начинается с блока границы + отступ в определённое количество пикселей
        // + отступ до поля игрового по Y
        if (fixedToBoard)
            tileSprite[i].setPosition((piecePosition.getX() + shape[i].getX()) * 40 + X_OFFSET,
                                      (piecePosition.getY() + shape[i].getY()) * 40 + Y_OFFSET);
        // к полю не привязаны фигуры в окне next, для разных фигур разные отступы
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
// для основного поля
void Piece::setPiecePosition(int x, int y) 
{
    setPiecePosition(x, y, true);
}
// перегрузка для тени
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