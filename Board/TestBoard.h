/*
Created by PlasmaLotus
Updated Nov 25, 2016
*/

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "Board.h"

#ifndef _TestBoard_
#define _TestBoard_


class TestBoard : public Board {
public:

	void initBoardFile(char path[]);
	void initBoardFile(std::string path);
	void reset();
	char path[1024];
	TestBoard();
	~TestBoard();
	//string pathString;


};

#endif