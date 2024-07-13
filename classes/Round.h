#pragma once

#include "Game.h"

class Round : public Game {
public:
    int pot;
    vector<Card> deck;
    vector<Card> communityCards;

    void shuffleDeck();
    void setupBlinds();
    void distributeHoleCards();
    void distributeCommunityCards();

    Round();
};
