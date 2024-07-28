#include "TextBox.h"

TextBox::TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font, int characterSize, sf::Color color, sf::Color textColor) {
    isActive = false;
    textIsValid = true;

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

/**
 * Changes outline color when user clicks on it, and allows user to type in the box.
 */
void TextBox::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mouse(event.mouseButton.x, event.mouseButton.y);
        if (box.getGlobalBounds().contains(mouse)) {
            isActive = true;
            box.setOutlineColor(highlightColor);
        } else {
            isActive = false;
            box.setOutlineColor(outlineColor);
        }
    }

    if (isActive && event.type == sf::Event::TextEntered) {
        // unicode 8 = backspace
        if (event.text.unicode == 8 && !text.getString().isEmpty()) {
            string str = text.getString();
            str.pop_back();
            text.setString(str);
            updateTextPosition();
        } else if (event.text.unicode < 128 && event.text.unicode != 8) {
            text.setString(text.getString() + static_cast<char>(event.text.unicode));
            updateTextPosition();
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

    // Center the text within the box
    text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
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
