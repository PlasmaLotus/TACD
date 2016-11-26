/*
Created by PlasmaLotus
Updated Nov 25, 2016
*/

#include "Game_SFML.h"
#include "Game.h"
#include "GeneralEnum.h"
#include "Main.h"

int Game::spriteColorInt(BlockColor color) {
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

void Game::setBoardTextures(Board board) {
	/*Set the texture of the blocks in the stack */

	int textureIndexX;
	int textureIndexY;
	/*Board SetTextureRect*/
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			textureIndexX = 7 * TILE_SIZE;
			textureIndexY = 0;

			textureIndexX = spriteColorInt(board.tiles[i][j].block.color)*TILE_SIZE;
			textureIndexY = 0;

			if (board.tiles[i][j].isBlock())
			{

				boardSprites[i][j].setTextureRect(sf::IntRect(textureIndexX, textureIndexY, TILE_SIZE, TILE_SIZE));
				boardSprites[i][j].setColor(sf::Color(255, 255, 255, 255));
				if (board.tiles[i][j].block.state == BlockState::matching )// || board.tiles[i][j].block.clearing)
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
				//TODO: code garbage blocks
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
void Game::setCursorPosition(Board board) {
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
void Game::setBlockPositions(Board board) {
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
						vectorX += 4 - board.tiles[i][j].swappingCounter;
						break;
					}
					case swappingRight:
					{
						vectorX -= 4 - board.tiles[i][j].swappingCounter;
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

void Game::draw()
{

	int bufferRowOffset = b1.bufferRowOffset;

	window.draw(boardFrameSprite);
	//boardFrameSprite.setColor(sf::Color(255, 255, 255, 128));
	setBoardTextures(b1);
	setBlockPositions(b1);
	setCursorPosition(b1);

	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			//boardSprites[i][j].setScale(sf::Vector2f(2.f, 2.f));
			window.draw(boardSprites[i][j]);
		}
	}

	for (int j = 0; j < BOARD_WIDTH; j++)
	{
		window.draw(bufferRowSprites[j]);//why does it get drawn twice
	}
	/*calls the .draw() function on all sprites*/
	/*
	for (int i = 0; i < NB_BLOCKS_SPRITES; i++)
	{
	blockSprites[i].setScale(sf::Vector2f(2.f, 2.f));
	}
	*/
	//drawBoard1(427, 58);

	window.draw(cursorSprite);
}

void Game::display()
{
	window.display();
}