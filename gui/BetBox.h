#pragma once

#include <cmath>

#include "TextBox.h"
#include "RecButton.h"

class BetBox {
public:
    BetBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font, int* bigBlindAmt);

    // OK button pressed
    bool confirmed;

    // Used to control valid input
    int ceil;
    int floor;

    sf::Vector2f position;
    sf::Vector2f size;

    TextBox* mainBox;
    int betAmount;

    RecButton* confirmation;
    sf::Text* confirmationLabel;

    RecButton* s2;
    sf::Text* label_s2;

    RecButton* s1;
    sf::Text* label_s1;

    RecButton* a1;
    sf::Text* label_a1;

    RecButton* a2;
    sf::Text* label_a2;

    int* bigBlindAmt;

    int updateBet();
    void handleEvent(sf::RenderWindow& window, sf::Event& event);
    void draw(sf::RenderWindow& window);
};
