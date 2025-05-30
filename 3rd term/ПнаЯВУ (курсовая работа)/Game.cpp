#include"Game.h"

Game::Game  (sf::RenderWindow* window, int boardWidth, int boardHeight, 
            bool volume, int* gamePartPtr, int* scorePtr,
            int* levelPtr, int* linesPtr, bool shadowFlag) 
{
    // ширина + 2 (боковые границы)
    this->boardWidth    = boardWidth + 2;
    // высота + 1 (нижняя граница)
    this->boardHeight   = boardHeight + 1;

    // инициализация объектов классов поля и создания фигур
    this->gameBoard     = new Board(this->boardWidth, this->boardHeight);
    this->pieceCreating = new PieceCreating(this->boardWidth / 2 - 2);

    // определение всех указателей
    this->window        = window;
    this->volume        = volume;
    this->gamePartPtr   = gamePartPtr;
    this->scorePtr      = scorePtr;
    this->levelPtr      = levelPtr;
    this->linesPtr      = linesPtr;
    this->shadowFlag    = shadowFlag;

    // отображение рейтинга
    scoreText.setFont(textFont);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color(252, 242, 231, 255));
    
    setScore(score);

    // отображение количества убранных линий
    linesText.setFont(textFont);
    linesText.setCharacterSize(24);
    linesText.setFillColor(sf::Color(252, 242, 231, 255));

    setLines(totalRows);

    // определение окна паузы
    pauseWindowTexture = Resources::getTexture("res/gamePaused.png");
    pauseWindow.setTexture(pauseWindowTexture);	

    // кнопки
    pauseButton   = new Button(sf::Vector2f(680, 330), Resources::getTexture("res/pauseNormal.png"), Resources::getTexture("res/pausePressed.png"));
    volumeButton  = new Button(sf::Vector2f(80, 330), Resources::getTexture("res/volumeon.png"), Resources::getTexture("res/volumeoff.png"));
    shadowButton  = new Button(sf::Vector2f(80, 430), Resources::getTexture("res/shadowNormal.png"), Resources::getTexture("res/shadowPressed.png"));
}

void Game::run()
{
    // инициализация поля
    gameBoard->initialization(40);

    // фон игры
    sf::Sprite background;
    sf::Texture backgroundTexture = Resources::getTexture("res/background.png");
    background.setTexture(backgroundTexture);

    // получение текущей фигуры
    Piece* currentPiece = pieceCreating->getPiece();
    // получение следующей фигуры
    Piece* nextPiece = pieceCreating->getPiece();
    // получение тени фигуры
    Piece* shadowPiece = pieceCreating->getShadowPiece(currentPiece);
    setShadowPosition(currentPiece, shadowPiece);

    // окно следующей фигуры
    NextPieceBoard nextBoard(nextPiece, 40);

    if (volume)
        GameSound::play(0);
    else
        GameSound::stop(0);

    // флаг быстрого падения
    bool fastFallFlag = false;
    // флаг мгновенного падения
    bool instantFallFlag = false;
    // флаг паузы
    bool pausedFlag = false;

    // установка часов для подсчёта времени
    sf::Clock frameClock;
    sf::Clock keyClock;
    sf::Time frameTime = frameClock.getElapsedTime();
    sf::Time keyTime = keyClock.getElapsedTime();

    // основной игровой цикл
    while (window->isOpen())
    {
        // позиция мыши
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

        // вход в основное меню
        if (*gamePartPtr == MENU)
        {
            GameSound::stop(0);
            break;
        }

        // если истинен флаг конца игры
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

        // обработка событий в очереди (закрытие окна и клавиши поворота фигуры/выхода/паузы)
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

            // если игра не на паузе
            if (!pausedFlag)
            {
                // нажата кнопка паузы, то поставить игру на паузу
                if (pauseButton->updateButton(mousePos))
                {
                    GameSound::play(1);
                    GameSound::stop(0);
                    pausedFlag = !pausedFlag;
                }
                // нажата кнопка звука, то включить/выключить звук
                else if (volumeButton->updateButton(mousePos))
                {
                    GameSound::play(1);
                    volume = !volume;
                    if (volume)
                        GameSound::play(0);
                    else
                        GameSound::stop(0);
                }
                // нажата кнопка тени, то включить/выключить тень
                else if (shadowButton->updateButton(mousePos))
                {
                    GameSound::play(1);
                    shadowFlag = !shadowFlag;
                }
            }
            // если игра на паузе, то продолжить играть можно нажав ввод/пробел (в условии дальше ещё P)
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

        // обработка событий непрерывного ввода клавиш (для более плавной игры независимо от очереди событий)
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

        // отрисовка
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

        // падение фигур
        frameTime = frameClock.getElapsedTime();
        if (!pausedFlag && (fastFallFlag || (frameTime.asSeconds() > 1 - (level - 1) * 0.025)))
        {
            frameClock.restart();

            // если падение фигуры на 1 вниз невозможно
            if (!fallDown(currentPiece))
            {
                // add возвращает true если фигура добавлена успешно
                gameOver = !gameBoard->add(currentPiece);

                delete currentPiece;
                delete shadowPiece;

                // следующая фигура становится текущей
                currentPiece = nextPiece;
                currentPiece->setPiecePosition(this->boardWidth / 2 - 1, 0);

                // новая следующая фигура
                nextPiece = pieceCreating->getPiece();
                nextBoard.setPiece(nextPiece);

                // новая фигура тени
                shadowPiece = pieceCreating->getShadowPiece(currentPiece);

                // удаление заполненных линий
                // получение числа очищенных строк с помощью метода updateBoard()
                int clearedRows = gameBoard->updateBoard();

                if (clearedRows)
                    GameSound::play(2);

                // обновление позиции тени фигуры
                setShadowPosition(currentPiece, shadowPiece);

                // обновление рейтинга и уровня
                this->totalRows += clearedRows;

                updateScore(clearedRows);
                updateLevel();
            }
            fastFallFlag = false;

            // обновление отображения рейтинга и количества убранных линий на экране
            setScore(score);
            setLines(totalRows);
        }
        if (!pausedFlag && instantFallFlag)
        {
            // увеличение рейтинга при мгновенном падении
            this->score += 10;

            currentPiece->setPiecePosition(shadowPiece->getPiecePosition().getX(), shadowPiece->getPiecePosition().getY());

            // add возвращает true если фигура добавлена успешно
            gameOver = !gameBoard->add(currentPiece);

            delete currentPiece;
            delete shadowPiece;

            // следующая фигура становится текущей
            currentPiece = nextPiece;
            currentPiece->setPiecePosition(this->boardWidth / 2 - 1, 0);

            // новая следующая фигура
            nextPiece = pieceCreating->getPiece();
            nextBoard.setPiece(nextPiece);

            // новая фигура тени
            shadowPiece = pieceCreating->getShadowPiece(currentPiece);

            // удаление заполненных линий
            // получаем число очищенных строк с помощью метода updateBoard()
            int clearedRows = gameBoard->updateBoard();

             if (clearedRows)
                 GameSound::play(2);

            // обновление позиции тени фигуры
            setShadowPosition(currentPiece, shadowPiece);

            // обновление рейтинга и уровня
            this->totalRows += clearedRows;

            updateScore(clearedRows);
            updateLevel();

            instantFallFlag = false;

            // обновление отображения рейтинга и количества убранных линий на экране
            setScore(score);
            setLines(totalRows);
        }
    }
}

bool Game::moveLeft(Piece* piece, Piece* shadowPiece) 
{
    // если не будет столкновения при движении влево
    if (!gameBoard->collidesWith(piece->getPiecePosition().getX() - 1,
                                 piece->getPiecePosition().getY(),
                                 piece->getCurrentShape())) 
    {
        // установить новую позицию фигуры на поле
        piece->setPiecePosition(piece->getPiecePosition().getX() - 1, 
                                piece->getPiecePosition().getY());
        // установить новую позицию тени на поле
        setShadowPosition(piece, shadowPiece);
        return true;
    }
    return false;
}

bool Game::moveRight(Piece* piece, Piece* shadowPiece)
{
    // если не будет столкновения при движении вправо
    if (!gameBoard->collidesWith(piece->getPiecePosition().getX() + 1,
                                 piece->getPiecePosition().getY(),
                                 piece->getCurrentShape())) 
    {
        // установить новую позицию фигуры на поле
        piece->setPiecePosition(piece->getPiecePosition().getX() + 1, 
                                piece->getPiecePosition().getY());
        // установить новую позицию тени на поле
        setShadowPosition(piece, shadowPiece);
        return true;
    }
    return false;
}

bool Game::rotate(Piece* piece, Piece* shadowPiece)
{
    // если не будет столкновения после поворота
    if (!gameBoard->collidesWith(piece->getPiecePosition().getX(),
                                 piece->getPiecePosition().getY(),
                                 piece->getRotationShape())) 
    {
        // повернуть фигуру
        piece->rotate();
        // повернуть тень
        setShadowPosition(piece, shadowPiece);
        return true;
    }
    return false;
}

bool Game::fallDown(Piece* piece) 
{
    // если после падения не будет столкновения
    if (!gameBoard->collidesWith(piece->getPiecePosition().getX(),
                                 piece->getPiecePosition().getY() + 1,
                                 piece->getCurrentShape())) 
    {
        // опустить фигуру
        piece->setPiecePosition(piece->getPiecePosition().getX(), piece->getPiecePosition().getY() + 1);
        return true;
    }
    return false;
}

void Game::setShadowPosition(Piece* currentPiece, Piece* shadowPiece)
{
    // установить поворот тени таким же как у фигуры
    shadowPiece->setRotation(currentPiece->getRotation());
    // установить позицию тени такой же как у фигуры
    shadowPiece->setPiecePosition(currentPiece->getPiecePosition());

    // нахождение нижайшего возможного положения тени
    // (движение вниз до обнаружения столкновения)
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
    // увеличение рейтинга на основании количества удалённых линий
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