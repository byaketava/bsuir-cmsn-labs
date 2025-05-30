#include "NextPieceBoard.h"

NextPieceBoard::NextPieceBoard(Piece* piece, int tileSize) 
{
    this->tileSize = tileSize;
    this->piece = piece;

    // определение позиции фигуры в окне NEXT
    int type = 0;
    type = this->piece->getCurrentShapeInt();
    switch (type)
    {
    case IP:
        this->piece->setPiecePosition(17, 2, false);
        break;
    case JP:
        this->piece->setPiecePosition(17, 3, false);
        break;
    case LP:
        this->piece->setPiecePosition(16, 3, false);
        break;
    case OP:
        this->piece->setPiecePosition(16, 2, false);
        break;
    case SP:
        this->piece->setPiecePosition(16, 3, false);
        break;
    case TP:
        this->piece->setPiecePosition(17, 3, false);
        break;
    case ZP:
        this->piece->setPiecePosition(16, 3, false);
        break;
    default:
        break;
    }
}

void NextPieceBoard::setPiece(Piece* piece)
{
    this->piece = piece;
    switch (piece->getCurrentShapeInt())
    {
    case IP:
        this->piece->setPiecePosition(17, 2, false);
        break;
    case JP:
        this->piece->setPiecePosition(17, 3, false);
        break;
    case LP:
        this->piece->setPiecePosition(16, 3, false);
        break;
    case OP:
        this->piece->setPiecePosition(16, 2, false);
        break;
    case SP:
        this->piece->setPiecePosition(16, 3, false);
        break;
    case TP:
        this->piece->setPiecePosition(17, 3, false);
        break;
    case ZP:
        this->piece->setPiecePosition(16, 3, false);
        break;
    default:
        break;
    }
}

void NextPieceBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(*piece);
}