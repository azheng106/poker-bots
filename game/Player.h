#pragma once

#include <iostream>
#include <vector>

#include "../gui/Text.h"
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
    vector< Card> holeCards;
    vector<int> bestScore;
    vector<Card> bestHand;

    bool bet(int* currentMinBet, int betAmount, Text& report);
    bool check(Text& report);
    bool raise(int* currentMinBet, int desiredBet, Text& report);
    bool call(int* currentMinBet, Text& report);
    bool fold(Text& report);
    void win(int potAmount, Text& report);

    bool operator==(Player& other) const;

};