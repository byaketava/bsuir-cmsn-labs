#pragma once
#include "Piece.h"

class LPiece : public Piece
{
    static Cell cells[4][4];
public:
    LPiece(int rotation, int spawnX);
};