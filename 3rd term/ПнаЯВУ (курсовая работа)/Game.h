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
    int boardWidth;                 // ������ ����
    int boardHeight;                // ������ ����

    PieceCreating* pieceCreating;   // ��������� �� ������ ������ PieceCreating ��� �������� �����
    Board* gameBoard;               // ��������� �� ������ ������ �������� ����
    bool gameOver = false;          // ���� ����� ����
    int score = 0;                  // �������
    int level = 1;                  // �������
    int totalRows = 0;              // ���������� �������� �����
    bool volume = true;             // ���� ����� (on/off)
    bool shadowFlag = true;         // ���� ���� (on/off)
    
    sf::Text scoreText;
    sf::Text linesText;

    sf::Font textFont = Resources::getFont("res/Exo-ExtraBold.ttf");

    int* gamePartPtr;               // ��������� �� ����������� ����� ����
    int* scorePtr;                  // ��������� �� �������� ���������� ��������
    int* levelPtr;                  // ��������� �� �������� ���������� ������
    int* linesPtr;                  // ��������� �� �������� ���������� ���������� �����

    sf::Image icon;                 // ������
    sf::RenderWindow* window;       // ���� sfml

    sf::Sprite pauseWindow;
    sf::Texture pauseWindowTexture;

    Button* pauseButton;
    Button* volumeButton;
    Button* shadowButton;

    // �������� ������
    // true - �������, false - ���
    bool moveLeft           (Piece* piece, Piece* shadowPiece);
    bool moveRight          (Piece* piece, Piece* shadowPiece);

    // ������� ������
    // true - �������, false - ���
    bool rotate             (Piece* piece, Piece* shadowPiece);

    // �������� ������ ���� �� 1 ������
    // true - �������, false - ���
    bool fallDown           (Piece* piece);

    // ������������� ������� ����
    void setShadowPosition  (Piece* currentPiece, Piece* shadowPiece);

    // ���������� ������� ������������ ���������� �������� �����
    void updateScore        (int clearedRows);

    // ���������� ������� ������������ ���������� �������� �����
    void updateLevel        ();
public:
    Game                    (sf::RenderWindow* window, int boardWidth,
                            int boardHeight, bool volume, int* gamePartPtr, 
                            int* scorePtr, int* levelPtr, int*linesPtr, bool shadowFlag);
    // ����������
    ~Game();

    // �������� ���� ����
    void run();

    // ������� ������� ������� �� �����
    void setScore(int score);

    // ������� ������� ���������� �������� ����� �� �����
    void setLines(int lines);
};