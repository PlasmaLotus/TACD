/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#include "GeneralEnum.h"

#ifndef _Block_
#define _Block_


class Block {
public:

	BlockColor color;
	BlockState state;
	BlockExtraState stateExtra;
	//BlockType type;
	
	bool inChain;
	bool matching;

	Block();
	virtual ~Block();
	BlockColor getColor();
	void setMatching(bool match);
	void setColor(BlockColor c);

private:

	static const int BlockHeight = 32;
	static const int BlockLength = 32;

};

#endif