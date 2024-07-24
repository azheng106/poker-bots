#pragma once

#include <SFML/Graphics.hpp>

#include "Text.h"

using namespace std;

class Button {
public:
    Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, Text text);

    sf::RectangleShape button;
    sf::Text buttonText;

    static sf::Color adjustColorBrightness(const sf::Color& color, int delta);
    static bool isMouseOverButton(sf::RectangleShape& button, sf::RenderWindow& window);
    static bool buttonClicked(sf::RectangleShape& button, sf::RenderWindow& window, sf::Event& event);
    void draw(sf::RenderWindow& window);
};
