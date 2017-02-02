/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#include "GameRenderer.h"
#include "Game.h"
#include "GeneralEnum.h"
#include "../Main.h"


GameRenderer::GameRenderer()
{
}
GameRenderer::GameRenderer(sf::RenderWindow &w) :
	window(&w) {

}
GameRenderer::~GameRenderer()
{
}

void GameRenderer::setWindow(sf::RenderWindow &w) {
	window = &w;
}
void GameRenderer::setWindow(sf::RenderWindow *w) {
	window = w;
}

void GameRenderer::setBoards(Board b) {
	b1 = &b;
}
void GameRenderer::setBoards(Board b, Board c) {
	b1 = &b;
	b2 = &c;
}

void GameRenderer::initRenderer() {

	std::string blockTexturePath = "assets/images/blocksUpdated.png";
	std::string boardFramePath = "assets/images/1p.png";
	std::string cursorPath = "assets/images/cursor.png";

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

int GameRenderer::spriteColorInt(BlockColor color) {
	switch (color)
	{
	case red: return 0;
	case green: return 1;
	case yellow: return 2;
	case blue: return 3;
	case purple: return 4;
	case pink: return 5;
		//case exclam: return 6;
	case none: return 7;
	default:
		return 7;
	}
}

void GameRenderer::setBoardTextures(Board *board) {
	/*Set the texture of the blocks in the stack */

	int textureIndexX;
	int textureIndexY;
	/*Board SetTextureRect*/
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{

			textureIndexX = spriteColorInt(board->tiles[i][j].block.color)*TILE_SIZE;
			textureIndexY = 0;

			if (board->tiles[i][j].isBlock())
			{

				boardSprites[i][j].setTextureRect(sf::IntRect(textureIndexX, textureIndexY, TILE_SIZE, TILE_SIZE));
				boardSprites[i][j].setColor(sf::Color(255, 255, 255, 255));
				if (board->tiles[i][j].block.state == BlockState::matching )// || board.tiles[i][j].block.clearing)
				{
					boardSprites[i][j].setColor(sf::Color(255, 255, 255, 178 + 127 * (board->tiles[i][j].matchingCounter % 2)));
					/*TODO: create flashing effect*/
				}

				if (board->tiles[i][j].block.state == BlockState::clearing || board->tiles[i][j].block.state == BlockState::cleared)
				{
					textureIndexY += TILE_SIZE;
					boardSprites[i][j].setTextureRect(sf::IntRect(textureIndexX, textureIndexY, TILE_SIZE, TILE_SIZE));
				}

				if (board->tiles[i][j].isClear() || board->tiles[i][j].block.state == BlockState::cleared)
				{
					/*nothing is showned*/
					boardSprites[i][j].setTextureRect(sf::IntRect(0, 0, 0, 0));
				}
				//boardSprites[i][j].setColor(sf::Color(255, 255, 255, 255));
			}
			else if (board->tiles[i][j].isAir())
			{
				boardSprites[i][j].setTextureRect(sf::IntRect(0, 0, 0, 0));
			}
			else if (board->tiles[i][j].isGarbage())
			{
				boardSprites[i][j].setTextureRect(sf::IntRect(spriteColorInt(BlockColor::none) * TILE_SIZE, textureIndexY, TILE_SIZE, TILE_SIZE));
			}
			
		}
	}
	/*BufferRow SetTextureRect*/
	for (int j = 0; j < BOARD_WIDTH; j++)
	{
		/*Creates a block with a height of the bufferRowOffset*/
		bufferRowSprites[j].setTextureRect(sf::IntRect(
			spriteColorInt(board->bufferRow[j].block.color)*TILE_SIZE, 0, TILE_SIZE, board->bufferRowOffset * 2));//16 same as tileSize

																												/*Darker BufferRow to differenciate it from other blocks*/
		bufferRowSprites[j].setColor(sf::Color(255, 255, 255, 64));
	}

	cursorSprite.setTexture(cursorTexture);
}
void GameRenderer::setCursorPosition(Board *board) {
	int displayX = 58;
	//int displayY = 427-TILE_SIZE;
	int displayY = 395;
	int spriteDisplaySize = 32;

	cursorTime++;
	//int size = cursorTexture.ge
	cursorSprite.setPosition(sf::Vector2f(displayX + board->cursor.column * spriteDisplaySize - 6, displayY - board->bufferRowOffset*(2) - board->cursor.row * spriteDisplaySize - 6));
	if (cursorTime % 60 == 0)
	{
		cursorTime = 0;
		cursorSprite.setTextureRect(sf::IntRect(0, 0, 75, 44));
	}
	else if (cursorTime % 30 == 0)
	{
		cursorSprite.setTextureRect(sf::IntRect(0, 45, 75, 44));
	}

}
void GameRenderer::setBlockPositions(Board *board) {
	/*Sets the position of all blocks sprites on the board;*/

	int bufferRowOffset = board->bufferRowOffset * (2);//spriteScale;

	int spriteDisplaySize = 32;
	int displayYTop = 43;
	int displayX = 58;
	//int displayY = 427-TILE_SIZE;
	int displayY = 395;

	int vectorX;
	int vectorY;
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{

			vectorX = displayX + spriteDisplaySize*j;
			vectorY = displayY - bufferRowOffset - spriteDisplaySize*i;
			/*
			if (i == board.TOP_ROW)
			{
			//Only display part of the top row blocks
			vectorY += board.bufferRowOffset * 2;
			}
			*/
			if (board->tiles[i][j].block.state == BlockState::swapping)
			{
				if (board->tiles[i][j].swappingCounter > 0)
				{

					switch (board->tiles[i][j].block.stateExtra)
					{
					case swappingLeft:
					{
						vectorX += TILE_SIZE -board->tiles[i][j].swappingCounter * TILE_SIZE / 5;
						break;
					}
					case swappingRight:
					{
						vectorX += -TILE_SIZE + board->tiles[i][j].swappingCounter * TILE_SIZE / 5;
						break;
					}
					default: break;
					}
				}
			}

			boardSprites[i][j].setPosition(sf::Vector2f(vectorX, vectorY));
			/*TODO: set position when blocks are swapping*/
		}
	}
	/*BufferRow*/
	//vectorX = displayX + spriteDisplaySize*BOARD_HEIGHT;
	vectorY = displayY + spriteDisplaySize - board->bufferRowOffset * 2;
	for (int j = 0; j < BOARD_WIDTH; j++)
	{
		vectorX = displayX + spriteDisplaySize*j;
		//vectorX = displayX + spriteDisplaySize*j;
		//vectorY = bufferRowOffset + displayY + BOARD_HEIGHT*spriteDisplaySize;

		bufferRowSprites[j].setPosition(sf::Vector2f(vectorX, vectorY));
	}
}


void GameRenderer::setBoardTextures(Board board) {
	/*Set the texture of the blocks in the stack */

	int textureIndexX;
	int textureIndexY;
	/*Board SetTextureRect*/
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{

			textureIndexX = spriteColorInt(board.tiles[i][j].block.color)*TILE_SIZE;
			textureIndexY = 0;

			if (board.tiles[i][j].isBlock())
			{

				boardSprites[i][j].setTextureRect(sf::IntRect(textureIndexX, textureIndexY, TILE_SIZE, TILE_SIZE));
				boardSprites[i][j].setColor(sf::Color(255, 255, 255, 255));
				if (board.tiles[i][j].block.state == BlockState::matching)// || board.tiles[i][j].block.clearing)
				{
					boardSprites[i][j].setColor(sf::Color(255, 255, 255, 178 + 127 * (board.tiles[i][j].matchingCounter % 2)));
					/*TODO: create flashing effect*/
				}

				if (board.tiles[i][j].block.state == BlockState::clearing || board.tiles[i][j].block.state == BlockState::cleared)
				{
					textureIndexY += TILE_SIZE;
					boardSprites[i][j].setTextureRect(sf::IntRect(textureIndexX, textureIndexY, TILE_SIZE, TILE_SIZE));
				}

				if (board.tiles[i][j].isClear() || board.tiles[i][j].block.state == BlockState::cleared)
				{
					/*nothing is showned*/
					boardSprites[i][j].setTextureRect(sf::IntRect(0, 0, 0, 0));
				}
				//boardSprites[i][j].setColor(sf::Color(255, 255, 255, 255));
			}
			else if (board.tiles[i][j].isAir())
			{
				boardSprites[i][j].setTextureRect(sf::IntRect(0, 0, 0, 0));
			}
			else if (board.tiles[i][j].isGarbage())
			{
				boardSprites[i][j].setTextureRect(sf::IntRect(spriteColorInt(BlockColor::none) * TILE_SIZE, textureIndexY, TILE_SIZE, TILE_SIZE));
			}

		}
	}
	/*BufferRow SetTextureRect*/
	for (int j = 0; j < BOARD_WIDTH; j++)
	{
		/*Creates a block with a height of the bufferRowOffset*/
		bufferRowSprites[j].setTextureRect(sf::IntRect(
			spriteColorInt(board.bufferRow[j].block.color)*TILE_SIZE, 0, TILE_SIZE, board.bufferRowOffset * 2));//16 same as tileSize

																												  /*Darker BufferRow to differenciate it from other blocks*/
		bufferRowSprites[j].setColor(sf::Color(255, 255, 255, 64));
	}

	cursorSprite.setTexture(cursorTexture);
}
void GameRenderer::setCursorPosition(Board board) {
	int displayX = 58;
	//int displayY = 427-TILE_SIZE;
	int displayY = 395;
	int spriteDisplaySize = 32;

	cursorTime++;
	//int size = cursorTexture.ge
	cursorSprite.setPosition(sf::Vector2f(displayX + board.cursor.column * spriteDisplaySize - 6, displayY - board.bufferRowOffset*(2) - board.cursor.row * spriteDisplaySize - 6));
	if (cursorTime % 60 == 0)
	{
		cursorTime = 0;
		cursorSprite.setTextureRect(sf::IntRect(0, 0, 75, 44));
	}
	else if (cursorTime % 30 == 0)
	{
		cursorSprite.setTextureRect(sf::IntRect(0, 45, 75, 44));
	}

}
void GameRenderer::setBlockPositions(Board board) {
	/*Sets the position of all blocks sprites on the board;*/

	int bufferRowOffset = board.bufferRowOffset * (2);//spriteScale;

	int spriteDisplaySize = 32;
	int displayYTop = 43;
	int displayX = 58;
	//int displayY = 427-TILE_SIZE;
	int displayY = 395;

	int vectorX;
	int vectorY;
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{

			vectorX = displayX + spriteDisplaySize*j;
			vectorY = displayY - bufferRowOffset - spriteDisplaySize*i;
			/*
			if (i == board.TOP_ROW)
			{
			//Only display part of the top row blocks
			vectorY += board.bufferRowOffset * 2;
			}
			*/
			if (board.tiles[i][j].block.state == BlockState::swapping)
			{
				if (board.tiles[i][j].swappingCounter > 0)
				{

					switch (board.tiles[i][j].block.stateExtra)
					{
					case swappingLeft:
					{
						vectorX += TILE_SIZE - board.tiles[i][j].swappingCounter * TILE_SIZE / 5;
						break;
					}
					case swappingRight:
					{
						vectorX += -TILE_SIZE + board.tiles[i][j].swappingCounter * TILE_SIZE / 5;
						break;
					}
					default: break;
					}
				}
			}

			boardSprites[i][j].setPosition(sf::Vector2f(vectorX, vectorY));
			/*TODO: set position when blocks are swapping*/
		}
	}
	/*BufferRow*/
	//vectorX = displayX + spriteDisplaySize*BOARD_HEIGHT;
	vectorY = displayY + spriteDisplaySize - board.bufferRowOffset * 2;
	for (int j = 0; j < BOARD_WIDTH; j++)
	{
		vectorX = displayX + spriteDisplaySize*j;
		//vectorX = displayX + spriteDisplaySize*j;
		//vectorY = bufferRowOffset + displayY + BOARD_HEIGHT*spriteDisplaySize;

		bufferRowSprites[j].setPosition(sf::Vector2f(vectorX, vectorY));
	}
}

void GameRenderer::render(Board b) {
	clear();
	//if (b1 != NULL)
	//{
		draw(b);
	//}
	display();
}
void GameRenderer::render() {
	clear();
	if (b1 != NULL)
	{
		draw(b1);
	}
	display();
}
void GameRenderer::clear() {
	if (window != NULL) {
		window->clear();
	}
	
}
void GameRenderer::display() {
	if (window != NULL) {
		window->display();
	}
}

void GameRenderer::draw(Board board) {
	if (window != NULL) {
		//int bufferRowOffset = b1.bufferRowOffset;

		/*drawBackground here*/

		window->draw(boardFrameSprite);

		setBoardTextures(board);
		setBlockPositions(board);
		setCursorPosition(board);

		//draw all blocks
		for (int i = 0; i < BOARD_HEIGHT; i++)
		{
			for (int j = 0; j < BOARD_WIDTH; j++)
			{
				window->draw(boardSprites[i][j]);
			}
		}
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			window->draw(bufferRowSprites[j]);//why does it get drawn twice
		}

		window->draw(cursorSprite);
	}
}

void GameRenderer::draw(Board *board) {
	if (window != NULL) {
		//int bufferRowOffset = b1.bufferRowOffset;

		/*drawBackground here*/

		window->draw(boardFrameSprite);

		setBoardTextures(*board);
		setBlockPositions(*board);
		setCursorPosition(*board);

		//draw all blocks
		for (int i = 0; i < BOARD_HEIGHT; i++)
		{
			for (int j = 0; j < BOARD_WIDTH; j++)
			{
				window->draw(boardSprites[i][j]);
			}
		}
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			window->draw(bufferRowSprites[j]);//why does it get drawn twice
		}

		window->draw(cursorSprite);
	}
}

