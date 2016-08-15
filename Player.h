//
// Created by Alejandro on 28/07/16.
//

#ifndef GAMEPLAY_PROTOTYPE_PLAYER_H
#define GAMEPLAY_PROTOTYPE_PLAYER_H

#include <SFML/Graphics.hpp>
#include "Entity.h"

#define up_i 0
#define down_i 1
#define right_i 2
#define left_i 3


class Player : public Entity
{
public:
    Player();
    void					processEvents();
    void					update(sf::Time elapsedTime);
    void					updateMovement(sf::Time elapsedTime);
    void                    setTexture(const sf::Texture& texture);

    float speed;
    sf::Sprite sprite;
    sf::FloatRect vert_rect;
    sf::FloatRect horz_rect;
    bool direction[4];
    float cross_thickness;

    void intersectedWith(Entity *other, sf::FloatRect intersection);

    void updateCross();
};


#endif //GAMEPLAY_PROTOTYPE_PLAYER_H
