#pragma once

#include <iostream>
#include <vector>

#include "Card.h"

using namespace std;

class Player {
public:
    Player(int index, int stash, string name);

    int index;
    string name;
    int money;
    bool isIn;
    bool isAllIn;
    bool hasMadeAction;
    bool hasRaised;
    bool hasChecked;
    int currentBet;
    int totalBet;
    std::vector<Card> holeCards;
    std::vector<int> bestScore;
    std::vector<Card> bestHand;

    bool bet(int* currentMinBet);
    bool check();
    bool raise(int* currentMinBet);
    bool call(int* currentMinBet);
    bool fold();
    void win(int potAmount);

    bool operator==(Player& other) const;
};