#ifndef _ControllerConfig_H_
#define _ControllerConfig_H_

#include <string.h>
#include <map>
#include <SFML/Window.hpp>

enum ControlMode { Keyboard, Joystick };
enum ControlKey { Up, Down, Left, Right, Shoot, Special, Start, NoInput };

class ControllerConfig{
public:
    ControllerConfig();
    ~ControllerConfig();
    bool loadConfig(std::string iniPath);
    
    

    void setKey(ControlMode mode, ControlKey key, sf::Keyboard::Key value);
    void setKey(ControlMode mode, ControlKey key, float value);
    void setKey(ControlMode mode, ControlKey key, int value);
    ControlKey getCommand(sf::Keyboard::Key key);
    ControlKey getCommand(sf::Joystick::Axis axis, float value);
    ControlKey getCommand(int button);
	int getJoystickNumber(void);
private:

	struct AxisHandler {
		//sf::Joystick::Axis axis;
		ControlKey positif;
		ControlKey negatif;
	};

	std::map<sf::Keyboard::Key, ControlKey> keyMap;
	std::map<int, ControlKey> buttonMap;
	std::map<sf::Joystick::Axis, AxisHandler> axisMap;
    

    unsigned int joystickNumber;//the joystick in question 
    float joystickDeadZone;//Zone in witch no input should result;
    float joystickMaxZone;//Difference between slighlty held and Max held, if necessary

};
#endif
