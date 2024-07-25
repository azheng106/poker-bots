#include "Default.h"

/**
 * Sets background and draws the version in the bottom right corner
 * @param window
 */
void Default::drawDefault(sf::RenderWindow& window) {
    Text version("poker-bots gui 1.0", 16, sf::Vector2f(600, 570), sf::Color::White);

    window.clear(sf::Color(0, 10, 30));
    version.draw(window);
}
