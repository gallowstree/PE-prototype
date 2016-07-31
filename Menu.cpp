//
// Created by Alejandro on 26/07/16.
//

#include "Menu.h"

Menu::Menu(sf::RenderWindow& window)
: window(window)
{


}

void Menu::run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyReleased:
                    return;
                default:
                    break;
            }
        }

        render();
    }
}


void Menu::render()
{
    auto circle = sf::CircleShape(10);
    circle.setFillColor(sf::Color::Blue);
    window.clear();
    window.draw(circle);
    window.display();
}

