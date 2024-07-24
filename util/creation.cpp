#include "SFML/Graphics.hpp"

using namespace std;

/**
 * Creates a rectanglar button, wow!
 * @param size sf::Vector2f
 * @param position sf::Vector2f
 * @param color sf::Color
 */
sf::RectangleShape createButton(sf::Vector2f size, sf::Vector2f position, sf::Color fillColor,
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
 * @param outlineColor sf::Color
 * @param letterSpacing
 * @param lineSpacing
 */
sf::Text createText(
        const std::string& content,
        sf::Font& font,
        int characterSize,
        sf::Vector2f position,
        sf::Color color,
        sf::Uint32 style = sf::Text::Regular,
        sf::Color outlineColor = sf::Color::Transparent,
        float outlineThickness = 0.0f,
        float letterSpacing = 1.0f,
        float lineSpacing = 1.0f
) {
    sf::Text text;
    text.setFont(font);
    text.setString(content);
    text.setCharacterSize(characterSize);
    text.setFillColor(color);
    text.setPosition(position);
    text.setStyle(style);
    text.setOutlineColor(outlineColor);
    text.setOutlineThickness(outlineThickness);
    text.setLetterSpacing(letterSpacing);
    text.setLineSpacing(lineSpacing);
    return text;
}