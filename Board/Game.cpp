/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "Game.h"

Game::Game():
gameState(GameCurrentState::RUNNING){
	//window.create(sf::VideoMode(800, 600), "SFML! Y U NO DRAW BLOCK!!");
}

Game::~Game(){
	//window.close();
}

void Game::reset() {
	b1.reset();// = Board();
	b2.reset();// = Board();
	b3.reset();// = Board();
	b4.reset();// = Board();
}

void Game::tick() {

	if (b1.boardState == BoardState::Countdown){
		printf("COUNTDOWN : %d / %d \n", b1.countdownFrameCount, b1.CountdownFrames);
	}


	if (gameState == GameCurrentState::RUNNING){
		b1.tick();
		b2.tick();
		b3.tick();
		b4.tick();
		frame++;
		printf("GameFrame: %d\n", frame);
	}


}

void Game::pause() {

}