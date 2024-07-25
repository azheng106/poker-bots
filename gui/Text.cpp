#include "Text.h"

const string BASE_PATH = "../../../";

/**
 * Constructor
 * @param text
 * @param font
 * @param characterSize
 * @param position
 * @param color
 * @param style
 */
Text::Text(string text, int characterSize, sf::Vector2f position, sf::Color color,
           sf::Uint32 style) {
    sf::Font robotoMono;
    robotoMono.loadFromFile(BASE_PATH+"fonts/RobotoMono-Regular.ttf");

    content.setString(text);
    content.setFont(robotoMono);
    content.setCharacterSize(characterSize);
    content.setPosition(position);
    content.setFillColor(color);
    content.setStyle(style);
}

/**
 * Draw the text to the window
 * @param window
 */
void Text::draw(sf::RenderWindow& window) {
    window.draw(content);
}