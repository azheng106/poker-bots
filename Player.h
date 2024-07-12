#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>

#include "Card.h"

using namespace std;

class Player {
public:
    string name;
    int money;
    int index;
    bool isIn;
    bool hasChecked;
    int currentBet;
    vector<Card> hand;

    Player (int index);
    void bet(int amount);
    void winPot(int amount);
    void fold();
    void check();
    void call(int amount);
};

#endif