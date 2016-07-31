//
// Created by Alejandro on 28/07/16.
//

#include "Player.h"


Player::Player():
        speed(500),
        direction(),
        sprite()
{

}

void Player::update(sf::Time elapsedTime)
{
    updateMovement(elapsedTime);
}

void Player::updateMovement(sf::Time elapsedTime)
{
    sf::Vector2f movement (0,0);
    if (direction[up])
    {
        movement.y -= speed;
    }
    if (direction[left])
    {
        movement.x -= speed;
    }
    if (direction[down])
    {
        movement.y += speed;
    }
    if (direction[right])
    {
        movement.x += speed;
    }

    sprite.move(movement * elapsedTime.asSeconds());
}

void Player::processEvents()
{
    direction[down] = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
    direction[up] = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
    direction[left] = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
    direction[right] = sf::Keyboard::isKeyPressed(sf::Keyboard::D);
}

void Player::setTexture(const sf::Texture &texture)
{
    sprite.setTexture(texture);
}





