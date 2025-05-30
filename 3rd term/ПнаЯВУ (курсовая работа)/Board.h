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
    int boardWidth;     // ширина поля
    int boardHeight;    // высота поля
    int** board;        // массив поля

    // текстура клеток
    sf::Texture tileset;

    // каждая клетка поля будет представлена 4 вершинами
    sf::VertexArray vertices;

    // обновляет текстуру одной клетки поля
    void updateTexture(Cell piecePos, Cell shapeCell, int color, int tileSize);

    // обновляет все клетки
    void updateAllTextures(int tileSize);
public:
    // конструктор класса
    Board(int boardWidth, int boardHeight);
    // деструктор класса
    ~Board();

    // создает массив вершин, представляющий поле
    // устанавливает позицию поля
    // добавляет текстуры используя метод updateAllTextures()
    void initialization(int tileSize);

    // проверка столкновений с другими фигурами/границами доски
    // возвращает false, если столкновений не обнаружено
    // возвращает true, если любая из клеток фигуры столкнулась с чем-либо
    bool collidesWith(int x, int y, Cell* shape);
    
    // добавляет фигуру на поле и обновляет текстуру поля
    // возвращает false, если игра окончена (фигура была добавлена в запрещенную зону)
    // возвращает true, если фигура была добавлена успешно
    bool add(Piece* piece);

    // удаляет заполненные линии, возвращает число удалённых за раз линий
    int updateBoard();

    // опускает все линии выше удаляемой вниз, обновляет текстуры
    void pushRowDown(int row);
protected:
    // отрисовывает поле
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};