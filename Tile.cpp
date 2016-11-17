/*
Created by PlasmaLotus
Updated Nov 7, 2016
*/

#include "Tile.h"

Tile::Tile():
type(air),
airLock(false),
//fallingCounter(DEFAULT_COUNTER_VALUE),
swappingCounter(DEFAULT_COUNTER_VALUE),
fallingBufferCounter(DEFAULT_COUNTER_VALUE),
floatingCounter(DEFAULT_COUNTER_VALUE){
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
	if (type == BlockType::air || block.state == BlockState::swapping)
		return true;
	return false;
}