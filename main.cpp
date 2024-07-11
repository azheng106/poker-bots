#include <iostream>
#include <random>
#include <vector>

#include "Card.h"
#include "Player.h"

using namespace std;

int main() {
    // Create random number generator
    random_device random;
    mt19937 gen(random());

    int pot = 0;
    int numPlayers;
    do {
        cout << "Input number of players (2-10)" << endl;
        cin >> numPlayers;
    } while (numPlayers < 2 || numPlayers > 10);

    // Create deck of cards
    vector<Card> deck;
    char suits[4] = {'c', 'd', 'h', 's'};

    // 11=J 12=Q 13=K 14=A
    for (int i=2; i<=14; i++) {
        for (int j=0; j<=3; j++) {
            Card card;
            card.value = i;
            card.suit = suits[j];

            deck.push_back(card);
        }
    }

    // Initialize players
    vector<Player> players;

    for (int i=1; i<=numPlayers; i++) {
        string name;
        cout << "Enter name for player " << i << endl;
        cin >> name;

        // change initial money later if needed
        Player player;
        player.money = 100000;
        player.name = name;
        player.isIn = true;

        players.push_back(player);
    }

    // Set range of values generated by RNG
    uniform_int_distribution<> dis(0, numPlayers - 1);

    int dealer = dis(gen);
    int smallBlind = dealer + 1;
    int bigBlind = smallBlind + 1;

    // Deal cards


    return 0;
}

//void playHand(int& dealerPos, int& pot, )
