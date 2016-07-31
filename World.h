//
// Created by Alejandro on 26/07/16.
//

#ifndef GAMEPLAY_PROTOTYPE_WORLD_H
#define GAMEPLAY_PROTOTYPE_WORLD_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "Player.h"


enum Textures
{
    CROSSHAIR,
    PLAYER_RED_SG
};

class World
{
public:
    World(sf::RenderWindow& window);

    void update(sf::Time elapsedTime);
    void render();
    void processEvents();
private:
    void updateCrosshair();
    void loadTextures();
    ResourceHolder<sf::Texture, Textures> textureHolder;
    Player player;
    sf::RenderWindow& window;
    sf::Sprite cursorSprite;
    sf::View camera;
    sf::Vector2f camCenter;
    sf::FloatRect bounds;

    void calculateCamCenter();
};




#endif //GAMEPLAY_PROTOTYPE_WORLD_H
