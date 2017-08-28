/*
Created by PlasmaLotus
Updated May 17, 2017
*/

#ifndef __GameState__
#define __GameState__

#include "State.h"
#include "../Board/Game.h"
#include "../Renderer/GameRenderer.h"
#include "../Controller/BoardController.h"
class GameState : public State {
public:
	GameState(sf::RenderWindow *w);

	virtual ~GameState();
	virtual void tick();
	Game *getGame();

	void pause();

private:
	Game *game;
	GameRenderer *renderer;
	sf::RenderWindow *window;
	ControllerConfig* p1KeyConfig;
	Controller *p1Controller;

};

#endif
