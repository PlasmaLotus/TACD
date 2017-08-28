/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#ifndef _Board_Controller_H_
#define _Board_Controller_H_

#include "Controller.h"
#include "../Board/Board.h"
#include "../Board/Game.h"

class BoardController : public Controller{
public:

	BoardController(ControllerConfig* config, Game* game, Board * b);
	~BoardController();
	void setBoard(Board* b);
	//void viewDebugJoystick();

private:
	Board* board;
	Game* game;
	void handleCommand(ControllerCommand command);

};

#endif // _Board_Controller_H_
