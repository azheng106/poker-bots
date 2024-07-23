#include "classes/Game.h"
#include <SFML/Graphics.hpp>

using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }

//    Game game;
//    game.setupPlayers();
//    while (!game.isFinished) {
//        game.playHand();
//    }

    return 0;
}