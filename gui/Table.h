#pragma once

#include "../game/Card.h"
#include "../game/Player.h"
#include "../gui/Text.h"

#include <cmath>
#include <vector>

class Table {
public:
    Table(sf::Vector2f size, sf::Vector2f position, vector<Card>& communityCards, vector<Player>& players, int& pot);

    sf::Vector2f size;
    sf::Vector2f position;

    sf::Font regularFont;
    sf::Font boldFont;

    sf::RectangleShape tableCenter;
    sf::CircleShape leftSemiCircle;
    sf::CircleShape rightSemiCircle;

    Text* potDisplay;
    sf::RectangleShape potBorder;
    sf::RectangleShape ccBorder;

    // Game Objects
    vector<Player>& players;
    vector<Card>& communityCards;
    int& pot;

    void addCommunityCards();
    void draw(sf::RenderWindow& window);
    void drawPlayers(sf::RenderWindow& window);
    void drawPlayer(sf::RenderWindow& window, Player& player, float posX, float posY, float horizontalMargin, sf::Font& regularFont, sf::Font& boldFont, sf::Vector2f size, string dirrBet, bool inverted=false);

    // File Paths
    static constexpr const char* BASE_PATH = "../../../";
};
