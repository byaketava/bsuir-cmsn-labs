#include "SingleScore.h"

SingleScore::SingleScore(const std::string& nick, int score) 
{
    this->nick = nick;
    this->score = score;
    font = Resources::getFont("res/Exo-ExtraBold.ttf");

    nickText.setFont(font);
    nickText.setCharacterSize(26);
    nickText.setFillColor(sf::Color(252, 242, 231, 255));

    scoreText.setFont(font);
    scoreText.setCharacterSize(26);
    scoreText.setFillColor(sf::Color(252, 242, 231, 255));
}

long SingleScore::getScore() const 
{
    return score;
}

void SingleScore::update(int x, int y) 
{
    nickText.setString(nick);
    nickText.setPosition(x, y);
    
    scoreText.setString(std::to_string(score));
    sf::FloatRect rectangle(555, 0, 140, 0);
    sf::FloatRect textBounds = scoreText.getGlobalBounds();
    float X = rectangle.left + (rectangle.width - textBounds.width) / 2.f;
    scoreText.setPosition(X , y);
}

void SingleScore::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(nickText);
    target.draw(scoreText);
} 