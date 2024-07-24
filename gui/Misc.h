#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Misc {
public:
    static sf::Color adjustColorBrightness(const sf::Color& color, int delta);
};
