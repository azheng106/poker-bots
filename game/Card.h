#pragma once

#include <SFML/Graphics.hpp>
#include <ostream>

#include "../gui/CardSprite.h"
#include "../gui/Misc.h"

using namespace std;

class Card {
public:
    Card(int value, char suit);

    int value;
    char suit;
    CardSprite* sprite;

    void generateSprite(sf::Vector2f position, sf::Vector2f size);

    friend ostream& operator<<(ostream& os, Card& card);
};