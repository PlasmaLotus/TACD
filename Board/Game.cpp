/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#include "Game.h"
#include "GeneralEnum.h"
#include "Main.h"

Game::Game(){
	//window.create(sf::VideoMode(800, 600), "SFML! Y U NO DRAW BLOCK!!");
}

Game::~Game(){
	//window.close();
}

void Game::reset() {
	b1.reset();// = Board();
	b2.reset();// = Board();
	
}

void Game::init()
{
	window.create(sf::VideoMode(800, 600), "TACD");

	std::string blockTexturePath = "assets/images/blocksUpdated.png";
	//blockTexturePath += "IMG Files/blocksUpdated.png";
	std::string boardFramePath = "assets/images/1p.png";
	//boardFramePath += "IMG Files/1p.png";
	std::string cursorPath = "assets/images/cursor.png";
	//cursorPath += "IMG Files/cursor.png";

	blockTexture.setRepeated(true);

	if (!blockTexture.loadFromFile(blockTexturePath))
	{
		// error...
		printf("%s\n", "What have I done : Block Texture Failure");
		//return -1;
	}
	else if (!boardFrameTexture.loadFromFile(boardFramePath))
	{
		// error...
		printf("%s\n", "What Happened : BoardTexture fail , TestDisplay");
		//return -1;
	}
	else if (!cursorTexture.loadFromFile(cursorPath))
	{
		printf("%s\n", "What Happened : Cursor Texture fail");
	}
	else
	{
		printf("All Texture Loaded\n");
		boardFrameSprite.setTexture(boardFrameTexture);

		for (int i = 0; i < BOARD_HEIGHT; i++)
		{
			for (int j = 0; j < BOARD_WIDTH; j++)
			{
				boardSprites[i][j].setTexture(blockTexture);
			}
		}
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			bufferRowSprites[j].setTexture(blockTexture);
		}

	}
}

void Game::run() {

	//Board board;
	ControllerCommand input =  ControllerCommand::NoInput;

	double MS_PER_FRAME = 1000.0 / FPS;//1000 ms per seconds
	//int MS_PER_FRAME = 16;//miliseconds per frame
						  //clock_t FPS = 60;
	sf::Clock current;
	sf::Time elapsed = current.restart();
	while (window.isOpen())
	{
		/*Manage Time Beta*/
		if (frame == 32767) {
			frame = 0;
		}
		else {
			frame++;
			milisecond++;

			if (milisecond >= 60)
			{
				second++;
				milisecond = 0;
				system("cmd /c cls");
			}

			if (second >= 60)
			{
				minute++;
				second = 0;
			}
		}
		/*~Manage Time Beta*/
		//current = clock();
		//elapsed = current - lastTime;
		current.restart();
		
		///get input here
		input = ControllerCommand::NoInput;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(EXIT_SUCCESS);
			}
			//handleInput(event, b1);
			//input = handleInput(event);
			handleInput(event, input);
		}
		/*
		if (input != ControllerCommand::NoInput)
		{
			b1.handleInput(input);
		}
		*/
		window.clear();

		printf("%d:%d  Frame: %d\n", minute, second, frame);
		printf("NB Frames: %3.2f     \nTemps: %d           \nClocks per Sec: %3.2f\n", (float)elapsed.asMilliseconds() * 60, elapsed, (float)CLOCKS_PER_SEC);
		b1.run(input);
		draw();
		b1.display();
		display();
		//lastTime = current;
		elapsed = current.getElapsedTime();

		if (MS_PER_FRAME - elapsed.asMilliseconds() > 0)
		{
			fflush(stdout);
			Sleep((int)(MS_PER_FRAME - elapsed.asMilliseconds()));
		}
		//system("cmd /c cls");
		gotoxy(0, 0);
	}

}

void Game::handleInput(sf::Event event, Board &board) {

	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::F1) {
			board.addInput(ControllerCommand::Pause);
		}
		if (event.key.code == sf::Keyboard::Up) {
			board.addInput(ControllerCommand::Up);
		}
		if (event.key.code == sf::Keyboard::Down) {
			board.addInput(ControllerCommand::Down);
		}
		if (event.key.code == sf::Keyboard::Left) {
			board.addInput(ControllerCommand::Left);
		}
		if (event.key.code == sf::Keyboard::Right) {
			board.addInput(ControllerCommand::Right);
		}
		if (event.key.code == sf::Keyboard::X || event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Space) {
			board.addInput(ControllerCommand::Swap);
		}
		if (event.key.code == sf::Keyboard::F4) {
			reset();
			board.addInput(ControllerCommand::NoInput);
		}
		if (event.key.code == sf::Keyboard::A) {
			board.addInput(ControllerCommand::ForceRaise);
		}
	}

}

ControllerCommand Game::handleInput(sf::Event event, ControllerCommand& input){

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::F1) {
				input =  ControllerCommand::Pause;
			}
			if (event.key.code == sf::Keyboard::Up) {
				input = ControllerCommand::Up;
			}
			if (event.key.code == sf::Keyboard::Down) {
				input = ControllerCommand::Down;
			}
			if (event.key.code == sf::Keyboard::Left) {
				input =  ControllerCommand::Left;
			}
			if (event.key.code == sf::Keyboard::Right) {
				input =  ControllerCommand::Right;
			}
			if (event.key.code == sf::Keyboard::X || event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Space) {
				input =  ControllerCommand::Swap;
			}
			if (event.key.code == sf::Keyboard::F4) {
				reset();
				input = ControllerCommand::NoInput;
			}
			if (event.key.code == sf::Keyboard::F1) {
				input = ControllerCommand::Cheat;
			}
			if (event.key.code == sf::Keyboard::A) {
				input =  ControllerCommand::ForceRaise;
			}
			return ControllerCommand::NoInput;
		}

		/*
		switch (event.key.code)
		{
			//list of keys
		case sf::Keyboard::F1: return ControllerCommand::Pause; break;
		case sf::Keyboard::Up: return ControllerCommand::Up; break;
		case sf::Keyboard::Down: return ControllerCommand::Down; break;
		case sf::Keyboard::Left: return ControllerCommand::Left; break;
		case sf::Keyboard::Right: return ControllerCommand::Right; break;
		case sf::Keyboard::Z:
		case sf::Keyboard::X: 
			return ControllerCommand::Swap; break;
		case sf::Keyboard::F4: reset(); 
		default: return ControllerCommand::NoInput; break;
		}
		break;
		*/

}
