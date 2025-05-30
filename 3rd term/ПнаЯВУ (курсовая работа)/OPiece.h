#pragma once
#include "Piece.h"

class OPiece : public Piece
{
    static Cell cells[4][4];
public:
    OPiece(int rotation, int spawnX);
};