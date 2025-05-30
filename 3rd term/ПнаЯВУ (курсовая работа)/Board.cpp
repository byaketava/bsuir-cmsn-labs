#include "Board.h"

void Board::initialization(int tileSize)
{
    // ������� �����
    this->setPosition(X_OFFSET, Y_OFFSET);

    // ��������� ������� ������
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(this->boardWidth * this->boardHeight * 4);

    // ������������� �������
    updateAllTextures(tileSize);
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const           
{
    states.transform *= getTransform();
    states.texture = &tileset;
    target.draw(vertices, states);
}

Board::Board(int boardWidth, int boardHeight) 
{
    this->boardWidth = boardWidth;
    this->boardHeight = boardHeight;
    this->tileset = Resources::getTexture("res/tiles.png");
   
    this->board = new int* [this->boardWidth];
    for (int i = 0; i < this->boardWidth; i++)
        this->board[i] = new int[boardHeight];

    for (int i = 0; i < this->boardWidth; i++) 
    {
        for (int j = 0; j < this->boardHeight; j++) 
        {
            if (i == 0 || i == this->boardWidth - 1 || j == this->boardHeight - 1) 
            {
                board[i][j] = WALL;
            }
            else 
            {
                board[i][j] = NONE;
            }
        }
    }
}

bool Board::collidesWith(int x, int y, Cell* shape)
{
    // ������ 4 ������ ������
    for (int i = 0; i < 4; i++)
    {
        // ���� �����-���� ������ �� ����� ������� ������ (������������ ����������)
        if (this->board[x + shape[i].getX()][y + shape[i].getY()] != NONE)
            return true;
    }
    // ���� ������������ �� ���������� ������� ����
    return false;
}

bool Board::add(Piece* piece)
{
    // ������ ������ ������ ����������� ������ ����� ������
    for (int i = 0; i < 4; i++) 
    {
        // ���� ������ � ���� ��������� ����� (~4 ����� � ������, ����������� �� ����), ������� false (gameover)
        if ((piece->getPiecePosition().getY() + piece->getCurrentShape()[i].getY() < 4) && 
            (piece->getPiecePosition().getX() + piece->getCurrentShape()[i].getX() >4 && piece->getPiecePosition().getX() + piece->getCurrentShape()[i].getX() < 7))
            return false;
        // ����� ��������� ������ ������ ������ (������)
        board[piece->getPiecePosition().getX() + piece->getCurrentShape()[i].getX()]
             [piece->getPiecePosition().getY() + piece->getCurrentShape()[i].getY()] = piece->getCurrentColor();
        // �������� �������� ������
        updateTexture(piece->getPiecePosition(), piece->getCurrentShape()[i], piece->getCurrentColor(), 40);
    }
    return true;
}

void Board::updateTexture(Cell piecePos, Cell shapeCell, int color, int tileSize)
{
    // �������� �������� ��������� ������
    sf::Vertex* quad = &vertices[(piecePos.getX() + shapeCell.getX() + (piecePos.getY() + shapeCell.getY()) * this->boardWidth) * 4];
    quad[0].texCoords = sf::Vector2f(color * tileSize, 0);
    quad[1].texCoords = sf::Vector2f((color + 1) * tileSize, 0);
    quad[2].texCoords = sf::Vector2f((color + 1) * tileSize, tileSize);
    quad[3].texCoords = sf::Vector2f(color * tileSize, tileSize);
}

int Board::updateBoard() 
{
    bool  fullRow = true;
    int lineCounter = 0;
    // ����� � ������ ������ (�� �������� �������) �������� �����
    for (int y = this->boardHeight-2; y > 0; y--) 
    {
        fullRow = true;
        for (int x = 1; x < this->boardWidth - 1; x++) 
        {
            // ���� ���� �� ���� ������ ����� (0 ������) - ����� �� ���������
            if (board[x][y] == NONE)
                fullRow = false;
        }
        if (fullRow)
        {
            pushRowDown(y);
            lineCounter++;
            // ������� ������ � �� �� �����, �� ������ ���� ��������� ���� ������ ���� ���������
            y++;
        }
    }
    return lineCounter;
}

void Board::pushRowDown(int row) 
{
    for (int y = row; y > 0; y--) 
    {
        for (int x = 1; x < this->boardWidth - 1; x++) 
        {
            board[x][y] = board[x][y - 1];
            // ���������� ������� ����� ��������� �������� � ������� ����
            updateAllTextures(40);
        }
    }
}

void Board::updateAllTextures(int tileSize) 
{
    // * �� ����������� �����
    for (int i = 1; i < this->boardWidth - 1; i++) 
    {
        for (int j = 0; j < this->boardHeight-1; j++) 
        {
            // ����� � ������ - � ���� (������������ �������������, � ����� ��������� �� �������� ������)
            int tileNumber = board[i][j];
            
            // ������� �������
            sf::Vertex* quad = &vertices[(i + j * this->boardWidth) * 4];

            // ����������� ��� 4 ������
            quad[0].position = sf::Vector2f(i * tileSize, j * tileSize);
            quad[1].position = sf::Vector2f((i + 1) * tileSize, j * tileSize);
            quad[2].position = sf::Vector2f((i + 1) * tileSize, (j + 1) * tileSize);
            quad[3].position = sf::Vector2f(i * tileSize, (j + 1) * tileSize);

            // ����������� ��� 4 ��������� ��������
            quad[0].texCoords = sf::Vector2f(tileNumber * tileSize, 0);             
            quad[1].texCoords = sf::Vector2f((tileNumber + 1) * tileSize, 0);       
            quad[2].texCoords = sf::Vector2f((tileNumber + 1) * tileSize, tileSize);
            quad[3].texCoords = sf::Vector2f(tileNumber * tileSize, tileSize);      
        }
    }
}

Board::~Board() 
{
    for (int i = 0; i < this->boardWidth; i++)
        delete[] this->board[i];
    delete[] this->board;
}