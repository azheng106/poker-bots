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
#include "../gui/CardSprite.h"
#include "../gui/Table.h"

using namespace std;

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
    void initSetupPlayersUI();
    void initTableTest();

    // Event Loop
    void processEvents();
    void update();
    void updateStatusText();
    void render();

    // Game Logic
    static int randomInt(int a, int b);
    void basicSetup(sf::Event& event);
    void setupPlayers(sf::Event& event);
    void setupHand(sf::Event& event);
    void playHand(sf::Event& event);

    void shuffleDeck();
    void setupBlinds();
    void distributeHoleCards();
    void distributeCommunityCards();
    void calculateRoundPot();
    void calculatePot();
    void doBlindBets();
    void getAction(Player& player);
    bool isTurnOver();
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
    int pot;
    int roundPot;
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
    sf::Font robotoMonoRegular;
    sf::Font robotoMonoBold;
    Text* statusText;

    // Basic Setup UI
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

    // Setup Players UI
    int currentPlayerIndex;
    Text* nameTextLabel;
    TextBox* nameTextBox;

    // Setup Hand UI
    Text* setupHandLoadingLabel;

    // Play Hand UI
    Table* table;

    // Showdown UI

    // Window
    sf::RenderWindow* window;

    // File Paths
    static constexpr const char* BASE_PATH = "../../../";
};
