#include "ControllerConfig.h"

/*Contains all the commands that do stuff*/
ControllerConfig::ControllerConfig() :
	joystickNumber(100),
	joystickDeadZone(15.f),
	joystickMaxZone(60.f)
{
	/*Defaultkeys*/
	keyMap[sf::Keyboard::Key::Up] = ControllerCommand::Up;
	keyMap[sf::Keyboard::Key::Down] = ControllerCommand::Down;
	keyMap[sf::Keyboard::Key::Left] = ControllerCommand::Left;
	keyMap[sf::Keyboard::Key::Right] = ControllerCommand::Right;
	keyMap[sf::Keyboard::Key::Return] = ControllerCommand::Start;
	keyMap[sf::Keyboard::Key::X] = ControllerCommand::Swap;
	keyMap[sf::Keyboard::Key::Z] = ControllerCommand::Swap;
	keyMap[sf::Keyboard::Key::F4] = ControllerCommand::Cheat;
	keyMap[sf::Keyboard::Key::A] = ControllerCommand::ForceRaise;

	buttonMap[0] = ControllerCommand::Swap;
	buttonMap[1] = ControllerCommand::Swap;
	buttonMap[2] = ControllerCommand::Swap;
	buttonMap[4] = ControllerCommand::ForceRaise;
	buttonMap[5] = ControllerCommand::ForceRaise;
	buttonMap[6] = ControllerCommand::Cheat;
	buttonMap[7] = ControllerCommand::Start;

	//axisMap.insert(std::pair<sf::Joystick::Axis, AxisHandler>(sf::Joystick::Axis::PovY, { ControllerCommand::Up, ControllerCommand::Down}));
	axisMap[sf::Joystick::Axis::PovY] = { ControllerCommand::Up, ControllerCommand::Up, ControllerCommand::Down , ControllerCommand::Down };
	axisMap[sf::Joystick::Axis::PovX] = { ControllerCommand::Right, ControllerCommand::Right, ControllerCommand::Left, ControllerCommand::Left };
	axisMap[sf::Joystick::Axis::Y] = { ControllerCommand::NoInput, ControllerCommand::Down, ControllerCommand::NoInput, ControllerCommand::Up };
	axisMap[sf::Joystick::Axis::X] = { ControllerCommand::NoInput, ControllerCommand::Right, ControllerCommand::NoInput, ControllerCommand::Left };
	//keyMap.insert(std::pair<sf::Keyboard::Key, ControllerCommand>(sf::Keyboard::Key::Up, ControllerCommand::Up));
}

ControllerConfig::~ControllerConfig()
{
}

bool ControllerConfig::loadConfig(std::string iniPath){
	
	if ((float)joystickNumber == joystickNumber)
	{
		return true;
	}
	return false;
}

/*Havent tested Set Key yet*/

void ControllerConfig::setKey(ControllerCommand key, sf::Keyboard::Key value){
	keyMap.at(value) = key;
}
void ControllerConfig::setKey(ControllerCommand key, float value){
	//axisMap.at(value) = key;
}
void ControllerConfig::setKey(ControllerCommand key, int value){
	buttonMap.at(value) = key;
}

ControllerCommand ControllerConfig::getCommand(sf::Keyboard::Key key)
{
	ControllerCommand command = ControllerCommand::NoInput;
	try {
		command = (keyMap.at(key));    //get the command associated to the key
	}
	catch (const std::out_of_range& oor) {
		return ControllerCommand::NoInput;
	}
	return command;
}

ControllerCommand ControllerConfig::getCommand(sf::Joystick::Axis axis, float value)
{
	ControllerCommand command = ControllerCommand::NoInput;
	if (value > joystickDeadZone || value *-1 > joystickDeadZone)//if the value is over the dead zone
	{
		try {
			if (value >= joystickMaxZone || value *-1 >= joystickMaxZone)//Higher than the treashhold to register max hold
			{
				if (value > 0.f)//positif
				{
					command = axisMap.at(axis).positifMax;
				}
				else
				{
					command = axisMap.at(axis).negatifMax;
				}
			}
			else
			{
				if (value > 0.f)//positif
				{
					command = axisMap.at(axis).positif;
				}
				else
				{
					command = axisMap.at(axis).negatif;
				}
			}
		}
		catch (const std::out_of_range& oor) {
			return ControllerCommand::NoInput;
		}
	}
	return command;

}

ControllerCommand ControllerConfig::getCommand(int button)
{
	ControllerCommand command = ControllerCommand::NoInput;
	if (button < sf::Joystick::getButtonCount(joystickNumber))
	{
		try {
			command = (buttonMap.at(button));      //get the command associated to the button
		}
		catch (const std::out_of_range& oor) {
			return ControllerCommand::NoInput;
		}
	}

	return command;
}

int ControllerConfig::getJoystickNumber(void)
{
	return joystickNumber;
}

void ControllerConfig::setJoystickNumber(int number) {
	joystickNumber = number;
}
