#include "Misc.h"

/**
 * Converts a percentage to a pixel value
 */
sf::Vector2f Misc::percentageToPixels(sf::Vector2f percentage, sf::RenderWindow& window) {
    sf::Vector2u windowSize = window.getSize();
    return sf::Vector2f((percentage.x / 100.f) * windowSize.x,(percentage.y / 100.f) * windowSize.y);
}

/**
 * Adds delta to each of the RGB color values of color
 */
sf::Color Misc::adjustColorBrightness(const sf::Color& color, int delta) {
    int red = max(0, color.r + delta);
    int green = max(0, color.g + delta);
    int blue = max(0, color.b + delta);

    return sf::Color(red, green, blue);
}

/**
 * Checks if the text in all text boxes are valid
 * @param boxes List of boxes to check, given in the format {box1, box2, box3}
 */
 bool Misc::textBoxesValid(initializer_list<TextBox> boxes) {
     for (TextBox box : boxes) {
         if (!box.textIsValid) {
             return false;
         }
     }
     return true;
 }
