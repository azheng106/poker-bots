#pragma once

#include "../game/Card.h"
#include "../game/Player.h"
#include "../gui/Text.h"

#include <cmath>
#include <vector>

class Table {
public:
    Table(sf::Vector2f size, sf::Vector2f position, vector<Card>& communityCards, vector<Player>& players);

    sf::Vector2f size;
    sf::Vector2f position;

    sf::Font regularFont;
    sf::Font boldFont;

    sf::RectangleShape tableCenter;
    sf::CircleShape leftSemiCircle;
    sf::CircleShape rightSemiCircle;

    vector<Card>& communityCards;
    sf::RectangleShape ccBorder;

    vector<Player>& players;

    void addCommunityCards();
    void draw(sf::RenderWindow& window);
    void drawPlayers(sf::RenderWindow& window);

    // File Paths
    static constexpr const char* BASE_PATH = "../../../";
};
