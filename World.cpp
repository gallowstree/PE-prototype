//
// Created by Alejandro on 26/07/16.
//

#include <math.h>
#include "World.h"
#include "SFUtils.h"
#include "Wall.h"

World::World(sf::RenderWindow& window) :
textureHolder(),
player(),
window(window),
cursorSprite(),
bounds(0,0,2400.0f, 2400.0f),
camera(),
camCenter(),
areas(),
static_objects()
{
    loadTextures();
    player.setTexture(textureHolder.get(Textures::PLAYER_RED_SG));
    player.movementBounds = sf::FloatRect(0,0, 2400.0f, 2400.0f);
    cursorSprite.setTexture(textureHolder.get(Textures::CROSSHAIR));
    camera.reset(sf::FloatRect(0,0, window.getSize().x, window.getSize().y));
    camera.setViewport(sf::FloatRect(0,0, 1.0f, 1.0f));
    init();

}

void World::update(sf::Time elapsedTime) {

    for (auto& area: areasForEntity(player))
    {
        for (auto& other_entity : static_objects[area])
        {
            sf::FloatRect intersection;
            if (other_entity->boundingBox.intersects(player.boundingBox, intersection))
            {
                player.intersectedWith(other_entity, intersection);
            }
        }
    }

    player.update(elapsedTime);

    player.intersectedWith(&player, sf::FloatRect());

    //debugEntitiesInArea();

    updateCrosshair();
}

void World::render()
{
    calculateCamCenter();

    sf::FloatRect visibleRect(camCenter.x - window.getSize().x /3, camCenter.y - window.getSize().y /3, window.getSize().x, window.getSize().y);

    int areaId = 0;
    for (auto &area : areas)
    {
        if (area->rect.intersects(visibleRect))
        {
            area->draw(window);
            //printf("Drawing area: %d ", areaId);
        }
        areaId++;
    }
    //printf("\n");

    for (const auto &staticEntity : world_entities)
    {
        auto drawRect = sf::RectangleShape(sf::Vector2f(staticEntity.boundingBox.width, staticEntity.boundingBox.height));
        drawRect.setPosition(staticEntity.boundingBox.left, staticEntity.boundingBox.top);
        drawRect.setFillColor(sf::Color::Cyan);

        window.draw(drawRect);
    }



    window.setView(camera);
    camera.setCenter(camCenter);
    auto rect = sf::RectangleShape(sf::Vector2f(player.boundingBox.width, player.boundingBox.height));
    rect.setFillColor(sf::Color::Green);
    rect.setPosition(player.sprite.getPosition());
    //rect.setRotation(player.sprite.getRotation());
    window.draw(rect);
    for (auto& area: areasForEntity(player))
    {
        for (auto& other_entity : static_objects[area])
        {
            sf::FloatRect intersection;
            if (other_entity->boundingBox.intersects(player.boundingBox, intersection))
            {
                printf("Player collision with entity id: %d at: x:%f, y:%f, w:%f, h:%f\n", other_entity->id,  intersection.left, intersection.top, intersection.width, intersection.height);
                auto drawRect = sf::RectangleShape(sf::Vector2f(intersection.width, intersection.height ) );
                drawRect.setPosition(intersection.left, intersection.top);
                drawRect.setFillColor(sf::Color::Red);
                window.draw(drawRect);
            }
        }
    }
    window.draw(player.sprite);




    window.draw(cursorSprite);

}

void World::updateCrosshair()
{
    sf::Vector2f mousePositionFloat = window.mapPixelToCoords((sf::Mouse::getPosition(window)));
    sf::Vector2f spriteCenter = getSpriteCenter(player.sprite);
    sf::Vector2f facing = mousePositionFloat - spriteCenter;
    float rads = atan2f(facing.y, facing.x);
    float degs = rads * 180/M_PI;
    sf::IntRect spriteRect = player.sprite.getTextureRect();
    player.sprite.setOrigin(sf::Vector2f(spriteRect.width/ 2, spriteRect.height / 2));
    player.sprite.setRotation(degs);

    sf::IntRect cursorSpriteRect = cursorSprite.getTextureRect();
    cursorSprite.setPosition(mousePositionFloat - sf::Vector2f(cursorSpriteRect.width*1.5f , cursorSpriteRect.height*1.5f));
}

void World::loadTextures()
{
    textureHolder.load(Textures::CROSSHAIR, "files/crosshair.png");
    textureHolder.load(Textures::PLAYER_RED_SG, "files/sprite.png");
}

void World::processEvents() {
    player.processEvents();
}

void World::calculateCamCenter()
{
    camCenter = player.sprite.getPosition();

    if (player.sprite.getPosition().x < window.getSize().x / 2)
        camCenter.x =  window.getSize().x / 2;
    else if (player.sprite.getPosition().x > bounds.width - window.getSize().x / 2)
        camCenter.x = player.sprite.getPosition().x;//bounds.width - 300;

    if (player.sprite.getPosition().y < window.getSize().y / 2)
        camCenter.y =  window.getSize().y / 2;
    else if (player.sprite.getPosition().y > bounds.height - window.getSize().y / 2)
        camCenter.y = player.sprite.getPosition().y;//bounds.height - 300;
}

std::vector<int16_t> World::areasForEntity(const Entity &entity)
{
    std::vector<int16_t> areas;

    int i = 0;
    for (auto &area : this->areas)
    {

        if (area->rect.intersects(entity.boundingBox))
        {
            areas.push_back(i);
            //printf("%i ",i);
        }

        i++;
    }
    //printf("\n");
    return areas;
}

void World::init()
{
    int noAreasX = 0;
    int noAreasY = 0;

    float area_size = 400;

    noAreasX = bounds.width / area_size;
    noAreasY = bounds.height / area_size;

    for (int x = 0; x < noAreasX; x++)
    {
        for (int y = 0; y < noAreasY; y++)
        {
            Area* newArea = new Area(x*area_size, y*area_size, area_size, area_size);
            areas.push_back(newArea);
            static_objects.push_back(std::vector<Entity*>());
        }
    }



    createStaticObjects();
}

void World::createStaticObjects()
{
    Wall wall1(0, 0, 1000, 20);
    Wall wall2(100, 500, 500, 20);
    world_entities.push_back(wall1);
    world_entities.push_back(wall2);

    for (auto& entity : world_entities)
    {
        if (entity.isStatic)
        {
            for (auto& area : areasForEntity(entity))
            {
                static_objects[area].push_back(&entity);
            }
        }
    }

}

void World::debugEntitiesInArea()
{
    int areaIndex = 0;
    for (auto& area : static_objects)
    {
        if (area.size() > 0)
            printf("area %d has entities ", areaIndex);
        for (auto& entity : area)
        {
            printf("%d ", entity->id);
        }
        if (area.size() > 0)
            printf("\n");
        areaIndex++;
    }
    printf("\n");
}




















