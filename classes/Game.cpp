#include "Game.h"

/**
 * Initialize players at the start of the game
 */
void Game::setupPlayers() {
    int numPlayers;
    do {
        cout << "Input number of players (2-10):" << endl;
        cin >> numPlayers;
    } while (numPlayers < 2 || numPlayers > 10);

    int stash;
    cout << "Input stash (amount of money each players starts with):" << endl;
    cin >> stash;

    for (int i=0; i<numPlayers; i++) {
        string name;
        cout << "Enter name for player " << i + 1 << endl;
        cin >> name;

        Player player(i+1);
        player.money = stash;
        player.name = name;

        players.push_back(player);
    }
}