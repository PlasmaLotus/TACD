/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "Block.h"

Block::~Block() {
}

Block::Block():
color(BlockColor::none),
state(BlockState::normal),
stateExtra(BlockExtraState::extraNormal),
//type = BlockType::air;
matching(false),
inChain(false){
}

