#include "classes/Game.h"
#include "util/creation.cpp"
#include "util/event.cpp"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

using namespace std;

// Used to access poker-bots resources from the .exe path
const string BASE_PATH = "../../../";

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Poker Bots");

    // Create button
    sf::RectangleShape button = createButton(sf::Vector2f(200, 50), sf::Vector2f(300, 275),
                                             sf::Color::Green);

    // Create font
    sf::Font font;
    font.loadFromFile(BASE_PATH+"fonts/RobotoMono-Regular.ttf");

    // Create text
    sf::Text text = createText("Click the button", font, 24, sf::Vector2f(10, 10),
                               sf::Color::White);
    sf::Text altText = createText("bro is about to win a gazillion dollars", font, 24,
                                  sf::Vector2f(10, 40), sf::Color::White);

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

        // Drawables
        window.draw(button);
        window.draw(text);
        window.draw(altText);

        window.display();
    }
    return 0;
}