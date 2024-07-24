#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "game/Game.h"
#include "gui/Button.h"
#include "gui/Text.h"
#include "gui/Default.h"

using namespace std;

// Used to access poker-bots resources from the .exe path
const string BASE_PATH = "../../../";

int main() {
    Game game;
    game.run();
}