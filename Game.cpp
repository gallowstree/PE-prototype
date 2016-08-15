//
// Created by Alejandro on 18/07/16.
//

#include "Game.h"


Game::Game(sf::RenderWindow& window)
: window(window),
  TimePerFrame(sf::seconds(1.f/60.f)),
  world(window)
{
    window.setVerticalSyncEnabled(true);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    bool shouldRender = true;
    while (window.isOpen())
    {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(TimePerFrame);
            shouldRender = true;
        }

        if (shouldRender)
        {
            render();
            shouldRender = false;
        }

    }
}

void Game::render()
{
    window.clear();
    world.render();
    window.display();
}

void Game::update(sf::Time elapsedTime)
{
    world.update(elapsedTime);
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }
    world.processEvents();
}





