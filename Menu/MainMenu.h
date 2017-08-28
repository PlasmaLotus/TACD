/*
Created by PlasmaLotus
Updated May 17, 2017
*/

#include "Menu.h"
//#include "MenuItem.h"
#include "../States/StateManager.h"

#ifndef __MainMenu__
#define __MainMenu__

class MainMenu : public Menu {

	MainMenu(sf::RenderWindow* w);
	MainMenu(sf::RenderWindow* w, Menu *pm);
	~MainMenu();
	void inputSelect();
};

#endif