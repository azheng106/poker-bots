#include "Text.h"

/**
 * Constructor
 * @param string
 * @param font
 * @param characterSize
 * @param position
 * @param color
 */
Text::Text(string string, sf::Font& font, int characterSize, sf::Vector2f position, sf::Color color) {
    text.setFont(font);
    text.setString(string);
    text.setCharacterSize(characterSize);
    text.setFillColor(color);

    // Set origin to the center of the text
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);

    // Set position
    text.setPosition(position);
}


void Text::updateOrigin() {
    // Center the origin of the text
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
}

void Text::draw(sf::RenderWindow& window) {
    window.draw(text);
}