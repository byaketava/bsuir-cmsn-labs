#include "OPiece.h"
#include "Enums.h"

Cell OPiece::cells[4][4] =
{
    {
        Cell(1, 1),  Cell(2, 1),  Cell(1, 2),  Cell(2, 2)
    },
    {
        Cell(1, 1),  Cell(2, 1),  Cell(1, 2),  Cell(2, 2)
    },
    {
        Cell(1, 1),  Cell(2, 1),  Cell(1, 2),  Cell(2, 2)
    },
    {
        Cell(1, 1),  Cell(2, 1),  Cell(1, 2),  Cell(2, 2)
    }
};

OPiece::OPiece(int rotation, int spawnX) : Piece(rotation, OP, (Cell*)cells, spawnX) {}