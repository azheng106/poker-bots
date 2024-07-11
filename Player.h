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

    void bet(int amount) {
        this->money -= amount;
    }
    void winPot(int amount) {
        this ->money += amount;
    }
};




#endif //PLAYER_H
