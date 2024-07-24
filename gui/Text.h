#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Text {
public:
    Text(string content, sf::Font& font, int characterSize, sf::Vector2f position, sf::Color color,
         sf::Uint32 style = sf::Text::Regular);

    sf::Text text;

    void draw(sf::RenderWindow& window);
};
