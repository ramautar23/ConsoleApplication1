#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>

Player::Player() {
    shape.setSize({ 15.f, 15.f });
    shape.setFillColor(sf::Color::Magenta);
    position = { 50.f, 500.f }; // Startpositie
    shape.setPosition(position);
    speed = 100.f;
}

void Player::handleInput() {
    movement = { 0.f, 0.f };
    using Key = sf::Keyboard::Key;
    if (sf::Keyboard::isKeyPressed(Key::Left))  movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(Key::Right)) movement.x += speed;
    if (sf::Keyboard::isKeyPressed(Key::Up))    movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(Key::Down))  movement.y += speed;
}

void Player::update(sf::Time dt) {
    
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Player::moveX(sf::Time dt) {
    previousPosition = position;
    position.x += movement.x * dt.asSeconds();
    shape.setPosition(position);
}

void Player::moveY(sf::Time dt) {
    previousPosition = position;
    position.y += movement.y * dt.asSeconds();
    shape.setPosition(position);
}

void Player::undoMoveX(sf::Time dt) {
    position.x = previousPosition.x;
    shape.setPosition(position);
}

void Player::undoMoveY(sf::Time dt) {
    position.y = previousPosition.y;
    shape.setPosition(position);
}

void Player::undoMove(sf::Time dt) {
    shape.move(-movement * dt.asSeconds());
}


