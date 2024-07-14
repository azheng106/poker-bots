#include "Game.h"

Game::Game() {
    initialDealerIndex = Game::randomInt(0, players.size() - 1);
    round = 1;
}

/**
 * Generates a random number between a and b, inclusive; [a, b]
 */
int Game::randomInt(int a, int b) {
    random_device random;
    mt19937 gen(random());
    uniform_int_distribution<> dis(a, b);
    return dis(gen);
}

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

    cout << "Input minimum bet (also big blind bet):" << endl;
    cin >> minimumBet;

    for (int i=0; i<numPlayers; i++) {
        string name;
        cout << "Enter name for player " << i + 1 << ":" << endl;
        cin >> name;

        Player player;
        player.money = stash;
        player.name = name;

        players.push_back(player);
    }
}

/**
 * Create a new deck of cards
 */
void Game::shuffleDeck() {
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
void Game::setupBlinds() {
    int dealerIndex = (initialDealerIndex + round - 1) % players.size();
    int smallBlindIndex = (dealerIndex + round) % players.size();
    int bigBlindIndex = (dealerIndex + round + 1) % players.size();

    dealer = players[dealerIndex];
    smallBlind = players[smallBlindIndex];
    bigBlind = players[bigBlindIndex];

    cout << "Dealer is " << dealer.name << endl;
    cout << "Small blind is " << smallBlind.name << endl;
    cout << "Big blind is " << bigBlind.name << endl;
}

/**
 * Distributes 2 cards to each player
 */
void Game::distributeHoleCards() {
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
void Game::distributeCommunityCards() {
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

void Game::playHand() {
//    int currentMinBet = 0;
//    for (auto& player: players) { // Reset players
//        player.isIn = true;
//        player.currentBet = 0;
//    }
//    /*
//      If first turn, force small blind and big blind to post bets
//      Ask each player to fold, call, or raise
//      If no one has bet players can also check or bet
//      Show community cards after everyone has placed an equal bet
//     */
//    if (communityCards.empty()) {
//        players.bet(minimumBet / 2);
//        *pot+=MIN_BET / 2;
//        (*players)[*bigBlind].bet(minimumBet);
//        *pot+=MIN_BET;
//    }
//
//    auto bettingRound = [&]() {
//        for (Player& player : *players) {
//            if (!player.isIn) continue;
//
//            bool validAction = false;
//            do {
//                int action;
//                cout << "Player " + player.name + "'s turn. [1] Call [2] Raise [3] Fold [4] Check" << endl;
//                cin >> action;
//                switch (action) {
//                    case 1:
//                        player.call(currentMinBet);
//                        validAction = true;
//                        break;
//                    case 2: {
//                        int raiseAmount;
//                        cout << "Enter raise amount: ";
//                        cin >> raiseAmount;
//                        player.bet((currentMinBet - player.currentBet) + raiseAmount);
//                        currentMinBet += raiseAmount;
//                        validAction = true;
//
//                        // Everyone that already checked must match bet
//                        for (auto& p : *players) {
//                            if (p.isIn && p.hasChecked) {
//                                p.call(currentMinBet);
//                                p.hasChecked = false;
//                            }
//                        }
//                        break;
//                    }
//                    case 3:
//                        player.fold();
//                        validAction = true;
//                        break;
//                    case 4:
//                        if (player.currentBet < currentMinBet) {
//                            cout << "You cannot check, you need to call or raise.\n";
//                        } else {
//                            player.check();
//                            validAction = true;
//                        }
//                        break;
//                    default:
//                        cout << "Invalid action.\n";
//                        break;
//                }
//            } while (!validAction);
//
//        }
//    };
//
//    cout << "Pre flop betting round" << endl;
//    bettingRound();
//
//    distributeCommunityCards();
//
//    for (auto& card : *communityCards) {
//        cout << "Community Card: " << card.value << " of " << card.suit << endl;
//    }
}

void Game::showdown() {
    round += 1;
}