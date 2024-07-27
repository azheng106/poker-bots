#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Text {
public:
    // Constructor to initialize the text object
    Text(string string, sf::Font& font, int characterSize, sf::Vector2f position, sf::Color color = sf::Color::White);

    // Used to recenter after text is changed
    void updateOrigin();

    // Draws the text to the window
    void draw(sf::RenderWindow& window);

    sf::Text text;
};
