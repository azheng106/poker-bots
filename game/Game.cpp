#include "Game.h"

Game::Game() {
    initVariables();
    initWindow();
    initRender();
    initFont();
    initUI();
}

Game::~Game() {
    delete window;
}

void Game::initVariables() {
    currentState = GameState::SETUP_PLAYERS;
    isFinished = false;
    round = 0;
}

void Game::initWindow() {
    int windowWidth = 800;
    int windowHeight = 600;

    window = new sf::RenderWindow(sf::VideoMode(windowWidth, windowHeight), "Poker Bots");
    window->setVerticalSyncEnabled(true);
}

void Game::initRender() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 1;
}

void Game::initFont() {
    if (!font.loadFromFile(string(BASE_PATH)+"fonts/RobotoMono-Regular.ttf")) {
        cout << "Font loading error\n";
    }
}

void Game::initUI() {
    // Status Text UI
    statusText = new Text("status text", font, 16, Misc::percentageToPixels(sf::Vector2f(50, 96), *window));

    // Player Setup UI
    numPlayers = 6;

    numPlayersText = new Text("# of Players: "+to_string(numPlayers), font, 20,
                              Misc::percentageToPixels(sf::Vector2f(49, 25), *window));

    decreasePlayers = new TriButton(Misc::percentageToPixels(sf::Vector2f(30, 25), *window), sf::Vector2f(50, 50),
                                    sf::Color::White, 270);
    increasePlayers = new TriButton(Misc::percentageToPixels(sf::Vector2f(70, 25), *window), sf::Vector2f(50, 50),
                                    sf::Color::White, 90);

    stashTextBox = new TextBox(Misc::percentageToPixels(sf::Vector2f(50, 50), *window),
                               sf::Vector2f(200, 40), font, 24, sf::Color::Transparent, sf::Color::White);

    stashTextBox->setString(to_string(stash));
    stash = 1000;
    stashTextBox->setString(to_string(stash));

    decreaseStash = new TriButton(Misc::percentageToPixels(sf::Vector2f(30, 50), *window), sf::Vector2f(50, 50),
                                  sf::Color::White, 270);
    increaseStash = new TriButton(Misc::percentageToPixels(sf::Vector2f(70, 50), *window), sf::Vector2f(50, 50),
                                  sf::Color::White, 90);
    // Setup Hand UI

    // Player Hand UI

    // Showdown UI
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
            case GameState::SETUP_PLAYERS:
                setupPlayers(event);
                break;
            case GameState::SETUP_HAND:
                break;
            case GameState::PLAY_HAND:
                break;
            case GameState::SHOWDOWN:
                break;
        }
    }
}

void Game::update() {
    switch (currentState) {
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
        case GameState::SETUP_PLAYERS:
            status = "setting up players (press enter to submit)";
            break;
        case GameState::SETUP_HAND:
            status = "setting up hand";
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
        case GameState::SETUP_PLAYERS:
            numPlayersText->draw(*window);
            decreasePlayers->draw(*window);
            increasePlayers->draw(*window);
            stashTextBox->draw(*window);
            decreaseStash->draw(*window);
            increaseStash->draw(*window);
            break;
        case GameState::SETUP_HAND:
            break;
        case GameState::PLAY_HAND:
            break;
        case GameState::SHOWDOWN:
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
void Game::setupPlayers(sf::Event& event) {
    if (event.type == sf::Event::Closed) {
        window->close();
    }

    if (decreasePlayers->isClicked(*window, event)) {
        numPlayers = max(2, numPlayers - 1);
        numPlayersText->text.setString("# of Players: " + to_string(numPlayers));
        numPlayersText->updateOrigin();
    }

    if (increasePlayers->isClicked(*window, event)) {
        numPlayers = min(10, numPlayers + 1);
        numPlayersText->text.setString("# of Players: " + to_string(numPlayers));
        numPlayersText->updateOrigin();
    }

    stashTextBox->handleEvent(event);
    stash = stashTextBox->retrieveTextAsInt();

    if (decreaseStash->isClicked(*window, event)) {
        stash = max(0, stash - 100);
        stashTextBox->setString(to_string(stash));
    }

    if (increaseStash->isClicked(*window, event)) {
        stash += 100;
        stashTextBox->setString(to_string(stash));
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        // Fetch the entered stash value
        stash = stoi(stashTextBox->getString());
        currentState = GameState::SETUP_HAND;
    }
}
//
//    int stash;
//    cout << "Input stash (amount of money each players starts with):\n";
//    cin >> stash;
//
//    cout << "Input minimum bet (also big blind bet):\n";
//    cin >> bigBlindBet;
//    currentMinBet = bigBlindBet;
//
//    for (int i=0; i<numPlayers; i++) {
//        string name;
//        cout << "Enter name for player " << i + 1 << ":\n";
//        cin >> name;
//
//        Player player(i, stash, name);
//        players.push_back(player);
//    }
//    initialDealerIndex = Game::randomInt(0, players.size() - 1);

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
void Game::playHand() {
    reset();
    if (isFinished) return;

    // 3 betting rounds: pre-flop, turn, river
    for (turn=1; turn<=3; turn++) {
        currentMinBet = bigBlindBet;
        hasOpened = false;

        // Reset players
        for (Player& player : players) {
            player.currentBet = 0;
            player.hasMadeAction = false;
            player.hasRaised = false;
            player.hasChecked = false;
        }

        switch (turn) {
            case 1:
                cout << "\nPre-flop\n\n";
                doBlindBets();
                break;
            case 2:
                cout << "\nNext round\n";
                break;
            case 3:
                cout << "\nFinal round\n";
                break;
        }

        int startingIndex;
        if (turn == 1) startingIndex = (bigBlind->index + 1) % players.size();
        else startingIndex = smallBlind->index % players.size();

        for (int i=startingIndex; !isTurnOver(); i=(i+1) % players.size()) {
            Player& player = players[i];
            if (!player.isIn || player.isAllIn) continue;

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
            getAction(player);
        }
        displayPot();
        calculatePot();
        distributeCommunityCards();
    }
    showdown();
}

void Game::showdown() {
    cout << "\nShowdown\n\n";
    cout << "The pot is worth a beefy $" << pot << "\n\n";

    vector<int> bestScore = {0};
    vector<Card> bestHand;
    vector<Player*> leadingPlayers;

    for (Player& player : players) {
        if (player.isIn) {
            cout << "Player " << player.name << " has bet $" << player.totalBet << "\n";

            player.bestScore = CardUtil::findBestScore(communityCards, player.holeCards);
            player.bestHand = CardUtil::findBestHand(communityCards, player.holeCards);

            // Debug usage
            cout << "Score: {";
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
            for (Card card: player.bestHand) {
                cout << card << "\n";
            }
        }
    }

    cout << "\n";

    if (leadingPlayers.size() == 1) {
        cout << "We have one winner" << "\n";
        leadingPlayers[0]->win(pot);
    } else {
        cout << "The pot must be split" << "\n";
        for (Player* winner : leadingPlayers) {
            winner->win(pot/(leadingPlayers.size()));
        }
    }

    for (int i=0; i<players.size(); i++) {
        if (players[i].money == 0) {
            cout << "\nPlayer " << players[i].name << " has gone bankrupt.\n";
            players.erase(players.begin()+i);
            i--;
        }
    }
}

/*
 * Prepare for a hand
 */
void Game::reset() {
    if (players.size() == 1) {
        cout << "\nPlayer " << players[0].name << " wins the game!\n";
        isFinished = true;
    } else {
        pot = 0;
        isHeadsUp = false;
        // Reset players
        for (Player& player : players) {
            player.isIn = true;
            player.isAllIn = false;
            player.totalBet = 0;
        }
        round += 1;
        communityCards.clear();

        cout << "\nSetup complete\n";

        shuffleDeck();
        setupBlinds();
        distributeHoleCards();
    }
}