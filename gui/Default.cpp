#include "Default.h"

// Used to access poker-bots resources from the .exe path
const string BASE_PATH = "../../../";

/**
 * Sets background and draws the version in the bottom right corner
 * @param window
 */
void Default::drawDefault(sf::RenderWindow& window) {
    sf::Font robotoMono;
    robotoMono.loadFromFile(BASE_PATH+"fonts/RobotoMono-Regular.ttf");

    Text version("poker-bots gui 1.0", robotoMono, 16, sf::Vector2f(600, 570), sf::Color::White);

    window.clear(sf::Color(0, 10, 30));
    version.draw(window);
}
