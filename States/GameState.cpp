/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "GameState.h"

GameState::GameState(sf::RenderWindow *w)
{
	window = w;
	game = new Game();
	renderer = new GameRenderer(window, game);
	//renderer = new GameRenderer();
	//renderer->addGame(game);
	//renderer->addWindow(window);
	p1KeyConfig = new ControllerConfig();
	p1Controller = new BoardController(p1KeyConfig, game, &(game->b1));
}

GameState::~GameState()
{
	delete p1KeyConfig;
	delete game;
	delete renderer;
	delete p1Controller;
}

void GameState::tick()
{
	switch (game->gameState)
	{
	case GameCurrentState::RUNNING:
		p1Controller->handleInput();
		p1Controller->updateConfig();
		game->tick();
		renderer->render();
		p1Controller->viewDebugJoystick();
		break;
	case GameCurrentState::PAUSED:
		break;
	case GameCurrentState::ENDED:
		break;
	default:
		break;
	}

}

Game * GameState::getGame()
{
	return game;
}

void GameState::pause() {

}

