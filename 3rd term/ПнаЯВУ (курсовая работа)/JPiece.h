#pragma once
#include "Piece.h"

class JPiece : public Piece
{
    static Cell cells[4][4];
public:
    JPiece(int rotation, int spawnX);
};

