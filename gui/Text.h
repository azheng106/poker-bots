#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Text {
public:
    Text(string text, int characterSize, sf::Vector2f position, sf::Color color,
         sf::Uint32 style = sf::Text::Regular);

    sf::Text content;

    void draw(sf::RenderWindow& window);
};
