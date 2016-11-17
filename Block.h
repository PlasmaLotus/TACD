/*
Created by PlasmaLotus
Updated Nov 7, 2016
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
	
	//manages if block is falling
	//verify the state falling instead
	//bool falling;
	bool inChain;
	/*
	bool grounded; 
	bool swapping; 
	bool inChain;
	*/
	bool matching;

	Block();
	BlockColor getColor();
	void setMatching(bool match);
	//Block(BlockState state, BlockColor color);
	//BlockState getState();
	virtual ~Block();

private:

	static const int BlockHeight = 16;
	static const int BlockLength = 16;

};

#endif