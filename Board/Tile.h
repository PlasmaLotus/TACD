/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "Block.h"
#include "GarbageBlock.h"

#ifndef _Tile_
#define _Tile_

enum BlockType { block, air, garbage };

struct Tile {

	BlockType type;
	Block block;
	GarbageBlock* g;
	static const int DEFAULT_COUNTER_VALUE = 0;
	static const int DEFAULT_POP_VALUE = 0;
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