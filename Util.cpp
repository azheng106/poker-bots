#include <iostream>
#include <algorithm>
#include <map>

#include "Util.h"

using namespace std;

vector<int> Util::isStraightFlush(vector<Card> cards) {
    vector<char> suits;
    vector<int> values;
    for (auto card : cards) {
        suits.push_back(card.suit);
        values.push_back(card.value);
    }
    if (!equal(suits.begin() + 1, suits.end(), suits.begin())) return {};
    sort(values.begin(), values.end());
    for (int i = 1; i < values.size(); i++) {
        if (values[i] != values[i-1] + 1) return {};
    }
    return {9, values[4]};
}

vector<int> Util::isFourOfaKind(vector<Card> cards) {
    map<int, int> valueCount;
    for (auto card : cards) {
        valueCount[card.value]++;
    }
    for (auto [value, count] : valueCount) {
        if (count == 4) {
            return {8, value};
        }
    }
    return {};
}

vector<int> Util::isFullHouse(vector<Card> cards) {
    map<int, int> valueCount;
    for (auto card : cards) {
        valueCount[card.value]++;
    }
    int triple = -1, pair = -1;
    for (auto [value, count] : valueCount) {
        if (count == 3) triple = value;
        if (count == 2) pair = value;
    }
    if (triple != -1 && pair != -1) {
        return {7, triple, pair};
    }
    return {};
}

vector<int> Util::isFlush(vector<Card> cards) {
    vector<char> suits;
    vector<int> values;
    for (auto card : cards) {
        suits.push_back(card.suit);
        values.push_back(card.value);
    }
    if (!equal(suits.begin() + 1, suits.end(), suits.begin())) return {};
    sort(values.begin(), values.end());
    return {6, values[4]};
}

vector<int> Util::isStraight(vector<Card> cards) {
    vector<int> values;
    for (auto card : cards) {
        values.push_back(card.value);
    }
    sort(values.begin(), values.end());
    for (int i = 1; i < values.size(); i++) {
        if (values[i] != values[i-1] + 1) return {};
    }
    return {5, values[4]};
}

vector<int> Util::isThreeOfAKind(vector<Card> cards) {
    map<int, int> valueCount;
    for (auto card : cards) {
        valueCount[card.value]++;
    }
    int triple = -1;
    for (auto [value, count] : valueCount) {
        if (count == 3) triple = value;
    }
    if (triple != -1) {
        return {4, triple};
    }
    return {};
}

vector<int> Util::isTwoPairs(vector<Card> cards) {
    map<int, int> valueCount;
    for (auto card : cards) {
        valueCount[card.value]++;
    }
    int pairCounter = 0;
    vector<int> pairValues;
    for (auto [value, count] : valueCount) {
        if (count == 2) {
            pairCounter += 1;
            pairValues.push_back(value);
        }
    }
    sort(pairValues.begin(), pairValues.end());
    if (pairCounter == 2) {
        return {3, pairValues[0], pairValues[1]};
    }
    return {};
}

vector<int> Util::isOnePair(vector<Card> cards) {};

vector<int> Util::isHighCard(vector<Card> cards) {};
