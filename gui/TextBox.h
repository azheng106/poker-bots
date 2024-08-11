#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

using namespace std;

class TextBox {
public:
    TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font, int characterSize, sf::Color color, sf::Color textColor, bool useNumbers = false);

    void handleEvent(sf::RenderWindow& window, sf::Event& event);
    void setOutlineColor(sf::Color color);
    void draw(sf::RenderWindow& window);
    void setString(string text);
    string getString();
    void setPosition(sf::Vector2f position);
    bool isMouseOver(sf::RenderWindow& window);
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
    bool numbersOnly;
};