/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#ifndef _Block_
#define _Block_

enum BlockColor { red, yellow, green, blue, orange, purple, none, pink };
enum BlockState { clearing, matching, cleared, swapping, floating, falling, landed, nothing, normal };
enum BlockExtraState { swappingLeft, swappingRight, extraNormal, fromClear, poped };

class Block {
public:

	BlockColor color;
	BlockState state;
	BlockExtraState stateExtra;
	bool inChain;
	bool matching;
	Block();
	virtual ~Block();

};

#endif