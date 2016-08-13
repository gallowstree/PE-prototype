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
    static int16_t lastId;
    sf::FloatRect boundingBox;
    sf::FloatRect movementBounds;
    int16_t id;
    bool isStatic;

    Entity();

    void intersectedWith(Entity* other, sf::FloatRect intersection);


};


#endif //GAMEPLAY_PROTOTYPE_ENTITY_H
