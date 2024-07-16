#include "Player.h"

using namespace std;

Player::Player(int index, int stash, string name) {
    this->index = index;
    this->name = name;

    isIn = true;
    money = stash;
    currentBet = 0;
}

bool Player::operator==(Player &other) const {
    return this->name == other.name && this->index == other.index;
}

/*
 * Standard opening for rounds. If betAmount=0, gets bet amount from input.
 * Checks if the player has enough money to make the bet, except if betAmount is passed in as a parameter.
 */
void Player::bet(int *currentMinBet, int betAmount, bool fromInput) {
    if (fromInput) {
        while (true) {
            // Go all in if the player can't make the minimum bet
            if (*currentMinBet > money) {
                isAllIn = true;
                break;
            }

            cout << "Current stash: $" << money << "\n";
            cout << "Amount to bet: $";
            cin >> betAmount;

            // Ask to go all in if the player tries to bet more than their stash
            if (betAmount > money) {
                string confirm;
                cout << "You don't have enough money to make this bet. Would you like to go all in? [y/n]\n";
                cin >> confirm;

                if (confirm == "y") {
                    isAllIn = true;
                    break;
                } else continue;
            }

            if (betAmount < *currentMinBet) {
                cout << "You must bet at least the minimum bet (the big blind) of $" << *currentMinBet << "\n";
                continue;
            }
            break;
        }
    }
    if (betAmount >= money) isAllIn = true;
    if (isAllIn) {
        betAmount = money;
        cout << "[ALL IN] " << name << " is going all in." << "\n";
    }
    if (betAmount > *currentMinBet) *currentMinBet = betAmount;
    currentBet += betAmount;
    money -= betAmount;
    if (!isAllIn) cout << "[TURN] Player " << name << " bets $" << currentBet << "\n";
}

/*
 * Skips turn
 */
void Player::check() {
    cout << "[TURN] Player " << name << " checks." << "\n";
}

/*
 * Standard raise after bet(s) have been made.
 * Asks the user for the raise amount, and then displays the total bet
 * Checks if the player has enough money to make the raise
 */
void Player::raise(int *currentMinBet) {
    int desiredBet;
    while (true) {
        // Go all in if the player can't make the minimum bet
        if (*currentMinBet > money) {
            isAllIn = true;
            break;
        }

        cout << "\nCurrent stash: $" << money << "\n";
        cout << "Current minimum bet: $" << *currentMinBet << "\n";
        cout << "Current minimum bet to raise: $" << 2*(*currentMinBet) << "\n";
        cout << "Raise to: $";
        cin >> desiredBet;

        if (desiredBet - currentBet > money) {
            string confirm;
            cout << "You don't have enough money to make that bet. Did you mean to go all in? [y/n]" << "\n";
            cin >> confirm;

            if (confirm == "y") {
                isAllIn = true;
            } else continue;
        }

        if (desiredBet < 2*(*currentMinBet)) {
            cout << "You have to raise by at least the minimum bet." << "\n";
            continue;
        }
        break;
    }
    if (!isAllIn) {
        cout << "[TURN] Player " << name << " raises to $" << desiredBet << "\n";
        hasRaised = true;
    }
    bet(currentMinBet, desiredBet - currentBet);
}

/*
 * Standard call. Will bet the current minimum bet.
 */
void Player::call(int currentMinBet) {
    int callAmount = currentMinBet - currentBet;
    cout << "[TURN] Player " << name << " calls." << "\n";
    bet(&currentMinBet, callAmount);
}

/*
 * Surrenders hand.
 */
void Player::fold() {
    isIn = false;
    cout << "[TURN] Player " << name << " folds." << "\n";
}

void Player::win(int potAmount) {
    money += potAmount;
    cout << "[END] Player " << name << " wins the pot of $" << potAmount << "!" << "\n";
}