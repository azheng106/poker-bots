#include "CardSprite.h"

CardSprite::CardSprite(int value, char suit, sf::Vector2f position, sf::Vector2f size) : size(size) {
    // Initialize fonts
    if (!regularFont.loadFromFile(string(BASE_PATH) + "fonts/RobotoMono-Regular.ttf")) {
        cout << "Font loading error\n";
    }
    if (!boldFont.loadFromFile(string(BASE_PATH) + "fonts/RobotoMono-Bold.ttf")) {
        cout << "Font loading error\n";
    }

    cardValue = to_string(value);
    cardSuit = suit;

    // Load suit texture
    string suitTextureFile = string(BASE_PATH) + "img/" + cardSuit + ".png";
    if (!suitTexture.loadFromFile(suitTextureFile)) {
        cout << "Failed to load suit texture\n";
    }
    suitSprite.setTexture(suitTexture);

    // Scale suit sprite to 60px
    suitSprite.setScale((size.x/2) / suitSprite.getLocalBounds().width, (size.x/2) / suitSprite.getLocalBounds().width);

    // Load card background texture
    string cardBackgroundFile = string(BASE_PATH) + "img/bg.png";
    if (!backgroundTexture.loadFromFile(cardBackgroundFile)) {
        cout << "Failed to load card background texture\n";
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Scale card background to 120x150px
    // 120, 150
    backgroundSprite.setScale(size.x / backgroundTexture.getSize().x, size.y / backgroundTexture.getSize().y);

    cardText.setFont(boldFont);
    cardText.setCharacterSize(size.x / 3);

    // Change text color to suit color
    switch (suit) {
        case 'c':
            cardText.setFillColor(sf::Color(0, 136, 0));
            break;
        case 'd':
            cardText.setFillColor(sf::Color(0, 81, 216));
            break;
        case 'h':
            cardText.setFillColor(sf::Color::Red);
            break;
        case 's':
            cardText.setFillColor(sf::Color::Black);
            break;
    }
    updateCard();
    setPosition(position);
}

void CardSprite::setPosition(sf::Vector2f position) {
    backgroundSprite.setPosition(position);
    suitSprite.setPosition(position.x + (size.x/4), position.y + (size.y/3));
    cardText.setPosition(position.x + (size.x/8), position.y + (size.y/30));
}

void CardSprite::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);
    window.draw(suitSprite);
    window.draw(cardText);
}

void CardSprite::updateCard() {
    if (cardValue == "11") cardValue = "J";
    else if (cardValue == "12") cardValue = "Q";
    else if (cardValue == "13") cardValue = "K";
    else if (cardValue == "14") cardValue = "A";

    cardText.setString(cardValue);
}
