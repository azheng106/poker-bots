#include "classes/Game.h"
#include "util.cpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

void CLI() {
    Game game;
    game.setupPlayers();
    while (!game.isFinished) {
        game.playHand();
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Poker Bots");

    // Create button
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setPosition(300, 275);
    button.setFillColor(sf::Color::Blue);

    while (window.isOpen()) {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }


            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (isMouseOverButton(button, window)) {
                        cout << "Button pressed" << endl;
                    }
                }
            }
        }
        window.clear();
        window.draw(button);
        window.display();
    }
    return 0;
}