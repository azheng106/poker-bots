#include "classes/Game.h"
#include "util/creation.cpp"
#include "util/event.cpp"
#include "SFML/Audio/Music.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

// Used to access poker-bots resources from the .exe path
const string BASE_PATH = "../../../";

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Poker Bots");

    // Create button
    sf::RectangleShape button = createButton(sf::Vector2f(200, 50), sf::Vector2f(300, 275),
                                             sf::Color::Green, sf::Color::White, 2);

    // Create font
    sf::Font robotoMono;
    robotoMono.loadFromFile(BASE_PATH+"fonts/RobotoMono-Regular.ttf");

    // Create text
    sf::Text text = createText("Click the button", robotoMono, 24, sf::Vector2f(10, 10),
                               sf::Color::White);
    sf::Text altText = createText("bro is about to win a gazillion dollars", robotoMono, 24,
                                  sf::Vector2f(10, 40), sf::Color::White);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Window is being closed
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // On mouse click
            if (event.type == sf::Event::MouseButtonPressed) {
                // Left click
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (isMouseOverButton(button, window)) {
                        cout << "Button pressed" << endl;
                        if (button.getFillColor() == sf::Color::Green) {
                            button.setFillColor(sf::Color::Blue);
                        } else button.setFillColor(sf::Color::Green);
                    }
                }
            }
        }
        window.clear();

        // Drawables
        window.draw(button);
        window.draw(text);
        window.draw(altText);

        window.display();
    }
    return 0;
}