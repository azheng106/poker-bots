#include "RecButton.h"

/**
 * Constructor
 * @param position
 * @param size
 * @param color
 * @param text
 */
RecButton::RecButton(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Color outlineColor, sf::Text text) {
        // Set up the button shape
        button.setOrigin(size.x/2, size.y/2);
        button.setSize(size);
        button.setPosition(position);

        // Set colors
        button.setFillColor(color);
        button.setOutlineColor(outlineColor);
        button.setOutlineThickness(2.f);

        // Store the original color for resetting
        originalOutlineColor = outlineColor;

        // Center the content in the button
        buttonText = text;
        sf::FloatRect textBounds = buttonText.getLocalBounds();

        // Set origin to the center of the content bounds
        buttonText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);

        // Calculate position

        // Adjust for baseline
        float baselineAdjustment = textBounds.top + textBounds.height;
        buttonText.setPosition(position.x, position.y - baselineAdjustment / 3.5f);
}

void RecButton::updateTextPosition() {
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    sf::FloatRect buttonBounds = button.getGlobalBounds();

    // Only change the x value of the origin for horizontal centering, 0.636 is finetuned for constant, centered y
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, buttonText.getCharacterSize()*0.636);
    buttonText.setPosition(buttonBounds.left + buttonBounds.width / 2.0f, buttonBounds.top + buttonBounds.height / 2.0f);
}

/**
 * Checks if the mouse is over a button
 * @param button
 * @param window
 */
bool RecButton::isMouseOver(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f coords = window.mapPixelToCoords(mousePos);
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(coords);
}

/**
 * Handles button events, such as darkening on click
 * @param button
 * @param window
 * @param event
 */
bool RecButton::isClicked(sf::RenderWindow& window, sf::Event& event) {
    sf::Color clickedColor = sf::Color::Cyan;

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isMouseOver(window)) {
            // Change button color to a slightly darker shade
            button.setOutlineColor(clickedColor);
            isButtonPressed = true;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (isButtonPressed) {
            isButtonPressed = false;
            button.setOutlineColor(originalOutlineColor);

            if (isMouseOver(window)) {
                return true;
            }
        }
    }
    return false;
}

/**
 * Draws the button to the window
 * @param window
 */
void RecButton::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(buttonText);
}

