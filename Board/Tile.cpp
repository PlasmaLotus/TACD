/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#include "Tile.h"

Tile::Tile():
type(air),
//airLock(false),
//fallingCounter(DEFAULT_COUNTER_VALUE),
swappingCounter(DEFAULT_COUNTER_VALUE),
fallingCounter(0),
floatingCounter(0),
matchingCounter(DEFAULT_COUNTER_VALUE),
//clearingCounter(DEFAULT_COUNTER_VALUE),
popCounter(DEFAULT_POP_VALUE),
popCounterFinal(DEFAULT_POP_VALUE),
//chainNumber(1),
g(nullptr),
chain(false){
}

Tile::~Tile() {
}

void Tile::setBlockMatching(bool match){
	block.matching = match;
}

bool Tile::isBlock(){
	if (type == BlockType::block)
		return true;
	return false;
}

bool Tile::isGarbage() {
	if (type == BlockType::garbage)
		return true;
	return false;
}

bool Tile::isAir() {
	/*Only really used in swapping algo*/
	if (type == BlockType::air)// || (block.state == BlockState::clearing && block.stateExtra == BlockExtraState::poped))
		return true;
	return false;
}

bool Tile::isClear() {
	if (block.state == BlockState::clearing && block.stateExtra == BlockExtraState::poped)
	{
		return true;
	}
	return false;
}