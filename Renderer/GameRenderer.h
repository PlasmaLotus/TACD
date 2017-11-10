/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#ifndef __GAME_Renderer__
#define __GAME_Renderer__

//#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <string.h>
#include <string>
#include <iostream>
#include "../Board/Game.h"

class GameRenderer {
public:
	void setBoardTextures(Board board);
	void setCursorPosition(Board board);
	void setBlockPositions(Board board);
	void render();
	//sf::Image render();
	void clear();
	void draw();
	void drawBoard();
	void drawBufferRow();
	void drawCursor();
	void display();
	void addGame(Game * g);
	void addWindow(sf::RenderWindow * g);
	sf::Texture getLastFrame();
	void setBoardTextures(Board * board);
	void setCursorPosition(Board * board);
	void setBlockPositions(Board * board);
	GameRenderer();
	GameRenderer(sf::RenderWindow* window, Game* game);
	~GameRenderer();
	//void setBoards(Board b1, Board b2);
	
	bool initRenderer();

	int spriteColorInt(BlockColor color);
	static const int TILE_SIZE = 32;
	static const int BOARD_WIDTH = 6;
	static const int BOARD_HEIGHT = 12;
	sf::RenderWindow* window;
	Game* game;
	Board* board;
	//Board* board = &game->b1;


	sf::Texture blockTexture;

	sf::Sprite boardSprites[BOARD_HEIGHT][BOARD_WIDTH];
	sf::Sprite bufferRowSprites[BOARD_WIDTH];

	sf::Texture boardFrameTexture;
	sf::Sprite boardFrameSprite;

	sf::Texture cursorTexture;
	sf::Sprite cursorSprite;

	/*Represent the starting pixel of the block sprites on the board*/
	const int displayX = 58;
	const int displayY = 395;
	const int spriteDisplaySize = 32;
	//int displayY = 427-TILE_SIZE;
	int cursorTime = -1;
	const int spriteScale = 2;
	sf::Texture lastFrame;//not implemented
	bool texturesLoaded = false;

	int p1XOffset;
	int p1Yoffset;
	int p2XOffset;
	int p2Yoffset;
	int p3XOffset;
	int p3Yoffset;
	int p4XOffset;
	int p4Yoffset;
};

#endif // !__Game_Renderer__
