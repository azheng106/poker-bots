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
        cout << "Input number of players (2-10):" << "\n";
        cin >> numPlayers;
    } while (numPlayers < 2 || numPlayers > 10);

    int stash;
    cout << "Input stash (amount of money each players starts with):" << "\n";
    cin >> stash;

    cout << "Input minimum bet (also big blind bet):" << "\n";
    cin >> minimumBet;

    for (int i=0; i<numPlayers; i++) {
        string name;
        cout << "Enter name for player " << i + 1 << ":" << "\n";
        cin >> name;

        Player player(i, stash, name);
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

    dealer = &players[dealerIndex];
    smallBlind = &players[smallBlindIndex];
    bigBlind = &players[bigBlindIndex];

    cout << "\n[SETUP] Dealer is " << dealer->name << "\n";
    cout << "[SETUP] Small blind is " << smallBlind->name << "\n";
    cout << "[SETUP] Big blind is " << bigBlind->name << "\n\n";
}

/**
 * Distributes 2 cards to each player
 */
void Game::distributeHoleCards() {
    if (deck.empty()) {
        shuffleDeck();
    }

    for (Player& player : players) {
        for (int i = 0; i < 2; i++) {
            int drawnCardIndex = randomInt(0, deck.size() - 1);
            Card drawnCard = deck[drawnCardIndex];
            deck.erase(deck.begin() + drawnCardIndex);
            player.hand.push_back(drawnCard);
        }
    }

    // Debug usage
    for (Player& player : players) {
        cout << "Player " << player.name << " has hole cards: " << player.hand[0] << ", " << player.hand[1] << "\n";
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

void Game::calculatePot() {
    pot = 0;
    for (Player& player : players) {
        pot += player.currentBet;
    }
    cout << "\n[POT] The pot is now worth $" << pot << "\n";
}

void Game::playHand() {
    pot = 0;
    for (Player& player: players) {
        player.isIn = true;
        player.currentBet = 0;
    }

    /*
      If first turn, force small blind and big blind to post bets
      Ask each player to fold, call, or raise
      If no one has bet players can also check or bet
      Show community cards after everyone has placed an equal bet
     */
    if (communityCards.empty()) {
        smallBlind->bet(minimumBet / 2);
        cout << "\n[TURN] Small blind " << smallBlind->name << " bets $" << smallBlind->currentBet << "\n";
        calculatePot();
        bigBlind->bet(minimumBet);
        cout << "\n[TURN] Big blind " << bigBlind->name << " bets $" << bigBlind->currentBet << "\n";
        calculatePot();
    }

    auto bettingRound = [&]() {
        for (auto & player : players) {
            if (!player.isIn) continue;
            bool validAction = false;
            do {
                int action;
                cout << "Player " + player.name + "'s turn. [1] Call [2] Raise [3] Fold [4] Check"  << "\n";
                cin >> action;
                switch (action) {
                    case 1:
                        player.call(minimumBet);
                        validAction = true;
                        calculatePot();
                        break;
                    case 2: {
                        player.raise(&minimumBet);
                        validAction = true;
                        calculatePot();
                        break;
                    }
                    case 3:
                        player.fold();
                        validAction = true;
                        calculatePot();
                        break;
                    case 4:
                        if (player.currentBet < minimumBet) {
                            cout << "You cannot check, you need to call or raise.\n";
                        } else {
                            player.check();
                            validAction = true;
                            calculatePot();
                        }
                        break;
                    default:
                        cout << "Invalid action.\n";
                        break;
                }
            } while (!validAction);
        }
    };

    cout << "\nPre flop betting round"  << "\n";
    bettingRound();
    distributeCommunityCards();
    for (Card& card : communityCards) {
        cout << "Community Card: " << card << "\n";
    }

    cout << "\nNext betting round" << "\n";
    bettingRound();
    distributeCommunityCards();
    for (Card& card : communityCards) {
        cout << "Community Card: " << card << "\n";
    }

    cout << "\nFinal betting round" << "\n";
    bettingRound();
    distributeCommunityCards();
    for (Card& card : communityCards) {
        cout << "Community Card: " << card << "\n";
    }

    showdown();
}

void Game::showdown() {
    cout << "SHOWDOWN" << "\n";
    round += 1;
    pot = 0;
}