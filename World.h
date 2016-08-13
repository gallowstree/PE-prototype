//
// Created by Alejandro on 26/07/16.
//

#ifndef GAMEPLAY_PROTOTYPE_WORLD_H
#define GAMEPLAY_PROTOTYPE_WORLD_H

#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "Player.h"
#include "Entity.h"
#include "Area.h"
#include <queue>

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


    std::vector<int16_t> areasForEntity(const Entity &entity);

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
    std::vector<Area*> areas;

    //Every position in the first vector represents an area (area 0, 1, ..., n)
    //Every vector in each position has references to every object in the area
    std::vector<std::vector<Entity*>> static_objects;

    std::vector<Entity> world_entities;

    void calculateCamCenter();

    void init();

    void createStaticObjects();

    void debugEntitiesInArea();
};




#endif //GAMEPLAY_PROTOTYPE_WORLD_H
