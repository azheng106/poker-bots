#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "game/Game.h"
#include "gui/Button.h"
#include "gui/Text.h"

using namespace std;

// Used to access poker-bots resources from the .exe path
const string BASE_PATH = "../../../";

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Poker Bots");

    // Create font
    sf::Font robotoMono;
    robotoMono.loadFromFile(BASE_PATH+"fonts/RobotoMono-Regular.ttf");

    // Create button
    Text buttonText("Don't Click", robotoMono, 26, sf::Vector2f(10, 10), sf::Color::White);
    Button button(sf::Vector2f(300, 275), sf::Vector2f(200, 50), sf::Color::Blue, buttonText);

    int counter = 0;

    while (window.isOpen()) {
        Text text(to_string(counter), robotoMono, 24, sf::Vector2f(300,100), sf::Color::White);

        sf::Event event{};
        while (window.pollEvent(event)) {
            // Window is being closed
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Button was clicked
            if (Button::buttonClicked(button.button, window, event)) {
                cout << "Button pressed\n";
            }
        }

        window.clear(sf::Color(0, 0, 30));

        // Drawables
        button.draw(window);
        text.draw(window);

        counter += 1;

        window.display();
    }
    return 0;
}