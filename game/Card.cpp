#include "Card.h"

Card::Card(int value, char suit){
    this->value = value;
    this->suit = suit;
}

void Card::generateSprite(sf::Font& font, sf::Vector2f position, sf::Vector2f size) {
    sprite = new CardSprite(value, suit, font, position, size);
}

ostream& operator<<(ostream& os, Card& card) {
    switch (card.value) {
        case 11:
            os << "Jack";
            break;
        case 12:
            os << "Queen";
            break;
        case 13:
            os << "King";
            break;
        case 14:
            os << "Ace";
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