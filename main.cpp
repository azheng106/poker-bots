#include <iostream>
#include <random>
#include <vector>

#include "classes/Card.h"
#include "classes/Player.h"
#include "classes/Round.h"
#include "classes/Game.h"

using namespace std;

void playHand(int *dealerIndex, int *smallBlind, int *bigBlind, int *pot,
              vector<Player> *players, vector<Card> *communityCards, vector<Card> *deck);

int main() {
//    int pot = 0;
//    int turn = 1;
//    vector<Player> players = setupPlayers(100);
//    int initialDealerIndex = Game::randomInt(0, players.size() - 1);
//
//    vector<int> blinds = setupBlinds(players, initialDealerIndex, 1);
//    int dealer = blinds[0];
//    int smallBlind = blinds[1];
//    int bigBlind = blinds[2];
//
//    Game game(players);
//
//    vector<Card> communityCards;
//    vector<Card> deck = game.createDeck();
//    distributeHoleCards(&deck, &players);
//    // Print out everyone's cards
//    for (Player player : players) {
//        Card first = player.hand[0];
//        Card second = player.hand[1];
//
//        cout << "[DEBUG] Player " << player.name << " has " << first.value << first.suit << " and " << second.value << second.suit << endl;
//    }
//    playHand(&dealer, &smallBlind, &bigBlind, &pot, &players, &communityCards, &deck);
//    return 0;
}

void playHand(int *dealerIndex, int *smallBlind, int *bigBlind, int *pot,
              vector<Player> *players, vector<Card> *communityCards, vector<Card> *deck) {
    int currentMinBet = 0;
    int MIN_BET = 2; // Big blind bet
    for (auto& player: *players) { // Reset players
        player.isIn = true;
        player.currentBet = 0;
    }
    /*
      If first turn, force small blind and big blind to post bets
      Ask each player to fold, call, or raise
      If no one has bet players can also check or bet
      Show community cards after everyone has placed an equal bet
     */
    if (communityCards->empty()) {
        (*players)[*smallBlind].bet(MIN_BET / 2);
        *pot+=MIN_BET / 2;
        (*players)[*bigBlind].bet(MIN_BET);
        *pot+=MIN_BET;
    }

    auto bettingRound = [&]() {
        for (Player& player : *players) {
            if (!player.isIn) continue;

            bool validAction = false;
            do {
                int action;
                cout << "Player " + player.name + "'s turn. [1] Call [2] Raise [3] Fold [4] Check" << endl;
                cin >> action;
                switch (action) {
                    case 1:
                        player.call(currentMinBet);
                        validAction = true;
                        break;
                    case 2: {
                        int raiseAmount;
                        cout << "Enter raise amount: ";
                        cin >> raiseAmount;
                        player.bet((currentMinBet - player.currentBet) + raiseAmount);
                        currentMinBet += raiseAmount;
                        validAction = true;

                        // Everyone that already checked must match bet
                        for (auto& p : *players) {
                            if (p.isIn && p.hasChecked) {
                                p.call(currentMinBet);
                                p.hasChecked = false;
                            }
                        }
                        break;
                    }
                    case 3:
                        player.fold();
                        validAction = true;
                        break;
                    case 4:
                        if (player.currentBet < currentMinBet) {
                            cout << "You cannot check, you need to call or raise.\n";
                        } else {
                            player.check();
                            validAction = true;
                        }
                        break;
                    default:
                        cout << "Invalid action.\n";
                        break;
                }
            } while (!validAction);

        }
    };

    cout << "Pre flop betting round" << endl;
    bettingRound();

    distributeCommunityCards(deck, communityCards);

    for (auto& card : *communityCards) {
        cout << "Community Card: " << card.value << " of " << card.suit << endl;
    }
}


int findBestHand(vector<Card> communityCards, Player player) {
    /*
     order of hands:
     10 - royal flush         - A♦, K♦, Q♦, J♦, 10♦
     9 - straight flush      - 10♦, 9♦, 8♦, 7♦, 6♦
     8 - four of a kind      - Q♣, Q♦, Q♥, Q♠, 4♣
     7 - full house          - A♦, A♥, A♠, 2♣, 2♥
     6 - flush               - K♣, J♣, 7♣, 5♣, 3♣
     5 - straight            - 10♣, 9♦, 8♥, 7♠, 6♣
     4 - three of a kind     - Q♣, Q♦, Q♥, 8♠, 2♠
     3 - two pairs           - 9♣, 9♦, 5♥, 5♥, 4♠
     2 - one pair            - A♣, A♦, J♥, 10♥, 6♥
     1 - high kard           - K♣, 8♣, 6♦, 3♦, 2♥
     */
    vector<Card> allCards = communityCards;
    allCards.insert(allCards.end(), player.hand.begin(), player.hand.end());
    int score = 100;

    vector<vector<Card>> combinations;
    for (int i = 0; i < allCards.size(); i++) {
        for (int j = i + 1; j < allCards.size(); j++) {
            for (int k = j + 1; k < allCards.size(); k++) {
                for (int l = k + 1; l < allCards.size(); l++) {
                    for (int m = l + 1; m < allCards.size(); m++) {
                        vector<Card> combo = {allCards[i], allCards[j], allCards[k], allCards[l], allCards[m]};
                        combinations.push_back(combo);
                    }
                }
            }
        }
    }
    return score;
}