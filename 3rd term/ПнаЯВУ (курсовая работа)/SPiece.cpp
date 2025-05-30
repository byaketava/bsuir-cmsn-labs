#include "SPiece.h"
#include "Enums.h"

Cell SPiece::cells[4][4] =
{
    {
        Cell(1, 0),  Cell(1, 1),  Cell(2, 1),  Cell(2, 2)
    },
    {
        Cell(0, 1),  Cell(1, 1),  Cell(1, 0),  Cell(2, 0)
    },
    {
        Cell(1, 0),  Cell(1, 1),  Cell(2, 1),  Cell(2, 2)
    },
    {
        Cell(0, 1),  Cell(1, 1),  Cell(1, 0),  Cell(2, 0)
    }
};

SPiece::SPiece(int rotation, int spawnX) : Piece(rotation, SP, (Cell*)cells, spawnX) {}