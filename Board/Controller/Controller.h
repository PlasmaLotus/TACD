#ifndef _Controller_H_
#define _Controller_H_

#include "SFML\Window.hpp"
#include "ControllerConfig.h"
#include "C:/Users/Lee-Stenio/Tanks 1.5D/v0.1/src/tank.h"

class Controller {
public:
	//sf::Joystick
    
    ControlMode mode;
    ControllerConfig config; 
    
    Tank* player;

	Controller();
	Controller(Tank * tank);
	~Controller();
	void updateConfig();
	void handleInput();
	void setPlayer(Tank* tank);

private:
	void handleCommand(ControlKey command);

};

#endif // _Controller_H_
