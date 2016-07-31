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

#endif //GAMEPLAY_PROTOTYPE_SFUTILS_H
