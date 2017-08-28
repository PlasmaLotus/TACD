/*
Created by PlasmaLotus
Updated August 06, 2017
*/

#include "Controller.h"

/*The controller recieves input from a Keyboard or Joystick and outputs Commands to execute on the Board and Game*/
Controller::Controller(ControllerConfig* c) :

mode(ControlMode::Keyboard),
config(c)
{
	if (config != NULL) {
		config->loadConfig("controllerConfig.ini");
	}
}

Controller::~Controller()
{
}

void Controller::updateConfig(){

	if (!sf::Joystick::isConnected(config->getJoystickNumber()))
	{
		config->setJoystickNumber(0);
		joystickConnected = true;
	}
	else {
		joystickConnected = false;
	}
}

void Controller::setControlMode(ControlMode cm) {
	mode = cm;
}
/*Checks if any input is pressed and acts accordingly*/
void Controller::handleInput(){
	if (config != NULL) {
		
		handleInputKeyboard();
		handleInputJoystick();
	}
	for (int i = 0; i < ControllerCommand::CommandMax; i++) {
	
		if (buttonHeldTime[i] <= _buttonHeldTime[i]) {
			//button isnt held
			buttonHeld[i] = false;
		}
		else {
			buttonHeld[i] = true;
		}
		
		if (buttonHeld[i] == false) {
			buttonHeldTime[i] = buttonHeldTimeMinimum;// 0
		}
		
		_buttonHeldTime[i] = buttonHeldTime[i];

		buttonUsedThisTick[i] = false;
		/*
		if (buttonHeldTime[i] >= 0) {
		buttonHeld[i] = true;
		}
		else {
		buttonHeld[i] = false;
		}
		*/

		/*
		if (buttonHeld[i]) {
			buttonHeldTime[i]++;
		}
		else {
			buttonHeldTime[i] = -1;
		}
		
		buttonHeld[i] = false;
		*/
	}
	
    return;
}
/*Act accordingly to the needed commands*/
 
void Controller::handleInputKeyboard() {
	/*Check Every key on the keyboard for a conrresponding key*/
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(i);
		if (sf::Keyboard::isKeyPressed(key))
		{
			handleCommand(config->getCommand(key));
		}
	}
}
void Controller::handleInputJoystick() {
	unsigned int js = config->getJoystickNumber();
	/*Check Buttons*/
	for (unsigned int i = 0; i < sf::Joystick::getButtonCount(js); i++)
	{
		if (sf::Joystick::isButtonPressed(js, i)) {
			handleCommand(config->getCommand(i));
		}
	}
	/*Check Axis*/
	for (int i = 0; i < sf::Joystick::AxisCount; i++)
	{
		sf::Joystick::Axis axis = static_cast<sf::Joystick::Axis>(i);
		if (sf::Joystick::hasAxis(js, axis))
		{
			handleCommand(config->getCommand(axis, sf::Joystick::getAxisPosition(js, axis)));
		}
	}
	
}
void Controller::viewDebugJoystick() {
	if (mode == ControlMode::Joystick) {
		printf("\n");
		printf("XAxis: %f3.2\n", sf::Joystick::getAxisPosition(config->getJoystickNumber(), sf::Joystick::Axis::X));
		printf("YAxis: %f3.2\n", sf::Joystick::getAxisPosition(config->getJoystickNumber(), sf::Joystick::Axis::Y));
		printf("PovXAxis: %f3.2\n", sf::Joystick::getAxisPosition(config->getJoystickNumber(), sf::Joystick::Axis::PovX));
		printf("PovYAxis: %f3.2\n", sf::Joystick::getAxisPosition(config->getJoystickNumber(), sf::Joystick::Axis::PovY));
	}
	int joystick = 0;
	for (int i = 0; i > sf::Joystick::Count; i++) {
	}

}

void Controller::handleCommand(ControllerCommand command) {
	/*Apply action on the player dependant on the command*/
}
ControllerConfig* Controller::getConfig() {
	return config;
}



/*Checks if any input is pressed and acts accordingly*/
void Controller::__handleInput() {
	if (config != NULL) {
		switch (mode)
		{
		case Keyboard:
		{
			/*Check Every key on the keyboard for a conrresponding key*/
			for (int i = 0; i < sf::Keyboard::KeyCount; i++)
			{
				sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(i);
				if (sf::Keyboard::isKeyPressed(key))
				{
					handleCommand(config->getCommand(key));
				}
			}
			break;
		}
		case Joystick:
		{
			unsigned int js = config->getJoystickNumber();
			/*Check Buttons*/
			for (unsigned int i = 0; i < sf::Joystick::getButtonCount(js); i++)
			{
				if (sf::Joystick::isButtonPressed(js, i)) {
					handleCommand(config->getCommand(i));
				}
			}
			/*Check Axis*/
			for (int i = 0; i < sf::Joystick::AxisCount; i++)
			{
				sf::Joystick::Axis axis = static_cast<sf::Joystick::Axis>(i);
				if (sf::Joystick::hasAxis(js, axis))
				{
					handleCommand(config->getCommand(axis, sf::Joystick::getAxisPosition(js, axis)));
				}
			}
			break;
		}
		default: break;
		}
	}
	for (int i = 0; i < ControllerCommand::CommandMax; i++) {


		if (buttonHeldTime[i] <= _buttonHeldTime[i]) {
			//button isnt held
			buttonHeld[i] = false;
		}
		else {
			buttonHeld[i] = true;
		}

		if (buttonHeld[i] == false) {
			buttonHeldTime[i] = buttonHeldTimeMinimum;// 0
		}

		_buttonHeldTime[i] = buttonHeldTime[i];

		buttonUsedThisTick[i] = false;
		/*
		if (buttonHeldTime[i] >= 0) {
		buttonHeld[i] = true;
		}
		else {
		buttonHeld[i] = false;
		}
		*/

		/*
		if (buttonHeld[i]) {
		buttonHeldTime[i]++;
		}
		else {
		buttonHeldTime[i] = -1;
		}

		buttonHeld[i] = false;
		*/
	}

	return;
}

void Controller::__updateConfig() {
	if (mode == ControlMode::Keyboard) {
		if (sf::Joystick::isConnected(0))
		{
			mode = ControlMode::Joystick;
			config->setJoystickNumber(0);
		}
		else
		{
			mode = ControlMode::Keyboard;
		}
	}
	else if (mode == ControlMode::Joystick) {

		if (!sf::Joystick::isConnected(config->getJoystickNumber()))
		{
			mode = Keyboard;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			mode = Keyboard;
		}
	}
}