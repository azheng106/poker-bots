#include "classes/Game.h"

using namespace std;

int main() {
    Game game;
    game.setupPlayers();
    while (!game.isFinished) {
        game.playHand();
    }
}