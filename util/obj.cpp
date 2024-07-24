#include "SFML/Graphics.hpp"

using namespace std;

/**
 * Creates a rectanglar button, wow!
 * @param size sf::Vector2f
 * @param position sf::Vector2f
 * @param color sf::Color
 */
sf::RectangleShape createRectangularButton(sf::Vector2f size, sf::Vector2f position, sf::Color fillColor,
                                           sf::Color outlineColor = sf::Color::Transparent, float borderThickness = 0.0f) {
    sf::RectangleShape button(size);
    button.setPosition(position);
    button.setFillColor(fillColor);

    if (outlineColor != sf::Color::Transparent || borderThickness != 0.0f) {
        button.setOutlineColor(outlineColor);
        button.setOutlineThickness(borderThickness);
    }

    return button;
}

/**
 * Creates text, wow!
 * @param content the actual text
 * @param font font file location to use
 * @param characterSize int
 * @param position position on window
 * @param color text color
 * @param style bold, italic, etc
 */
sf::Text createText(string content, sf::Font& font, int characterSize, sf::Vector2f position, sf::Color color,
                    sf::Uint32 style = sf::Text::Regular) {
    sf::Text text;
    text.setString(content);
    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setPosition(position);
    text.setFillColor(color);
    text.setStyle(style);
    return text;
}

sf::Color adjustColorBrightness(const sf::Color& color, int delta) {
    int red = max(0, color.r + delta);
    int green = max(0, color.g + delta);
    int blue = max(0, color.b + delta);

    return sf::Color(red, green, blue);
}