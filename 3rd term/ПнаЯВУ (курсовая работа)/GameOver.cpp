#include "GameOver.h"

GameOver::GameOver(sf::RenderWindow* window, std::string filename, int* gameStatePtr, int* scorePtr, int* linesPtr) 
{
    this->window = window;
    this->gamePartPtr = gameStatePtr;
    this->scorePtr = scorePtr;
    this->linesPtr = linesPtr;
    this->filename = filename;    
    this->textFont = Resources::getFont("res/Exo-ExtraBold.ttf");

    nickText.setFont(textFont);
    nickText.setCharacterSize(26);
    nickText.setFillColor(sf::Color(252, 242, 231, 255));
    nickText.setString("start typing...");
    nickText.setPosition(window->getSize().x / 2 - nickText.getGlobalBounds().width / 2, 565);

    scoreText.setFont(textFont);
    scoreText.setCharacterSize(26);
    scoreText.setFillColor(sf::Color(252, 242, 231, 255));
    scoreText.setString(std::to_string(*scorePtr));
    scoreText.setPosition(window->getSize().x / 2 - scoreText.getGlobalBounds().width / 2, 335);

    linesText.setFont(textFont);
    linesText.setCharacterSize(26);
    linesText.setFillColor(sf::Color(252, 242, 231, 255));
    linesText.setString(std::to_string(*linesPtr));
    linesText.setPosition(window->getSize().x / 2 - linesText.getGlobalBounds().width / 2, 435);

    menuButton          = new Button(sf::Vector2f(220, 644), Resources::getTexture("res/menuNormal.png"), Resources::getTexture("res/menuPressed.png"));
    playButton          = new Button(sf::Vector2f(380, 644), Resources::getTexture("res/playNormal.png"), Resources::getTexture("res/playPressed.png"));
    leaderboardButton   = new Button(sf::Vector2f(540, 644), Resources::getTexture("res/leadersNormal.png"), Resources::getTexture("res/leadersPressed.png"));
}

GameOver::~GameOver() 
{
    delete this->menuButton;
    delete this->playButton;
    delete this->leaderboardButton;
}

void GameOver::run() 
{
    // установка заднего фона
    sf::Sprite  background;
    sf::Texture backgroundText = Resources::getTexture("res/gameoverBackground.png");
    background.setTexture(backgroundText);

    while (window->isOpen()) 
    {
        if (*gamePartPtr != GAMEOVER)
        {
            // при нажатии любой кнопки рейтинг сохранится в файл
            addScore();
            break;
        }
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // при закрытии окна рейтинг сохранится в файл
                addScore();
                window->close();
            }

            // если был введён текст
            if (event.type == sf::Event::TextEntered)
            {
                // если был нажат backspace
                if (event.text.unicode == '\b')
                {
                    // удаляется последний символ из строки nick
                    if (nick.length() > 0)
                        nick.erase(nick.length() - 1, 1);
                }
                // если символ отличен от пробела и находится в пределах A-z или 0-9
                else if (event.text.unicode != ' ' && ((event.text.unicode >= 'A' && event.text.unicode <= 'z') || (event.text.unicode >= '0' && event.text.unicode <= '9')))
                {
                    // и длина ника <= 15
                    if (nick.length() <= 15)
                        // добавить новый символ к нику
                        nick += event.text.unicode;
                }

                // установка текста для ника
                nickText.setString(nick);
                // установка позиции текста ника
                nickText.setPosition(window->getSize().x / 2 - nickText.getGlobalBounds().width / 2, 565);
            }
        }

        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

        if (menuButton->updateButton(mousePos)) 
        {
            GameSound::play(1);
            *gamePartPtr = MENU;
        }

        if (playButton->updateButton(mousePos)) 
        {
            GameSound::play(1);
            *gamePartPtr = GAME;
        }

        if (leaderboardButton->updateButton(mousePos)) 
        {
            GameSound::play(1);
            *gamePartPtr = LEADERBOARD;
        }

        window->clear();
        window->draw(background);

        window->draw(scoreText);
        window->draw(linesText);
        window->draw(nickText);

        window->draw(*menuButton);
        window->draw(*playButton);
        window->draw(*leaderboardButton);

        window->display();
    }
}

void GameOver::addScore() 
{
    // открытие файла рейтингов
    std::ofstream outputStream;
    outputStream.open(filename, std::fstream::out | std::fstream::app);

    // если никнейм не был введён
    if (nick == "")
        nick = "NoName";

    //запись в файл (никнейм - " " - рейтинг - \n)
    outputStream << nick << " " << std::to_string(*scorePtr) << "\n";
    outputStream.close();
}