/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "MenuController.h"

/*The controller recieves input from a Keyboard or Joystick and outputs Commands to execute on the Board and Game*/


MenuController::MenuController(ControllerConfig* c, Menu* m) :
Controller(c),
menu(m)
{
	config.loadConfig("controllerConfig.ini");
	buttonCanBeHeld[ControllerCommand::Left] = true;
	buttonCanBeHeld[ControllerCommand::Right] = true;
	buttonCanBeHeld[ControllerCommand::Up] = true;
	buttonCanBeHeld[ControllerCommand::Down] = true;
	buttonCanBeHeld[ControllerCommand::ForceRaise] = true;
}

MenuController::~MenuController()
{
}

/*Act accordingly to the needed commands*/
void MenuController::handleCommand(ControllerCommand command){
    /*Apply action on the player dependant on the command*/
	buttonHeldTime[command]++;
	buttonHeld[command] = true;
	if (buttonHeldTime[command] <= 0 ||
		(buttonCanBeHeld[command] == true && buttonHeldTime[command] >= buttonHeldTimeLimit) ) {
		if (menu != NULL) {
			switch (command)
			{
			case ControllerCommand::Up:
			{
				menu->inputUp();
				break;
			}
			case ControllerCommand::Down:
			{
				menu->inputDown();
				break;
			}
			case ControllerCommand::Left:
			{
				menu->inputLeft();
				break;
			}
			case ControllerCommand::Right:
			{
				menu->inputRight();
				break;
			}
			case ControllerCommand::Swap:
			{
				menu->inputSelect();
				break;
			}
			case ControllerCommand::SwapAlt:
			{
				menu->inputBack();
				break;
			}
			case ControllerCommand::ForceRaise:
			{
				break;
			}
			case ControllerCommand::Pause:
			{
				menu->inputSelect();
				break;
			}
			case ControllerCommand::Cheat:
			{
				//board->Cheat();
				break;
			}
			case ControllerCommand::NoInput:
			default: break;
			}
		}
	}
}
    
void MenuController::setMenu(Menu* b){
        menu = b;
}
