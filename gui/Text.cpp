#include "Text.h"

/**
 * Constructor
 * @param text
 * @param font
 * @param characterSize
 * @param position
 * @param color
 * @param style
 */
Text::Text(string text, sf::Font &font, int characterSize, sf::Vector2f position, sf::Color color) {
    content.setString(text);
    content.setFont(font);
    content.setCharacterSize(characterSize);
    content.setPosition(position);
    content.setFillColor(color);
}

/**
 * Draw the text to the window
 * @param window
 */
void Text::draw(sf::RenderWindow& window) {
    window.draw(content);
}