#include "Table.h"

Table::Table(sf::Vector2f size, sf::Vector2f position, vector<Card>& communityCards, vector<Player>& players, int& roundPot, int& pot) : size(size), position(position), communityCards(communityCards), players(players), roundPot(roundPot), pot(pot) {
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

    // Display total pot
    totalPotDisplay = new Text("$" + to_string(pot), boldFont, 20, sf::Vector2f(position.x, position.y - (size.y / 4)), sf::Color::White);

    // Display roundPot
    roundPotDisplay = new Text("$" + to_string(roundPot), boldFont, 24, sf::Vector2f(position.x, position.y - (size.y / 8)), sf::Color::White);

    // Highlight around total pot display
    totalPotBorder.setSize(sf::Vector2f(size.x / 3.0, size.y / 8));
    totalPotBorder.setFillColor(sf::Color(0, 60, 0));
    totalPotBorder.setOrigin(totalPotBorder.getSize().x / 2, totalPotBorder.getSize().y / 2);
    totalPotBorder.setPosition(position.x, position.y - (size.y / 4));

    // Highlight around roundPot display
    roundPotBorder.setSize(sf::Vector2f(size.x / 2.0, size.y / 6));
    roundPotBorder.setFillColor(sf::Color(0, 80, 0));
    roundPotBorder.setOrigin(roundPotBorder.getSize().x / 2, roundPotBorder.getSize().y / 2);
    roundPotBorder.setPosition(position.x, position.y - (size.y / 8));

    // Border around community cards area
    ccBorder.setSize(sf::Vector2f(size.x/1.5, size.y/4));
    ccBorder.setOutlineThickness(2.f);
    ccBorder.setOutlineColor(sf::Color::White);
    ccBorder.setFillColor(sf::Color::Transparent);
    ccBorder.setOrigin(ccBorder.getSize().x/2, ccBorder.getSize().y/2);
    ccBorder.setPosition(position.x, position.y + (size.y / 8));
}

void Table::addCommunityCards() {
    float horizontalMargin = 5;
    float verticalMargin = 5;

    float cardWidth = ((size.x/1.5) - (6 * horizontalMargin)) / 5;
    float cardHeight = (size.y / 4) - (2 * verticalMargin);

    float posX = position.x - (2 * cardWidth) - (2 * horizontalMargin);
    float posY = position.y + (size.y / 8);

    for (Card& card : communityCards) {
        card.sprite->setPosition(sf::Vector2f(posX, posY));
        card.sprite->setSize(sf::Vector2f(cardWidth, cardHeight));
        posX += cardWidth + horizontalMargin;
    }
}

void Table::updatePots() {
    totalPotDisplay->text.setString("$" + to_string(pot));
    totalPotDisplay->updateOrigin();

    roundPotDisplay->text.setString("$" + to_string(roundPot));
    roundPotDisplay->updateOrigin();
}

void Table::draw(sf::RenderWindow& window) {
    addCommunityCards();

    window.draw(tableCenter);
    window.draw(leftSemiCircle);
    window.draw(rightSemiCircle);
    window.draw(roundPotBorder);
    window.draw(totalPotBorder);
    window.draw(ccBorder);

    updatePots();
    roundPotDisplay->draw(window);
    totalPotDisplay->draw(window);

    for (Card& card : communityCards) {
        card.sprite->draw(window);
    }
}

void Table::drawPlayers(sf::RenderWindow& window) {
    float horizontalMargin = 5;
    float posX, posY;

    // eyeballing with:
        // Size: (500, 350), Position: (600, 360)

    // Draw 3 players on the bottom of the rectangle
    posX = position.x - (size.x / 2.5);
    posY = position.y + (size.y / 1.8);
    for (int i = 0; i < 3 && i < players.size(); i++) {
        drawPlayer(window, players[i], posX, posY, horizontalMargin, regularFont, boldFont, size, "up");

        posX += (size.x / 2.5);
    }

    posX += (size.x / 6.5);
    posY -= (size.y / 3.2);
    // Draw 2 players on the right semicircle
    for (int i = 3; i < 5 && i < players.size(); i++) {
        drawPlayer(window, players[i], posX, posY, horizontalMargin, regularFont, boldFont, size, "left");
        posY -= (size.y / 2.0);
    }

    // Draw 3 players on the top of the rectangle
    posX = position.x + (size.x / 2.5);
    posY = position.y - (size.y / 1.3);
    for (int i = 5; i < 8 && i < players.size(); i++) {
        drawPlayer(window, players[i], posX, posY, horizontalMargin, regularFont, boldFont, size, "down",true);
        posX -= (size.x / 2.5);
    }

    posX -= (size.x / 6.5);
    posY += (size.y / 1.9);
    // Draw 2 players on the left semicircle
    for (int i = 8; i < 10 && i < players.size(); i++) {
        drawPlayer(window, players[i], posX, posY, horizontalMargin, regularFont, boldFont, size, "right");
        posY += (size.y / 2.0);
    }
}

void Table::drawPlayer(sf::RenderWindow& window, Player& player, float posX, float posY, float horizontalMargin, sf::Font& regularFont, sf::Font& boldFont, sf::Vector2f size, string dirrBet, bool inverted) {
    string name = player.name;
    string money = to_string(player.money);

    // Draw player's name and money
    Text nameLabel(name, regularFont, 18, sf::Vector2f(posX, posY + (size.y / 5)));
    Text moneyLabel("\n$" + money, boldFont, 18, sf::Vector2f(posX, posY + (size.y / 12)));

    // Draw player's hole cards
    Card& card1 = player.holeCards[0];
    Card& card2 = player.holeCards[1];

    card1.sprite->setSize(sf::Vector2f(60, 72));
    card2.sprite->setSize(sf::Vector2f(60, 72));

    if (!inverted) {
        card1.sprite->setPosition(sf::Vector2f(posX - (card1.sprite->size.x / 2) - (horizontalMargin / 2), posY));
        card2.sprite->setPosition(sf::Vector2f(posX + (card2.sprite->size.x / 2) + (horizontalMargin / 2), posY));
    } else {
        card1.sprite->setPosition(sf::Vector2f(posX - (card1.sprite->size.x / 2) - (horizontalMargin / 2), posY + (size.y / 4.8)));
        card2.sprite->setPosition(sf::Vector2f(posX + (card2.sprite->size.x / 2) + (horizontalMargin / 2), posY + (size.y / 4.8)));

        nameLabel.text.setPosition(sf::Vector2f(posX, posY - (size.y / 24)));
        moneyLabel.text.setPosition(sf::Vector2f(posX, posY - (size.y / 24)));
    }

    // Draw player bet based on direction it should be displayed, assumes down direction is already inverted
    Text currentBetLabel("$" + to_string(player.currentBet), boldFont, 18, sf::Vector2f(posX, posY), sf::Color::White);
    currentBetLabel.updateOrigin();

    if (!player.currentBet) currentBetLabel.text.setString("");

    // Allow for it to also display status, such as Check or All In
    if (player.hasChecked && player.currentBet == 0) {
        currentBetLabel.text.setString("check");
        currentBetLabel.updateOrigin();
    }
    if (player.isAllIn) {
        currentBetLabel.text.setString("all in, $" + to_string(player.allInAmount));
        currentBetLabel.updateOrigin();
    }

    if (dirrBet == "up") {
        currentBetLabel.text.setPosition(sf::Vector2f(posX, posY - (size.y / 5.4)));
    } else if (dirrBet == "down") {
        currentBetLabel.text.setPosition(sf::Vector2f(posX, posY + (size.y / 2.6)));
    } else if (dirrBet == "left") {
        currentBetLabel.text.setPosition(sf::Vector2f(posX - (size.x / 4), posY));
    } else if (dirrBet == "right") {
        currentBetLabel.text.setPosition(sf::Vector2f(posX + (size.x / 4), posY));
    }

    // Highlight elements if it's the player's turn
    if (player.highlight) {
        card1.sprite->highlight = true;
        card2.sprite->highlight = true;

        nameLabel.text.setFillColor(player.highlightColor);
        moneyLabel.text.setFillColor(player.highlightColor);
    }

    // Only draw the cards if the player hasn't folded
    if (player.isIn) {
        currentBetLabel.draw(window);

        card1.sprite->draw(window);
        card2.sprite->draw(window);
    } else {
        nameLabel.text.setFillColor(sf::Color(100, 100, 100));
        moneyLabel.text.setFillColor(sf::Color(100, 100, 100));
    }

    nameLabel.draw(window);
    moneyLabel.draw(window);
}