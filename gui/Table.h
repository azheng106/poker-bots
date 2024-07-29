#pragma once

#include "../game/Card.h"

#include <vector>

class Table {
public:
    Table(sf::Vector2f size, sf::Vector2f position, vector<Card>& communityCards);

    sf::Vector2f size;
    sf::Vector2f position;

    sf::Font fancyFont;

    sf::RectangleShape tableCenter;
    sf::CircleShape leftSemiCircle;
    sf::CircleShape rightSemiCircle;

    vector<Card>& communityCards;
    sf::RectangleShape ccBorder;

    void addCommunityCards();
    void draw(sf::RenderWindow& window);

    // File Paths
    static constexpr const char* BASE_PATH = "../../../";
};
