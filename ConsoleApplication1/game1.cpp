#include <optional>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Wall.h"  
#include "Goal.h"
#include "player.h"
#include <iostream>            


Game::Game()
    : window(sf::VideoMode{ {800u,600u} }, "Maze Game"),
    timePerFrame(sf::seconds(1.f / 60.f)),
    player()
{
    objects.push_back(&player);
    Goal* goal = new Goal({ 720.f, 520.f }, { 40.f, 40.f });
    objects.push_back(goal);

    // Buitenranden
    objects.push_back(new Wall({ 0.f, 0.f }, { 800.f, 20.f }));
    objects.push_back(new Wall({ 0.f, 580.f }, { 800.f, 20.f }));
    objects.push_back(new Wall({ 0.f, 0.f }, { 20.f, 600.f }));
    objects.push_back(new Wall({ 780.f, 0.f }, { 20.f, 600.f }));

    // Horizontale muren
    objects.push_back(new Wall({ 40.f, 60.f }, { 180.f, 20.f }));
    objects.push_back(new Wall({ 260.f, 120.f }, { 200.f, 20.f }));
    objects.push_back(new Wall({ 500.f, 180.f }, { 250.f, 20.f }));
    objects.push_back(new Wall({ 100.f, 240.f }, { 300.f, 20.f }));
    objects.push_back(new Wall({ 420.f, 300.f }, { 200.f, 20.f }));
    objects.push_back(new Wall({ 80.f, 360.f }, { 240.f, 20.f }));
    objects.push_back(new Wall({ 350.f, 420.f }, { 300.f, 20.f }));
    objects.push_back(new Wall({ 150.f, 500.f }, { 130.f, 20.f }));
    objects.push_back(new Wall({ 400.f, 500.f }, { 160.f, 20.f }));
    objects.push_back(new Wall({ 40.f, 140.f }, { 140.f, 20.f }));
    objects.push_back(new Wall({ 180.f, 320.f }, { 140.f, 20.f }));
    objects.push_back(new Wall({ 460.f, 380.f }, { 120.f, 20.f }));
    objects.push_back(new Wall({ 600.f, 440.f }, { 100.f, 20.f }));
    objects.push_back(new Wall({ 300.f, 60.f }, { 180.f, 20.f }));

    // Verticale muren
    objects.push_back(new Wall({ 100.f, 80.f }, { 20.f, 120.f }));
    objects.push_back(new Wall({ 200.f, 160.f }, { 20.f, 120.f }));
    objects.push_back(new Wall({ 300.f, 240.f }, { 20.f, 120.f }));
    objects.push_back(new Wall({ 400.f, 100.f }, { 20.f, 120.f }));
    objects.push_back(new Wall({ 500.f, 200.f }, { 20.f, 120.f }));
    objects.push_back(new Wall({ 600.f, 280.f }, { 20.f, 120.f }));
    objects.push_back(new Wall({ 700.f, 360.f }, { 20.f, 120.f }));
    objects.push_back(new Wall({ 250.f, 460.f }, { 20.f, 100.f }));
    objects.push_back(new Wall({ 600.f, 460.f }, { 20.f, 60.f }));
    objects.push_back(new Wall({ 180.f, 300.f }, { 20.f, 120.f }));
    objects.push_back(new Wall({ 450.f, 360.f }, { 20.f, 120.f }));
    objects.push_back(new Wall({ 520.f, 60.f }, { 20.f, 80.f }));
    objects.push_back(new Wall({ 650.f, 160.f }, { 20.f, 100.f }));
    objects.push_back(new Wall({ 160.f, 100.f }, { 20.f, 80.f }));
    objects.push_back(new Wall({ 280.f, 200.f }, { 20.f, 80.f }));
    objects.push_back(new Wall({ 380.f, 360.f }, { 20.f, 100.f }));
    objects.push_back(new Wall({ 500.f, 460.f }, { 20.f, 60.f }));
    objects.push_back(new Wall({ 700.f, 260.f }, { 20.f, 80.f }));

    // Moeilijkheid verhogen, maar doorgang houden
    objects.push_back(new Wall({ 680.f, 480.f }, { 40.f, 20.f }));      
    objects.push_back(new Wall({ 720.f, 400.f }, { 20.f, 60.f }));      
    objects.push_back(new Wall({ 580.f, 460.f }, { 40.f, 20.f }));      
    objects.push_back(new Wall({ 640.f, 520.f }, { 20.f, 20.f }));      

    // Afleidingsmuur rechtsboven
    objects.push_back(new Wall({ 600.f, 60.f }, { 160.f, 20.f }));
    objects.push_back(new Wall({ 720.f, 80.f }, { 20.f, 120.f }));

    // Valstrik midden
    objects.push_back(new Wall({ 400.f, 360.f }, { 100.f, 20.f }));
    objects.push_back(new Wall({ 500.f, 300.f }, { 20.f, 60.f }));

    // Extra dead end links
    objects.push_back(new Wall({ 100.f, 400.f }, { 60.f, 20.f }));
    objects.push_back(new Wall({ 140.f, 420.f }, { 20.f, 60.f }));


}

Game::~Game() {
    for (auto obj : objects) {
        if (obj != &player)
            delete obj;
    }
    objects.clear();
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        processEvents();
        sf::Time dt = clock.restart();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>())
            window.close();
    }
}

void Game::update(sf::Time dt) {
    // 1. Speler verplaatsen
    player.handleInput();
    player.moveX(dt);

    // Botsing per X
    for (auto obj : objects) {
        if (auto wall = dynamic_cast<Wall*>(obj)) {
            if (player.getBounds().findIntersection(wall->getBounds())) {
                player.undoMoveX(dt); // Herstel alleen X-beweging
                break;
            }
        }
    }

    player.moveY(dt);

    // Botsing per Y
    for (auto obj : objects) {
        if (auto wall = dynamic_cast<Wall*>(obj)) {
            if (player.getBounds().findIntersection(wall->getBounds())) {
                player.undoMoveY(dt); // Herstel alleen Y-beweging
                break;



            }
        }
    }
}



void Game::render() {
    window.clear(sf::Color::Black);
    for (auto obj : objects) {
        obj->draw(window);
    }
    window.display();
}


