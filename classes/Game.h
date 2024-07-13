#pragma once

#include "Player.h"

class Game {
public:
    int round;
    int minimumBet;
    int initialDealerIndex;
    vector<Player> players;

    void setupPlayers();
};
