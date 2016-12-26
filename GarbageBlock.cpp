#include "GarbageBlock.h"

GarbageBlock::GarbageBlock()
{
	row = 10;
	col = 0;
	height = 1;
	size = 3;
}

GarbageBlock::GarbageBlock(int r, int c, int h, int s)
{
	row = r;
	col = c;
	height = h;
	size = s;
}

GarbageBlock::~GarbageBlock()
{
}
