/*
Created by PlasmaLotus
Updated May 13, 2017
*/



#ifndef _Game_
#define _Game_

#include "Board.h"
#include "TestBoard.h"
#include "../Main.h"

enum GameCurrentState{RUNNING, PAUSED, ENDED};

class Game{
	
public:
	int frame = 0;


	Board b1;
	Board b2;
	Board b3;
	Board b4;
	GameCurrentState gameState;
	Game();
	~Game();

	void reset();
	void tick();

	void pause();

private:

	bool ControllerUp = false;
	bool ControllerDown = false;
	bool ControllerLeft = false;
	bool ControllerRight = false;
	bool ControllerSwap = false;



};

#endif // !_Game_

