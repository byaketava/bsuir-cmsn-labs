#pragma once
#include "Piece.h"

class IPiece : public Piece 
{
    static Cell cells[4][4];
public:
    IPiece(int rotation, int spawnX);
};