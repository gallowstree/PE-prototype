//
// Created by Alejandro on 28/07/16.
//

#include "Player.h"
#include "Wall.h"


Player::Player():
        speed(400),
        direction(),
        sprite()

{
    boundingBox = sf::FloatRect(sprite.getPosition().x, sprite.getPosition().y, 60, 60);
    type = EntityType::Player_T;
    resetMovementFlag();
}

void Player::update(sf::Time elapsedTime)
{
    updateMovement(elapsedTime);
}

void Player::updateMovement(sf::Time elapsedTime)
{

    //Fix no areas when player is in the edge of the map
    sf::Vector2f movement (0,0);
    if (direction[up_i] && sprite.getPosition().y - speed* elapsedTime.asSeconds() > movementBounds.top && canMove[up_i])
    {
        movement.y -= speed;
    }
    if (direction[left_i] && sprite.getPosition().x - speed * elapsedTime.asSeconds() > 0 && canMove[left_i])
    {
        movement.x -= speed;
    }
    if (direction[down_i] && sprite.getPosition().y < movementBounds.top + movementBounds.height && canMove[down_i])
    {
        movement.y += speed;
    }
    if (direction[right_i] && sprite.getPosition().x < movementBounds.top + movementBounds.width && canMove[right_i])
    {
        movement.x += speed;
    }

    sprite.move(movement * elapsedTime.asSeconds());
    boundingBox.top = sprite.getPosition().y;
    boundingBox.left = sprite.getPosition().x;

    resetMovementFlag();
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

    if (other->type == EntityType::Wall_T)
    {
        if (intersection.top > boundingBox.top + boundingBox.height / 2)
        {
            canMove[down_i] = false;
        }

        if (intersection.top < boundingBox.top + boundingBox.height / 2)
        {
            canMove[up_i] = false;
        }

        if (intersection.left < boundingBox.left + boundingBox.width / 2)
        {
            canMove[left_i] = false;
            printf("gato\n");
        }

        if (intersection.left > boundingBox.left + boundingBox.width / 2)
        {
            canMove[right_i] = false;
        }


    }
    else
    {

    }
}

void Player::resetMovementFlag()
{
    for (int i = 0; i < 4; i++)
    {
        canMove[i] = true;
    }
}








