#pragma once
#include <SFML/Audio.hpp>
#include "Piece.h"
#include "Board.h"
#include "NextPieceBoard.h"
#include "PieceCreating.h"
#include "Button.h"
#include "Enums.h"
#include "GameSound.h"

class Game 
{
private:
    int boardWidth;                 // ширина поля
    int boardHeight;                // высота поля

    PieceCreating* pieceCreating;   // указатель на объект класса PieceCreating для создания фигур
    Board* gameBoard;               // указатель на объект класса игрового поля
    bool gameOver = false;          // флаг конца игры
    int score = 0;                  // рейтинг
    int level = 1;                  // уровень
    int totalRows = 0;              // количество убранных линий
    bool volume = true;             // флаг звука (on/off)
    bool shadowFlag = true;         // флаг тени (on/off)
    
    sf::Text scoreText;
    sf::Text linesText;

    sf::Font textFont = Resources::getFont("res/Exo-ExtraBold.ttf");

    int* gamePartPtr;               // указатель на выполняемую часть игры
    int* scorePtr;                  // указатель на основную переменную рейтинга
    int* levelPtr;                  // указатель на основную переменную уровня
    int* linesPtr;                  // указатель на основную переменную количества линий

    sf::Image icon;                 // иконка
    sf::RenderWindow* window;       // окно sfml

    sf::Sprite pauseWindow;
    sf::Texture pauseWindowTexture;

    Button* pauseButton;
    Button* volumeButton;
    Button* shadowButton;

    // движение фигуры
    // true - успешно, false - нет
    bool moveLeft           (Piece* piece, Piece* shadowPiece);
    bool moveRight          (Piece* piece, Piece* shadowPiece);

    // поворот фигуры
    // true - успешно, false - нет
    bool rotate             (Piece* piece, Piece* shadowPiece);

    // опускает фигуру вниз на 1 клетку
    // true - успешно, false - нет
    bool fallDown           (Piece* piece);

    // устанавливает позицию тени
    void setShadowPosition  (Piece* currentPiece, Piece* shadowPiece);

    // измененяет рейтинг относительно количества удалённых строк
    void updateScore        (int clearedRows);

    // измененяет уровень относительно количества удалённых строк
    void updateLevel        ();
public:
    Game                    (sf::RenderWindow* window, int boardWidth,
                            int boardHeight, bool volume, int* gamePartPtr, 
                            int* scorePtr, int* levelPtr, int*linesPtr, bool shadowFlag);
    // деструктор
    ~Game();

    // основной цикл игры
    void run();

    // выводит текущий рейтинг на экран
    void setScore(int score);

    // выводит текущее количество убранных линий на экран
    void setLines(int lines);
};