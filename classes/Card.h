#pragma once

#include <ostream>
#include <locale>

using namespace std;

class Card {
public:
    int value;
    char suit;

    Card(int value, char suit);

    friend ostream& operator<<(ostream& os, Card& card);
};