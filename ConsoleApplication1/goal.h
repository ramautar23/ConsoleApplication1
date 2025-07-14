#pragma once
#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Goal : public GameObject {
public:
    Goal(const sf::Vector2f& pos, const sf::Vector2f& size);
    void handleInput() override {}
    void update(sf::Time) override {}
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape shape;
};
