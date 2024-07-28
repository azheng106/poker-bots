#pragma once

#include <SFML/Graphics.hpp>

#include <random>
#include <algorithm>
#include <variant>

#include "Player.h"
#include "CardUtil.h"

#include "../gui/RecButton.h"
#include "../gui/TriButton.h"
#include "../gui/TextBox.h"
#include "../gui/Text.h"

class Game {
public:
    // Constructor and Destructor
    Game();
    ~Game();

    // Main Game Loop
    void run();
private:
    // Initialization
    void initVariables();
    void initWindow();
    void initRender();
    void initFont();
    void initBasicUI();

    // Event Loop
    void processEvents();
    void update();
    void updateStatusText();
    void render();

    // Game Logic
    static int randomInt(int a, int b);
    void basicSetup(sf::Event& event);
    void shuffleDeck();
    void setupBlinds();
    void distributeHoleCards();
    void distributeCommunityCards();
    void displayPot();
    void calculatePot();
    void doBlindBets();
    void getAction(Player& player);
    bool isTurnOver();
    void playHand();
    void showdown();
    void reset();

    // Game Variables
    enum GameState { BASIC_SETUP, SETUP_PLAYERS, SETUP_HAND, PLAY_HAND, SHOWDOWN };
    GameState currentState;

    // Basic Setup
    int numPlayers;
    int stash;
    int bigBlindBet;

    int round;
    int turn;
    int pot;
    bool hasOpened;
    int currentMinBet;
    int initialDealerIndex;
    bool skipToEnd;
    int playersFolded;
    int playersBetting;
    bool isFinished;
    bool isHeadsUp;

    // Players
    Player* dealer;
    Player* smallBlind;
    Player* bigBlind;
    vector<Player> players;

    // Cards
    vector<Card> deck;
    vector<Card> communityCards;

    // Global UI Elements
    sf::Font regularFont;
    sf::Font boldFont;
    Text* statusText;

    // Setup Players UI
    Text* numPlayersLabel;
    TextBox* numPlayersBox;
    TriButton* decreasePlayers;
    TriButton* increasePlayers;

    Text* stashTextBoxLabel;
    TextBox* stashTextBox;
    TriButton* decreaseStash;
    TriButton* increaseStash;

    Text* bigBlindBoxLabel;
    TextBox* bigBlindBox;
    TriButton* decreaseBigBlind;
    TriButton* increaseBigBlind;

    // Setup Hand UI

    // Play Hand UI

    // Showdown UI

    // Window
    sf::RenderWindow* window;

    // File Paths
    static constexpr const char* BASE_PATH = "../../../";
};
