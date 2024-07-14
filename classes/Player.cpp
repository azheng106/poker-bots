#include "Player.h"

using namespace std;

Player::Player(int index, int stash, string name) {
    this->index = index;
    this->name = name;

    isIn = true;
    money = stash;
    recentBet = 0;
}

bool Player::operator==(Player &other) const {
    return this->name == other.name && this->index == other.index;
}

/*
 * Standard opening for rounds. If no betAmount is provided, gets bet amount from input.
 * Checks if the player has enough money to make the bet, except if betAmount is passed in as a parameter.
 */
void Player::bet(int betAmount=0) {
    if (betAmount == 0) {
        while (true) {
            cout << "Current stash: $" << money << endl;

            cout << "Amount to bet:" << endl;
            cin >> betAmount;

            if (money < betAmount) {
                cout << "You don't have enough money to make that bet." << endl;
                continue;
            }
            cout << "[TURN] Player " << name << " bets $" << betAmount << endl;
            break;
        }
    }
    recentBet = betAmount;
    money -= betAmount;
}

/*
 * Standard raise after bet(s) have been made.
 * Asks the user for the raise amount, and then displays the total bet
 * Checks if the player has enough money to make the raise
 */
void Player::raise(int *currentMinBet) {
    int raiseAmount;
    while (true) {
        cout << "Current stash: $" << money << endl;
        cout << "Current minimum bet: " << *currentMinBet << endl;

        cout << "Enter raise amount: ";
        cin >> raiseAmount;

        if (money < (raiseAmount - recentBet)) {
            cout << "You don't have enough money to make that raise." << endl;
            continue;
        }
        break;
    }
    *currentMinBet += raiseAmount;
    bet(*currentMinBet - recentBet);
    cout << "[TURN] Player " << name << " raises to $" << recentBet << endl;
}

/*
 * Skips turn
 */
void Player::check() {
    cout << "[TURN] Player " << name << " checks." << endl;
}

void Player::call(int currentMinBet) {
    int callAmount = currentMinBet - recentBet;
    cout << "current min bet" << currentMinBet << endl;
    cout << "Call Amount: " << callAmount << endl;
    cout << "current bet " << recentBet << endl;
    if (callAmount > 0) {
        bet(callAmount);
    } else {
        cout << "Current bet > minimum bet, checking." << endl;
        check();
    }
}

void Player::fold() {
    isIn = false;
    cout << "Player " << name << " folds." << endl;
}

void Player::win(int potAmount) {
    money += potAmount;
    cout << "Player " << name << " wins the pot of $" << potAmount << "!" << endl;
}