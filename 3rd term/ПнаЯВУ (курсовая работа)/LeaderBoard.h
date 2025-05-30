#include <SFML/Graphics.hpp>
#include <vector>
#include "SingleScore.h"
#include "Enums.h"
#include "Button.h"
#include "GameSound.h"

class LeaderBoard 
{
private:
    sf::RenderWindow* window;

    Button* menuButton;

    std::vector<SingleScore*> scores;
    std::string filename;

    int* gamePartPtr;
    int* scorePtr;
public:
    // конструктор
    LeaderBoard(sf::RenderWindow* window, std::string filename, int* gamePartPtr, int* scorePtr);
    // деструктор
    ~LeaderBoard();
    // сортировка рейтингов
    void sortScores();
    // основной цикл таблицы лидеров
    void run();
};