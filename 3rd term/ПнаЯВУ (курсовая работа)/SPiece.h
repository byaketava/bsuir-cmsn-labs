#pragma once
#include "Piece.h"

class SPiece : public Piece
{
    static Cell cells[4][4];
public:
    SPiece(int rotation, int spawnX);
};