#pragma once
#include <vector>
#include <random>
#include <chrono>
#include "Enums.h"
#include "Piece.h"
#include "IPiece.h"
#include "JPiece.h"
#include "LPiece.h"
#include "OPiece.h"
#include "TPiece.h"
#include "SPiece.h"
#include "ZPiece.h"
#include "ShadowPiece.h"

class PieceCreating
{
    std::vector <int> pieces;
    int spawnX;

    // ��������� ������ ����� ���������� ��������, � ����� ������������ ��
    void fillVector();
public:
    // ����������� ������
    PieceCreating(int spawnX);

    // ���������� ��������� ������ �� �������, ������� � �� �������
    // ���� ������ ��� ���� ������������ ���������, �� ���������� ����� fillVector()
    Piece* getPiece();

    // ���������� ���� �������� ������
    Piece* getShadowPiece(Piece* currentPiece);
};