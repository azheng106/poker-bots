#include "Round.h"

Round::Round(Game& game) : game(game){
    if (game.players.empty()) {
        cout << "[DEBUG] Cannot create a round without any players. Create a game object, and then use setupPlayers().";
    }
    this->players = game.players;
    pot = 0;
    shuffleDeck();
    setupBlinds();
}

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
    int dealerIndex = (initialDealerIndex + round - 1) % players.size();
    int smallBlindIndex = (dealerIndex + round) % players.size();
    int bigBlindIndex = (dealerIndex + round + 1) % players.size();

    cout << "Dealer is " << players[dealerIndex].name << endl;
    cout << "Small blind is " << players[smallBlindIndex].name << endl;
    cout << "Big blind is " << players[bigBlindIndex].name << endl;

    Player dealer = players[dealerIndex];
    Player smallBlind = players[smallBlindIndex];
    Player bigBlind = players[bigBlindIndex];
}

/**
 * Distributes 2 cards to each player
 */
void Round::distributeHoleCards() {
    for (Player player : players) {
        for (int i = 0; i < 2; i++) {
            int drawnCardIndex = randomInt(0, deck.size() - 1);
            Card drawnCard = deck[drawnCardIndex];
            deck.erase(deck.begin() + drawnCardIndex);
            player.hand.push_back(drawnCard);
            cout << "Player " << player.name << " hole #" << i + 1 << ": " << drawnCard << endl;
        }
    }
}

/**
 * Distributes community cards to the flop
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