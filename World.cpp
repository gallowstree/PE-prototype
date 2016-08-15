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

    player.update(elapsedTime);

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

    updateCrosshair();
}

void World::render()
{
    calculateCamCenter();
    sf::FloatRect visibleRect(camCenter.x - window.getSize().x/2, camCenter.y - window.getSize().y/2, window.getSize().x, window.getSize().y);
    for (auto &area : areas)
    {
        if (area->rect.intersects(visibleRect))
        {
            area->draw(window, debugAreaGrid);
        }
    }

    debug_drawVisibleRect(visibleRect);

    for (const auto &staticEntity : world_entities)
    {
        auto drawRect = sf::RectangleShape(sf::Vector2f(staticEntity.boundingBox.width, staticEntity.boundingBox.height));
        drawRect.setPosition(staticEntity.boundingBox.left, staticEntity.boundingBox.top);
        drawRect.setFillColor(sf::Color::Cyan);

        window.draw(drawRect);
    }

    window.setView(camera);
    camera.setCenter(camCenter);

    debug_drawPlayerBox();
    debug_drawPlayerCollisionRects();
    window.draw(player.sprite);

    window.draw(cursorSprite);
}

void World::updateCrosshair()
{
    sf::Vector2f mousePositionFloat = window.mapPixelToCoords((sf::Mouse::getPosition(window)));
    sf::Vector2f spriteCenter = player.boundingBox.getPosition() + player.boundingBox.getSize() / 2.0f;//getSpriteCenter(player.sprite);
    sf::Vector2f facing = mousePositionFloat - spriteCenter;
    float rads = atan2f(facing.y, facing.x);
    float degs = rads * 180/M_PI;
    sf::IntRect spriteRect = player.sprite.getTextureRect();
    player.sprite.setOrigin(player.boundingBox.getSize() / 2.0f);
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
    camCenter = player.boundingBox.getPosition();

    if (player.boundingBox.getPosition().x < window.getSize().x / 2)
        camCenter.x =  window.getSize().x / 2;
    else if (player.boundingBox.getPosition().x > bounds.width - window.getSize().x / 2)
        camCenter.x = player.boundingBox.getPosition().x;//bounds.width - 300;

    if (player.boundingBox.getPosition().y < window.getSize().y / 2)
        camCenter.y =  window.getSize().y / 2;
    else if (player.boundingBox.getPosition().y > bounds.height - window.getSize().y / 2)
        camCenter.y = player.boundingBox.getPosition().y;//bounds.height - 300;
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
    Wall wall1(500, 500, 20, 1000);
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

void World::debug_drawVisibleRect(sf::FloatRect visibleRect)
{
    if (debugVisibleRect)
    {
        sf::RectangleShape visible = sf::RectangleShape();
        shapeFromFloatRect(visibleRect, visible);
        visible.setFillColor(sf::Color::Transparent);
        visible.setOutlineColor(sf::Color::Green);
        visible.setOutlineThickness(10);
        window.draw(visible);
    }
}

void World::debug_drawPlayerCollisionRects()
{
    for (auto& area: areasForEntity(player))
    {
        for (auto& other_entity : static_objects[area])
        {
            sf::FloatRect intersection;
            if (other_entity->boundingBox.intersects(player.boundingBox, intersection))
            {
                auto drawRect = sf::RectangleShape(sf::Vector2f(intersection.width, intersection.height ) );
                drawRect.setPosition(intersection.left, intersection.top);
                drawRect.setFillColor(sf::Color::Red);
                window.draw(drawRect);
            }
        }
    }
}

void World::debug_drawPlayerBox() const
{
    if (debugPlayerBox)
    {
        auto rect = sf::RectangleShape(sf::Vector2f(player.boundingBox.width, player.boundingBox.height));
        rect.setFillColor(sf::Color::Green);
        rect.setPosition(player.boundingBox.left, player.boundingBox.top);
        window.draw(rect);

        sf::RectangleShape cross  = sf::RectangleShape();
        cross.setFillColor(sf::Color::Magenta);
        shapeFromFloatRect(player.horz_rect, cross);
        window.draw(cross);
        shapeFromFloatRect(player.vert_rect, cross);
        window.draw(cross);
    }
}




















