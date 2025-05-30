#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio/Sound.hpp>
#include "Button.h"
#include <iostream>
#include <fstream>
#include "Enums.h"
#include "GameSound.h"

class GameOver 
{
private:
    sf::RenderWindow* window;
    sf::Font textFont;
    sf::Text nickText;
    sf::Text scoreText;
    sf::Text linesText;

    Button* menuButton;
    Button* playButton;
    Button* leaderboardButton;

    int* gamePartPtr;
    int* scorePtr;
    int* linesPtr;

    std::string filename;
    std::string nick;

public:
    // ����������
    GameOver(sf::RenderWindow* window, std::string filename, int* gameStatePtr, int* scorePtr, int* linesPtr);

    // ����������
    ~GameOver();

    // ������� ���� ����� ���� (���� ��������, ����� ��������� �������)
    void run();

    // ���������� ������ �������� � ����
    void addScore();
};