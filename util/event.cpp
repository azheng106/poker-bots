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

/**
 * Handles button events
 */
bool buttonClicked(sf::RectangleShape& button, sf::RenderWindow& window, sf::Event& event) {
    static bool isButtonPressed = false;
    static sf::Color originalColor = button.getFillColor();

    sf::Color clickedColor = adjustColorBrightness(originalColor, -100);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isMouseOverButton(button, window)) {
            // Change button color to a slightly darker shade
            button.setFillColor(clickedColor);
            isButtonPressed = true;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (isButtonPressed) {
            isButtonPressed = false;
            button.setFillColor(originalColor);

            if (isMouseOverButton(button, window)) {
                return true;  // Button clicked
            }
        }
    }
    return false;
}