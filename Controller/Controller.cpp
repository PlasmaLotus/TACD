#include "Controller.h"

/*The controller recieves input from a Keyboard or Joystick and outputs Commands to execute*/

Controller::Controller():
swapHeld(false),
swapHeldCounter(0),
mode(ControlMode::Keyboard)
{
	config.loadConfig("controllerConfig.ini");
}

Controller::Controller(Board* b) :
swapHeld(false),
swapHeldCounter(0),
mode(ControlMode::Keyboard),
board(b)
{
	config.loadConfig("controllerConfig.ini");
}

Controller::~Controller()
{
}

void Controller::updateConfig(){
    if (mode == ControlMode::Keyboard){
        if (sf::Joystick::isConnected(0))
        {
            mode = ControlMode::Joystick;
			config.setJoystickNumber(0);
			//buttonHeld = (bool*) malloc(sf::Joystick::getButtonCount(0)*sizeof(bool));
        }
        else
        {
        }
    }
    else if (mode == ControlMode::Joystick){
		
		if (!sf::Joystick::isConnected(config.getJoystickNumber()))
		{
			mode = Keyboard;
		}
        //config = new JoystickConfig;
        //handle switching to keyboard mode
    }
    //config.load("controller.ini");
}

/*Checks if any input is pressed and acts accordingly*/
void Controller::handleInput(){
    
    //InputHandler inputHandler;
	if (--swapHeldCounter < 0)
	{
		swapHeld = false;
	}

    switch (mode)
    {
        case Keyboard:
        {
            //config.up()
            //polling is done strait here...
			//for (auto& X : config.getKeys())
			for (int i = 0; i < sf::Keyboard::KeyCount; i++)
			{
				sf::Keyboard::Key key = static_cast<sf::Keyboard::Key>(i);
				if (sf::Keyboard::isKeyPressed(key))
				{
					handleCommand(config.getCommand(key));
				}
			}
            break;
        }
        case Joystick:
        {
			unsigned int js = config.getJoystickNumber();

			/*Check Buttons*/
			for (unsigned int i = 0; i < sf::Joystick::getButtonCount(js); i++)
			{
				if (sf::Joystick::isButtonPressed(js, i)) {
					handleCommand(config.getCommand(i));
				}
			}

			/*Check Axis*/
			for (int i = 0; i < sf::Joystick::AxisCount; i++)
			{
				sf::Joystick::Axis axis = static_cast<sf::Joystick::Axis>(i);
				if (sf::Joystick::hasAxis(js, axis))
				{
					handleCommand(config.getCommand(axis, sf::Joystick::getAxisPosition(js, axis)));
				}
			}
			/*
			if (sf::Joystick::hasAxis(js, sf::Joystick::Axis::PovX))
			{
				handleCommand(config.getCommand(sf::Joystick::Axis::PovX, sf::Joystick::getAxisPosition(js, sf::Joystick::Axis::PovX)));
			}
			...
			*/
            break;
        }
        default: break;
        
    }
    return;
}
/*Act accordingly to the needed commands*/
void Controller::handleCommand(ControllerCommand command){
    /*Apply action on the player dependant on the command*/

    switch (command) 
    {
        case ControllerCommand::Up :
		{
			if (board != NULL) {
				board->moveCursorUp();
			}
			break;
		}
        case ControllerCommand::Down :
		{
			if (board != NULL) {
				board->moveCursorDown();
			}
			break;
		}
        case ControllerCommand::Left :
		{
			if (board != NULL) {
				board->moveCursorLeft();
			}
			break;
		}
        case ControllerCommand::Right :
        {
            if (board != NULL){
				board->moveCursorRight();
            }
			break;
        }
        case ControllerCommand::Swap :
        {
            if (board != NULL){
				/*
				if (!swapHeld)
				{
					board->swapBlocks();
					swapHeld = true;
					swapHeldCounter = 3;
				}
				else
				{
					swapHeldCounter = 3;
				}
				*/
				board->swapBlocks();
            }
			break;
        }
		case ControllerCommand::ForceRaise :
		{
			if (board != NULL) {
				board->forceRaise();
			}
			break;
		}

		case ControllerCommand::Cheat:
		{
			if (board != NULL) {
				//board->Cheat();
			}
			break;
		}
        case ControllerCommand::NoInput :
        default: break;
    }
}
    
void Controller::setBoard(Board* b){
        board = b;
}
