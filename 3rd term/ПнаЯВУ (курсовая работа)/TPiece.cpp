#include "TPiece.h"
#include "Enums.h"

Cell TPiece::cells[4][4] =
{
    {
        Cell(0, 1),  Cell(1, 1),  Cell(1, 0),  Cell(1, 2)
    },
    {
        Cell(0, 1),  Cell(1, 1),  Cell(1, 0),  Cell(2, 1)
    },
    {
        Cell(1, 0),  Cell(1, 1),  Cell(1, 2),  Cell(2, 1)
    },
    {
        Cell(0, 1),  Cell(1, 1),  Cell(2, 1),  Cell(1, 2)
    }
};

TPiece::TPiece(int rotation, int spawnX) : Piece(rotation, TP, (Cell*)cells, spawnX) {}