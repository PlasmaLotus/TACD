/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#include "GameRenderer.h"
#include "Board.h"
#include "TestBoard.h"
#include "../Controller/Controller.h"

#ifndef _Game_
#define _Game_

#define TILE_SIZE 32

class Game{
	
public:

	Board b1;
	//TestBoard b1;
	Board b2;
	Controller p1Controller;
	sf::RenderWindow *window;

	Game();
	Game(sf::RenderWindow &w);
	~Game();
	/*Game Time*/
	int frame;
	int second;
	int minute;
	int milisecond;
	/*~Game Time*/

	void reset();
	void init();
	void initController();
	void run();
	void render();
	void tick();

	void handleInputPressRelease(sf::Event event, Board & board);
	void handleInput(sf::Event event, Board & board);
	ControllerCommand handleInput(sf::Event event, ControllerCommand & input);
	ControllerCommand handleInput(sf::Event event);

private:
	GameRenderer renderer;


	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;

	bool ControllerUp = false;
	bool ControllerDown = false;
	bool ControllerLeft = false;
	bool ControllerRight = false;
	bool ControllerSwap = false;


};

#endif // !_Game_

