#include "MenuItem.h"


/*Under Construction*/

MenuItem::MenuItem(std::string name, command c) :
	_optionType(MenuItemType::NONE),
	_name(name),
	_fn(c),
	_value(0),
	_max(0) {

}

MenuItem::MenuItem(std::string name, command c, int value, int max,
	MenuItemType type) :
	_optionType(type),
	_name(name),
	_fn(c),
	_value(value),
	_max(max) {

}

MenuItem::~MenuItem() {
}

command MenuItem::getFn() const {
	return _fn;
}

void MenuItem::increase()
{
	if (range < maxRange) {
		range++;
	}
}

void MenuItem::decrease()
{
	if (range >= 0) {
		range--;
	}
}

void MenuItem::select()
{
}

void MenuItem::handleInput()
{
}

void MenuItem::setMenuType(MenuItemType t)
{
	menuItemType = t;
}

const std::string MenuItem::getOptionString() const {
	
	return "OK M8";
}