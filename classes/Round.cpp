#include "Round.h"

/**
 * Create a new deck of cards
 */
void Round::shuffleDeck() {
    char suits[4] = {'c', 'd', 'h', 's'};
    // 11=J, 12=Q, 13=K, 14=A
    for (int i=2; i<=14; i++) {
        for (int j=0; j<=3; j++) {
            Card card(i, suits[j]);
            deck.push_back(card);
        }
    }
}

/**
 * Setup small and big blinds
 */
void Round::setupBlinds() {
    unsigned long long dealerIndex = (initialDealerIndex + round - 1) % players.size();
    unsigned long long smallBlindIndex = (dealerIndex + round) % players.size();
    unsigned long long bigBlindIndex = (dealerIndex + round + 1) % players.size();
    cout << "Dealer is " << players[dealerIndex].name << endl;
    cout << "Small blind is " << players[smallBlindIndex].name << endl;
    cout << "Big blind is " << players[bigBlindIndex].name << endl;

    dealer = players[dealerIndex];
    smallBlind = players[smallBlindIndex];
    bigBlind = players[bigBlindIndex];
}

/**
 * Distributes 2 cards to each player
 */
void Round::distributeHoleCards() {
    for (int i=0; i<2; i++) {
        for (Player player : players) {
            int drawnCardIndex = randomInt(0, deck.size()-1);
            Card drawnCard = deck[drawnCardIndex];
            deck.erase(deck.begin() + drawnCardIndex);
            player.hand.push_back(drawnCard);
        }
    }
}

/**
 * Distributes community cards
 */
void Round::distributeCommunityCards() {
    if (communityCards.empty()) {
        for (int i=0; i<3; i++) {
            int drawnCardIndex = Game::randomInt(0, deck.size()-1);
            communityCards.push_back(deck[drawnCardIndex]);
            deck.erase(deck.begin() + drawnCardIndex);
        }
    } else if (communityCards.size() < 5)  {
        int drawnCardIndex = Game::randomInt(0, deck.size()-1);
        communityCards.push_back(deck[drawnCardIndex]);
        deck.erase(deck.begin() + drawnCardIndex);
    }
}