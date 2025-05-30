#include "PieceCreating.h"

PieceCreating::PieceCreating(int spawnX)
{
    this->spawnX = spawnX;
    fillVector();
}

void PieceCreating::fillVector() 
{
    // ���������� ������� ����� ���������� �������� (�� ��������������� � ������������)
    this->pieces.push_back(IP);
    this->pieces.push_back(JP);
    this->pieces.push_back(LP);
    this->pieces.push_back(OP);
    this->pieces.push_back(SP);
    this->pieces.push_back(TP);
    this->pieces.push_back(ZP);

    // ������������� ����� � ������� ���������� ��������� �����
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(this->pieces.begin(), this->pieces.end(), std::default_random_engine(seed));
}

Piece* PieceCreating::getPiece() 
{
    // ���� ������ ����, �� ��������� ��� ������
    if (pieces.empty())
        fillVector();

    // ��������� ��������� ������
    int random = pieces[0];

    // �������� � �� �������
    pieces.erase(pieces.begin(), pieces.begin() + 1);

    Piece* figure = NULL;
    switch (random) 
    {
    case 1:
        figure = new IPiece(0, spawnX);
        break;
    case 2:
        figure = new JPiece(0, spawnX);
        break;
    case 3:
        figure = new LPiece(0, spawnX);
        break;
    case 4:
        figure = new OPiece(0, spawnX);
        break;
    case 5:
        figure = new SPiece(0, spawnX);
        break;
    case 6:
        figure = new TPiece(0, spawnX);
        break;
    case 7:
        figure = new ZPiece(0, spawnX);
        break;
    }
    return figure;
}

Piece* PieceCreating::getShadowPiece(Piece* currentPiece) 
{
    return new ShadowPiece(currentPiece->getRotation(), currentPiece->getShapes());
}