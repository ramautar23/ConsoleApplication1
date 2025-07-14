#pragma once
#include <SFML/Graphics.hpp>

class GameObject {
public:
    virtual void handleInput() = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual ~GameObject() = default;
};
