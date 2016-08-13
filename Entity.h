//
// Created by Alejandro on 13/08/16.
//

#ifndef GAMEPLAY_PROTOTYPE_ENTITY_H
#define GAMEPLAY_PROTOTYPE_ENTITY_H


#include <stdint.h>
#include <SFML/Graphics.hpp>
#include <queue>

class Entity
{
public:
    std::queue<int16_t> area();
    sf::FloatRect boundingBox;
    sf::FloatRect movementBounds;

    void intersectedWith(Entity& other)
    {

    }

};


#endif //GAMEPLAY_PROTOTYPE_ENTITY_H
