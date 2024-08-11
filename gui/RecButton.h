#pragma once

#include <SFML/Graphics.hpp>

#include "Misc.h"

using namespace std;

class RecButton {
    // Rectangular button
public:
    RecButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Color outlineColor, sf::Text text);

    bool isButtonPressed;
    sf::Color originalOutlineColor;

    sf::RectangleShape button;
    sf::Text buttonText;

    void updateTextPosition();
    bool isMouseOver(sf::RenderWindow& window);
    bool isClicked(sf::RenderWindow& window, sf::Event& event);
    void draw(sf::RenderWindow& window);
};
