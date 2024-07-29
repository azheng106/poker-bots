#include "Game.h"

Game::Game() {
    initVariables();
    initWindow();
    initFont();
    initRender();
    initBasicUI();
    initSetupPlayersUI();
    initDeckTest();
    initTableTest();
}

Game::~Game() {
    delete window;
}

void Game::initVariables() {
    currentState = GameState::BASIC_SETUP;
    isFinished = false;
    round = 0;
    currentPlayerIndex = 0;
    shuffleDeck();
}

void Game::initWindow() {
    int windowWidth = 1200;
    int windowHeight = 800;

    window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Poker Bots");
    window->setVerticalSyncEnabled(true); // Limit FPS to refresh rate
}

void Game::initRender() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;

    window->clear(sf::Color(0, 0, 30));
    Text loadingLabel("Loading assets", regularFont, 36, Misc::percentageToPixels(sf::Vector2f(50, 50), *window));
    loadingLabel.draw(*window);
    window->display();
}

void Game::initFont() {
    if (!regularFont.loadFromFile(string(BASE_PATH) + "fonts/RobotoMono-Regular.ttf")) {
        cout << "Font loading error\n";
    }
    if (!boldFont.loadFromFile(string(BASE_PATH) + "fonts/RobotoMono-Bold.ttf")) {
        cout << "Font loading error\n";
    }
    if (!fancyFont.loadFromFile(string(BASE_PATH) + "fonts/Kanit-Regular.ttf")) {
        cout << "Font loading error\n";
    }
}

void Game::initBasicUI() {
    // Application Text label at the top
    appText = new Text("sponsored by thebigblackdarren", regularFont, 16, Misc::percentageToPixels(sf::Vector2f(50, 4), *window));

    // Status Text label at the bottom, which is updated by updateStatusText() as the game progresses
    statusText = new Text("status text", regularFont, 16, Misc::percentageToPixels(sf::Vector2f(50, 96), *window));

    // # of Players
    numPlayers = 6;

    numPlayersLabel = new Text("Players", boldFont, 42,
                               Misc::percentageToPixels(sf::Vector2f(50, 15), *window));

    numPlayersBox = new TextBox(Misc::percentageToPixels(sf::Vector2f(50, 25), *window),
                                sf::Vector2f(200, 56), regularFont, 30, sf::Color::Transparent, sf::Color::White, true);

    numPlayersBox->setString(to_string(numPlayers));

    decreasePlayers = new TriButton(Misc::percentageToPixels(sf::Vector2f(35, 25), *window), sf::Vector2f(70, 60),
                                    sf::Color::White, 270);
    increasePlayers = new TriButton(Misc::percentageToPixels(sf::Vector2f(65, 25), *window), sf::Vector2f(70, 60),
                                    sf::Color::White, 90);

    // Stash
    stash = 1000;

    stashTextBoxLabel = new Text("Stash", boldFont, 42, Misc::percentageToPixels(sf::Vector2f(50, 40), *window));

    stashTextBox = new TextBox(Misc::percentageToPixels(sf::Vector2f(50, 50), *window),
                               sf::Vector2f(200, 56), regularFont, 30, sf::Color::Transparent, sf::Color::White, true);

    stashTextBox->setString(to_string(stash));

    decreaseStash = new TriButton(Misc::percentageToPixels(sf::Vector2f(35, 50), *window), sf::Vector2f(70, 60),
                                  sf::Color::White, 270);
    increaseStash = new TriButton(Misc::percentageToPixels(sf::Vector2f(65, 50), *window), sf::Vector2f(70, 60),
                                  sf::Color::White, 90);

    // Big Blind
    bigBlindBet = 10;

    bigBlindBoxLabel = new Text("Big Blind", boldFont, 42, Misc::percentageToPixels(sf::Vector2f(50, 65), *window));

    bigBlindBox = new TextBox(Misc::percentageToPixels(sf::Vector2f(50, 75), *window),
                              sf::Vector2f(200, 56), regularFont, 30, sf::Color::Transparent, sf::Color::White, true);

    bigBlindBox->setString(to_string(bigBlindBet));

    decreaseBigBlind = new TriButton(Misc::percentageToPixels(sf::Vector2f(35, 75), *window), sf::Vector2f(70, 60),
                                       sf::Color::White, 270);

    increaseBigBlind = new TriButton(Misc::percentageToPixels(sf::Vector2f(65, 75), *window), sf::Vector2f(70, 60),
                                     sf::Color::White, 90);
}

void Game::initSetupPlayersUI() {
    currentPlayerIndex = 1;
    nameTextLabel = new Text("Player " + to_string(currentPlayerIndex) + " Name", boldFont, 42,
                             Misc::percentageToPixels(sf::Vector2f(50, 35), *window));
    nameTextBox = new TextBox(Misc::percentageToPixels(sf::Vector2f(50, 50), *window),
                              sf::Vector2f(300, 64), regularFont, 36,
                              sf::Color::Transparent, sf::Color::White);
}

void Game::initDeckTest() {
    int posX = 120;
    int posY = 180;

    for (Card& card : deck) {
        card.generateSprite(fancyFont, sf::Vector2f(posX, posY), sf::Vector2f(75, 90)); // Keep x : y ratio to 5 : 6
        posX += 85;
        if (posX >= window->getSize().x - 120) {
            posY += 100;
            posX = 120;
        }
    }
}

void Game::initTableTest() {
    // Players currently unused; will eventually help draw player seats
    table = new Table(sf::Vector2f(500, 500), Misc::percentageToPixels(sf::Vector2f(50, 50), *window), communityCards, players);
}

void Game::run() {
    while (window->isOpen()) {
        processEvents();
        update();
        updateStatusText();
        render();
    }
}

void Game::processEvents() {
    sf::Event event{};
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();

        switch (currentState) {
            case GameState::BASIC_SETUP:
                basicSetup(event);
                break;
            case GameState::SETUP_PLAYERS:
                setupPlayers(event);
                break;
            case GameState::SETUP_HAND:
                //TEMPORARY
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    currentState = GameState::PLAY_HAND;
                }
                break;
            case GameState::PLAY_HAND:
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    distributeCommunityCards();
                }
                break;
            case GameState::SHOWDOWN:
                break;
        }
    }
}

void Game::update() {
    switch (currentState) {
        case GameState::BASIC_SETUP:
            break;
        case GameState::SETUP_PLAYERS:
            break;
        case GameState::SETUP_HAND:
            break;
        case GameState::PLAY_HAND:
            break;
        case GameState::SHOWDOWN:
            break;
    }
}

void Game::updateStatusText() {
    string status;
    switch (currentState) {
        case GameState::BASIC_SETUP:
            status = "basic setup (press enter to continue)";
            break;
        case GameState::SETUP_PLAYERS:
            status = "setting up players (press enter to continue)";
            break;
        case GameState::SETUP_HAND:
            status = "showing deck test (press enter to continue)"; // FOR TESTING ONLY! normally displays "setting up hand"
            break;
        case GameState::PLAY_HAND:
            status = "showing table test (press enter to DISTRIBUTE)"; // FOR TESTING ONLY! normally displays "playing hand"
            break;
        case GameState::SHOWDOWN:
            status = "showdown";
            break;
    }
    statusText->text.setString(status);
    statusText->updateOrigin();
}

void Game::render() {
    window->clear(sf::Color(0, 0, 30));

    switch (currentState) {
        case GameState::BASIC_SETUP:
            numPlayersLabel->draw(*window);
            numPlayersBox->draw(*window);
            decreasePlayers->draw(*window);
            increasePlayers->draw(*window);

            stashTextBoxLabel->draw(*window);
            stashTextBox->draw(*window);
            decreaseStash->draw(*window);
            increaseStash->draw(*window);

            bigBlindBoxLabel->draw(*window);
            bigBlindBox->draw(*window);
            decreaseBigBlind->draw(*window);
            increaseBigBlind->draw(*window);
            break;
        case GameState::SETUP_PLAYERS:
            nameTextLabel->draw(*window);
            nameTextBox->draw(*window);
            break;
        case GameState::SETUP_HAND: {
            for (Card& card : deck) {
                card.sprite->draw(*window);
            }
            break;
        }
        case GameState::PLAY_HAND:
            // Testing purposes only to show table
            table->draw(*window);

            // Very buggy
            //table->drawPlayers(*window);

            // Testing end
            break;
        case GameState::SHOWDOWN:
            break;
    }
    appText->draw(*window);
    statusText->draw(*window);
    window->display();
}

/**
 * Generates a random number between a and b, inclusive; [a, b]
 */
int Game::randomInt(int a, int b) {
    random_device random;
    mt19937 gen(random());
    uniform_int_distribution<> dis(a, b);
    return dis(gen);
}

/**
 * Initialize players at the start of the game
 */
void Game::basicSetup(sf::Event& event) {
    // Number of Players Selection
    numPlayersBox->handleEvent(event);
    if (numPlayersBox->retrieveTextAsInt() >= 2 && numPlayersBox->retrieveTextAsInt() <= 10) {
        numPlayers = numPlayersBox->retrieveTextAsInt();
        numPlayersBox->textIsValid = true;
    } else {
        numPlayersBox->textIsValid = false;
    }

    if (decreasePlayers->isClicked(*window, event)) {
        numPlayers = max(2, numPlayers - 1);
        numPlayersBox->setString(to_string(numPlayers));
        numPlayersBox->textIsValid = true;
    }

    if (increasePlayers->isClicked(*window, event)) {
        numPlayers = min(10, numPlayers + 1);
        numPlayersBox->setString(to_string(numPlayers));
        numPlayersBox->textIsValid = true;
    }
    // Stash Selection
    stashTextBox->handleEvent(event);
    if (stashTextBox->retrieveTextAsInt() >= 1 && stashTextBox->retrieveTextAsInt() <= 1000000) {
        stash = stashTextBox->retrieveTextAsInt();
        stashTextBox->textIsValid = true;
    } else {
        stashTextBox->textIsValid = false;
    }

    if (decreaseStash->isClicked(*window, event)) {
        stash = max(1, stash - 100);
        stashTextBox->setString(to_string(stash));
        stashTextBox->textIsValid = true;
    }

    if (increaseStash->isClicked(*window, event)) {
        stash = min(1000000, stash + 100);
        stashTextBox->setString(to_string(stash));
        stashTextBox->textIsValid = true;
    }

    // Big Blind Bet
    bigBlindBox->handleEvent(event);
    if (bigBlindBox->retrieveTextAsInt() >= 1 && bigBlindBox->retrieveTextAsInt() <= stash) {
        bigBlindBet = bigBlindBox->retrieveTextAsInt();
        bigBlindBox->textIsValid = true;
    } else {
        bigBlindBox->textIsValid = false;
    }

    if (decreaseBigBlind->isClicked(*window, event)) {
        bigBlindBet = max(1, bigBlindBet - 10);
        bigBlindBox->setString(to_string(bigBlindBet));
        bigBlindBox->textIsValid = true;
    }

    if (increaseBigBlind->isClicked(*window, event)) {
        bigBlindBet = min(stash, bigBlindBet + 10);
        bigBlindBox->setString(to_string(bigBlindBet));
        bigBlindBox->textIsValid = true;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        if (Misc::textBoxesValid({*numPlayersBox, *stashTextBox, *bigBlindBox})) {
            currentState = GameState::SETUP_PLAYERS;
            cout << "Basic Setup Complete\n";
            cout << "\t# of Players: " << numPlayers << "\n";
            cout << "\tStash: $" << stash << "\n";
            cout << "\tBig Blind: $" << bigBlindBet << "\n";
        } else {
            cout << "Some box(es) are invalid" << endl;
        }
    }
}

/**
 * Initialize setup player UI and handle events
 */
void Game::setupPlayers(sf::Event& event) {
    nameTextBox->handleEvent(event);
    string enteredName = nameTextBox->getString();

    // If the Enter key is pressed and the text box is not empty
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        if (!enteredName.empty()) {
            // Create a new player with the entered name
            Player player(currentPlayerIndex, stash, enteredName);
            players.push_back(player);

            // Move to the next player
            currentPlayerIndex++;
            nameTextLabel->text.setString("Player " + to_string(currentPlayerIndex) + " Name");

            // Clear the text box after each name entry
            nameTextBox->setString("");
        }
    }

    // Check if all players are processed
    if (currentPlayerIndex > numPlayers) {
        currentState = GameState::SETUP_HAND;
        cout << "Players Setup Complete" << endl;
        for (Player& player : players) {
            cout << "\t" << player.index << ". " << player.name << "\n";
        }
        initialDealerIndex = Game::randomInt(1, players.size());
        cout << "\tInitial Dealer Index: " << initialDealerIndex << "\n";
    }
}

/**
 * Create a new deck of cards
 */
void Game::shuffleDeck() {
    deck.clear();
    char suits[4] = {'c', 'd', 'h', 's'};
    // 11=J, 12=Q, 13=K, 14=A
    for (int i=2; i<=14; i++) {
        for (int j=0; j<=3; j++) {
            Card card(i, suits[j]);
            deck.push_back(card);
        }
    }
}

/**
 * Setup small and big blinds
 */
void Game::setupBlinds() {
    int dealerIndex = (initialDealerIndex + round - 1) % players.size();
    int smallBlindIndex = (dealerIndex + 1) % players.size();
    int bigBlindIndex = (smallBlindIndex + 1) % players.size();

    dealer = &players[dealerIndex];
    smallBlind = &players[smallBlindIndex];
    bigBlind = &players[bigBlindIndex];

    cout << "\nDealer is " << dealer->name << "\n";
    cout << "Small blind is " << smallBlind->name << "\n";
    cout << "Big blind is " << bigBlind->name << "\n\n";
}

/**
 * Distributes 2 cards to each player
 */
void Game::distributeHoleCards() {
    if (deck.empty()) {
        shuffleDeck();
    }

    for (Player& player : players) {
        player.holeCards.clear();
        for (int i = 0; i < 2; i++) {
            int drawnCardIndex = randomInt(0, deck.size() - 1);
            Card drawnCard = deck[drawnCardIndex];
            deck.erase(deck.begin() + drawnCardIndex);
            player.holeCards.push_back(drawnCard);
        }
    }

    // Debug usage
    for (Player& player : players) {
        cout << "Player " << player.name << " has hole cards: " << player.holeCards[0] << ", " << player.holeCards[1] << "\n";
    }
}

/**
 * Distributes community cards to the flop
 */
void Game::distributeCommunityCards() {
    int burnCard = Game::randomInt(0, deck.size()-1);
    deck.erase(deck.begin() + burnCard);
    cout << "\nBurn card discarded\n";
    if (communityCards.empty()) {
        for (int i=0; i<3; i++) {
            int drawnCardIndex = Game::randomInt(0, deck.size()-1);
            communityCards.push_back(deck[drawnCardIndex]);
            deck.erase(deck.begin() + drawnCardIndex);
        }
    } else if (communityCards.size() < 5)  {
        int drawnCardIndex = Game::randomInt(0, deck.size()-1);
        communityCards.push_back(deck[drawnCardIndex]);
        deck.erase(deck.begin() + drawnCardIndex);
    }

    cout << "\n";
    for (Card& card : communityCards) {
        cout << "Community Card: " << card << "\n";
    }
}

/*
 * Displays the pot value
 */
void Game::displayPot() {
    int tempPot = 0;
    for (Player& player : players) {
        tempPot += player.currentBet;
    }
    cout << "Pot is now worth $" << max(tempPot, pot) << "\n";
}

/*
 * Updates pot value at the end of the round, and sets all player current bets to 0
 */
void Game::calculatePot() {
    for (Player& player : players) {
        pot += player.currentBet;
        player.totalBet += player.currentBet;
        player.currentBet = 0;
    }
}

/*
 * Does small and big blind bets on turn 1
 */
void Game::doBlindBets() {
    int smallBlindBet = bigBlindBet / 2;

    if (smallBlind->money <= smallBlindBet) {
        smallBlind->isAllIn = true;
        cout << smallBlind->name << " is going all in to bet the small blind.\n";
    }

    cout << "Small blind " << smallBlind->name << " bets $" << smallBlindBet << "\n\n";
    smallBlind->currentBet += min(smallBlindBet, smallBlind->money);
    smallBlind->money -= min(smallBlindBet, smallBlind->money);

    if (bigBlind->money <= bigBlindBet) {
        bigBlind->isAllIn = true;
        cout << bigBlind->name << " is going all in to bet the big blind.\n";
    }

    cout << "Big blind " << bigBlind->name << " bets $" << bigBlindBet << "\n";
    bigBlind->currentBet += min(bigBlindBet, bigBlind->money);
    bigBlind->money -= min(bigBlindBet, bigBlind->money);

    hasOpened = true;
}

/*
 * Asks the player for what they will do
 */
void Game::getAction(Player& player) {
    // Heads up implementation
    if (playersBetting == 2) {
        isHeadsUp = true;
        cout << "Heads up" << "\n";
    }

    string action;
    bool validAction = false;

    while (!validAction) {
        cout << "\nPlayer " + player.name + "'s turn. You have $" << player.money << ". Your current bet is $"
        << player.currentBet << ". Type one option: ";

        // No bet has been made yet
        if (!hasOpened) {
            cout << "[Bet] [Check] [Fold]\n";
        } else if (!player.hasRaised || isHeadsUp) {
            cout << "[Raise] [Call ($" << currentMinBet << ")] [Fold]\n";
        } else {
            cout << "[Call ($" << currentMinBet << ")] [Fold]\n";
        }

        cin >> action;

        if (!hasOpened) {
            if (action == "bet") {
                validAction = player.bet(&currentMinBet);
                hasOpened = true;
            } else if (action == "check") {
                validAction = player.check();
            }
        } else {
            if (!player.hasRaised || isHeadsUp) {
                if (action == "raise") {
                    validAction = player.raise(&currentMinBet);
                } else if (action == "call") {
                    validAction = player.call(&currentMinBet);
                }
            } else {
                if (action == "call") {
                    validAction = player.call(&currentMinBet);
                }
            }
        }

        if (action == "fold") {
            validAction = player.fold();
        }

        if (!validAction) {
            cout << "Invalid option.\n";
        }
    }
    player.hasMadeAction = true;
}

/*
 * Returns true if le turn is over
 */
bool Game::isTurnOver() {
    bool isTurnOver = true;
    bool checkedAround = true;

    for (Player& player : players) {
        if (player.isIn && !player.isAllIn) {
            if (playersBetting == 1 && player.currentBet == currentMinBet) {
                skipToEnd = true;
            }
            if (player.currentBet != currentMinBet) {
                isTurnOver = false;
            }
            if (!player.hasMadeAction) {
                isTurnOver = false;
            }
            if (!player.hasChecked) {
                checkedAround = false;
            }
        }
    }

    if (checkedAround || skipToEnd) {
        return true;
    }

    return isTurnOver;
}

/*
 * Rewrite; plays a holeCards
 */
//void Game::playHand() {
//    reset();
//    if (isFinished) return;
//
//    // 3 betting rounds: pre-flop, turn, river
//    for (turn=1; turn<=3; turn++) {
//        currentMinBet = bigBlindBet;
//        hasOpened = false;
//
//        // Reset players
//        for (Player& player : players) {
//            player.currentBet = 0;
//            player.hasMadeAction = false;
//            player.hasRaised = false;
//            player.hasChecked = false;
//        }
//
//        switch (turn) {
//            case 1:
//                cout << "\nPre-flop\n\n";
//                doBlindBets();
//                break;
//            case 2:
//                cout << "\nNext round\n";
//                break;
//            case 3:
//                cout << "\nFinal round\n";
//                break;
//        }
//
//        int startingIndex;
//        if (turn == 1) startingIndex = (bigBlind->index + 1) % players.size();
//        else startingIndex = smallBlind->index % players.size();
//
//        for (int i=startingIndex; !isTurnOver(); i=(i+1) % players.size()) {
//            Player& player = players[i];
//            if (!player.isIn || player.isAllIn) continue;
//
//            playersFolded = 0;
//            playersBetting = 0;
//
//            for (Player& player : players) {
//                if (player.isIn && !player.isAllIn) {
//                    playersBetting += 1;
//                }
//                if (!player.isIn) {
//                    playersFolded += 1;
//                }
//            }
//            getAction(player);
//        }
//        displayPot();
//        calculatePot();
//        distributeCommunityCards();
//    }
//    showdown();
//}
//
//void Game::showdown() {
//    cout << "\nShowdown\n\n";
//    cout << "The pot is worth a beefy $" << pot << "\n\n";
//
//    vector<int> bestScore = {0};
//    vector<Card> bestHand;
//    vector<Player*> leadingPlayers;
//
//    for (Player& player : players) {
//        if (player.isIn) {
//            cout << "Player " << player.name << " has bet $" << player.totalBet << "\n";
//
//            player.bestScore = CardUtil::findBestScore(communityCards, player.holeCards);
//            player.bestHand = CardUtil::findBestHand(communityCards, player.holeCards);
//
//            // Debug usage
//            cout << "Score: {";
//            for (int i: player.bestScore) {
//                cout << i << ",";
//            }
//            cout << "}\n";
//
//            if (CardUtil::compareScores(player.bestScore, bestScore)) {
//                bestScore = player.bestScore;
//                leadingPlayers.clear();
//                leadingPlayers.push_back(&player);
//            } else if (player.bestScore == bestScore) {
//                leadingPlayers.push_back(&player);
//            }
//        }
//    }
//
//    for (Player& player : players) {
//        if (player.isIn) {
//            cout << "\n";
//            cout << "Player " << player.name << "'s best hand is a " <<
//            CardUtil::deduceHandType(player.bestScore) << ":" << "\n";
//            for (Card card: player.bestHand) {
//                cout << card << "\n";
//            }
//        }
//    }
//
//    cout << "\n";
//
//    if (leadingPlayers.size() == 1) {
//        cout << "We have one winner" << "\n";
//        leadingPlayers[0]->win(pot);
//    } else {
//        cout << "The pot must be split" << "\n";
//        for (Player* winner : leadingPlayers) {
//            winner->win(pot/(leadingPlayers.size()));
//        }
//    }
//
//    for (int i=0; i<players.size(); i++) {
//        if (players[i].money == 0) {
//            cout << "\nPlayer " << players[i].name << " has gone bankrupt.\n";
//            players.erase(players.begin()+i);
//            i--;
//        }
//    }
//}

/*
 * Prepare for a hand
 */
//void Game::reset() {
//    if (players.size() == 1) {
//        cout << "\nPlayer " << players[0].name << " wins the game!\n";
//        isFinished = true;
//    } else {
//        pot = 0;
//        isHeadsUp = false;
//        // Reset players
//        for (Player& player : players) {
//            player.isIn = true;
//            player.isAllIn = false;
//            player.totalBet = 0;
//        }
//        round += 1;
//        communityCards.clear();
//
//        cout << "\nSetup complete\n";
//
//        shuffleDeck();
//        setupBlinds();
//        distributeHoleCards();
//    }
//}
