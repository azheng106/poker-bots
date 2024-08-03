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

bool Player::bet(int *currentMinBet, int betAmount, Text& report) {
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

    if (!isAllIn) report.text.setString(name + " bets $" + to_string(currentBet));
    if (isAllIn) report.text.setString(name + " goes all in with $" + to_string(currentBet));
    return validAction;
}

bool Player::check(Text& report) {
    hasChecked = true;
    report.text.setString(name + " checks.");
    return true;
}

bool Player::raise(int *currentMinBet, int desiredBet, Text& report) {
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
        report.text.setString(name + " raises to $" + to_string(currentBet));
    }
    if (isAllIn) report.text.setString(name + " goes all in with $" + to_string(currentBet));

    return validAction;
}

bool Player::call(int *currentMinBet, Text& report) {
    int callAmount = *currentMinBet - currentBet;
    if (callAmount >= money) isAllIn = true;

    if (isAllIn) {
        callAmount = money;
    }

    currentBet += callAmount;
    money -= callAmount;

    if (!isAllIn) report.text.setString(name + " calls $" + to_string(currentBet));
    if (isAllIn) report.text.setString(name + " goes all in with $" + to_string(currentBet));
    return true;
}

bool Player::fold(Text& report) {
    isIn = false;
    report.text.setString(name + " folds.");
    return true;
}

void Player::win(int potAmount, Text& report) {
    money += potAmount;
    report.text.setString(name + " wins $" + to_string(potAmount));
}