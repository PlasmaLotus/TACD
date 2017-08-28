/*
Created by PlasmaLotus
Updated August 06, 2017
*/

#ifndef _Controller_H_
#define _Controller_H_

#include "SFML\Window.hpp"
#include "ControllerConfig.h"

class Controller {
public:

	Controller(ControllerConfig* c);
	~Controller();
	void updateConfig();
	void __updateConfig();
	void setControlMode(ControlMode mode);
	void handleInput();
	void __handleInput();
	void handleInputKeyboard();
	void handleInputJoystick();

	void viewDebugJoystick();
	ControllerConfig * getConfig();
	ControlMode mode;
	ControllerConfig* config;
	virtual void handleCommand(ControllerCommand command);

	const int buttonHeldTimeLimit = 20;
	const int buttonHeldTimeMinimum = 0;
	bool buttonHeld[ControllerCommand::CommandMax] = { true };
	bool buttonUsedThisTick[ControllerCommand::CommandMax] = { false };
	int buttonHeldTime[ControllerCommand::CommandMax] = { buttonHeldTimeMinimum };
	int _buttonHeldTime[ControllerCommand::CommandMax] = { buttonHeldTimeMinimum };
	bool buttonCanBeHeld[ControllerCommand::CommandMax] = { false };
	bool keyboardConnected = true;
	bool joystickConnected = false;
};

#endif // _Controller_H_
