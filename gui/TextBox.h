#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class TextBox {
public:
    TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font, int characterSize, sf::Color color, sf::Color textColor);

    void handleEvent(sf::Event& event);
    void draw(sf::RenderWindow& window);
    void setString(string text);
    string getString();
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void updateTextPosition();

    int retrieveTextAsInt();

    sf::RectangleShape box;
    sf::Color outlineColor;
    sf::Color originalOutlineColor;
    sf::Color highlightColor;
    sf::Color originalHighlightColor;
    sf::Text text;
    bool isActive;
    bool textIsValid;
};