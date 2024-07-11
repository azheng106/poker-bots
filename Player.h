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
    Status status;
    void bet(int const amount) {
        this->money -= amount;
    }

};




#endif //PLAYER_H
