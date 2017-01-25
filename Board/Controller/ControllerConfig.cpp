#include "ControllerConfig.h"

/*Contains all the commands that do stuff*/
ControllerConfig::ControllerConfig() :
	joystickNumber(100),
	joystickDeadZone(15.f),
	joystickMaxZone(60.f)
	/*
	joystickUp({}),
	joystickDown,
	joystickLeft,
	joystickRight,
	joystickActionA,
	joystickActionB,
	joystickStart,
	*/
{
	/*Defaultkeys*/
	keyMap[sf::Keyboard::Key::Up] = ControlKey::Up;
	keyMap[sf::Keyboard::Key::Down] = ControlKey::Down;
	keyMap[sf::Keyboard::Key::Left] = ControlKey::Left;
	keyMap[sf::Keyboard::Key::Right] = ControlKey::Right;
	keyMap[sf::Keyboard::Key::Return] = ControlKey::Start;
	keyMap[sf::Keyboard::Key::X] = ControlKey::Shoot;
	keyMap[sf::Keyboard::Key::Z] = ControlKey::Special;

	buttonMap[0] = ControlKey::Shoot;
	buttonMap[1] = ControlKey::Special;
	buttonMap[2] = ControlKey::Shoot;
	buttonMap[3] = ControlKey::Special;
	buttonMap[5] = ControlKey::Start;

	axisMap.insert(std::pair<sf::Joystick::Axis, AxisHandler>(sf::Joystick::Axis::PovX, { ControlKey::Up, ControlKey::Down}));
	axisMap[sf::Joystick::Axis::PovY] = { ControlKey::Right, ControlKey::Left };


	//keyMap.insert(std::pair<sf::Keyboard::Key, ControlKey>(sf::Keyboard::Key::Up, ControlKey::Up));
}



ControllerConfig::~ControllerConfig()
{
}

bool ControllerConfig::loadConfig(std::string iniPath){
	return false;

}

void ControllerConfig::setKey(ControlMode mode, ControlKey key, sf::Keyboard::Key value){
	keyMap.at(value) = key;
}
void ControllerConfig::setKey(ControlMode mode, ControlKey key, float value){
	//axisMap.at(value) = key;
}
void ControllerConfig::setKey(ControlMode mode, ControlKey key, int value){
	buttonMap.at(value) = key;
}

ControlKey ControllerConfig::getCommand(sf::Keyboard::Key key)
{
	ControlKey command = ControlKey::NoInput;
	try {
		command = (keyMap.at(key));    //get the command associated to the key
	}
	catch (const std::out_of_range& oor) {
		return ControlKey::NoInput;
	}
	return command;
}

ControlKey ControllerConfig::getCommand(sf::Joystick::Axis axis, float value)
{
	ControlKey command = ControlKey::NoInput;
	if (value > joystickDeadZone || value *-1 > joystickDeadZone)//if the value is over the dead zone
	{
		try {
			if (value > 0.f)//positif
			{
				command = axisMap.at(axis).positif;
			}
			else
			{
				command = axisMap.at(axis).negatif;
			}
		}
		catch (const std::out_of_range& oor) {
			return ControlKey::NoInput;
		}
	}
	return command;

}

ControlKey ControllerConfig::getCommand(int button)
{
	ControlKey command = ControlKey::NoInput;
	if (button < sf::Joystick::getButtonCount(joystickNumber))
	{
		try {
			command = (buttonMap.at(button));      //get the command associated to the button
		}
		catch (const std::out_of_range& oor) {
			return ControlKey::NoInput;
		}
	}

	return command;
}

int ControllerConfig::getJoystickNumber(void)
{
	return joystickNumber;
}
