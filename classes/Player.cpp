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
            cout << "Current stash: $" << money << "\n";

            cout << "Amount to bet: $";
            cin >> betAmount;

            if (money < betAmount) {
                cout << "You don't have enough money to make that bet." << "\n";
                continue;
            }

            if (betAmount < *currentMinBet) {
                cout << "You must bet at least the minimum bet (the big blind) of $" << *currentMinBet << "\n";
                continue;
            }
            break;
        }
    }
    currentBet += betAmount;
    money -= betAmount;
    cout << "[TURN] Player " << name << " bets $" << currentBet << "\n";
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
        cout << "\nCurrent stash: $" << money << "\n";
        cout << "Current minimum bet: $" << *currentMinBet << "\n";
        cout << "Current minimum bet to raise: $" << 2*(*currentMinBet) << "\n";
        cout << "Raise to: $";
        cin >> desiredBet;

        if (desiredBet < 2*(*currentMinBet)) {
            cout << "You have to raise by at least the minimum bet." << "\n";
            continue;
        }

        if (money < desiredBet - currentBet) {
            cout << "You don't have enough money to make that raise." << "\n";
            continue;
        }

        break;
    }
    cout << "[TURN] Player " << name << " raises to $" << desiredBet << "\n";
    bet(currentMinBet, desiredBet - currentBet);
    *currentMinBet = currentBet;
    hasRaised = true;
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