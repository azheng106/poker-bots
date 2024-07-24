#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size, sf::Color color, Text text) {
        // Set up the button shape
        button.setSize(size);
        button.setPosition(position);
        button.setFillColor(color);

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

sf::Color Button::adjustColorBrightness(const sf::Color& color, int delta) {
    int red = max(0, color.r + delta);
    int green = max(0, color.g + delta);
    int blue = max(0, color.b + delta);

    return sf::Color(red, green, blue);
}

bool Button::isMouseOverButton(sf::RectangleShape& button, sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f coords = window.mapPixelToCoords(mousePos);
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(coords);
}

bool Button::buttonClicked(sf::RectangleShape& button, sf::RenderWindow& window, sf::Event& event) {
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

void Button::draw(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(buttonText);
}

