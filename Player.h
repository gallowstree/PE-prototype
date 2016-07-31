//
// Created by Alejandro on 28/07/16.
//

#ifndef GAMEPLAY_PROTOTYPE_PLAYER_H
#define GAMEPLAY_PROTOTYPE_PLAYER_H

#include <SFML/Graphics.hpp>

#define up 0
#define down 1
#define right 2
#define left 3


class Player
{
public:
    Player();
    void					processEvents();
    void					update(sf::Time elapsedTime);
    void					updateMovement(sf::Time elapsedTime);
    void                    setTexture(const sf::Texture& texture);

    float speed;
    sf::Sprite sprite;
    bool direction[4];
};


#endif //GAMEPLAY_PROTOTYPE_PLAYER_H
