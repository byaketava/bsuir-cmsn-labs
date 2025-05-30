#pragma once
#include <vector>
#include <random>
#include <chrono>
#include "Enums.h"
#include "Piece.h"
#include "IPiece.h"
#include "JPiece.h"
#include "LPiece.h"
#include "OPiece.h"
#include "TPiece.h"
#include "SPiece.h"
#include "ZPiece.h"
#include "ShadowPiece.h"

class PieceCreating
{
    std::vector <int> pieces;
    int spawnX;

    // заполняет вектор всеми возможными фигурами, а затем перемешивает их
    void fillVector();
public:
    // конструктор класса
    PieceCreating(int spawnX);

    // возвращает случайную фигуру из вектора, удаляет её из вектора
    // если вектор при этом опустошается полностью, то вызывается метод fillVector()
    Piece* getPiece();

    // возвращает тень нынешней фигуры
    Piece* getShadowPiece(Piece* currentPiece);
};