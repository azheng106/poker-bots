#pragma once

#include <ostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Card {
public:
    Card(int value, char suit, sf::Texture& texture);
    void draw(sf::RenderWindow& window, sf::Vector2f position);

    int value;
    char suit;
    sf::Sprite sprite;

    friend ostream& operator<<(ostream& os, Card& card);
};