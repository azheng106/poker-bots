#pragma once

#include <cmath>

#include "TextBox.h"
#include "RecButton.h"

class BetBox {
public:
    BetBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font);

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

    RecButton* d4;
    sf::Text* label_d4;

    RecButton* d2;
    sf::Text* label_d2;

    RecButton* x2;
    sf::Text* label_x2;

    RecButton* x4;
    sf::Text* label_x4;

    int updateBet();
    void handleEvent(sf::RenderWindow& window, sf::Event& event);
    void draw(sf::RenderWindow& window);
};
