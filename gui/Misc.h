#pragma once

#include <SFML/Graphics.hpp>
#include "TextBox.h"

using namespace std;

class Misc {
public:
    static sf::Vector2f percentageToPixels(sf::Vector2<float> percentage, sf::RenderWindow& window);
    static sf::Color adjustColorBrightness(const sf::Color& color, int delta);
    static bool textBoxesValid(initializer_list<TextBox> boxes);
};
