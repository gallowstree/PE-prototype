#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"

using namespace std;

int main()
{
   sf::RenderWindow window(sf::VideoMode(800, 700), "SFML Application", sf::Style::Close);

   //Menu(window).run();
   Game(window).run();
}