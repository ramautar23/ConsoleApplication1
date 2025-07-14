#pragma once
#include "GameObject.h"
#include <SFML/Graphics.hpp>

class Player : public GameObject {
public:
    Player();
    void handleInput();
    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);

    sf::FloatRect getBounds() const;
    sf::Vector2f getMovement() const { return movement; }

    void moveX(sf::Time dt);
    void moveY(sf::Time dt);
    void undoMoveX(sf::Time dt);
    void undoMoveY(sf::Time dt);
    void undoMove(sf::Time dt);

private:
    sf::RectangleShape shape;
    sf::Vector2f movement;
    sf::Vector2f position;
    sf::Vector2f previousPosition;
    float speed = 100.f;
};

