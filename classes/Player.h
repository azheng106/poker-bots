#pragma once

#include <iostream>
#include <vector>

#include "Card.h"

using namespace std;

class Player {
public:
    int index;
    string name;
    int money{};
    bool isIn;
    bool isAllIn;
    bool hasRaised;
    bool hasChecked;

    // Total amount of money the player has bet this betting round
    int currentBet;

    // Total amount of money the player has bet this holeCards
    int totalBet;

    vector<Card> holeCards;

    vector<int> bestScore;
    vector<Card> bestHand;

    Player(int index, int stash, string name);

    bool bet(int *currentMinBet);
    bool check();
    bool raise(int *currentMinBet);
    bool call(int *currentMinBet);
    bool fold();
    void win(int potAmount);

    bool operator==(Player& other) const;
};