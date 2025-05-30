#include <fstream>
#include <sstream>
#include "LeaderBoard.h"

using namespace std;

LeaderBoard::LeaderBoard(sf::RenderWindow* window, string filename, int* gamePartPtr, int* scorePtr)
{
    this->window = window;
    this->gamePartPtr = gamePartPtr;
    this->scorePtr = scorePtr;
    this->filename = filename;

    menuButton = new Button(sf::Vector2f(380, 744), Resources::getTexture("res/menuNormal.png"), Resources::getTexture("res/menuPressed.png"));

    // открытие файла с рейтингами
    ifstream inputStream;
    inputStream.open(filename, ios::in);

    // добавление рейтингов в вектор
    string line;
    if (inputStream.is_open())
    {
        while (getline(inputStream, line))
        {
            stringstream ss(line);
            string nick;
            int score;
            ss >> nick >> score;
            scores.push_back(new SingleScore(nick, score));
        }
    }
    else
    {
        // если невозможно открыть файл, то создать его
        ofstream outputStream;
        outputStream.open(filename, ios::out);
        outputStream.close();
    }
    inputStream.close();

    // сортировка вектора
    sortScores();

    // оставить только первые 10 рейтингов в векторе, остальные удалить
    while (scores.size() > 10)
    {
        scores.pop_back();
    }

    // позиция в окне
    for (int i = 0; i < scores.size(); i++)
    {
        scores[i]->update(245, 202 + i * 50);
    }
}

LeaderBoard::~LeaderBoard() 
{
    for (SingleScore* single : scores)
        delete single;

    delete menuButton;
}

void LeaderBoard::sortScores() 
{
    sort(scores.begin(), scores.end(), [](SingleScore* first, SingleScore* second) {return first->getScore() > second->getScore();});
}

void LeaderBoard::run()
{
    sf::Sprite background;
    sf::Texture backgroundTexture = Resources::getTexture("res/LeaderboardBackground.png");
    background.setTexture(backgroundTexture);

    while (window->isOpen()) 
    {
        if (*gamePartPtr != LEADERBOARD)
            break;

        sf::Event event;
        while (window->pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window->close();
            else if (event.key.code == sf::Keyboard::Escape)
                *gamePartPtr = MENU;
        }

        sf::Vector2f mousePos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

        if (menuButton->updateButton(mousePos))
        {
            GameSound::play(1);
            *gamePartPtr = MENU;
        }

        window->clear();
        window->draw(background);
        window->draw(*menuButton);
        for (SingleScore* single : scores)
            window->draw(*single);
        window->display();
    }
}