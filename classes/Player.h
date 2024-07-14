#pragma once

#include <iostream>
#include <vector>

#include "Card.h"

using namespace std;

class Player {
public:
    string name;
    int money = 0;
    bool isIn;
    bool hasChecked;
    int currentBet;
    vector<Card> hand;

    Player();

    void bet(int betAmount);
    void win(int potAmount);
    void call(int amount);
    void check();
    void fold();
};