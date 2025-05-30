#include "JPiece.h"
#include "Enums.h"

Cell JPiece::cells[4][4] =
{ 
    {
        Cell(1, 0),  Cell(1, 1),  Cell(1, 2),  Cell(0, 2)
    },
    {
        Cell(0, 0),  Cell(0, 1),  Cell(1, 1),  Cell(2, 1)
    },
    {
        Cell(2, 0),  Cell(1, 0),  Cell(1, 1),  Cell(1, 2)
    },
    {
        Cell(0, 1),  Cell(1, 1),  Cell(2, 1),  Cell(2, 2)
    }
};

JPiece::JPiece(int rotation, int spawnX) : Piece(rotation, JP, (Cell*)cells, spawnX) {}