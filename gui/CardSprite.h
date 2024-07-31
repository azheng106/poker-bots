#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class CardSprite {
public:
    CardSprite(int value, char suit, sf::Font& textFont, sf::Vector2f position, sf::Vector2f size);
    void setPosition(sf::Vector2f position);
    void setSize(sf::Vector2f size);
    void draw(sf::RenderWindow& window);
    void updateCard();

    sf::Vector2f size;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font fancyFont;
    sf::Text cardText;
    string cardValue;
    char cardSuit;

    // File Paths
    static constexpr const char* BASE_PATH = "../../../";
};
