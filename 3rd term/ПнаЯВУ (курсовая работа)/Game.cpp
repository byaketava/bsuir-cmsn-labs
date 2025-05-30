#include"Game.h"

Game::Game  (sf::RenderWindow* window, int boardWidth, int boardHeight, 
            bool volume, int* gamePartPtr, int* scorePtr,
            int* levelPtr, int* linesPtr, bool shadowFlag) 
{
    // ������ + 2 (������� �������)
    this->boardWidth    = boardWidth + 2;
    // ������ + 1 (������ �������)
    this->boardHeight   = boardHeight + 1;

    // ������������� �������� ������� ���� � �������� �����
    this->gameBoard     = new Board(this->boardWidth, this->boardHeight);
    this->pieceCreating = new PieceCreating(this->boardWidth / 2 - 2);

    // ����������� ���� ����������
    this->window        = window;
    this->volume        = volume;
    this->gamePartPtr   = gamePartPtr;
    this->scorePtr      = scorePtr;
    this->levelPtr      = levelPtr;
    this->linesPtr      = linesPtr;
    this->shadowFlag    = shadowFlag;

    // ����������� ��������
    scoreText.setFont(textFont);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color(252, 242, 231, 255));
    
    setScore(score);

    // ����������� ���������� �������� �����
    linesText.setFont(textFont);
    linesText.setCharacterSize(24);
    linesText.setFillColor(sf::Color(252, 242, 231, 255));

    setLines(totalRows);

    // ����������� ���� �����
    pauseWindowTexture = Resources::getTexture("res/gamePaused.png");
    pauseWindow.setTexture(pauseWindowTexture);	

    // ������
    pauseButton   = new Button(sf::Vector2f(680, 330), Resources::getTexture("res/pauseNormal.png"), Resources::getTexture("res/pausePressed.png"));
    volumeButton  = new Button(sf::Vector2f(80, 330), Resources::getTexture("res/volumeon.png"), Resources::getTexture("res/volumeoff.png"));
    shadowButton  = new Button(sf::Vector2f(80, 430), Resources::getTexture("res/shadowNormal.png"), Resources::getTexture("res/shadowPressed.png"));
}

void Game::run()
{
    // ������������� ����
    gameBoard->initialization(40);

    // ��� ����
    sf::Sprite background;
    sf::Texture backgroundTexture = Resources::getTexture("res/background.png");
    background.setTexture(backgroundTexture);

    // ��������� ������� ������
    Piece* currentPiece = pieceCreating->getPiece();
    // ��������� ��������� ������
    Piece* nextPiece = pieceCreating->getPiece();
    // ��������� ���� ������
    Piece* shadowPiece = pieceCreating->getShadowPiece(currentPiece);
    setShadowPosition(currentPiece, shadowPiece);

    // ���� ��������� ������
    NextPieceBoard nextBoard(nextPiece, 40);

    if (volume)
        GameSound::play(0);
    else
        GameSound::stop(0);

    // ���� �������� �������
    bool fastFallFlag = false;
    // ���� ����������� �������
    bool instantFallFlag = false;
    // ���� �����
    bool pausedFlag = false;

    // ��������� ����� ��� �������� �������
    sf::Clock frameClock;
    sf::Clock keyClock;
    sf::Time frameTime = frameClock.getElapsedTime();
    sf::Time keyTime = keyClock.getElapsedTime();

    // �������� ������� ����
    while (window->isOpen())
    {
        // ������� ����
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

        // ���� � �������� ����
        if (*gamePartPtr == MENU)
        {
            GameSound::stop(0);
            break;
        }

        // ���� ������� ���� ����� ����
        if (gameOver)
        {
            GameSound::stop(0);
            *gamePartPtr = GAMEOVER;
            *levelPtr = level;
            *scorePtr = score;
            *linesPtr = totalRows;

            delete currentPiece;
            delete nextPiece;
            delete shadowPiece;

            break;
        }

        sf::Event event;

        // ��������� ������� � ������� (�������� ���� � ������� �������� ������/������/�����)
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            // ���� ���� �� �� �����
            if (!pausedFlag)
            {
                // ������ ������ �����, �� ��������� ���� �� �����
                if (pauseButton->updateButton(mousePos))
                {
                    GameSound::play(1);
                    GameSound::stop(0);
                    pausedFlag = !pausedFlag;
                }
                // ������ ������ �����, �� ��������/��������� ����
                else if (volumeButton->updateButton(mousePos))
                {
                    GameSound::play(1);
                    volume = !volume;
                    if (volume)
                        GameSound::play(0);
                    else
                        GameSound::stop(0);
                }
                // ������ ������ ����, �� ��������/��������� ����
                else if (shadowButton->updateButton(mousePos))
                {
                    GameSound::play(1);
                    shadowFlag = !shadowFlag;
                }
            }
            // ���� ���� �� �����, �� ���������� ������ ����� ����� ����/������ (� ������� ������ ��� P)
            if (pausedFlag && (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)))
            {
                pausedFlag = !pausedFlag;
                if (volume)
                    GameSound::play(0);
                else
                    GameSound::stop(0);
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                {
                    if (!pausedFlag)
                        rotate(currentPiece, shadowPiece);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                {
                    *gamePartPtr = MENU;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                {
                    pausedFlag = !pausedFlag;
                    if (pausedFlag)
                        GameSound::stop(0);
                    else if (volume)
                        GameSound::play(0);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
                {
                    shadowFlag = !shadowFlag;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
                {
                    volume = !volume;
                    if (volume)
                        GameSound::play(0);
                    else
                        GameSound::stop(0);
                }
            }
        }

        // ��������� ������� ������������ ����� ������ (��� ����� ������� ���� ���������� �� ������� �������)
        keyTime = keyClock.getElapsedTime();
        if (!pausedFlag)
        {
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                && keyTime.asSeconds() > 0.04)
            {
                fastFallFlag = true;
                keyClock.restart();
            }
            else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::F))
                && keyTime.asSeconds() > 0.2)
            {
                instantFallFlag = true;
                keyClock.restart();
            }
            else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                && keyTime.asSeconds() > 0.1)
            {
                moveLeft(currentPiece, shadowPiece);
                keyClock.restart();
            }
            else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                && keyTime.asSeconds() > 0.1)
            {
                moveRight(currentPiece, shadowPiece);
                keyClock.restart();
            }
        }

        // ���������
        window->clear();
        window->draw(background);
        window->draw(nextBoard);
        window->draw(*gameBoard);

        window->draw(scoreText);
        window->draw(linesText);

        window->draw(*pauseButton);
        window->draw(*volumeButton);
        window->draw(*shadowButton);
        if (shadowFlag)
            window->draw(*shadowPiece);
        window->draw(*currentPiece);
        if (pausedFlag)
            window->draw(pauseWindow);

        window->display();

        // ������� �����
        frameTime = frameClock.getElapsedTime();
        if (!pausedFlag && (fastFallFlag || (frameTime.asSeconds() > 1 - (level - 1) * 0.025)))
        {
            frameClock.restart();

            // ���� ������� ������ �� 1 ���� ����������
            if (!fallDown(currentPiece))
            {
                // add ���������� true ���� ������ ��������� �������
                gameOver = !gameBoard->add(currentPiece);

                delete currentPiece;
                delete shadowPiece;

                // ��������� ������ ���������� �������
                currentPiece = nextPiece;
                currentPiece->setPiecePosition(this->boardWidth / 2 - 1, 0);

                // ����� ��������� ������
                nextPiece = pieceCreating->getPiece();
                nextBoard.setPiece(nextPiece);

                // ����� ������ ����
                shadowPiece = pieceCreating->getShadowPiece(currentPiece);

                // �������� ����������� �����
                // ��������� ����� ��������� ����� � ������� ������ updateBoard()
                int clearedRows = gameBoard->updateBoard();

                if (clearedRows)
                    GameSound::play(2);

                // ���������� ������� ���� ������
                setShadowPosition(currentPiece, shadowPiece);

                // ���������� �������� � ������
                this->totalRows += clearedRows;

                updateScore(clearedRows);
                updateLevel();
            }
            fastFallFlag = false;

            // ���������� ����������� �������� � ���������� �������� ����� �� ������
            setScore(score);
            setLines(totalRows);
        }
        if (!pausedFlag && instantFallFlag)
        {
            // ���������� �������� ��� ���������� �������
            this->score += 10;

            currentPiece->setPiecePosition(shadowPiece->getPiecePosition().getX(), shadowPiece->getPiecePosition().getY());

            // add ���������� true ���� ������ ��������� �������
            gameOver = !gameBoard->add(currentPiece);

            delete currentPiece;
            delete shadowPiece;

            // ��������� ������ ���������� �������
            currentPiece = nextPiece;
            currentPiece->setPiecePosition(this->boardWidth / 2 - 1, 0);

            // ����� ��������� ������
            nextPiece = pieceCreating->getPiece();
            nextBoard.setPiece(nextPiece);

            // ����� ������ ����
            shadowPiece = pieceCreating->getShadowPiece(currentPiece);

            // �������� ����������� �����
            // �������� ����� ��������� ����� � ������� ������ updateBoard()
            int clearedRows = gameBoard->updateBoard();

             if (clearedRows)
                 GameSound::play(2);

            // ���������� ������� ���� ������
            setShadowPosition(currentPiece, shadowPiece);

            // ���������� �������� � ������
            this->totalRows += clearedRows;

            updateScore(clearedRows);
            updateLevel();

            instantFallFlag = false;

            // ���������� ����������� �������� � ���������� �������� ����� �� ������
            setScore(score);
            setLines(totalRows);
        }
    }
}

bool Game::moveLeft(Piece* piece, Piece* shadowPiece) 
{
    // ���� �� ����� ������������ ��� �������� �����
    if (!gameBoard->collidesWith(piece->getPiecePosition().getX() - 1,
                                 piece->getPiecePosition().getY(),
                                 piece->getCurrentShape())) 
    {
        // ���������� ����� ������� ������ �� ����
        piece->setPiecePosition(piece->getPiecePosition().getX() - 1, 
                                piece->getPiecePosition().getY());
        // ���������� ����� ������� ���� �� ����
        setShadowPosition(piece, shadowPiece);
        return true;
    }
    return false;
}

bool Game::moveRight(Piece* piece, Piece* shadowPiece)
{
    // ���� �� ����� ������������ ��� �������� ������
    if (!gameBoard->collidesWith(piece->getPiecePosition().getX() + 1,
                                 piece->getPiecePosition().getY(),
                                 piece->getCurrentShape())) 
    {
        // ���������� ����� ������� ������ �� ����
        piece->setPiecePosition(piece->getPiecePosition().getX() + 1, 
                                piece->getPiecePosition().getY());
        // ���������� ����� ������� ���� �� ����
        setShadowPosition(piece, shadowPiece);
        return true;
    }
    return false;
}

bool Game::rotate(Piece* piece, Piece* shadowPiece)
{
    // ���� �� ����� ������������ ����� ��������
    if (!gameBoard->collidesWith(piece->getPiecePosition().getX(),
                                 piece->getPiecePosition().getY(),
                                 piece->getRotationShape())) 
    {
        // ��������� ������
        piece->rotate();
        // ��������� ����
        setShadowPosition(piece, shadowPiece);
        return true;
    }
    return false;
}

bool Game::fallDown(Piece* piece) 
{
    // ���� ����� ������� �� ����� ������������
    if (!gameBoard->collidesWith(piece->getPiecePosition().getX(),
                                 piece->getPiecePosition().getY() + 1,
                                 piece->getCurrentShape())) 
    {
        // �������� ������
        piece->setPiecePosition(piece->getPiecePosition().getX(), piece->getPiecePosition().getY() + 1);
        return true;
    }
    return false;
}

void Game::setShadowPosition(Piece* currentPiece, Piece* shadowPiece)
{
    // ���������� ������� ���� ����� �� ��� � ������
    shadowPiece->setRotation(currentPiece->getRotation());
    // ���������� ������� ���� ����� �� ��� � ������
    shadowPiece->setPiecePosition(currentPiece->getPiecePosition());

    // ���������� ��������� ���������� ��������� ����
    // (�������� ���� �� ����������� ������������)
    while (!gameBoard->collidesWith(shadowPiece->getPiecePosition().getX(),
                                    shadowPiece->getPiecePosition().getY() + 1,
                                    shadowPiece->getCurrentShape())) 
    {
        shadowPiece->setPiecePosition(shadowPiece->getPiecePosition().getX(),
                                      shadowPiece->getPiecePosition().getY() + 1);
    }
}

void Game::updateScore(int clearedRows) 
{
    // ���������� �������� �� ��������� ���������� �������� �����
    switch (clearedRows) 
    {
    case 1:
        this->score += 50 * this->level;
        break;
    case 2:
        this->score += 150 * this->level;
        break;
    case 3:
        this->score += 350 * this->level;
        break;
    case 4:
        this->score += 750 * this->level;
        break;
    }
}

void Game::updateLevel() 
{
    this->level = this->totalRows / 5 + 1;
}

void Game::setScore(int score)
{
    scoreText.setString(std::to_string(score));
    sf::FloatRect rectangle(90, 100, 120, 50);
    sf::FloatRect textBounds = scoreText.getGlobalBounds();
    float X = rectangle.left + (rectangle.width - textBounds.width) / 2.f;
    float Y = rectangle.top + (rectangle.height - textBounds.height) / 2.f;
    scoreText.setPosition(X, Y);
}

void Game::setLines(int lines)
{
    linesText.setString(std::to_string(lines));
    sf::FloatRect rectangle(90, 220, 120, 50);
    sf::FloatRect textBounds = linesText.getGlobalBounds();
    float X = rectangle.left + (rectangle.width - textBounds.width) / 2.f;
    float Y = rectangle.top + (rectangle.height - textBounds.height) / 2.f;
    linesText.setPosition(X, Y);
}

Game::~Game() 
{
    delete this->gameBoard;
    delete this->pieceCreating;

    delete this->pauseButton;
    delete this->volumeButton;
    delete this->shadowButton;
}