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

    Player *dealer;
    Player *smallBlind;
    Player *bigBlind;

    static int randomInt(int a, int b);
    void setupPlayers();
    void shuffleDeck();
    void setupBlinds();
    void distributeHoleCards();
    void distributeCommunityCards();
    void calculatePot();
    void getAction(Player& player);
    void playHand();
    void showdown();

    Game();
};
