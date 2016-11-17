
#include "SFML.h"
#include "Board.h"

#ifndef _Game_
#define _Game_

class Game{
	
public:

	Board b1;
	Board b2;
	sf::RenderWindow window;
	//sf::RenderWindow window(sf::VideoMode(800, 600), "Why doesnt the block draw");

Game();
~Game();

void init();

int test2();

int test();

void run();


private:

	void draw();
	void display();
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;

};

#endif // !_Game_

