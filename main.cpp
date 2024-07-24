#include "classes/Game.h"
#include "util/obj.cpp"
#include "util/event.cpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

// Used to access poker-bots resources from the .exe path
const string BASE_PATH = "../../../";

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Poker Bots");

    // Create button
    sf::RectangleShape button = createRectangularButton(sf::Vector2f(200, 50), sf::Vector2f(300, 275),
                                                        sf::Color::Green, sf::Color::White, 2);

    // Create font
    sf::Font robotoMono;
    robotoMono.loadFromFile(BASE_PATH+"fonts/RobotoMono-Regular.ttf");

    // Create text
    sf::Text text = createText("bro is about to win a gazillion dollars", robotoMono, 24,
                               sf::Vector2f(10, 10), sf::Color::White);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Window is being closed
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Button was clicked
            if (buttonClicked(button, window, event)) {
                cout << "Button pressed\n";
            }
        }
        window.clear();

        // Drawables
        window.draw(button);
        window.draw(text);

        window.display();
    }
    return 0;
}