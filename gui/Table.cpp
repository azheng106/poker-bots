#include "Table.h"

Table::Table(sf::Vector2f size, sf::Vector2f position, vector<Card>& communityCards) : size(size), position(position), communityCards(communityCards) {
    // READ THIS!
    /*
     * sf::Vector2f size refers to the size of the rectangular center. The actual rectangular bounds are much bigger
     * For the size, x=y provides the best card sprites, i.e. size = sf::Vector2f(300, 300)
     */

    if (!fancyFont.loadFromFile(string(BASE_PATH) + "fonts/Kanit-Regular.ttf")) {
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
    ccBorder.setSize(sf::Vector2f(size.x, size.y/4));
    ccBorder.setOutlineThickness(2.f);
    ccBorder.setOutlineColor(sf::Color::White);
    ccBorder.setFillColor(sf::Color::Transparent);
    ccBorder.setOrigin(ccBorder.getSize().x/2, ccBorder.getSize().y/2);
    ccBorder.setPosition(position);

    addCommunityCards();
}

void Table::addCommunityCards() {
    float horizontalMargin = 5;
    float verticalMargin = 5;

    float cardWidth = (size.x - (6 * horizontalMargin)) / 5;
    float cardHeight = (size.y / 4) - (2 * verticalMargin);

    float posX = position.x - (2 * cardWidth) - (2 * horizontalMargin);
    float posY = position.y;

    for (Card& card : communityCards) {
        card.generateSprite(fancyFont, sf::Vector2f(posX, posY), sf::Vector2f(cardWidth, cardHeight));
        posX += cardWidth + horizontalMargin;
    }
}

void Table::draw(sf::RenderWindow& window) {
    window.draw(tableCenter);
    window.draw(leftSemiCircle);
    window.draw(rightSemiCircle);
    window.draw(ccBorder);

    for (Card& card : communityCards) {
        card.sprite->draw(window);
    }
}
