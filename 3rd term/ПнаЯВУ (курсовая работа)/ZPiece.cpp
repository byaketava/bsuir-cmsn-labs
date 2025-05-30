#include "ZPiece.h"
#include "Enums.h"

Cell ZPiece::cells[4][4] =
{
    {
        Cell(2, 0),  Cell(2, 1),  Cell(1, 1),  Cell(1, 2)
    },
    {
        Cell(0, 0),  Cell(1, 0),  Cell(1, 1),  Cell(2, 1)
    },
    {
        Cell(2, 0),  Cell(2, 1),  Cell(1, 1),  Cell(1, 2)
    },
    {
        Cell(0, 0),  Cell(1, 0),  Cell(1, 1),  Cell(2, 1)
    }
};

ZPiece::ZPiece(int rotation, int spawnX) : Piece(rotation, ZP, (Cell*)cells, spawnX) {}