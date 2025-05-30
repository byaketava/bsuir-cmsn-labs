#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"

class Button : public sf::Drawable
{
private:
    sf::Sprite normal;                  // объект нормальной кнопки
    sf::Sprite pressed;                 // объект нажатой кнопки
    sf::Sprite* currentState;           // указатель на текущий вид кнопки
    bool isPressed = false;
    bool isNormal = true;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    Button(sf::Vector2f position, const sf::Texture& normal, const sf::Texture& pressed);
    bool updateButton(sf::Vector2f mousePos);
    bool mouseOnButton(sf::Vector2f mousePos);
};