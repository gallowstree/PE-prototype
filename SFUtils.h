//
// Created by Alejandro on 28/07/16.
//

#ifndef GAMEPLAY_PROTOTYPE_SFUTILS_H
#define GAMEPLAY_PROTOTYPE_SFUTILS_H

#import <SFML/Graphics.hpp>

sf::Vector2f getSpriteCenter(const sf::Sprite& sprite)
{
    sf::IntRect spriteRect = sprite.getTextureRect();
    sf::Vector2f spriteCenter = sprite.getPosition() + sf::Vector2f(spriteRect.width/ 2, spriteRect.height / 2);
    return spriteCenter;
}


void shapeFromFloatRect(const sf::FloatRect& rect, sf::RectangleShape& shape)
{
    shape.setSize(sf::Vector2f(rect.width, rect.height));
    shape.setPosition(rect.left, rect.top);
}
#endif //GAMEPLAY_PROTOTYPE_SFUTILS_H
