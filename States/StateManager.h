/*
Created by PlasmaLotus
Updated May 17, 2017
*/

#ifndef __StateManager__
#define __StateManager__

#include "SFML\Graphics.hpp"
#include "State.h"
#include "GameState.h"
#include "../Renderer/GameRenderer.h"
#include "../Main.h"

class StateManager {
public:
	StateManager();
	~StateManager();
	static StateManager& getInstance();
	void switchToState(State* state);
	void goBack();
	void quit();
	void run();
	static const int FPS = 60;
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;
private:
	bool running;
	sf::RenderWindow window;
	State *currentState;
	State *oldState;
	//GameRenderer *renderer;
	
};

#endif
