#include "Misc.h"

sf::Color Misc::adjustColorBrightness(const sf::Color& color, int delta) {
    int red = max(0, color.r + delta);
    int green = max(0, color.g + delta);
    int blue = max(0, color.b + delta);

    return sf::Color(red, green, blue);
}
