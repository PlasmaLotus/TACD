/*
Created by PlasmaLotus
Updated May 13, 2017
*/


//This class creates a random board
#include <time.h>
#include <random>
#include "BoardRandomBoardHandler.h"

RandomBoardGenerator::RandomBoardGenerator():
	rowInitHeight(6),
	nbPositions(6){
	std::srand(time(NULL));
	init();
}

RandomBoardGenerator::~RandomBoardGenerator(){
}

void RandomBoardGenerator::init(){
	for (int i = 0; i < nbPositions; i++)
	{
		_boardInitBlocks[i] = { 5, i };
	}
	//_boardInitBlocks = { {10,0}, {10, 1}, {10, 2}, {10, 3}, {10, 4} };
	//_boardInitBlocks = { (10,0), (10,1), (10,2), (10,3), (10,4) };
	/*
	_boardInitBlocksFull = {
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{1,1,1,1,1,1},
		{1,1,1,1,1,1},
		{1,1,1,1,1,1},
		{1,1,1,1,1,1},
		{1,1,1,1,1,1}
	};
	*/
	nbBoards = 2;
	int innerRandomHandler;
	int randomHandler =  rand() % (nbBoards+1);
	
	switch(randomHandler)
	{
		case 1:
		{
			//full column split
			innerRandomHandler = rand() % 6;
			for (int i = 0; i < nbPositions; i++)
			{
				_boardInitBlocks[i] = {i, innerRandomHandler};
				//_boardInitBlocks[i].row = i;
				//_boardInitBlocks[i].row = innerRandomHandler;
				//_boardInitBlocks[i] = { i, innerRandomHandler };
				/*
					{0,0,0,0,0,0},
					{1,1,1,1,0,1},
					{1,1,1,1,0,1},
					{1,1,1,1,0,1},
					{1,1,1,1,0,1},
					{1,1,1,1,0,1},
					{1,1,1,1,0,1}
				*/
			}
			
			break;
		}
		case 2:
		{
			_boardInitBlocks[0] = { 4, 1 };
			_boardInitBlocks[1] = { 4, 4 };
			_boardInitBlocks[2] = { 5, 0 };
			_boardInitBlocks[3] = { 5, 1 };
			_boardInitBlocks[4] = { 5, 4 };
			_boardInitBlocks[5] = { 5, 5 };
			/*
			{0,0,0,0,0,0},
			{0,0,1,1,0,0},
			{1,0,1,1,0,1},
			{1,1,1,1,1,1},
			{1,1,1,1,1,1},
			{1,1,1,1,1,1},
			{1,1,1,1,1,1}
			*/
			break;
		}
		case 0: 
		default: break;
	}
	
}

bool RandomBoardGenerator::get(int row, int column){
	
	for (int i = 0; i< nbPositions; i++)
	{
		if (_boardInitBlocks[i].row == row && _boardInitBlocks[i].column == column)
		{
			return true;
		}
	}
	return false;
}