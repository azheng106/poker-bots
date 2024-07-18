#include "classes/Game.h"
#include "classes/CardUtil.h"

using namespace std;

int main() {
    vector<Card> communityCards = {Card(12, 's'), Card(13, 'c'), Card(10, 'h')
    , Card(9, 'c'), Card(3, 's')};
    vector<Card> playerHand = {Card(11, 'h'), Card(6, 's')};
    CardUtil::findBestHand(communityCards, playerHand);
//    Game game;
//    game.setupPlayers();
//    game.setupBlinds();
//    game.shuffleDeck();
//    game.distributeHoleCards();
//    game.playHand();
}