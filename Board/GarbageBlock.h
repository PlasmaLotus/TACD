/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#ifndef _GarbageBlock_
#define _GarbageBlock_

enum GarbageColor{black, white};
class GarbageBlock {

public:
	int row, col;//coordonates of the lower right corner
	int height;
	int size;
	GarbageColor color;
	GarbageBlock();
	GarbageBlock(int row, int col, int height, int size);
	~GarbageBlock();

};

#endif
