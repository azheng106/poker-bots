#include "TriButton.h"

TriButton::TriButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, float angle) {
    float halfWidth = size.x / 2.f;
    float halfHeight = size.y / 2.f;

    // Define triangle points
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0, -halfHeight)); // Top vertex
    triangle.setPoint(1, sf::Vector2f(-halfWidth, halfHeight)); // Bottom left vertex
    triangle.setPoint(2, sf::Vector2f(halfWidth, halfHeight)); // Bottom right vertex

    // Set position and color
    triangle.setPosition(position);
    triangle.setFillColor(color);
    triangle.setOutlineColor(sf::Color::Black); // Optional: Add an outline color
    triangle.setOutlineThickness(2.f); // Optional: Add outline thickness

    // Store the original color for resetting
    originalButtonColor = color;

    // Rotate the triangle around its center
    triangle.setRotation(angle);
}

bool TriButton::isMouseOver(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f coords = window.mapPixelToCoords(mousePos);

    // Get the global bounds of the triangle, accounting for rotation
    sf::FloatRect buttonBounds = triangle.getGlobalBounds();
    return buttonBounds.contains(coords);
}

bool TriButton::isClicked(sf::RenderWindow& window, sf::Event& event) {
    sf::Color clickedColor = Misc::adjustColorBrightness(triangle.getFillColor(), -100);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isMouseOver(window)) {
            // Change button color to a slightly darker shade
            triangle.setFillColor(clickedColor);
            isButtonPressed = true;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (isButtonPressed) {
            isButtonPressed = false;
            triangle.setFillColor(originalButtonColor);

            if (isMouseOver(window)) {
                return true;
            }
        }
    }
    return false;
}

void TriButton::draw(sf::RenderWindow& window) {
    window.draw(triangle);
}
