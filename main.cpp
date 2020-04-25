#include <SFML/Graphics.hpp>
#include "Alien.h"
#include "Crab.h"
#include "Octopus.h"
#include "Squid.h"

#define NUMALIENS 9
#define ALIENSPEED 20

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	Alien* alienArray[NUMALIENS] = { new Crab(200,100),new Crab(300,100), new Crab(400,100), 
		new Squid(200,200), new Squid(300,200), new Squid(400,200),
		new Octopus(200,300), new Octopus(300,300), new Octopus(400,300)};
	

	int count = 0, downCount = 0;
	char direction = 'r', lastDirection = 'r';
	while (window.isOpen())
	{
		count++;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//draw all the aliens
		for (int i = 0; i < NUMALIENS; i++) {
			alienArray[i]->drawAlien(window);
		}

		// MOVE ALIENS IN ZIG ZAG PATTERN
		if (count % 1000 ==0) { // they only move every 1000th run, makes them "jump" like in the game
			for (int i = 0; i < NUMALIENS; i++) { // do for every alien
			if (direction == 'd') { // if direction should be down, move all dowb
				i = NUMALIENS; // resent counter so we start at 1st alien next loop
				for (int k = 0; k < NUMALIENS;k++) {
					alienArray[k]->moveAlien('d', ALIENSPEED); // move all the aliens down
				}
				if (lastDirection == 'r') { // switch from r to l
					direction = 'l';
				}
				else if (lastDirection == 'l') { // switch from l to r
					direction = 'r';
				}
			}
			else {
				alienArray[i]->moveAlien(direction, ALIENSPEED); // move left or right
				sf::Vector2f alienPos = alienArray[i]->getPosition();
				if (direction == 'r') {
					if (alienPos.x > 750) { //if we reach right border, move down
						for (int j = i + 1; j < NUMALIENS; j++) {
							alienArray[j]->moveAlien(direction, ALIENSPEED); // move the rest of the aliens before moving down
						}
						direction = 'd';
						lastDirection = 'r';
					}
				}
				else if (direction == 'l') {
					if (alienPos.x < 50) { // if we reach left border move down
						for (int j = i + 1; j < NUMALIENS; j++) {
							alienArray[j]->moveAlien(direction, ALIENSPEED); // move the rest of the aliens before moving down
						}
						direction = 'd';
						lastDirection = 'l';
					}
				}
			}
			}
			window.display();
			window.clear();

		}

		
	}
	return 0;
}