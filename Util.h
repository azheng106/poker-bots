#ifndef POKERBOTS_UTIL_H
#define POKERBOTS_UTIL_H

#include <iostream>
#include <vector>

#include "Card.h"

using namespace std;

class Util {
public:
    vector<int> isStraightFlush(vector<Card> cards);
    vector<int> isFourOfaKind(vector<Card> cards);
    vector<int> isFullHouse(vector<Card> cards);
    vector<int> isFlush(vector<Card> cards);
    vector<int> isStraight(vector<Card> cards);
    vector<int> isThreeOfAKind(vector<Card> cards);
    vector<int> isTwoPairs(vector<Card> cards);
    vector<int> isOnePair(vector<Card> cards);
    vector<int> isHighCard(vector<Card> cards);
};

#endif
