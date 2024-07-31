#include "Table.h"

Table::Table(sf::Vector2f size, sf::Vector2f position, vector<Card>& communityCards, vector<Player>& players) : size(size), position(position), communityCards(communityCards), players(players) {
    if (!regularFont.loadFromFile(string(BASE_PATH) + "fonts/Kanit-Regular.ttf")) {
        cout << "Font loading error\n";
    }
    if (!boldFont.loadFromFile(string(BASE_PATH) + "fonts/Kanit-Bold.ttf")) {
        cout << "Font loading error\n";
    }

    // Rectangular center
    tableCenter.setSize(size);
    tableCenter.setFillColor(sf::Color(0, 100, 0)); // green
    tableCenter.setOrigin(size.x/2, size.y/2);
    tableCenter.setPosition(position);

    // Left "semicircle"; a circle that has half covered by the rectangular center
    leftSemiCircle.setRadius(size.y/2);
    leftSemiCircle.setPointCount(100);
    leftSemiCircle.setFillColor(sf::Color(0, 100, 0));
    leftSemiCircle.setOrigin(size.y/2, size.y/2);
    leftSemiCircle.setPosition(position.x - size.x/2, position.y);
    leftSemiCircle.setRotation(90);

    // Right "semicircle"
    rightSemiCircle.setRadius(size.y/2);
    rightSemiCircle.setPointCount(100);
    rightSemiCircle.setFillColor(sf::Color(0, 100, 0));
    rightSemiCircle.setOrigin(size.y/2, size.y/2);
    rightSemiCircle.setPosition(position.x + size.x/2, position.y);
    rightSemiCircle.setRotation(270);

    // Border around community cards area
    ccBorder.setSize(sf::Vector2f(size.x/1.5, size.y/4));
    ccBorder.setOutlineThickness(2.f);
    ccBorder.setOutlineColor(sf::Color::White);
    ccBorder.setFillColor(sf::Color::Transparent);
    ccBorder.setOrigin(ccBorder.getSize().x/2, ccBorder.getSize().y/2);
    ccBorder.setPosition(position);
}

void Table::addCommunityCards() {
    float horizontalMargin = 5;
    float verticalMargin = 5;

    float cardWidth = ((size.x/1.5) - (6 * horizontalMargin)) / 5;
    float cardHeight = (size.y / 4) - (2 * verticalMargin);

    float posX = position.x - (2 * cardWidth) - (2 * horizontalMargin);
    float posY = position.y;

    for (Card& card : communityCards) {
        card.sprite->setPosition(sf::Vector2f(posX, posY));
        card.sprite->setSize(sf::Vector2f(cardWidth, cardHeight));
        posX += cardWidth + horizontalMargin;
    }
}

void Table::draw(sf::RenderWindow& window) {
    addCommunityCards();

    window.draw(tableCenter);
    window.draw(leftSemiCircle);
    window.draw(rightSemiCircle);
    window.draw(ccBorder);

    for (Card& card : communityCards) {
        card.sprite->draw(window);
    }
}

void Table::drawPlayers(sf::RenderWindow& window) {
    float horizontalMargin = 5;

    /*
     * 2 Players on bottom of rectangle:
     * - Money and name are displayed beside the hole cards
     */
    float posX = position.x - (size.x / 5.0); // work in progress
    float posY = position.y + (size.y / 1.6);

    for (int i = 0; i <= 1 && i < players.size(); i++) {
        Player& player = players[i];
        string name = player.name;
        string money = to_string(player.money);

        // Draw player's hole cards
        Card& card1 = player.holeCards[0];
        Card& card2 = player.holeCards[1];

        card1.sprite->setSize(sf::Vector2f(60, 72));
        card2.sprite->setSize(sf::Vector2f(60, 72));

        card1.sprite->setPosition(sf::Vector2f(posX - (card1.sprite->size.x / 2) - (horizontalMargin / 2), posY));
        card2.sprite->setPosition(sf::Vector2f(posX + (card2.sprite->size.x / 2) + (horizontalMargin / 2), posY));

        card1.sprite->draw(window);
        card2.sprite->draw(window);

        // Draw player's name and money
        Text nameLabel(name, regularFont, 18, sf::Vector2f(posX, posY + (size.y / 4)), sf::Color::White);
        Text moneyLabel("\n$" + money, boldFont, 24, sf::Vector2f(posX, posY + (size.y / 12)), sf::Color::White);

        nameLabel.draw(window);
        moneyLabel.draw(window);

        posX += (size.x / 2.5);
    }
}