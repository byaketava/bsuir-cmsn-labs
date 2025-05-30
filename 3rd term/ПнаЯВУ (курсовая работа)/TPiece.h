#pragma once
#include "Piece.h"

class TPiece : public Piece
{
    static Cell cells[4][4];
public:
    TPiece(int rotation, int spawnX);
};