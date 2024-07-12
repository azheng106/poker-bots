//
// Created by azhen on 7/11/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

using namespace std;

class Player {
public:
    string name;
    int money;
    int index;
    bool isIn;
    bool hasChecked;
    int currentBet;
    vector<Card> hand;

    Player (int index) {
        this->index = index;
        isIn = true;
        currentBet = 0;
        hasChecked = false;
    }
    void bet(int amount) {
        money -= amount;
        currentBet += amount;
        cout << "Player " << name << " bets $" << amount << endl;
    }
    void winPot(int amount) {
        money += amount;
        cout << "Player " << name << " wins $" << amount << "!" << endl;
    }
    void fold() {
        isIn = false;
        cout << "Player " << name << " folds." << endl;
    }
    void check() {
        cout << "Player " << name << " checks." << endl;
    }
    void call(int amount) {
        int callAmount = amount - currentBet;
        if (callAmount > 0) {
            bet(callAmount);
        } else {
            cout << "Current bet > minimum bet, checking." << endl;
            check();
        }
    }
};




#endif //PLAYER_H
