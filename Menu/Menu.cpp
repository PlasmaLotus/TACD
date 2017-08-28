#include "Menu.h"

/*Under Construction*/

Menu::~Menu()
{
	//window->create(sf::VideoMode(800, 600), "TACD");
	delete previousMenu;
	delete nextMenu;
}

Menu::Menu(sf::RenderWindow* w)
{
	window = w;
}

Menu::Menu(sf::RenderWindow* w, Menu * pm)
{
	previousMenu = pm;
	window = w;
}

void Menu::tick()
{
	handleInput();
}

void Menu::handleInput()
{

}

void Menu::inputLeft()
{
	if (items.at(selection).menuItemType == MenuItem::MenuItemType::RANGE) {
		items.at(selection).decrease();
	}
}

void Menu::inputRight()
{
	if (items.at(selection).menuItemType == MenuItem::MenuItemType::RANGE) {
		items.at(selection).increase();
	}
}

void Menu::inputUp()
{
	if (selection <= 0) {
		selection = items.size() - 1;
	}
}

void Menu::inputDown()
{
	if (selection >= items.size()) {
		selection = 0;
	}

}

void Menu::inputSelect()
{
	
}

void Menu::inputBack() {
	if (previousMenu != NULL){
		delete this;
	}
}

void Menu::setPreviousMenu(Menu* menu)
{
	previousMenu = menu;
}

void Menu::addItem(MenuItem menuItem) {
	items.push_back(menuItem);
}