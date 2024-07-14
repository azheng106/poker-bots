#pragma once

#include <random>

#include "Player.h"

class Game {
public:
    int round;
    int pot = 0;
    int minimumBet;
    int initialDealerIndex;
    vector<Player> players;

    vector<Card> deck;
    vector<Card> communityCards;

    Player dealer{-1, -1, "a"};
    Player smallBlind{-1, -1, "a"};
    Player bigBlind{-1, -1, "a"};

    static int randomInt(int a, int b);
    void setupPlayers();
    void shuffleDeck();
    void setupBlinds();
    void distributeHoleCards();
    void distributeCommunityCards();
    void playHand();
    void showdown();

    Game();
};
