#include "Board.h"

void Board::initialization(int tileSize)
{
    // позиция доски
    this->setPosition(X_OFFSET, Y_OFFSET);

    // изменение массива вершин
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(this->boardWidth * this->boardHeight * 4);

    // инициализация текстур
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
    // каждые 4 клетки фигуры
    for (int i = 0; i < 4; i++)
    {
        // если какая-либо клетка не пуста вернуть истину (столкновение обнаружено)
        if (this->board[x + shape[i].getX()][y + shape[i].getY()] != NONE)
            return true;
    }
    // если столкновения не обнаружено вернуть ложь
    return false;
}

bool Board::add(Piece* piece)
{
    // каждая клетка фигуры заполняется числом цвета фигуры
    for (int i = 0; i < 4; i++) 
    {
        // если клетка в зоне появления фигур (~4 блока в высоту, центральные по иксу), вернуть false (gameover)
        if ((piece->getPiecePosition().getY() + piece->getCurrentShape()[i].getY() < 4) && 
            (piece->getPiecePosition().getX() + piece->getCurrentShape()[i].getX() >4 && piece->getPiecePosition().getX() + piece->getCurrentShape()[i].getX() < 7))
            return false;
        // иначе заполнить клетку цветом фигуры (числом)
        board[piece->getPiecePosition().getX() + piece->getCurrentShape()[i].getX()]
             [piece->getPiecePosition().getY() + piece->getCurrentShape()[i].getY()] = piece->getCurrentColor();
        // обновить текстуру клетки
        updateTexture(piece->getPiecePosition(), piece->getCurrentShape()[i], piece->getCurrentColor(), 40);
    }
    return true;
}

void Board::updateTexture(Cell piecePos, Cell shapeCell, int color, int tileSize)
{
    // обновить текстуру одиночной клетки
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
    // поиск с нижней строки (не учитывая границу) двигаясь вверх
    for (int y = this->boardHeight-2; y > 0; y--) 
    {
        fullRow = true;
        for (int x = 1; x < this->boardWidth - 1; x++) 
        {
            // если хотя бы одна клетка пуста (0 внутри) - линия не заполнена
            if (board[x][y] == NONE)
                fullRow = false;
        }
        if (fullRow)
        {
            pushRowDown(y);
            lineCounter++;
            // возврат поиска в то же место, на случай если опущенная вниз строка тоже заполнена
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
            // обновление текстур после изменения значений в клетках поля
            updateAllTextures(40);
        }
    }
}

void Board::updateAllTextures(int tileSize) 
{
    // * не обновляются стены
    for (int i = 1; i < this->boardWidth - 1; i++) 
    {
        for (int j = 0; j < this->boardHeight-1; j++) 
        {
            // число в клетке - её цвет (определяется перечислением, а затем смещением по текстуре плиток)
            int tileNumber = board[i][j];
            
            // текущий квадрат
            sf::Vertex* quad = &vertices[(i + j * this->boardWidth) * 4];

            // определение его 4 вершин
            quad[0].position = sf::Vector2f(i * tileSize, j * tileSize);
            quad[1].position = sf::Vector2f((i + 1) * tileSize, j * tileSize);
            quad[2].position = sf::Vector2f((i + 1) * tileSize, (j + 1) * tileSize);
            quad[3].position = sf::Vector2f(i * tileSize, (j + 1) * tileSize);

            // определение его 4 координат текстуры
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