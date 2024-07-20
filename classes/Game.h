#pragma once

#include <random>
#include <algorithm>

#include "Player.h"
#include "CardUtil.h"

class Game {
public:
    Game();

    int round;
    int turn;
    int pot;
    bool hasOpened;
    int bigBlindBet;
    int currentMinBet;
    int initialDealerIndex;
    bool skipToEnd;
    int playersFolded;
    int playersBetting;
    bool isFinished;
    bool isHeadsUp;

    Player* dealer;
    Player* smallBlind;
    Player* bigBlind;
    vector<Player> players;

    vector<Card> deck;
    vector<Card> communityCards;

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
    void reset();
};
