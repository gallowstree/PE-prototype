//
// Created by Alejandro on 18/07/16.
//

#ifndef GAMEPLAY_PROTOTYPE_GAME_H
#define GAMEPLAY_PROTOTYPE_GAME_H


#include <SFML/Graphics.hpp>
#include <map>
#include <string.h>
#include "World.h"

class Game
{
public:
    Game(sf::RenderWindow& window);
    void run();
    sf::RenderWindow& window;
    sf::Time TimePerFrame;
    World world;

    void processEvents();

    void update(sf::Time time);

    void render();

};


#endif //GAMEPLAY_PROTOTYPE_GAME_H
