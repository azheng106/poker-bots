#include "SFML/Graphics.hpp"

using namespace std;

/**
 * Creates a rectanglar button, wow!
 * @param size sf::Vector2f
 * @param position sf::Vector2f
 * @param color sf::Color
 */
sf::RectangleShape createButton(sf::Vector2f size, sf::Vector2f position, sf::Color color) {
    sf::RectangleShape button(size);
    button.setPosition(position);
    button.setFillColor(color);
    return button;
}

/**
 * Creates text, wow!
 * @param content
 * @param font
 * @param characterSize
 * @param position
 * @param color
 */
sf::Text createText(string content, sf::Font& font, int characterSize, sf::Vector2f position, sf::Color color) {
    sf::Text text;
    text.setFont(font);
    text.setString(content);
    text.setCharacterSize(characterSize);
    text.setFillColor(color);
    text.setPosition(position);
    return text;
}