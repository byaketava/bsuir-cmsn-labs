#pragma once
#include "Piece.h"

class ZPiece : public Piece
{
    static Cell cells[4][4];
public:
    ZPiece(int rotation, int spawnX);
};