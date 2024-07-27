#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class Misc {
public:
    static sf::Vector2f percentageToPixels(sf::Vector2<float> percentage, sf::RenderWindow& window);
    static sf::Color adjustColorBrightness(const sf::Color& color, int delta);
};
