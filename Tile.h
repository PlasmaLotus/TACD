/*
Created by PlasmaLotus
Updated Nov 7, 2016
*/

#include "Block.h"
#include "GeneralEnum.h"

#ifndef _Tile_
#define _Tile_

//enum TileType {air, block, garbage};

struct Tile {

	BlockType type;
	Block block;
	//GarbageBlock* g;
	static const char DEFAULT_COUNTER_VALUE = 254;

	//char fallingCounter;
	char swappingCounter;
	char fallingBufferCounter;
	char floatingCounter;
	bool airLock;//should only prevent swapping

	Tile();
	~Tile();
	void setBlockMatching(bool match);
	bool isBlock();
	bool isGarbage();
	bool isAir();
};

#endif