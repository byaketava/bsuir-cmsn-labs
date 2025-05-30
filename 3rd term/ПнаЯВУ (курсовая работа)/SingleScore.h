#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include <string>

class SingleScore : public sf::Drawable
{
private:
    sf::Font font;
    sf::Text nickText;
    sf::Text scoreText;

    std::string nick;
    int score = 0;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
    // конструктор
    SingleScore(const std::string& nick, int score);

    // возвращает значение рейтинга
    long getScore() const;

    // устанавливает позицию рейтинга на экране
    void update(int x, int y);
};