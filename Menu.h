//
// Created by Alejandro on 26/07/16.
//

#ifndef GAMEPLAY_PROTOTYPE_MENU_H
#define GAMEPLAY_PROTOTYPE_MENU_H


#include <SFML/Graphics.hpp>

class Menu {

public:
    Menu(sf::RenderWindow& window);

    void run();
    sf::RenderWindow&  window;

    void render();
};


#endif //GAMEPLAY_PROTOTYPE_MENU_H
