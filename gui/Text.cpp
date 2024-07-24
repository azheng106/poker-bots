#include "Text.h"

Text::Text(string content, sf::Font& font, int characterSize, sf::Vector2f position, sf::Color color,
        sf::Uint32 style) {
    text.setString(content);
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setPosition(position);
    text.setFillColor(color);
    text.setStyle(style);
}

// Draw the text
void Text::draw(sf::RenderWindow& window) {
    window.draw(text);
}