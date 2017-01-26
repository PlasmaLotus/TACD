#ifndef _Controller_H_
#define _Controller_H_

#include "SFML\Window.hpp"
#include "ControllerConfig.h"
#include "../Board/Board.h"
#include "../Board/GeneralEnum.h"

class Controller {
public:

	Controller();
	Controller(Board * b);
	~Controller();
	void updateConfig();
	void handleInput();
	void setBoard(Board* b);

private:
	Board* board;

	ControlMode mode;
	ControllerConfig config;
	void handleCommand(ControllerCommand command);
	bool swapHeld;
	int swapHeldCounter;
	bool *buttonHeld;

};

#endif // _Controller_H_
