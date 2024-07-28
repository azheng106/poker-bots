#include "TextBox.h"

TextBox::TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font, int characterSize, sf::Color color, sf::Color textColor, bool useNumbers) {
    isActive = false;
    textIsValid = true;
    numbersOnly = useNumbers;

    highlightColor = sf::Color::Blue;
    originalHighlightColor = highlightColor;

    box.setSize(size);
    box.setFillColor(color);

    outlineColor = sf::Color::Green;
    originalOutlineColor = outlineColor;
    box.setOutlineColor(outlineColor);

    box.setOutlineThickness(1.f);

    text.setFont(font);
    text.setCharacterSize(characterSize);
    text.setFillColor(textColor);
    text.setPosition(position);
    text.setString("");

    // Center position
    box.setOrigin(size.x / 2.0f, size.y / 2.0f);
    updateTextPosition();
    box.setPosition(position);
}

void TextBox::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
        if (box.getGlobalBounds().contains(mouse)) {
            isActive = true;
            // Clear the text box if the text was invalid
            if (!textIsValid) setString("");
            box.setOutlineColor(highlightColor);
        } else {
            isActive = false;
            // Inform of invalid text
            if (!textIsValid) setString("Invalid");
            box.setOutlineColor(outlineColor);
        }
    }

    if (isActive && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b' && !text.getString().isEmpty()) { // Backspace key
            string str = text.getString();
            str.pop_back();
            text.setString(str);
            updateTextPosition();
        } else if (event.text.unicode == '\r' || event.text.unicode == '\t' || event.text.unicode == '\n') {
            // Do nothing if user presses tab or enter key
        } else if (event.text.unicode < 128) {
            char enteredChar = static_cast<char>(event.text.unicode);
            // If only numbers are allowed, check if it is a digit (0-9)
            if (!numbersOnly || (enteredChar >= '0' && enteredChar <= '9')) {
                text.setString(text.getString() + enteredChar);
                updateTextPosition();
            }
        }
    }
}

void TextBox::draw(sf::RenderWindow& window) {
    if (!textIsValid && !isActive) {
        box.setOutlineColor(sf::Color::Red);
    } else if (isActive) {
        box.setOutlineColor(highlightColor);
    } else {
        box.setOutlineColor(originalOutlineColor);
    }

    window.draw(box);
    window.draw(text);
}

void TextBox::setString(std::string text) {
    this->text.setString(text);
    updateTextPosition();
}

std::string TextBox::getString() {
    return text.getString();
}

void TextBox::setPosition(sf::Vector2f position) {
    box.setPosition(position);
    text.setPosition(position);
    updateTextPosition();
}

void TextBox::setSize(sf::Vector2f size) {
    box.setSize(size);
    box.setOrigin(size.x / 2.0f, size.y / 2.0f);
    updateTextPosition();
}

void TextBox::updateTextPosition() {
    sf::FloatRect textBounds = text.getLocalBounds();
    sf::FloatRect boxBounds = box.getGlobalBounds();

    // Only change the x value of the origin for horizontal centering, 0.636 is finetuned for constant, centered y
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, text.getCharacterSize()*0.636);
    text.setPosition(boxBounds.left + boxBounds.width / 2.0f, boxBounds.top + boxBounds.height / 2.0f);
}


int TextBox::retrieveTextAsInt() {
    try {
        return stoi(text.getString().toAnsiString());
    } catch (invalid_argument) {
        return 0; // Return 0 if the string is not a valid integer
    } catch (out_of_range) {
        return 0; // Return 0 if the integer is out of range
    }
}
