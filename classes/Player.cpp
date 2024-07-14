#include "Player.h"

using namespace std;

Player::Player(int index, int stash, string name) {
    this->index = index;
    isIn = true;
    currentBet = 0;
    hasChecked = false;
    money = stash;
    this->name = name;
}

void Player::bet(int betAmount) {
    currentBet = betAmount;
    money -= betAmount;
    if (money < 0) {
        cout << "BLUD TRYING TO PLAY THE FOOL" << endl;
        fold();
        return;
    }
    cout << "Player " << name << " bets $" << betAmount << endl;
}

void Player::raise(int *currentMinBet) {
    int raiseAmount;
    cout << "Enter raise amount: ";
    cin >> raiseAmount;
    bet((*currentMinBet - currentBet) + raiseAmount);
    *currentMinBet += raiseAmount;
}

void Player::check() {
    cout << "Player " << name << " checks." << endl;
}

void Player::call(int currentMinBet) {
    int callAmount = currentMinBet - currentBet;
    cout << "current min bet" << currentMinBet << endl;
    cout << "Call Amount: " << callAmount << endl;
    cout << "current bet " << currentBet << endl;
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
