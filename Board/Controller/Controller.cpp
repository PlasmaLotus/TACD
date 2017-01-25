#include "Controller.h"


/*The controller recieves input from a Keyboard or Joystick and outputs Commands to execute*/


Controller::Controller():
mode(ControlMode::Keyboard)
{
	config.loadConfig("controllerConfig.ini");
}

Controller::Controller(Tank* tank):
mode(ControlMode::Keyboard),
player(tank)
{
    //player = tank;
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
            //config = new JoystickConfig:
        }
        else
        {
            //config = new KeyboardConfig;
        }
    }
    else if (mode == ControlMode::Joystick){
        //config = new JoystickConfig;
        //handle switching to keyboard mode
    }
    //config.load("controller.ini");
}

/*Checks if any input is pressed and acts accordingly*/
void Controller::handleInput(){
    
    //InputHandler inputHandler;
    
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

			/*
            if (sf::Keyboard::isKeyPressed(config.KeyboardUp){
                player->moveUp();
            }
            if (sf::Keyboard::isKeyPressed(config.KeyboardkDown)){
                player->moveDown();
            }
            if (sf::Keyboard::isKeyPressed(config.KeyboardLeft)){
                player->rotateLeft();
            }
            if (sf::Keyboard::isKeyPressed(config.KeyboardRight)){
                player->rotateRight();
            }
            */
            
            //if (sf::Keyboard::isKeyPressed(config.KeyboardActionA)){
                //shoot things}
            
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
			if (sf::Joystick::hasAxis(js, sf::Joystick::Axis::PovX))
			{
				handleCommand(config.getCommand(sf::Joystick::Axis::PovX, sf::Joystick::getAxisPosition(js, sf::Joystick::Axis::PovX)));
			}
			if (sf::Joystick::hasAxis(js, sf::Joystick::Axis::PovY))
			{
				handleCommand(config.getCommand(sf::Joystick::Axis::PovY, sf::Joystick::getAxisPosition(js, sf::Joystick::Axis::PovY)));
			}
			if (sf::Joystick::hasAxis(js, sf::Joystick::Axis::R))
			{
				handleCommand(config.getCommand(sf::Joystick::Axis::R, sf::Joystick::getAxisPosition(js, sf::Joystick::Axis::R)));
			}
			if (sf::Joystick::hasAxis(js, sf::Joystick::Axis::U))
			{
				handleCommand(config.getCommand(sf::Joystick::Axis::U, sf::Joystick::getAxisPosition(js, sf::Joystick::Axis::U)));
			}
			if (sf::Joystick::hasAxis(js, sf::Joystick::Axis::V))
			{
				handleCommand(config.getCommand(sf::Joystick::Axis::V, sf::Joystick::getAxisPosition(js, sf::Joystick::Axis::V)));
			}
			if (sf::Joystick::hasAxis(js, sf::Joystick::Axis::X))
			{
				handleCommand(config.getCommand(sf::Joystick::Axis::X, sf::Joystick::getAxisPosition(js, sf::Joystick::Axis::X)));
			}
			if (sf::Joystick::hasAxis(js, sf::Joystick::Axis::Y))
			{
				handleCommand(config.getCommand(sf::Joystick::Axis::Y, sf::Joystick::getAxisPosition(js, sf::Joystick::Axis::Y)));
			}
			if (sf::Joystick::hasAxis(js, sf::Joystick::Axis::Z))
			{
				handleCommand(config.getCommand(sf::Joystick::Axis::Z, sf::Joystick::getAxisPosition(js, sf::Joystick::Axis::Z)));
			}

            //if (config.JoystickUp.buttonType)
            break;
        }
        default: break;
        
    }
    return;
}
/*Act accordingly to the needed commands*/
void Controller::handleCommand(ControlKey command){
    /*Apply action on the player dependant on the command*/
    switch (command) 
    {
        case ControlKey::Up :
        {
            if (player != NULL){
                player->moveUp();
            }
        }
        
        case ControlKey::Down :
        {
            if (player != NULL){
                player->moveDown();
            }
        }
        
        case ControlKey::Left :
        {
            if (player != NULL){
                player->rotateLeft();
            }
        }
        
        case ControlKey::Right :
        {
            if (player != NULL){
                player->rotateRight();
            }
        }
        
        case ControlKey::Shoot :
        {
            if (player != NULL){
                //player->shoot();
            }
        }
		case ControlKey::Special :
		{
			if (player != NULL) {
				//player->shootSpecial();
			}
		}
        case ControlKey::NoInput :
        default: break;
        
    }
}
    
void Controller::setPlayer(Tank* tank){
        player = tank;
}
