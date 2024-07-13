#pragma once

#include "Game.h"

class Round : public Game {
public:
    int pot;
    vector<Card> deck;
    vector<Card> communityCards;
    Player dealer;
    Player smallBlind;
    Player bigBlind;

    void shuffleDeck();
    void setupBlinds();
    void distributeHoleCards();
    void distributeCommunityCards();
};
