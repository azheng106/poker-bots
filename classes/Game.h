#pragma once

#include <random>

#include "Player.h"

class Game {
public:
    int round;
    int minimumBet;
    int initialDealerIndex;
    vector<Player> players;

    void setupPlayers();
    static int randomInt(int a, int b);
};
