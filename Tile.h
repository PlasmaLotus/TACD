/*
Created by PlasmaLotus
Updated Nov 25, 2016
*/

#include "Block.h"
#include "GarbageBlock.h"
#include "GeneralEnum.h"

#ifndef _Tile_
#define _Tile_

//enum TileType {air, block, garbage};

struct Tile {

	BlockType type;
	Block block;
	GarbageBlock* g;
	static const int DEFAULT_COUNTER_VALUE = 254;
	static const int DEFAULT_POP_VALUE = 4096;
	//char fallingCounter;
	int swappingCounter;
	int fallingCounter;
	int floatingCounter;
	int matchingCounter;/*Also Knowned as FlashingCounter*/
	//char flashingCounter;
	//char clearingCounter;
	int popCounter;
	int popCounterFinal;
	//int chainNumber;
	bool chain;


	Tile();
	~Tile();
	void setBlockMatching(bool match);
	bool isBlock();
	bool isGarbage();
	bool isAir();
	bool isClear();
};

#endif