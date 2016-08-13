#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Menu.h"

using namespace std;

int main()
{
   sf::RenderWindow window(sf::VideoMode(800, 700), "SFML Application", sf::Style::Close);

   if(sf::FloatRect(10,10,100, 100).intersects(sf::FloatRect(20,20,40,40)))
   {
      printf("holiiiii");
   }
   else
   {
      return  0;
   }


   //Menu(window).run();
   Game(window).run();
}