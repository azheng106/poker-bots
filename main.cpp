#include <iostream>
#include <random>

using namespace std;
enum Status {
    IN, OUT
};
int main() {
    // Create random number generator
    random_device random;
    mt19937 gen(random());

    int pot = 0;
    int numPlayers;
    do {
        cout << "Input number of players (2-10)" << endl;
        cin >> numPlayers;
    } while (numPlayers < 2 || numPlayers > 10);

    // Set range of values generated by RNG
    uniform_int_distribution<> dis(0, numPlayers - 1);

    int dealer = dis(gen);
    int smallBlind = dealer + 1;
    int bigBlind = smallBlind + 1;

    return 0;
}

void playHand(int& dealerPos, int& pot, )
