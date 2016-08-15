//
// Created by Alejandro on 28/07/16.
//

#include "Player.h"
#include "Wall.h"


Player::Player():
        speed(1000),
        direction(),
        sprite(),
        cross_thickness(5)

{
    boundingBox = BoundingBox(sprite.getPosition().x, sprite.getPosition().y, 50, 50);
    updateCross();
    type = EntityType::Player_T;
    horz_rect.width = boundingBox.width;
    vert_rect.height = boundingBox.height;
}

void Player::update(sf::Time elapsedTime)
{
    updateMovement(elapsedTime);
}

void Player::updateMovement(sf::Time elapsedTime)
{

    //Fix no areas when player is in the edge of the map
    sf::Vector2f movement (0,0);
    if (direction[up_i] && boundingBox.getPosition().y - speed* elapsedTime.asSeconds() > movementBounds.top)
    {
        movement.y -= speed;
    }
    if (direction[left_i] && boundingBox.getPosition().x - speed * elapsedTime.asSeconds() > 0)
    {
        movement.x -= speed;
    }
    if (direction[down_i] && boundingBox.getPosition().y < movementBounds.top + movementBounds.height)
    {
        movement.y += speed;
    }
    if (direction[right_i] && boundingBox.getPosition().x < movementBounds.top + movementBounds.width)
    {
        movement.x += speed;
    }

    movement *= elapsedTime.asSeconds();
    boundingBox.top += movement.y;
    boundingBox.left += movement.x;
    updateCross();

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
        if (intersection.intersects(vert_rect))
        {
            if (intersection.top > boundingBox.top + boundingBox.height / 2)
            {
                boundingBox.top -= intersection.height;
                //sprite.move(0, -intersection.height);
            }

            if (intersection.top < boundingBox.top + boundingBox.height / 2)
            {
                boundingBox.top += intersection.height;
                //sprite.move(0, intersection.height);
            }
        }

        if (intersection.intersects(horz_rect))
        {
            if (intersection.left < boundingBox.left + boundingBox.width / 2)
            {
                boundingBox.left += intersection.width;
                //sprite.move(intersection.width, 0);
            }

            if (intersection.left > boundingBox.left + boundingBox.width / 2)
            {
                boundingBox.left -= intersection.width;
                //sprite.move(-intersection.width, 0);
            }
        }
        updateCross();
    }
    else
    {

    }
}

void Player::updateCross()
{
    vert_rect.left = boundingBox.left + boundingBox.width / 2 - cross_thickness/2;
    vert_rect.top = boundingBox.top;
    vert_rect.width = cross_thickness;
    horz_rect.left = boundingBox.left;
    horz_rect.top = boundingBox.top  + boundingBox.height / 2 - cross_thickness/2;
    horz_rect.height = cross_thickness;
    sprite.setPosition(boundingBox.left + boundingBox.width/2, boundingBox.top + boundingBox.height/2);
}










