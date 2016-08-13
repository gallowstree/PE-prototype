//
// Created by Alejandro on 28/07/16.
//

#include "Player.h"


Player::Player():
        speed(400),
        direction(),
        sprite()

{
    boundingBox = sf::FloatRect(sprite.getPosition().x, sprite.getPosition().y, 60, 60);
}

void Player::update(sf::Time elapsedTime)
{
    updateMovement(elapsedTime);
}

void Player::updateMovement(sf::Time elapsedTime)
{

    //Fix no areas when player is in the edge of the map
    sf::Vector2f movement (0,0);
    if (direction[up_i] && sprite.getPosition().y - speed* elapsedTime.asSeconds() > movementBounds.top)
    {
        movement.y -= speed;
    }
    if (direction[left_i] && sprite.getPosition().x - speed * elapsedTime.asSeconds() > 0)
    {
        movement.x -= speed;
    }
    if (direction[down_i] && sprite.getPosition().y < movementBounds.top + movementBounds.height)
    {
        movement.y += speed;
    }
    if (direction[right_i] && sprite.getPosition().x < movementBounds.top + movementBounds.width)
    {
        movement.x += speed;
    }

    sprite.move(movement * elapsedTime.asSeconds());
    boundingBox.top = sprite.getPosition().y;
    boundingBox.left = sprite.getPosition().x;
}

void Player::processEvents()
{
    direction[down_i] = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    direction[up_i] = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    direction[left_i] = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    direction[right_i] = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

void Player::setTexture(const sf::Texture &texture)
{
    sprite.setTexture(texture);
    //sprite.setColor(sf::Color::Green);
}

void Player::intersectedWith(Entity* other, sf::FloatRect intersection)
{
    Entity::intersectedWith(other, intersection);
}






