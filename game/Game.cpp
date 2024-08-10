#include "Game.h"

Game::Game() : handInProgress(false), showdownInProgress(false) {
    initVariables();
    initWindow();
    initFont();
    initRender();
    initDeck();
    initBasicUI();
    initSetupPlayersUI();
    initTable();
    initActionMenu();
}

Game::~Game() {
    delete window;
}

void Game::initVariables() {
    currentState = GameState::BASIC_SETUP;
    setupHandComplete = false;
    isFinished = false;
    pot = 0;
    round = 0;
    option = 0;
    showBetBox = false;

    // Use Black and Red Cards Only
    useTwoColor = false;
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
    if (!regularFont.loadFromFile(string(BASE_PATH) + "fonts/Kanit-Regular.ttf")) {
        cout << "Font loading error\n";
    }
    if (!boldFont.loadFromFile(string(BASE_PATH) + "fonts/Kanit-Bold.ttf")) {
        cout << "Font loading error\n";
    }
    // Roboto Mono currently unused
    if (!robotoMonoRegular.loadFromFile(string(BASE_PATH) + "fonts/RobotoMono-Regular.ttf")) {
        cout << "Font loading error\n";
    }
    if (!robotoMonoBold.loadFromFile(string(BASE_PATH) + "fonts/RobotoMono-Bold.ttf")) {
        cout << "Font loading error\n";
    }
}

void Game::initBasicUI() {
    // Status Text label at the bottom, which is updated by updateStatusText() as the game progresses
    statusText = new Text("status text", regularFont, 16, Misc::percentageToPixels(sf::Vector2f(50, 4), *window));

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

void Game::initTable() {
    // Players currently unused; will eventually help draw player seats
    table = new Table(sf::Vector2f(500, 350), Misc::percentageToPixels(sf::Vector2f(50, 45), *window), communityCards, players, roundPot, pot);
}

void Game::initActionMenu() {
    report = new Text("Texas Hold'Em Poker", boldFont, 24, Misc::percentageToPixels(sf::Vector2f(50, 85), *window), sf::Color::Cyan);

    label1 = new sf::Text;
    label1->setFillColor(sf::Color::White);
    label1->setFont(regularFont);
    label1->setCharacterSize(16);
    label1->setString("Raise [Q]");

    label2 = new sf::Text;
    label2->setFillColor(sf::Color::White);
    label2->setFont(regularFont);
    label2->setCharacterSize(16);
    label2->setString("Call [W]");

    label3 = new sf::Text;
    label3->setFillColor(sf::Color::White);
    label3->setFont(regularFont);
    label3->setCharacterSize(16);
    label3->setString("Fold [E]");

    opt1 = new RecButton(Misc::percentageToPixels(sf::Vector2f(7, 95), *window), Misc::percentageToPixels(sf::Vector2f(8, 6), *window), sf::Color::Transparent, sf::Color::White, *label1);
    opt2 = new RecButton(Misc::percentageToPixels(sf::Vector2f(17, 95), *window), Misc::percentageToPixels(sf::Vector2f(8, 6), *window), sf::Color::Transparent, sf::Color::White, *label2);
    opt3 = new RecButton(Misc::percentageToPixels(sf::Vector2f(27, 95), *window), Misc::percentageToPixels(sf::Vector2f(8, 6), *window), sf::Color::Transparent, sf::Color::Red, *label3);

    betBox = new TextBox(Misc::percentageToPixels(sf::Vector2f(45, 95), *window), Misc::percentageToPixels(sf::Vector2f(20, 6), *window), regularFont, 20, sf::Color::Transparent, sf::Color::White, true);
}

void Game::run() {
    while (window->isOpen()) {
        processEvents();
        updateStatusText();
        render();
    }
}

void Game::processEvents() {
    sf::Event event{};
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
            if (handInProgress) stopPlayHand();
        }
        switch (currentState) {
            case GameState::BASIC_SETUP:
                basicSetup(event);
                break;
            case GameState::SETUP_PLAYERS:
                setupPlayers(event);
                break;
            case GameState::SETUP_CARD_SPRITES:
                setupCardSprites();
                break;
            case GameState::SETUP_HAND:
                setupHand();
                break;
            case GameState::PLAY_HAND:
                if (!handInProgress) startPlayHand();
                listenForOptionSelect(event);
                break;
            case GameState::SHOWDOWN:
                if (!showdownInProgress) startShowdown();
                break;
        }
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
        case GameState::SETUP_CARD_SPRITES:
            // There is a loading screen
            break;
        case GameState::SETUP_HAND:
            // There is a loading screen
            break;
        case GameState::PLAY_HAND:
            status = "playing hand";
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
        case GameState::SETUP_CARD_SPRITES:
            break;
        case GameState::SETUP_HAND:
            break;
        case GameState::PLAY_HAND:
            table->draw(*window);
            table->drawPlayers(*window);

            report->updateOrigin();
            report->draw(*window);

            opt1->updateTextPosition();
            opt1->draw(*window);

            opt2->updateTextPosition();
            opt2->draw(*window);

            opt3->updateTextPosition();
            opt3->draw(*window);

            if (showBetBox) betBox->draw(*window);
            break;
        case GameState::SHOWDOWN:
            table->draw(*window);
            table->drawPlayers(*window);

            report->updateOrigin();
            report->draw(*window);
            break;
    }
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
    numPlayersBox->handleEvent(*window, event);
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
    stashTextBox->handleEvent(*window, event);
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
    bigBlindBox->handleEvent(*window, event);
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
    nameTextBox->handleEvent(*window, event);
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
        currentState = GameState::SETUP_CARD_SPRITES;
        cout << "Players Setup Complete" << endl;
        for (Player& player : players) {
            cout << "\t" << player.index << ". " << player.name << "\n";
        }
        initialDealerIndex = Game::randomInt(1, players.size());
        cout << "\tInitial Dealer Index: " << initialDealerIndex << "\n";
    }
}

/**
 * Setup card sprites
 */
void Game::setupCardSprites() {
    static bool setupComplete = false;

    if (!setupComplete) {
        window->clear(sf::Color(0, 0, 30));
        loadingLabel = new Text("Generating sprites", regularFont, 36, Misc::percentageToPixels(sf::Vector2f(50, 50), *window));
        loadingLabel->draw(*window);
        window->display();

        // Generate sprites for each card
        for (Card& card : deck) {
            card.generateSprite(boldFont, sf::Vector2f(0, 0), sf::Vector2f(75, 90), useTwoColor); // Keep x : y ratio to 5 : 6
        }
        setupComplete = true;
    }
    if (setupComplete) {
        currentState = GameState::SETUP_HAND;
    }
}

/**
 * Set up the hand, i.e. setting up blinds, etc.
 */
void Game::setupHand() {
    if (!setupHandComplete) {
        resetDeck();

        report->text.setString("Texas Hold'Em Poker");

        window->clear(sf::Color(0, 0, 30));
        loadingLabel = new Text("Preparing game", regularFont, 36, Misc::percentageToPixels(sf::Vector2f(50, 50), *window));
        loadingLabel->draw(*window);
        window->display();

        if (players.size() == 1) {
            cout << "\nPlayer " << players[0].name << " wins the game!\n";
            isFinished = true;
        }

        roundPot = 0;
        pot = 0;
        isHeadsUp = false;
        skipToEnd = false;

        // Reset players
        for (Player& player : players) {
            player.isIn = true;
            player.isAllIn = false;
            player.hasMadeAction = false;
            player.hasChecked = false;
            player.currentBet = 0;
            player.totalBet = 0;
        }

        communityCards.clear();
        distributeHoleCards();
        setupBlinds();

        round += 1;

        setupHandComplete = true;
        cout << "Setup complete\n";
    }
    if (setupHandComplete) {
        currentState = GameState::PLAY_HAND;
    }
}

void Game::startPlayHand() {
    handInProgress = true;
    if (!playHandThread.joinable()) playHandThread = thread(&Game::playHand, this);
}

void Game::stopPlayHand() {
    handInProgress = false;
}

/**
 * Listen to option select event
 */
void Game::listenForOptionSelect(sf::Event& event) {
    betBox->handleEvent(*window, event);

    if (!betBox->isActive) {
        if (opt1->isClicked(*window, event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)) {
            if (opt1->buttonText.getString() == "Bet [Q]") {
                showBetBox = true;
                betBox->isActive = true;
                betBox->setString(to_string(currentMinBet));
            }
            if (opt1->buttonText.getString() == "Raise [Q]") {
                showBetBox = true;
                betBox->isActive = true;
                betBox->setString(to_string(2*currentMinBet));
            }
        }
        if (opt2->isClicked(*window, event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::W)) {
            option = 2;
            showBetBox = false;
        }
        if (opt3->isClicked(*window, event) || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::E)) {
            option = 3;
            showBetBox = false;
        }
    }

    if (betBox->isActive && (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)) {
        betBoxInput = betBox->retrieveTextAsInt();
        betBox->isActive = false;
        option = 1;
    }
}

/**
 * Initiliaze the actual fucking hand! Finally!
 */
void Game::playHand() {
    while (true) {
        while (handInProgress) {
            lock_guard<mutex> lock(mtx);

            // Reset round variables at the start of each turn
            for (turn=1; turn<=4; turn++) {
                calculateRoundPot();
                currentMinBet = bigBlindBet;
                hasOpened = false;

                // Reset player states
                for (Player& player : players) {
                    player.currentBet = 0;
                    player.hasMadeAction = false;
                    player.hasRaised = false;
                    player.hasChecked = false;
                }

                // Handle different rounds
                switch (turn) {
                    case 1:
                        report->text.setString("Pre-Flop");

                        std::cout << "\nPre-flop\n\n";
                        doBlindBets();
                        calculateRoundPot();
                        break;
                    case 2:
                        report->text.setString("The Flop");

                        std::cout << "\nFlop\n";
                        break;
                    case 3:
                        report->text.setString("The Turn");

                        std::cout << "\nTurn\n";
                        break;
                    case 4:
                        report->text.setString("The River");

                        std::cout << "\nRiver\n";
                        break;
                }

                int startingIndex;
                if (turn == 1) startingIndex = bigBlind->index % players.size();
                else startingIndex = smallBlind->index % players.size();

                for (int i=startingIndex; !isTurnOver(); i=(i+1) % players.size()) {
                    Player& player = players[i];

                    if (!player.isIn || player.isAllIn) continue;

                    this_thread::sleep_for(chrono::seconds(1));
                    report->text.setString("It's " + player.name + "'s turn.");

                    player.highlight = true;
                    getAction(player);
                    player.highlight = false;

                    playersFolded = 0;
                    playersBetting = 0;

                    for (Player& player : players) {
                        if (player.isIn && !player.isAllIn) {
                            playersBetting += 1;
                        }
                        if (!player.isIn) {
                            playersFolded += 1;
                        }
                    }

                    calculateRoundPot();
                }
                calculatePot();
                if (turn!=4) distributeCommunityCards();
            }
            std::cout << "Hand finished\n\n";
            currentState = GameState::SHOWDOWN;
            stopPlayHand();
        }
    }
}

/**
 * Create a new deck of cards
 */
void Game::initDeck() {
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
 * Reset deck for next hand
 */
void Game::resetDeck() {
    deck.insert(deck.end(), usedCards.begin(), usedCards.end());
    usedCards.clear();

    cout << "Deck reset. Size still " << deck.size() << "\n";
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
    for (Player& player : players) {
        player.holeCards.clear();
        for (int i = 0; i < 2; i++) {
            int drawnCardIndex = randomInt(0, deck.size() - 1);
            Card drawnCard = deck[drawnCardIndex];
            usedCards.push_back(drawnCard);
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
    int burnCardIndex = Game::randomInt(0, deck.size() - 1);
    usedCards.push_back(deck[burnCardIndex]);
    deck.erase(deck.begin() + burnCardIndex);
    cout << "\nBurn card discarded\n";
    if (communityCards.empty()) {
        for (int i=0; i<3; i++) {
            int drawnCardIndex = Game::randomInt(0, deck.size()-1);
            communityCards.push_back(deck[drawnCardIndex]);
            usedCards.push_back(deck[drawnCardIndex]);
            deck.erase(deck.begin() + drawnCardIndex);
        }
    } else if (communityCards.size() < 5)  {
        int drawnCardIndex = Game::randomInt(0, deck.size()-1);
        communityCards.push_back(deck[drawnCardIndex]);
        usedCards.push_back(deck[drawnCardIndex]);
        deck.erase(deck.begin() + drawnCardIndex);
    }

    cout << "\n";
    for (Card& card : communityCards) {
        cout << "Community Card: " << card << "\n";
    }
}

/*
 * Calculate the current rounds' roundPot
 */
void Game::calculateRoundPot() {
    roundPot = 0;
    for (Player& player : players) {
        roundPot += player.currentBet;
    }
}

/*
 * Updates roundPot value at the end of the round, and sets all player current bets to 0
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
bool Game::getAction(Player& player) {
    // Heads up implementation
    if (playersBetting == 2) {
        isHeadsUp = true;
    }

    bool validAction = false;

    opt1->button.setOutlineColor(sf::Color::White);

    // No bet has been made yet
    if (!hasOpened) {
        opt1->buttonText.setString("Bet [Q]");
        opt2->buttonText.setString("Check [W]");
    } else if (!player.hasRaised || isHeadsUp) {
        opt1->buttonText.setString("Raise [Q]");
        opt2->buttonText.setString("Call [W]");
    } else {
        opt1->button.setOutlineColor(sf::Color::Red);
        opt1->buttonText.setString("Can't Raise");
        opt2->buttonText.setString("Call [W]");
    }

    while (!validAction) {
        if (!hasOpened) {
            // Bet
            if (option == 1) {
                validAction = player.bet(&currentMinBet, betBoxInput, *report);
                if (validAction) {
                    hasOpened = true;
                    betBox->setString("");
                    showBetBox = false;
                }
            // Check
            } else if (option == 2) {
                validAction = player.check(*report);
            }
        } else {
            if (!player.hasRaised || isHeadsUp) {
                if (option == 1) { // Raise
                    validAction = player.raise(&currentMinBet, betBoxInput, *report);
                    if (validAction) {
                        betBox->setString("");
                        showBetBox = false;
                    }
                } else if (option == 2) { // Call
                    validAction = player.call(&currentMinBet, *report);
                }
            } else {
                if (option == 2) { // Call
                    validAction = player.call(&currentMinBet, *report);
                }
            }
        }

        if (option == 3) { // Fold
            validAction = player.fold(*report);
        }
    }
    player.hasMadeAction = true;
    option = 0;
    return true;
}

/*
 * Returns true if le turn is over
 */
bool Game::isTurnOver() {
    bool isTurnOver = true;
    bool checkedAround = true;

    for (Player& player : players) {
        if (player.isIn && !player.isAllIn) {
            if (playersBetting == 1 && player.currentBet == currentMinBet && playersFolded != players.size() - 1) {
                skipToEnd = true;
            }
            if (playersBetting == 1 && playersFolded == players.size() - 1) {
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
        if (player.isAllIn) {
            checkedAround = false;
        }
    }

    if (checkedAround || skipToEnd) {
        return true;
    }

    return isTurnOver;
}

void Game::startShowdown() {
    showdownInProgress = true;
    if (!showdownThread.joinable()) showdownThread = thread(&Game::showdown, this);
}

void Game::stopShowdown() {
    showdownInProgress = false;
}

void Game::showdown() {
    while (true) {
        bool showdownFinished = false;

        while (showdownInProgress) {
            lock_guard<mutex> lock(mtx);

            if (showdownFinished) {
                // Loop back to hand setup; doesn't work yet
                stopShowdown();
                setupHandComplete = false;
                currentState = GameState::SETUP_HAND;
                continue;
            }

            this_thread::sleep_for(chrono::seconds(1));
            report->text.setFillColor(sf::Color::Yellow);
            report->text.setString("Showdown");
            this_thread::sleep_for(chrono::seconds(2));

            report->text.setString("The pot is worth a beefy $" + to_string(pot));
            this_thread::sleep_for(chrono::seconds(2));

            vector<int> bestScore = {0};
            vector<Card> bestHand;
            vector<Player*> leadingPlayers;

            for (Player& player : players) {
                player.highlightColor = sf::Color::Yellow;
                if (player.isIn) {
                    report->text.setString("Player " + player.name + " has bet $" + to_string(player.totalBet));

                    player.highlight = true;
                    this_thread::sleep_for(chrono::seconds(2));
                    player.highlight = false;

                    player.bestScore = CardUtil::findBestScore(communityCards, player.holeCards);
                    player.bestHand = CardUtil::findBestHand(communityCards, player.holeCards);

                    // Debug usage
                    cout << player.name + "'s Score: {";
                    for (int i: player.bestScore) {
                        cout << i << ",";
                    }
                    cout << "}\n";

                    if (CardUtil::compareScores(player.bestScore, bestScore)) {
                        bestScore = player.bestScore;
                        leadingPlayers.clear();
                        leadingPlayers.push_back(&player);
                    } else if (player.bestScore == bestScore) {
                        leadingPlayers.push_back(&player);
                    }
                }
            }

            for (Player& player : players) {
                if (player.isIn) {
                    cout << "\n";
                    cout << "Player " << player.name << "'s best hand is a " <<
                         CardUtil::deduceHandType(player.bestScore) << ":" << "\n";

                    report->text.setString("Player " + player.name + "'s best hand is a " + CardUtil::deduceHandType(player.bestScore));

                    for (Card& card : CardUtil::findBestHand(communityCards, player.holeCards)) {
                        cout << card << "\n";
                    }

                    player.highlight = true;
                    this_thread::sleep_for(chrono::seconds(2));
                    player.highlight = false;

                    for (Card card: player.bestHand) {
                        // Skip for now
                    }
                }
            }

            if (leadingPlayers.size() == 1) {
                report->text.setString("We have one winner, " + leadingPlayers[0]->name);

                leadingPlayers[0]->win(pot, *report);

                leadingPlayers[0]->highlightColor = sf::Color::Green;
                leadingPlayers[0]->highlight = true;
            } else {
                for (Player* player : leadingPlayers) {
                    player->highlight = true;
                }
                report->text.setString("We have multiple winners");
                this_thread::sleep_for(chrono::seconds(2));

                for (Player* winner : leadingPlayers) {
                    winner->win(pot/(leadingPlayers.size()), *report);

                    winner->highlightColor = sf::Color::Green;
                    winner->highlight = true;

                    this_thread::sleep_for(chrono::seconds(2));
                }
            }

            this_thread::sleep_for(chrono::seconds(5));

            for (int i=0; i<players.size(); i++) {
                players[i].highlight = false;
                players[i].highlightColor = sf::Color::Cyan;
                if (players[i].money == 0) {
                    players.erase(players.begin()+i);
                    i--;
                }
            }
            report->text.setFillColor(sf::Color::Cyan);
            showdownFinished = true;
        }
    }
}
