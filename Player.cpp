#include <iostream>

#include "Player.h"

using namespace std;

Player::Player (int index) {
    this->index = index;
    isIn = true;
    currentBet = 0;
    hasChecked = false;
}

void Player::bet(int amount) {
    money -= amount;
    currentBet += amount;
    cout << "Player " << name << " bets $" << amount << endl;
}

void Player::winPot(int amount) {
    money += amount;
    cout << "Player " << name << " wins $" << amount << "!" << endl;
}

void Player::fold() {
    isIn = false;
    cout << "Player " << name << " folds." << endl;
}

void Player::check() {
    cout << "Player " << name << " checks." << endl;
}

void Player::call(int amount) {
    int callAmount = amount - currentBet;
    if (callAmount > 0) {
        bet(callAmount);
    } else {
        cout << "Current bet > minimum bet, checking." << endl;
        check();
    }
}
