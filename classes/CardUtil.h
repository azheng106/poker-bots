#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#include "Card.h"

class CardUtil {
public:
    static vector<int> scoreHighCard(vector<Card> cards);
    static vector<int> scoreOnePair(vector<Card> cards);
    static vector<int> scoreTwoPairs(vector<Card> cards);
    static vector<int> scoreThreeOfAKind(vector<Card> cards);
    static vector<int> scoreStraight(vector<Card> cards);
    static vector<int> scoreFlush(vector<Card> cards);
    static vector<int> scoreFullHouse(vector<Card> cards);
    static vector<int> scoreFourOfAKind(vector<Card> cards);
    static vector<int> scoreStraightFlush(vector<Card> cards);
    static vector<int> scoreHand(vector<Card> cards);
    static vector<int> findBestScore(vector<Card> communityCards, vector<Card> holeCards);
    static vector<Card> findBestHand(vector<Card> communityCards, vector<Card> holeCards);
    static string deduceHandType(vector<int> score);
};
