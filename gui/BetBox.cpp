#include "BetBox.h"

BetBox::BetBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font) : position(position), size(size), confirmed(false) {
    int largeFontSize = 24;
    int smallFontSize = 18;
    mainBox = new TextBox(position, size, font, largeFontSize, sf::Color::Transparent, sf::Color::White, true);

    confirmationLabel = new sf::Text;
    confirmationLabel->setFillColor(sf::Color::White);
    confirmationLabel->setFont(font);
    confirmationLabel->setCharacterSize(smallFontSize);
    confirmationLabel->setString("Confirm");

    label_d4 = new sf::Text;
    label_d4->setFillColor(sf::Color::White);
    label_d4->setFont(font);
    label_d4->setCharacterSize(smallFontSize);
    label_d4->setString("D4");

    label_d2 = new sf::Text;
    label_d2->setFillColor(sf::Color::White);
    label_d2->setFont(font);
    label_d2->setCharacterSize(smallFontSize);
    label_d2->setString("D2");

    label_x2 = new sf::Text;
    label_x2->setFillColor(sf::Color::White);
    label_x2->setFont(font);
    label_x2->setCharacterSize(smallFontSize);
    label_x2->setString("M2");

    label_x4 = new sf::Text;
    label_x4->setFillColor(sf::Color::White);
    label_x4->setFont(font);
    label_x4->setCharacterSize(smallFontSize);
    label_x4->setString("M4");

    float margin = size.x / 24;
    sf::Vector2f buttonSize = sf::Vector2f((size.x - (4 * margin)) / 6, size.y / 2);

    confirmation = new RecButton(sf::Vector2f(position.x, position.y - (size.y / 2) - (buttonSize.y / 2) - margin), sf::Vector2f(buttonSize.x * 2, buttonSize.y), sf::Color::Transparent, sf::Color::White, *confirmationLabel);

    d4 = new RecButton(sf::Vector2f(position.x - (size.x / 2) + (buttonSize.x * 0.5), position.y - (size.y / 2) - (buttonSize.y / 2) - margin), buttonSize, sf::Color::Transparent, sf::Color::White, *label_d4);
    d2 = new RecButton(sf::Vector2f(position.x - (size.x / 2) + (buttonSize.x * 1.5) + margin, position.y - (size.y / 2) - (buttonSize.y / 2) - margin), buttonSize, sf::Color::Transparent, sf::Color::White, *label_d2);

    x2 = new RecButton(sf::Vector2f(position.x + (size.x / 2) - (buttonSize.x * 1.5) - margin, position.y - (size.y / 2) - (buttonSize.y / 2) - margin), buttonSize, sf::Color::Transparent, sf::Color::White, *label_x2);
    x4 = new RecButton(sf::Vector2f(position.x + (size.x / 2) - (buttonSize.x * 0.5), position.y - (size.y / 2) - (buttonSize.y / 2) - margin), buttonSize, sf::Color::Transparent, sf::Color::White, *label_x4);
}

int BetBox::updateBet() {
    betAmount = mainBox->retrieveTextAsInt();

    if (!mainBox->isActive) {
        if (betAmount > ceil) betAmount = ceil;
        if (betAmount < floor) betAmount = floor;
    }

    mainBox->setString(to_string(betAmount));
    return betAmount;
}

void BetBox::handleEvent(sf::RenderWindow& window, sf::Event& event) {
    mainBox->handleEvent(window, event);

    if (confirmation->isClicked(window, event)) {
        confirmed = true;
    }

    if (d4->isClicked(window, event)) {
        betAmount = round(float(betAmount) / 4);
        mainBox->setString(to_string(betAmount));
    }
    if (d2->isClicked(window, event)) {
        betAmount = round(float(betAmount) / 2);
        mainBox->setString(to_string(betAmount));
    }
    if (x2->isClicked(window, event)) {
        betAmount *= 2;
        mainBox->setString(to_string(betAmount));
    }
    if (x4->isClicked(window, event)) {
        betAmount *= 4;
        mainBox->setString(to_string(betAmount));
    }
    updateBet();
}

void BetBox::draw(sf::RenderWindow& window) {
    mainBox->draw(window);

    confirmation->draw(window);
    d4->draw(window);
    d2->draw(window);
    x2->draw(window);
    x4->draw(window);
}