#pragma once

#include <random>
#include <algorithm>

#include "Player.h"
#include "CardUtil.h"

class Game {
public:
    int round;
    int turn;
    int pot;
    bool hasOpened;
    int bigBlindBet;
    int currentMinBet;
    int initialDealerIndex;
    vector<Player> players;

    // Used to skip to the end if all but one player folds, or if all but one player is all in and minimum bet is met
    bool skipToEnd;
    int playersFolded;
    // Players in the game but not all in, used for checkedAround rounds
    int playersBetting;

    // Evaluates to true when one player remains (rest have $0)
    bool isFinished;

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
    void reset();

    Game();
};
