#pragma once

#include <ostream>

using namespace std;

class Card {
public:
    Card(int value, char suit);

    int value;
    char suit;

    friend ostream& operator<<(ostream& os, Card& card);
};