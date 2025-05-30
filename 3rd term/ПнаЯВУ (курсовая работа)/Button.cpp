#include "Button.h"

// конструктор кнопки
Button::Button(sf::Vector2f position, const sf::Texture& normal, const sf::Texture& pressed)
{
    this->normal.setTexture(normal);                        // нормальная кнопка
    this->pressed.setTexture(pressed);                      // нажатая кнопка

    this->normal.setPosition(position);                     // где будет кнопка на экране
    this->pressed.setPosition(position);                    // (для двух состояний)

    currentState = &this->normal;                           // изначально кнопка в нормальном состоянии, поэтому передача указателя на него
}

// отрисовка кнопки
void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
    target.draw(*currentState);
}

// проверка наведения
// истинно, если мышь наведена на кнопку
bool Button::mouseOnButton(sf::Vector2f mousePos)
{
    return currentState->getGlobalBounds().contains(mousePos); 
}

// изменение состояния кнопки в зависимости от событий мыши и позиции указателя
// истинно, если кнопка нажата и мышь на кнопке
bool Button::updateButton(sf::Vector2f mousePos) 
{
    if (mouseOnButton(mousePos))                                    // если курсор в пределах кнопки
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))    // если нажата левая кнпока
        {
            isPressed = true;                                       // флаг нажатой кнопки истинный
            isNormal = false;                                       // флаг нормальной кнопки ложный
            currentState = &this->pressed;                          // изменение текущего состояния на нажатое
        }
        else if (isPressed)                                         // если кнопка была нажата
        {
            isPressed = false;                                      // изменение состояний флагов и кнопки обратно на нормальное
            isNormal = true;
            currentState = &this->normal;
            return true;
        }
    }
    else if (isPressed)                                             // если кнопка была в нажатом состоянии
    {
        isPressed = false;
        isNormal = true;
        currentState = &this->normal;                               // изменение состояния на нормальное
    }
    return false;                                                   // кнопка не была нажата
}