//
// Created by azhen on 7/11/2024.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

using namespace std;

class Player {
public:
    int money;
    int index;
    string name;
    bool isIn;
    vector<Card> hand;
    int currentBet;

    Player(int index) {
        this->index = index;
        isIn = true;
        currentBet = 0;
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
};




#endif //PLAYER_H
