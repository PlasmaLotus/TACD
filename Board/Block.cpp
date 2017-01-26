/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#include "Block.h"

Block::~Block() {
}

Block::Block():
color(BlockColor::none),
state(BlockState::normal),
stateExtra(BlockExtraState::extraNormal),
matching(false),
inChain(false){
}

BlockColor Block::getColor()
{
	return color;
}

void Block::setColor(BlockColor c)
{
	color = c;
}

void Block::setMatching(bool match) {
	matching = match;
}