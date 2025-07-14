#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "GameObject.h"
#include <vector>  // voor std::vector

class Game {
public:
    Game();
    ~Game();
    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();
    void createWalls();


    sf::RenderWindow window;
    sf::Time timePerFrame;

    Player player;                        // Jouw spelerobject
    std::vector<GameObject*> objects;     // Lijst met alle objecten (speler + muren)
};
