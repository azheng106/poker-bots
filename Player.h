#ifndef PLAYER_H
#define PLAYER_H

#include <string>
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

    void bet(int betAmount);
    void win(int potAmount);
    void call(int amount);
    void check();
    void fold();
};

#endif