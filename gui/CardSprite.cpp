#include "CardSprite.h"

CardSprite::CardSprite(int value, char suit, sf::Font& textFont, sf::Vector2f position, sf::Vector2f size) : size(size), fancyFont(textFont) {
    cardValue = std::to_string(value);
    cardSuit = suit;

    // Load card background texture
    string cardBackgroundFile = std::string(BASE_PATH) + "img/" + cardSuit + ".png";
    if (!backgroundTexture.loadFromFile(cardBackgroundFile)) {
        std::cout << "Failed to load card background texture\n";
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Scale card background
    backgroundSprite.setScale(size.x / backgroundTexture.getSize().x, size.y / backgroundTexture.getSize().y);

    // Set the origin to the center of the sprite
    backgroundSprite.setOrigin(backgroundTexture.getSize().x / 2, backgroundTexture.getSize().y / 2);

    cardText.setFont(fancyFont);
    cardText.setCharacterSize(size.x / 2.5);
    cardText.setFillColor(sf::Color::White);

    updateCard();
    setPosition(position);
}

void CardSprite::setPosition(sf::Vector2f position) {
    backgroundSprite.setPosition(position);
    cardText.setPosition(position.x - (size.x/3), position.y - (size.y/2.2));
}

void CardSprite::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(cardText);
}

void CardSprite::updateCard() {
    if (cardValue == "11") cardValue = "J";
    else if (cardValue == "12") cardValue = "Q";
    else if (cardValue == "13") cardValue = "K";
    else if (cardValue == "14") cardValue = "A";

    cardText.setString(cardValue);
}
