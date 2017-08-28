/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#ifndef _Menu_Controller_H_
#define _Menu_Controller_H_

#include "Controller.h"
#include "../Menu/Menu.h"

class MenuController : public Controller {
public:

	
	MenuController(ControllerConfig* config, Menu* menu);
	~MenuController();
	//void updateConfig();
	//void handleInput();
	void setMenu(Menu* b);

	//void viewDebugJoystick();

private:
	Menu* menu;
	ControlMode mode;
	ControllerConfig config;
	ControllerConfig* config_;
	void handleCommand(ControllerCommand command);
	bool buttonHeld[ControllerCommand::CommandMax];
	int buttonHeldTime[ControllerCommand::CommandMax];
	bool buttonCanBeHeld[ControllerCommand::CommandMax] = {false};
	const int buttonHeldTimeLimit = 35;
};

#endif // _Controller_H_
