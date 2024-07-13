#include "Player.h"

using namespace std;

Player::Player (int index) {
    this->index = index;
    isIn = true;
    currentBet = 0;
    hasChecked = false;
}

void Player::bet(int betAmount) {
    money -= betAmount;
    currentBet = betAmount;
    cout << "Player " << name << " bets $" << betAmount << endl;
}

void Player::win(int potAmount) {
    money += potAmount;
    cout << "Player " << name << " wins the pot of $" << potAmount << "!" << endl;
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

void Player::check() {
    cout << "Player " << name << " checks." << endl;
}

void Player::fold() {
    isIn = false;
    cout << "Player " << name << " folds." << endl;
}
