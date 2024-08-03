#include "Player.h"

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

bool Player::bet(int *currentMinBet, int betAmount) {
    bool validAction = true;
    while (true) {
        // Go all in if the player can't make the minimum bet
        if (*currentMinBet > money) {
            isAllIn = true;
            break;
        }

        // Ask to go all in if the player tries to bet more than their stash
        if (betAmount > money) {
            isAllIn = true;
            break;
        }

        if (betAmount < *currentMinBet) {
            validAction = false;
        }
        break;
    }
    if (isAllIn) {
        betAmount = money;
    }
    if (!validAction) return validAction;

    if (betAmount > *currentMinBet) *currentMinBet = betAmount;
    currentBet += betAmount;
    money -= betAmount;

    return validAction;
}

bool Player::check() {
    hasChecked = true;
    return true;
}

bool Player::raise(int *currentMinBet, int desiredBet) {
    bool validAction = true;
    int raiseAmount;

    while (true) {
        // Go all in if the player can't make the minimum bet
        if (2*(*currentMinBet) > money) {
            isAllIn = true;
            break;
        }

        raiseAmount = desiredBet - currentBet;

        if (raiseAmount > money) {
            isAllIn = true;
        }

        if (desiredBet < 2 * (*currentMinBet)) {
            validAction = false;
        }
        break;
    }
    if (!validAction) return validAction;

    if (raiseAmount == money) isAllIn = true;
    if (isAllIn) {
        raiseAmount = money;
        desiredBet = money + currentBet;
    }

    if (desiredBet > *currentMinBet) *currentMinBet = desiredBet;

    currentBet += raiseAmount;
    money -= raiseAmount;

    if (!isAllIn) {
        hasRaised = true;
    }

    return validAction;
}

bool Player::call(int *currentMinBet) {
    int callAmount = *currentMinBet - currentBet;
    if (callAmount >= money) isAllIn = true;

    if (isAllIn) {
        callAmount = money;
    }

    currentBet += callAmount;
    money -= callAmount;
    return true;
}

bool Player::fold() {
    isIn = false;
    return true;
}

void Player::win(int potAmount) {
    money += potAmount;
    cout << "Player " << name << " wins $" << potAmount << "!\n";
}