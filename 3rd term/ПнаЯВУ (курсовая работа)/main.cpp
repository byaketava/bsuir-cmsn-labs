#include "Game.h"
#include "Button.h"
#include "Menu.h"
#include "GameOver.h"
#include "LeaderBoard.h"
#include "GameSound.h"

int main() 
{
    bool volume = true;
    int score = 0;
    int level = 1;
    int lines = 0;
    int boardWidth = 10;
    int boardHeight = 20;
    int gamePart = MENU;
    bool shadowFlag = true;

    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();						                
    // разрешение экрана
    sf::RenderWindow window(sf::VideoMode(900, 900), L"TETRA PEACE", sf::Style::Close);
    window.setPosition(sf::Vector2i((desktop.width - 900) / 2, (desktop.height - 900) / 2 - 40));	
    // позиция окна относительно экрана
    window.setVerticalSyncEnabled(true);

    // загрузка иконки
    sf::Image icon;
    icon.loadFromFile("res/icon.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // менеджер ресурсов
    Resources resourceManager;

    // музыка
    GameSound music;

    while (window.isOpen()) 
    {
        if (gamePart == EXIT)
            break;
        switch (gamePart) 
        {
        case MENU: 
        {
            Menu menu(&window, &gamePart);
            menu.run();
            break;
        }
        case GAME: 
        {
            Game game(&window, boardWidth, boardHeight, volume, &gamePart, &score, &level, &lines, shadowFlag);
            game.run();
            break;
        }
        case GAMEOVER: 
        {
            GameOver gameOver(&window, "scores.txt", &gamePart, &score, &lines);
            gameOver.run();
            break;
        }
        case LEADERBOARD: 
        {
            LeaderBoard leaderboard(&window, "scores.txt", &gamePart, &score);
            leaderboard.run();
            break;
        }
        default:
            gamePart = EXIT;
            break;
        }
    }
    return 0;
}