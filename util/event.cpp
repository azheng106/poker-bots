#include "SFML/Graphics.hpp"

using namespace std;

/**
 * Checks if a mouse is over a button, wow!
 * @param button sf::RecntangleShape&; the actual button
 * @param window sf::RenderWindow&; the window the button is in
 */
bool isMouseOverButton(sf::RectangleShape& button, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f coords = window.mapPixelToCoords(mousePos);
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(coords);
}