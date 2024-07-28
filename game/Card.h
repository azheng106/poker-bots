#pragma once

#include <ostream>
#include <SFML/Graphics.hpp>
using namespace std;

class Card {
public:
    Card(int value, char suit);

    int value;
    char suit;

    friend ostream& operator<<(ostream& os, Card& card);
};