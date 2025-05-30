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
    // �����������
    LeaderBoard(sf::RenderWindow* window, std::string filename, int* gamePartPtr, int* scorePtr);
    // ����������
    ~LeaderBoard();
    // ���������� ���������
    void sortScores();
    // �������� ���� ������� �������
    void run();
};