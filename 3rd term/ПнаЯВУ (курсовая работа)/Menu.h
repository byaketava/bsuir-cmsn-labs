#pragma once
#include "Button.h"
#include "Enums.h"
#include "GameSound.h"

class Menu 
{
private:
    sf::RenderWindow* window;

    Button* startButton;
    Button* exitButton;
    Button* leaderboardButton;

    int* gamePartPtr;
public:
    Menu(sf::RenderWindow* window, int* gamePartPtr);
    ~Menu();
    void run();
};