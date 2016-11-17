/*
Created by PlasmaLotus
Updated Nov 7, 2016
*/

#include "Block.h"

Block::~Block() {
}

Block::Block()
{
	color = none;
	state = BlockState::normal;
	//type = BlockType::air;
	matching = false;
	inChain = false;
}

BlockColor Block::getColor()
{
	return color;
}

void Block::setMatching(bool match) {
	matching = match;
}