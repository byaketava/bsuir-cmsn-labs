#include "Menu.h"

Menu::Menu(sf::RenderWindow* window, int* gamePartPtr)
{
    this->window      = window;
    this->gamePartPtr = gamePartPtr;

    startButton       = new Button(sf::Vector2f(380, 400), Resources::getTexture("res/playNormal.png"), Resources::getTexture("res/playPressed.png"));
    leaderboardButton = new Button(sf::Vector2f(380, 500), Resources::getTexture("res/leadersNormal.png"), Resources::getTexture("res/leadersPressed.png"));
    exitButton        = new Button(sf::Vector2f(380, 600), Resources::getTexture("res/exitNormal.png"), Resources::getTexture("res/exitPressed.png"));
}

void Menu::run()
{
    sf::Sprite background;
    sf::Texture backgroundTexture = Resources::getTexture("res/menuBackground.png");
    background.setTexture(backgroundTexture);

    while (window->isOpen()) 
    {
        if (*gamePartPtr != MENU)
            break;

        sf::Event event;

        while (window->pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
                window->close();
        }

        // позиция мыши
        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

        if (startButton->updateButton(mousePos) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            GameSound::play(1);
            *gamePartPtr = GAME;
        }

        if (leaderboardButton->updateButton(mousePos) || sf::Keyboard::isKeyPressed(sf::Keyboard::L))
        {
            GameSound::play(1);
            *gamePartPtr = LEADERBOARD;
        }

        if (exitButton->updateButton(mousePos))
        {
            GameSound::play(1);
            *gamePartPtr = EXIT;
        }

        window->clear();
        window->draw(background);

        window->draw(*startButton);
        window->draw(*leaderboardButton);
        window->draw(*exitButton);

        window->display();
    }
}

Menu::~Menu()
{
    delete this->startButton;
    delete this->leaderboardButton;
    delete this->exitButton;
}
