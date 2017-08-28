/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "Block.h"
#include "Tile.h"

#ifndef _RandomBoardGenerator_
#define _RandomBoardGenerator_

class RandomBoardGenerator {
public:
	RandomBoardGenerator();
	~RandomBoardGenerator();

	void init();
	bool get(int row, int column);

	struct Position {
		int row, column;
	};

	int rowInitHeight;
private:
	
	Position _boardInitBlocks[6];
	int nbPositions;
	char _boardInitBlocksFull[11][6];
	int nbBoards;
	
};

#endif