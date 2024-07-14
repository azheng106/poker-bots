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
    bool hasChecked;
    int currentBet;
    vector<Card> hand;

    Player(int index, int stash, string name);

    void bet(int betAmount);
    void raise(int *currentMinBet);
    void check();
    void call(int amount);
    void fold();
    void win(int potAmount);

    bool operator==(Player& other) const {
        return this->name == other.name && this->index == other.index;
    }
};