#pragma once

#include <SFML/Graphics.hpp>

#include "Misc.h"

class TriButton {
    // Triangular button
public:
    TriButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, float angle);

    bool isMouseOver(sf::RenderWindow& window);
    bool isClicked(sf::RenderWindow& window, sf::Event& event);
    void draw(sf::RenderWindow& window);

private:
    sf::ConvexShape triangle;
    sf::Color originalButtonColor;
    bool isButtonPressed = false;
};
