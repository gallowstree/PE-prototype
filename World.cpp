//
// Created by Alejandro on 26/07/16.
//

#include <math.h>
#include "World.h"
#include "SFUtils.h"

World::World(sf::RenderWindow& window) :
textureHolder(),
player(),
window(window),
cursorSprite(),
bounds(0,0,2000.0f, 2000.0f),
camera(),
camCenter()
{
    loadTextures();
    player.setTexture(textureHolder.get(Textures::PLAYER_RED_SG));
    cursorSprite.setTexture(textureHolder.get(Textures::CROSSHAIR));
    camera.reset(sf::FloatRect(0,0, 800, 700));
    camera.setViewport(sf::FloatRect(0,0, 1.0f, 1.0f));
}

void World::update(sf::Time elapsedTime) {
    player.update(elapsedTime);
    updateCrosshair();
}

void World::render()
{
    calculateCamCenter();

    window.setView(camera);
    camera.setCenter(camCenter);
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

    if (player.sprite.getPosition().x < 400)
        camCenter.x = 400;
    else if (player.sprite.getPosition().x > bounds.width - 400)
        camCenter.x = bounds.width - 400;

    if (player.sprite.getPosition().y < 400)
        camCenter.y = 400;
    else if (player.sprite.getPosition().y > bounds.height - 400)
        camCenter.y = bounds.height - 400;
}











