#pragma once

#include <random>
#include <algorithm>

#include "Player.h"
#include "CardUtil.h"

class Game {
public:
    int round;
    int turn;
    int pot = 0;
    bool hasOpened;
    int bigBlindBet;
    int currentMinBet;
    int initialDealerIndex;
    vector<Player> players;

    vector<Card> deck;
    vector<Card> communityCards;

    bool isHeadsUp;

    Player *dealer;
    Player *smallBlind;
    Player *bigBlind;

    static int randomInt(int a, int b);
    void setupPlayers();
    void shuffleDeck();
    void setupBlinds();
    void distributeHoleCards();
    void distributeCommunityCards();
    void displayPot();
    void calculatePot();
    void doBlindBets();
    void getAction(Player& player);
    bool isTurnOver();
    void playHand();
    void showdown();

    Game();
};
