#pragma once

#include <ostream>
#include <locale>

using namespace std;

class Card {
public:
    int value;
    char suit;

    Card(int value, char suit);

    friend ostream& operator<<(ostream& os, Card& card) {
        switch (card.value) {
            case 11:
                os << "J";
                break;
            case 12:
                os << "Q";
                break;
            case 13:
                os << "K";
                break;
            case 14:
                os << "A";
                break;
            default:
                os << card.value;
                break;
        }
        switch (card.suit) {
            case 'c':
                os << " of Clubs";
                break;
            case 'd':
                os << " of Diamonds";
                break;
            case 'h':
                os << " of Hearts";
                break;
            case 's':
                os << " of Spades";
                break;
        }
        return os;
    }
};