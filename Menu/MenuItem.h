/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

/*Under Construction*/

#ifndef _Menu_Item_
#define _Menu_Item_
#include <string>
#include <functional>

class Menu;

typedef std::function<void() > command;

class MenuItem {
public:

	enum MenuItemType{
		NONE, TOGGLE, PLAYER, RANGE};

	MenuItem(std::string, command c);
	MenuItem(std::string name, command c, int value, int max, MenuItemType type);
	virtual ~MenuItem();
	command getFn() const;
	void increase();
	void decrease();
	void select();
	void handleInput();
	void setMenuType(MenuItemType t);

	const std::string getOptionString() const;

	MenuItemType menuItemType;
private:
	
	unsigned int range;
	unsigned int maxRange;
	MenuItemType _optionType;
	std::string _name;
	command _fn;
	int _value;
	int _max;
};

#endif
