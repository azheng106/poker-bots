#pragma once

#include "Game.h"

class Round : public Game {
public:
    // Inherited from class Game
    int round;
    int minimumBet;
    int initialDealerIndex;
    vector<Player> players;

    // Round only
    int pot;
    vector<Card> deck;
    vector<Card> communityCards;
    Player dealer;
    Player smallBlind;
    Player bigBlind;

    void shuffleDeck();
};
