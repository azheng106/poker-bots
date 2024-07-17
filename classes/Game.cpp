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
    cin >> bigBlindBet;
    currentMinBet = bigBlindBet;

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
        cout << "[DEBUG] Player " << player.name << " has hole cards: " << player.hand[0] << ", " << player.hand[1] << "\n";
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

    cout << "\n";
    for (Card& card : communityCards) {
        cout << "[CARD] Community Card: " << card << "\n";
    }
}

/*
 * Displays the pot value
 */
void Game::displayPot() {
    int tempPot = 0;
    for (Player& player : players) {
        tempPot += player.currentBet;
    }
    cout << "[POT] Pot is now worth $" << tempPot << "\n";
}

/*
 * Updates pot value at the end of the round, and sets all player current bets to 0
 */
void Game::calculatePot() {
    for (Player& player : players) {
        pot += player.currentBet;
        player.totalBet += player.currentBet;
        player.currentBet = 0;
    }
}

void Game::doBlindBets() {
    smallBlind->currentBet += bigBlindBet / 2;
    smallBlind->money -= bigBlindBet / 2;
    cout << "[BLIND] Small blind " << smallBlind->name << " bets $" << bigBlindBet / 2 << "\n";
    bigBlind->currentBet += bigBlindBet;
    bigBlind->money -= bigBlindBet;
    cout << "[BLIND] Big blind " << bigBlind->name << " bets $" << bigBlindBet << "\n";
    displayPot();
    hasOpened = true;
}

void Game::getAction(Player& player) {
    string action;

    while (true) {
        cout << "\nPlayer " + player.name + "'s turn. You have $" << player.money << ". Type one option: ";

        // No bet has been made yet
        if (!hasOpened) {
            cout << "[Bet] [Check] [Fold]" << "\n";
        } else if (!player.hasRaised) {
            cout << "[Raise] [Call] [Fold]" << "\n";
        } else {
            cout << "[Call] [Fold]" << "\n";
        }
        cin >> action;

        if (!hasOpened && action=="bet") {
            player.bet(&currentMinBet);
            hasOpened = true;
            break;
        } else if (!hasOpened && action=="check") {
            player.check();
            break;
        } else if (hasOpened && !player.hasRaised && action=="raise") {
            player.raise(&currentMinBet);
            break;
        } else if (hasOpened && action=="call") {
            player.call(&currentMinBet);
            break;
        } else if (action=="fold") {
            player.fold();
            break;
        } else {
            cout << "Invalid option.\n";
            continue;
        }
    }
};

bool Game::isTurnOver() {
    bool isTurnOver = true;
    bool checkedAround = true;

    for (Player& player : players) {
        if (player.isIn && !player.isAllIn) {
            if (player.currentBet != currentMinBet) {
                isTurnOver = false;
            }
            if (!player.hasChecked) checkedAround = false;
        }
    }

    // Debug usage only
    cout << "\n";
    for (Player& player : players) {
        if (player.isIn) {
            cout << "[DEBUG] Player " << player.name << " has $" << player.currentBet << " in the pot.\n";
        }
    }
    if (checkedAround) return true;
    return isTurnOver;
}

// Rewrite
void Game::playHand() {
    pot = 0;
    // Reset players
    for (Player& player : players) {
        player.isIn = true;
        player.isAllIn = false;
        player.totalBet = 0;
    }

    // 3 betting rounds: pre-flop, turn, river
    for (turn=1; turn<=3; turn++) {
        hasOpened = false;
        for (Player& player : players) {
            player.currentBet = 0;
            player.hasRaised = false;
            player.hasChecked = false;
        }
        currentMinBet = bigBlindBet;
        switch (turn) {
            case 1:
                cout << "\n[ROUND] Pre-flop\n\n";
                doBlindBets();
                break;
            case 2:
                cout << "\n[ROUND] Next round\n";
                break;
            case 3:
                cout << "\n[ROUND] Final round\n";
                break;
        }

        int startingIndex;
        if (turn == 1) startingIndex = (bigBlind->index + 1) % players.size();
        else startingIndex = smallBlind->index % players.size();

        for (int i=startingIndex; !isTurnOver(); i=(i+1) % players.size()) {
            Player& player = players[i];
            if (!player.isIn) continue;
            if (player.isAllIn) continue;
            // Skip small and big blind if it's turn 1
            if (turn==1 && (player.currentBet>=currentMinBet) && (&player==smallBlind || &player==bigBlind)) continue;
            getAction(player);
        }
        calculatePot();
        distributeCommunityCards();
    }
    showdown();
}

void Game::showdown() {
    cout << "\nSHOWDOWN TIME (SPONSORED BY THEBIGBLACKDARREN CORP)" << "\n\n";

    for (Player& player : players) {
        if (player.isIn) {
            cout << "Player " << player.name << " has bet $" << player.totalBet << "\n";
        }
    }
    round += 1;
}