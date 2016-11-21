
#include "SFML.h"
#include "Board.h"

#ifndef _Game_
#define _Game_

#define TILE_SIZE 32

class Game{
	
public:

	Board b1;
	Board b2;
	sf::RenderWindow window;
	//sf::RenderWindow window(sf::VideoMode(800, 600), "Why doesnt the block draw");

Game();
~Game();

void init();

int test2();

int test();

void run();


private:
	static const int BOARD_WIDTH = 6;
	static const int BOARD_HEIGHT = 12;

	sf::Sprite spriteColor(BlockColor color);

	int spriteColorInt(BlockColor color);

	void setBoardTextures(Board board);

	void setCursorPosition(Board board);

	void setBlockPositions(Board board);

	void setBoardTextures(sf::Sprite ** boardSprite, Board board);

	void setBoardTextures(sf::Sprite ** boardSprite);

	void drawBoard1(int row, int column);

	void draw();
	void display();
	void _testDisplay(Board & board);
	void testDisplay(Board & board);
	int SCREEN_WIDTH = 640;
	int SCREEN_HEIGHT = 480;


	sf::Texture blockTexture;
	static const int NB_BLOCKS_SPRITES = 9;
	sf::Sprite blockSprites[NB_BLOCKS_SPRITES];


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

