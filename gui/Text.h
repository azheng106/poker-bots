#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

using namespace std;

class Text {
public:
    Text(string text, sf::Font &font, int characterSize, sf::Vector2f position, sf::Color color);

    sf::Text content;

    void draw(sf::RenderWindow& window);
};
