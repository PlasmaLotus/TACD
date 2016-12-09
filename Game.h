/*
Created by PlasmaLotus
Updated Nov 25, 2016
*/

#include "Game_SFML.h"
#include "Board.h"
#include "TestBoard.h"

#ifndef _Game_
#define _Game_

#define TILE_SIZE 32

class Game{
	
public:

	//Board b1;
	TestBoard b1;
	Board b2;
	sf::RenderWindow window;

	Game();
	~Game();
	/*Game Time*/
	int frame;
	int second;
	int minute;
	int milisecond;
	/*~Game Time*/

	void reset();
	void init();
	void run();

	void handleInputPressRelease(sf::Event event, Board & board);
	void handleInput(sf::Event event, Board & board);
	ControllerCommand handleInput(sf::Event event);

private:
	static const int BOARD_WIDTH = 6;
	static const int BOARD_HEIGHT = 12;

	int spriteColorInt(BlockColor color);

	void setBoardTextures(Board board);

	void setCursorPosition(Board board);

	void setBlockPositions(Board board);

	void draw();
	void display();
	void _testDisplay(Board & board);
	void testDisplay(Board & board);
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;

	bool ControllerUp = false;
	bool ControllerDown = false;
	bool ControllerLeft = false;
	bool ControllerRight = false;
	bool ControllerSwap = false;

	sf::Texture blockTexture;

	sf::Sprite boardSprites[BOARD_HEIGHT][BOARD_WIDTH];
	sf::Sprite bufferRowSprites[BOARD_WIDTH];

	sf::Texture boardFrameTexture;
	sf::Sprite boardFrameSprite;

	sf::Texture cursorTexture;
	sf::Sprite cursorSprite;
	int cursorTime = -1;
	const int spriteScale = 2;

	/*Represent the starting pixel of the block sprites on the board*/
	const int displayX = 58;
	const int displayY = 395;
	const int spriteDisplaySize = 32;
	//int displayY = 427-TILE_SIZE;
};

#endif // !_Game_

