#include "LPiece.h"
#include "Enums.h"

Cell LPiece::cells[4][4] =
{
    {
        Cell(1, 0),  Cell(1, 1),  Cell(1, 2),  Cell(2, 2)
    },
    {
        Cell(0, 1),  Cell(1, 1),  Cell(2, 1),  Cell(0, 2)
    },
    {
        Cell(0, 0),  Cell(1, 0),  Cell(1, 1),  Cell(1, 2)
    },
    {
        Cell(0, 1),  Cell(1, 1),  Cell(2, 1),  Cell(2, 0)
    }
};

LPiece::LPiece(int rotation, int spawnX) : Piece(rotation, LP, (Cell*)cells, spawnX) {}