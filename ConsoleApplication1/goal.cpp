#include "Goal.h"

Goal::Goal(const sf::Vector2f& pos, const sf::Vector2f& size) {
    shape.setSize(size);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(pos);
}

void Goal::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::FloatRect Goal::getBounds() const {
    return shape.getGlobalBounds();
}
