#include "classes/Game.h"
#include "classes/CardUtil.h"

using namespace std;

int main() {
    /*
     * TESTING
     */
//    vector<Card> communityCards = {Card(12, 's'), Card(13, 'c'), Card(10, 'h')
//    , Card(9, 'c'), Card(3, 's')};
//    vector<Card> playerHand = {Card(11, 'h'), Card(6, 's')};
//    vector<Card> bestHand = CardUtil::findBestHand(communityCards, playerHand);
//
//    for (Card card : bestHand) {
//        cout << card << "\n";
//    }
    /*
     * TESTING END
     */
    Game game;
    game.setupPlayers();
    while (true) {
        game.reset();
        game.playHand();
    }
}