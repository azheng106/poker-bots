#include "Button.h"

/**
 * Constructor
 * @param position
 * @param size
 * @param color
 * @param text
 */
Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, sf::Color outlineColor, Text text) {
        // Set up the button shape
        button.setSize(size);
        button.setPosition(position);

        button.setFillColor(color);
        originalButtonColor = color;

        button.setOutlineColor(outlineColor);

        // Center the content in the button
        buttonText = text.content;
        sf::FloatRect textBounds = buttonText.getLocalBounds();

        // Set origin to the center of the content bounds
        buttonText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);

        // Calculate position
        float centerX = position.x + size.x / 2.f;
        float centerY = position.y + size.y / 2.f;

        // Adjust for baseline
        float baselineAdjustment = textBounds.top + textBounds.height;
        buttonText.setPosition(centerX, centerY - baselineAdjustment / 3.5f);
}

/**
 * Checks if the mouse is over a button
 * @param button
 * @param window
 */
bool Button::isMouseOver(sf::RenderWindow& window) {
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
bool Button::isClicked(sf::RenderWindow& window, sf::Event& event) {
    sf::Color clickedColor = Misc::adjustColorBrightness(originalButtonColor, -100);

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        if (isMouseOver(window)) {
            // Change button color to a slightly darker shade
            button.setFillColor(clickedColor);
            isButtonPressed = true;
        }
    }

    if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
        if (isButtonPressed) {
            isButtonPressed = false;
            button.setFillColor(originalButtonColor);

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
void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(buttonText);
}

