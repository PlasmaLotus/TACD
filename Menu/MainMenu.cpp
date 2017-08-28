#include "MainMenu.h"

MainMenu::MainMenu(sf::RenderWindow* w) :Menu(w) {

	//addItem(new MenuItem());
}

MainMenu::MainMenu(sf::RenderWindow* w, Menu *pm):Menu(w, pm) {
	
		/*
		addItem(
			MenuItem("1P Endless",
				[&]() {
			StateManager::getInstance().switchToState(new EndlessGameState);
		}));
		addItem(
			MenuItem("VS AI",
				[&]() {
			StateManager::getInstance().switchToState(new AIGameState);
		}));
		addItem(
			MenuItem("2P VS",
				[&]() {
			StateManager::getInstance().switchToState(new VsGameState);
		}));
		addItem(
			MenuItem("Options",
				[&]() {
			StateManager::getInstance().switchToState(new OptionsMenuState);
		}));

		*/
		addItem(
			MenuItem("Quit",
				[&]() {
			StateManager::getInstance().quit();
		}));
		
}

MainMenu::~MainMenu() {
}

void MainMenu::inputSelect() {
	nextMenu = new MainMenu(window, this);
	//next
}