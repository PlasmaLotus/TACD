/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#ifndef __GAME_Renderer__
#define __GAME_Renderer__

//#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <string.h>
#include <string>
#include <iostream>
#include "Board.h"

class GameRenderer {
public:
	
	GameRenderer();
	GameRenderer(sf::RenderWindow &w);
	~GameRenderer();
	void setWindow(sf::RenderWindow & w);
	void setWindow(sf::RenderWindow * w);
	void setBoards(Board b);
	void setBoards(Board b, Board c);
	void initRenderer();
	void render();
	void render(Board b);
private:

	Board *b1;
	Board *b2;
	static const int BOARD_WIDTH = 6;
	static const int BOARD_HEIGHT = 12;

	sf::RenderWindow *window;
	
	int spriteColorInt(BlockColor color);
	void setBoardTextures(Board *board);
	void setCursorPosition(Board *board);
	void setBlockPositions(Board *board);
	void setBoardTextures(Board board);
	void setCursorPosition(Board board);
	void setBlockPositions(Board board);
	
	void clear();
	void draw(Board board);
	void draw(Board * board);
	//void draw(Board * board);
	void display();

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

#endif // !__Game_Renderer__
