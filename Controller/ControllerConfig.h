#ifndef _ControllerConfig_H_
#define _ControllerConfig_H_

#include <string.h>
#include <map>
#include <SFML/Window.hpp>

enum ControlMode { Keyboard, Joystick };
#include "../Board/GeneralEnum.h"

class ControllerConfig{
public:
    ControllerConfig();
    ~ControllerConfig();
    bool loadConfig(std::string iniPath);
    

    void setKey(ControllerCommand key, sf::Keyboard::Key value);
    void setKey(ControllerCommand key, float value);
    void setKey(ControllerCommand key, int value);
    ControllerCommand getCommand(sf::Keyboard::Key key);
    ControllerCommand getCommand(sf::Joystick::Axis axis, float value);
    ControllerCommand getCommand(int button);
	int getJoystickNumber(void);
	void setJoystickNumber(int number);
private:

	struct AxisHandler {
		//sf::Joystick::Axis axis;
		ControllerCommand positif;
		ControllerCommand positifMax;
		ControllerCommand negatif;
		ControllerCommand negatifMax;
	};

	/*Cette structure de donnée me permet d'assigner une commande a chaque bouton, je suis ouvert au changements*/
	std::map<sf::Keyboard::Key, ControllerCommand> keyMap;
	std::map<int, ControllerCommand> buttonMap;
	std::map<sf::Joystick::Axis, AxisHandler> axisMap;

    unsigned int joystickNumber;//the joystick in question 
    float joystickDeadZone;//Zone in witch no input should result;
    float joystickMaxZone;//Difference between slighlty held and Max held, if necessary

};
#endif
