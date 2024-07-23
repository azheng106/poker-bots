#include <SFML/Graphics.hpp>

bool isMouseOverButton(sf::RectangleShape& button, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f cords = window.mapPixelToCoords(mousePos);
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(cords);
}