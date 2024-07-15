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
void Player::bet(int betAmount) {
    if (betAmount == 0) {
        while (true) {
            cout << "\nCurrent stash: $" << money << "\n";

            cout << "Amount to bet: $";
            cin >> betAmount;

            if (money < betAmount) {
                cout << "You don't have enough money to make that bet." << "\n";
                continue;
            }
            cout << "\n[TURN] Player " << name << " bets $" << betAmount << "\n";
            break;
        }
    }
    currentBet += betAmount;
    money -= betAmount;
}

/*
 * Skips turn
 */
void Player::check() {
    cout << "\n[TURN] Player " << name << " checks." << "\n";
}

/*
 * Standard call. Will bet the current minimum bet.
 */
void Player::call(int currentMinBet) {
    int callAmount = currentMinBet - currentBet;
    bet(callAmount);
    cout << "\n[TURN] Player " << name << " calls, now betting $" << currentBet << "\n";
}

/*
 * Standard raise after bet(s) have been made.
 * Asks the user for the raise amount, and then displays the total bet
 * Checks if the player has enough money to make the raise
 */
void Player::raise(int *currentMinBet) {
    int raiseAmount;
    while (true) {
        cout << "\nCurrent stash: $" << money << "\n";
        cout << "Current minimum bet: $" << *currentMinBet << "\n";
        cout << "Enter raise amount: $";
        cin >> raiseAmount;

        if (raiseAmount < *currentMinBet) {
            cout << "You have to raise by at least the minimum bet." << "\n";
            continue;
        }

        if (money < (raiseAmount + *currentMinBet)) {
            cout << "You don't have enough money to make that raise." << "\n";
            continue;
        }

        break;
    }
    bet(raiseAmount + *currentMinBet - currentBet);
    cout << "\n[TURN] Player " << name << " raises to $" << currentBet << "\n";
    *currentMinBet = currentBet;
}

/*
 * Surrenders hand.
 */
void Player::fold() {
    isIn = false;
    cout << "\n[TURN] Player " << name << " folds." << "\n";
}

void Player::win(int potAmount) {
    money += potAmount;
    cout << "\n[END] Player " << name << " wins the pot of $" << potAmount << "!" << "\n";
}