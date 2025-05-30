#include "IPiece.h"
#include "Enums.h"

Cell IPiece::cells[4][4] =
{ 
    {
        Cell(1, 0),  Cell(1, 1),  Cell(1, 2),  Cell(1, 3)
    },
    {
        Cell(0, 1),  Cell(1, 1),  Cell(2, 1),  Cell(3, 1)
    },
    {
        Cell(2, 0),  Cell(2, 1),  Cell(2, 2),  Cell(2, 3)
    },
    {
        Cell(0, 2),  Cell(1, 2),  Cell(2, 2),  Cell(3, 2)
    }
};

IPiece::IPiece(int rotation, int spawnX) : Piece(rotation, IP, (Cell*)cells, spawnX) {}