#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"

class Button : public sf::Drawable
{
private:
    sf::Sprite normal;                  // ������ ���������� ������
    sf::Sprite pressed;                 // ������ ������� ������
    sf::Sprite* currentState;           // ��������� �� ������� ��� ������
    bool isPressed = false;
    bool isNormal = true;
protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
public:
    Button(sf::Vector2f position, const sf::Texture& normal, const sf::Texture& pressed);
    bool updateButton(sf::Vector2f mousePos);
    bool mouseOnButton(sf::Vector2f mousePos);
};