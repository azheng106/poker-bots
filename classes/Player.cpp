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

void Player::bet(int *currentMinBet) {
    int betAmount;
    while (true) {
        // Go all in if the player can't make the minimum bet
        if (*currentMinBet > money) {
            isAllIn = true;
            break;
        }
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
    if (betAmount == money) isAllIn = true;
    if (isAllIn) {
        betAmount = money;
        cout << "[ALL IN] " << name << " is going all in." << "\n";
    }
    if (betAmount > *currentMinBet) *currentMinBet = betAmount;
    currentBet += betAmount;
    money -= betAmount;
    if (!isAllIn) cout << "[TURN] Player " << name << " bets $" << currentBet << "\n";
}

void Player::check() {
    cout << "[TURN] Player " << name << " checks." << "\n";
    hasChecked = true;
}

void Player::raise(int *currentMinBet) {
    int desiredBet;
    int raiseAmount;
    while (true) {
        // Go all in if the player can't make the minimum bet
        if (*currentMinBet > money) {
            isAllIn = true;
            break;
        }
        cout << "Current minimum bet: $" << *currentMinBet << "\n";
        cout << "Current minimum bet to raise: $" << 2*(*currentMinBet) << "\n";
        cout << "Raise to: $";
        cin >> desiredBet;

        raiseAmount = desiredBet - currentBet;

        if (raiseAmount > money) {
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
    if (raiseAmount == money) isAllIn = true;
    if (isAllIn) {
        raiseAmount = money;
        desiredBet = money + currentBet;
        cout << "[ALL IN] " << name << " is going all in." << "\n";
    }
    if (desiredBet > *currentMinBet) *currentMinBet = desiredBet;
    currentBet += raiseAmount;
    money -= raiseAmount;
    if (!isAllIn) {
        cout << "[TURN] Player " << name << " raises to $" << desiredBet << "\n";
        hasRaised = true;
    }
}

void Player::call(int *currentMinBet) {
    int callAmount = *currentMinBet - currentBet;
    if (callAmount >= money) isAllIn = true;
    if (isAllIn) {
        callAmount = money;
        cout << "[ALL IN] " << name << " is going all in." << "\n";
    } else {
        cout << "[TURN] Player " << name << " calls." << "\n";
    }
    currentBet += callAmount;
    money -= callAmount;
}

void Player::fold() {
    isIn = false;
    cout << "[TURN] Player " << name << " folds." << "\n";
}

void Player::win(int potAmount) {
    money += potAmount;
    cout << "[END] Player " << name << " wins the pot of $" << potAmount << "!" << "\n";
}