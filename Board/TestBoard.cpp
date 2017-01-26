/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#include "TestBoard.h"

using namespace std;

void TestBoard::initBoardFile(char* path)
{
	FILE *file;
	//file = fopen(path, "r");
	fopen_s(&file, path, "r");
	char c = '+';

	if (file == NULL)
	{
		fclose(file);
	}
	else
	{
		while(c!= EOF)
		{
			for (int i = BOARD_HEIGHT - 1; i >= 0; i--)
			{
				for (int j = 0; j < BOARD_WIDTH; j++)
				{
					c = fgetc(file);
					switch (c)
					{
					case '1':
					{
						tiles[i][j].type = BlockType::block;
						tiles[i][j].block.setColor(BlockColor::red);
						break;
					}
					case '2':
					{
						tiles[i][j].type = BlockType::block;
						tiles[i][j].block.setColor(BlockColor::blue);
						break;
					}
					case '3':
					{
						tiles[i][j].type = BlockType::block;
						tiles[i][j].block.setColor(BlockColor::green);
						break;
					}
					case '4':
					{
						tiles[i][j].type = BlockType::block;
						tiles[i][j].block.setColor(BlockColor::purple);
						break;
					}
					case '5':
					{
						tiles[i][j].type = BlockType::block;
						tiles[i][j].block.setColor(BlockColor::yellow);
						break;
					}
					case '6':
					{
						tiles[i][j].type = BlockType::block;
						tiles[i][j].block.setColor(BlockColor::pink);
						break;
					}
					case '7':
					{
						tiles[i][j].type = BlockType::block;
						tiles[i][j].block.setColor(BlockColor::orange);
						break;
					}
					case '0':
					{
							tiles[i][j].type = BlockType::air;
							break;
					}
					default:
						break;

					}

					fgetc(file);

				}
			}

		}
	}
	fclose(file);
}

void TestBoard::reset()
{
	clearAll();
	initBoardFile(path);
}

TestBoard::TestBoard()
{
	strcat_s(path, "assets/TestBoards/Board6.pop");

	initBoardFile(path);
	stackRaiseEnabled = false;
}

TestBoard::~TestBoard()
{

}
