#include "Wall.h"

// Constructor: stel positie en grootte in van de muur
Wall::Wall(const sf::Vector2f& pos, const sf::Vector2f& size) {
    shape.setSize(size);                // Stel de afmetingen in
    shape.setFillColor(sf::Color::Blue);  // Geef de muur een blauwe kleur
    shape.setPosition(pos);            // Zet de muur op de opgegeven positie
}

// Tekent de muur op het scherm in je Game::render() loop
void Wall::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

// Hulpmethode voor botsingsdetectie, geeft rechthoek (bounds) terug
sf::FloatRect Wall::getBounds() const {
    return shape.getGlobalBounds();
}
