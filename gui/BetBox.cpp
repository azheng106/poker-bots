#include "BetBox.h"

BetBox::BetBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font, int* bigBlindAmt) : position(position), size(size), confirmed(false), bigBlindAmt(bigBlindAmt) {
    int largeFontSize = 24;
    int smallFontSize = 18;
    mainBox = new TextBox(position, size, font, largeFontSize, sf::Color::Transparent, sf::Color::White, true);

    confirmationLabel = new sf::Text;
    confirmationLabel->setFillColor(sf::Color::White);
    confirmationLabel->setFont(font);
    confirmationLabel->setCharacterSize(smallFontSize);
    confirmationLabel->setString("Confirm");

    label_s2 = new sf::Text;
    label_s2->setFillColor(sf::Color::White);
    label_s2->setFont(font);
    label_s2->setCharacterSize(smallFontSize);
    label_s2->setString("-2");

    label_s1 = new sf::Text;
    label_s1->setFillColor(sf::Color::White);
    label_s1->setFont(font);
    label_s1->setCharacterSize(smallFontSize);
    label_s1->setString("-1");

    label_a1 = new sf::Text;
    label_a1->setFillColor(sf::Color::White);
    label_a1->setFont(font);
    label_a1->setCharacterSize(smallFontSize);
    label_a1->setString("+1");

    label_a2 = new sf::Text;
    label_a2->setFillColor(sf::Color::White);
    label_a2->setFont(font);
    label_a2->setCharacterSize(smallFontSize);
    label_a2->setString("+2");

    float margin = size.x / 24;
    sf::Vector2f buttonSize = sf::Vector2f((size.x - (4 * margin)) / 6, size.y / 2);

    confirmation = new RecButton(sf::Vector2f(position.x, position.y - (size.y / 2) - (buttonSize.y / 2) - margin), sf::Vector2f(buttonSize.x * 2, buttonSize.y), sf::Color::Transparent, sf::Color::White, *confirmationLabel);

    s2 = new RecButton(sf::Vector2f(position.x - (size.x / 2) + (buttonSize.x * 0.5), position.y - (size.y / 2) - (buttonSize.y / 2) - margin), buttonSize, sf::Color::Transparent, sf::Color::White, *label_s2);
    s1 = new RecButton(sf::Vector2f(position.x - (size.x / 2) + (buttonSize.x * 1.5) + margin, position.y - (size.y / 2) - (buttonSize.y / 2) - margin), buttonSize, sf::Color::Transparent, sf::Color::White, *label_s1);

    a1 = new RecButton(sf::Vector2f(position.x + (size.x / 2) - (buttonSize.x * 1.5) - margin, position.y - (size.y / 2) - (buttonSize.y / 2) - margin), buttonSize, sf::Color::Transparent, sf::Color::White, *label_a1);
    a2 = new RecButton(sf::Vector2f(position.x + (size.x / 2) - (buttonSize.x * 0.5), position.y - (size.y / 2) - (buttonSize.y / 2) - margin), buttonSize, sf::Color::Transparent, sf::Color::White, *label_a2);
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

    if (s2->isClicked(window, event)) {
        betAmount -= 2 * *bigBlindAmt;
        mainBox->setString(to_string(betAmount));
    }
    if (s1->isClicked(window, event)) {
        betAmount -= *bigBlindAmt;
        mainBox->setString(to_string(betAmount));
    }
    if (a1->isClicked(window, event)) {
        betAmount += *bigBlindAmt;
        mainBox->setString(to_string(betAmount));
    }
    if (a2->isClicked(window, event)) {
        betAmount += 2 * *bigBlindAmt;
        mainBox->setString(to_string(betAmount));
    }
    updateBet();
}

void BetBox::draw(sf::RenderWindow& window) {
    mainBox->draw(window);

    confirmation->draw(window);
    s2->draw(window);
    s1->draw(window);
    a1->draw(window);
    a2->draw(window);
}