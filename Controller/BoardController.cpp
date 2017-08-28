/*
Created by PlasmaLotus
Updated August 06, 2017
*/

#include "BoardController.h"

/*The controller recieves input from a Keyboard or Joystick and outputs Commands to execute on the Board and Game*/
BoardController::BoardController(ControllerConfig* c, Game * g, Board* b):
	Controller(c),
	board(b),
	game(g)
{
	/*
	Controller::Controller(c);
	config = c;
	board = b;
	game = g;
	mode = ControlMode::Keyboard;
	*/
	if (config != NULL) {
		config->loadConfig("controllerConfig.ini");
	}
	buttonCanBeHeld[ControllerCommand::Left] = true;
	buttonCanBeHeld[ControllerCommand::Right] = true;
	buttonCanBeHeld[ControllerCommand::Up] = true;
	buttonCanBeHeld[ControllerCommand::Down] = true;
	buttonCanBeHeld[ControllerCommand::ForceRaise] = true;
	//buttonCanBeHeld[ControllerCommand::Swap] = false;
	//buttonCanBeHeld[ControllerCommand::SwapAlt] = false;

}

BoardController::~BoardController()
{
}

/*Act accordingly to the needed commands*/
void BoardController::handleCommand(ControllerCommand command){
    /*Apply action on the player dependant on the command*/

	if (command == ControllerCommand::Swap || command == ControllerCommand::SwapAlt) {
		int debug = 1;
	}
	if (command == ControllerCommand::Up ) {
		int debug = 2;
	}

	/*
	if (buttonCanBeHeld[command] == false) {
			if (buttonHeld[command] == true){}
	}
	else 
	*/
	if (!buttonUsedThisTick[command]) {
		buttonUsedThisTick[command] = true;
		if (buttonHeldTime[command] <= 0 ||
				(buttonCanBeHeld[command] == false  && buttonHeld[command] == false )||
				(buttonCanBeHeld[command] == true && buttonHeldTime[command] >= buttonHeldTimeLimit) ) {
				if (board != NULL) {
					switch (command)
					{
					case ControllerCommand::Up:
					{
						board->moveCursorUp();
						break;
					}
					case ControllerCommand::Down:
					{
						board->moveCursorDown();
						break;
					}
					case ControllerCommand::Left:
					{
						board->moveCursorLeft();
						break;
					}
					case ControllerCommand::Right:
					{
						board->moveCursorRight();
						break;
					}
					case ControllerCommand::Swap:
					{
						board->swapBlocks();
						break;
					}
					case ControllerCommand::SwapAlt:
					{
						board->swapBlocks();
						break;
					}
					case ControllerCommand::ForceRaise:
					{
						board->forceRaise();
						break;
					}
					case ControllerCommand::Pause:
					{
						if (game != NULL) {
							game->pause();
						}
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
	
	
	buttonHeldTime[command]++;
	buttonHeld[command] = true;
}
    
void BoardController::setBoard(Board* b){
        board = b;
}
