 /*
Created by PlasmaLotus
Updated Nov 7, 2016
*/

#include <time.h>
#include <random>
#include <ctype.h>//for displayboard
#include <windows.h>
#include <iostream>

#include "Tile.h"
#include "Board.h"
#include "Block.h"
#include "GeneralEnum.h"
#include "BoardRandomBoardHandler.h"

Board::Board() :
boardSize(BOARD_WIDTH),
boardWidth(BOARD_WIDTH),
boardHeight(BOARD_HEIGHT),
bufferRowTics(0),
bufferRowOffset(0),
chain(false),
combo(false),
_activeBlocks(false),
cursor({ 4,2 }) {
	std::srand(time(NULL));
	initBoardRandom();
	//init_Board(120);
}

Board::~Board(){
}

/*
Board::Board() {

	if (dimension.equals(BoardDimension._2D))
	{
		this.boardSize = board2DSize;
	}
	else
	{
		this.boardSize = board3DSize;
	}
	//if 
	//cursor = new Cursor();
	cursor.row, cursor.column = 6, 2;
	_board = new Tile[boardHeight][boardSize];
	_bufferRow = new Tile[boardSize];

	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			tiles[i][j].type = air;
			tiles[i][j].block.Block();
		}
	}

	for (int j = 0; j < boardSize; j++)
	{
		_bufferRow[j] = new Tile(BlockType.empty);
		_bufferRow[j].setTile(j, -1);
		//_bufferRow[j].block = new Block(BlockState.normal);
	}

}
*/
void Board::display() {

	displayBoard();
	displaybufferRow();

}
void Board::displayBoard()
{
	//bool lul;
	//char cursor1 = '\201', cursor2 = '\203', cursor3 = '\187', cursor4 = '\200', cursor5 = '\202', cursor6 = '\188';

	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{

			if (tiles[i][j].block.matching)
			{

				switch (tiles[i][j].block.getColor())
				{
				case red: textBoard[i][j] = 'R'; break;
				case green: textBoard[i][j] = 'G'; break;
				case blue: textBoard[i][j] = 'B'; break;
				case yellow: textBoard[i][j] = 'Y'; break;
				case purple: textBoard[i][j] = 'P'; break;
				case orange: textBoard[i][j] = 'O'; break;
				default: textBoard[i][j] = '_'; break;
				}
			}
			else
			{
				switch (tiles[i][j].block.getColor())
				{
				case red: textBoard[i][j] = 'r'; break;
				case green: textBoard[i][j] = 'g'; break;
				case blue: textBoard[i][j] = 'b'; break;
				case yellow: textBoard[i][j] = 'y'; break;
				case purple: textBoard[i][j] = 'p'; break;
				case orange: textBoard[i][j] = 'o'; break;
				default: textBoard[i][j] = '_'; break;
				}
			}

		}
	}

	//int cursorLocation2 = -1;
	//prints it backwards 
	printf("Board:\n Size: %d\n ", sizeof(Board));
	//printf(" ");
	//for (int i = 0; i < boardHeight; i++)
	for (int i = BOARD_HEIGHT - 1; i >= 0;i--)
	{
		
		for (int j = 0; j < boardWidth; j++)
		{
			//printf(" ");
			if (i == cursor.row && (j == cursor.column || j == cursor.column + 1)) {
				SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE), 0x5B);
			}
			else {
				SetConsoleTextAttribute(GetStdHandle(STD_INPUT_HANDLE), 0x1A);
			}
			std::cout << textBoard[i][j];
			//printf("%c", textBoard[i][j]);
			if (j < BOARD_WIDTH - 1)
			{
				if (i == cursor.row && j == cursor.column ) {
					printf("||");
				}
				else
				printf(", ");
			}

		}
		printf("\n ");
	}
	//return textBoard;
	
}
void Board::displaybufferRow()
{
	for (int j = 0; j < boardWidth; j++)
	{
		if (bufferRow[j].block.matching)
		{
			switch (bufferRow[j].block.getColor())
			{
			case red: textbufferRow[j] = 'R'; break;
			case green: textbufferRow[j] = 'G'; break;
			case blue: textbufferRow[j] = 'B'; break;
			case yellow: textbufferRow[j] = 'Y'; break;
			case orange: textbufferRow[j] = 'O'; break;
			case purple: textbufferRow[j] = 'P'; break;
			default: textbufferRow[j] = ' '; break;
			}
		}
		else
		{
			switch (bufferRow[j].block.getColor())
			{
			case red: textbufferRow[j] = 'r'; break;
			case green: textbufferRow[j] = 'g'; break;
			case blue: textbufferRow[j] = 'b'; break;
			case yellow: textbufferRow[j] = 'y'; break;
			case orange: textbufferRow[j] = 'o'; break;
			case purple: textbufferRow[j] = 'p'; break;
			default: textbufferRow[j] = ' '; break;
			}
		}
	}
	printf("bufferRow:\n ");
		for (int j = 0; j < boardWidth; j++)
		{
			printf("%c", textbufferRow[j]);
			if (j < BOARD_WIDTH - 1)
			{
				printf(", ");
			}

		}
		//printf("\n");
		printf("  bufferRow Raise Amount = %d / 16", bufferRowOffset);
		//3.2f
}

BlockColor Board::randomColor(void) {
	int defaultNbColor = 5;
	return randomColor(defaultNbColor);
}
BlockColor Board::randomColor(int nbColor) {
	//int nbBlocks = 5;
	int i = (int)(rand() % nbColor);

	switch (i)
	{
	case 0: return blue;
	case 1: return green;
	case 2: return yellow;
	case 3: return purple;
	case 4: return red;
	case 5: return orange;
	default: return none;
	}
}

void Board::init_Board(int nbBlocks = 30) {
	int blockCounter = 0;
	/*
	Checks the whole board for matches
	*/
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{

			blockCounter++;
			if (blockCounter <= nbBlocks)
			{
				tiles[i][j].block.state = BlockState::normal;
				//tiles[i][j].block.type = BlockType::block;
				tiles[i][j].type = BlockType::block;
				tiles[i][j].block.color = Board::randomColor(5);
			}
		}
	}

	for (int j = 0; j < boardWidth; j++)
	{
		bufferRow[j].block.state = BlockState::normal;
		//bufferRow[j].block.type = BlockType::block;
		bufferRow[j].type = BlockType::block;
		bufferRow[j].block.color = randomColor(5);
	}

}

void Board::initBoardRandom(){
	
	/*Init Board*/
	for (int i = 0; i < randomBoardHandler.rowInitHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			//blockCounter++;
			if (!randomBoardHandler.get(i,j) )
			{
				//tiles[i][j].block.type = BlockType::block;
				tiles[i][j].type = BlockType::block;
				tiles[i][j].block.state = BlockState::normal;
				tiles[i][j].block.color = Board::randomColor(5);
			}
		}
	}

	/*Init BufferRow*/
	for (int j = 0; j < boardWidth; j++)
	{
		//bufferRow[j].block.type = BlockType::block;
		bufferRow[j].type = BlockType::block;
		bufferRow[j].block.state = BlockState::normal;
		bufferRow[j].block.color = randomColor(5);
	}


	/*Loop until no matches*/
	while(checkAllMatches())
	{
		for (int i = 0; i < randomBoardHandler.rowInitHeight; i++)
		{
			for (int j = 0; j < boardWidth; j++)
			{
				if (tiles[i][j].isBlock() && tiles[i][j].block.matching)
				{
					tiles[i][j].block.color = Board::randomColor(5);
					tiles[i][j].block.setMatching(false);
				}

			}

		}
		for (int j = 0; j < boardWidth; j++)
		{
			if (bufferRow[j].isBlock() && bufferRow[j].block.matching)
			{
				bufferRow[j].block.color = Board::randomColor(5);
				bufferRow[j].block.setMatching(false);
			}
		}

	}
	
}

void Board::bufferRowNewbufferRow(){

	for (int j = 0; j < boardWidth; j++)
	{
		//bufferRow[j].block.type = BlockType::block;
		bufferRow[j].type = BlockType::block;
		bufferRow[j].block.state = BlockState::normal;
		bufferRow[j].block.color = randomColor(5);
	}
	//got the same code in initBoardRandom
	while (checkMatchbufferRow()) {
		for (int j = 0; j < boardWidth; j++)
		{
			if (bufferRow[j].block.matching) {
				bufferRow[j].block.color = randomColor(5);
				bufferRow[j].block.setMatching(false);
			}
		}
	}

}

bool Board::swappable(int row, int col) {

	Tile& tile = tiles[row][col];
	
	if (!tile.airLock)
	{
		if (tile.isBlock() || tile.isAir())
		{

			if (tile.block.state == BlockState::normal || tile.block.state == BlockState::falling || BlockState::swapping)
			{
				return true;
			}

		}
	}
	return false;
}
bool Board::swapBlock() {
	//cannot swap garbage blocks, matched blocks, falling blocks (unless they are on the right frame....), other swapping blocks
	if (swappable(cursor.row, cursor.column) && swappable(cursor.row, cursor.column+ 1))
	{

		if (tiles[cursor.row][cursor.column].isAir() && tiles[cursor.row][cursor.column + 1].isAir())
		{
			return false;
		}

		if (tiles[cursor.row][cursor.column].isAir())
		{
			//airlock the block under the air one if it is an air as well
			if (tiles[cursor.row - 1][cursor.column].isAir())
			{
				tiles[cursor.row - 1][cursor.column].block.state = BlockState::floating;
			}
			//airlock the row of blocks to prevent them from swapping
			for (int i = cursor.row; i < boardHeight; i++)
			{
				if (tiles[i][cursor.column + 1].isBlock())
				{
					tiles[i][cursor.column + 1].airLock = true;
				}
				else
				{
					break;
				}
			}

		}
		else if (tiles[cursor.row][cursor.column + 1].isAir())
		{
			//airlock the block under the air one if it is an air as well
			if (tiles[cursor.row - 1][cursor.column + 1].isAir())
			{
				tiles[cursor.row - 1][cursor.column + 1].block.state = BlockState::floating;
			}
			//airlock the row of blocks to prevent them from swapping
			for (int i = cursor.row; i < boardHeight; i++)
			{
				if (tiles[i][cursor.column].isBlock())
				{
					tiles[i][cursor.column].airLock = true;
				}
				else
				{
					break;
				}
			}

		}
		//actual block swapping
		_swapBlocks(cursor.row, cursor.column, cursor.row, cursor.column + 1);
		
		//setting up blocks
		tiles[cursor.row][cursor.column].block.state = BlockState::swapping;
		tiles[cursor.row][cursor.column + 1].block.state = BlockState::swapping;
		tiles[cursor.row][cursor.column].block.stateExtra = BlockExtraState::swappingRight;//goes towards right
		tiles[cursor.row][cursor.column + 1].block.stateExtra = BlockExtraState::swappingLeft;//goes towards left

		tiles[cursor.row][cursor.column].swappingCounter = 0;
		tiles[cursor.row][cursor.column + 1].swappingCounter = 0;

		/*Make both block in chain if 1 of them is when swapping them*/
		if (tiles[cursor.row][cursor.column].block.inChain || tiles[cursor.row][cursor.column + 1].block.inChain) {
			tiles[cursor.row][cursor.column].block.inChain = true;
			tiles[cursor.row][cursor.column + 1].block.inChain = true;
		}
	}
	return true;
}

bool Board::moveCursor(ControllerCommand d) {
	//Gets a controller commant (not even done yet) and moves the cursor around the board
	switch (d)
	{
		case up:
		{
		if (cursor.row < TOP_ROW)
			{
				cursor.row++;
				return true;
			}
			else {
				return false;
			}
		}
		case down:
		{
			if (cursor.row > 0)
			{
				cursor.row--;
			return true;
			}
			else {
				return false;
			}
		}
		case left:
		{
			if (cursor.column > 0)
			{
				cursor.column--;
				return true;
			}
			else {
				return false;
			}
		}
		case right:
		{
			if (cursor.column < BOARD_WIDTH -1)
			{
				cursor.column++;
				return true;
			}
			else {
				return false;
			}
		}
		default: return false;
	}
}
bool Board::handleInput(ControllerCommand input) {
	return moveCursor(input);
}
bool Board::_checkMatch(int row, int column, int row2, int column2)
{
	//if within bounds
	if (row2 >= 0 && row2 < BOARD_HEIGHT && column2 >= 0 && column2 < BOARD_WIDTH)
	{
		//if both of them are blocks
		if (tiles[row][column].isBlock() && tiles[row2][column2].isBlock())
		{
			//if both block states are normal
			if (tiles[row][column].block.state == BlockState::normal && tiles[row2][column2].block.state == BlockState::normal)
			{
				//if both have the same color
				if (tiles[row][column].block.color == tiles[row2][column2].block.color)
				{
					return true;
				}
			}

		}
	}
	return false;
}

bool Board::checkMatch(void) {
	//returns true if a match has been made
	bool match = false;
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{

			//4 steps	
			if(_checkMatch(i, j, (i + 1), j)
				&& _checkMatch(i, j, (i + 2), j) )
			{
				tiles[i][j].setBlockMatching(true);
				if (i + 1 < boardHeight)
						tiles[i + 1][j].setBlockMatching(true);
				if (i + 2 < boardHeight)
						tiles[i + 2][j].setBlockMatching(true);
				match = true;
			}
									
			if(_checkMatch(i, j, i - 1, j)
					&& _checkMatch(i, j, i - 2, j) )
			{
				tiles[i][j].setBlockMatching(true);
				if (i - 1 >= 0)
						tiles[i - 1][j].setBlockMatching(true);
				if (i - 2 >= 0)
						tiles[i - 2][j].setBlockMatching(true);
				match = true;
			}
									
			if( _checkMatch(i, j, i, j + 1) 
					&& _checkMatch(i, j, i, j + 2) )
			{
				tiles[i][j].block.setMatching(true);
				if (j + 1 < boardSize)
						tiles[i][j + 1].setBlockMatching(true);
				if (j + 2 < boardSize)
						tiles[i][j + 2].setBlockMatching(true);
				match = true;
			}
					
			if( _checkMatch(i, j, i, j - 1) 
					&& _checkMatch(i, j, i, j - 2) )
			{
				tiles[i][j].setBlockMatching(true);
				if (j - 1 >= 0)
						tiles[i][j - 1].setBlockMatching(true);
				if (j - 2 >= 0)
						tiles[i][j - 2].setBlockMatching(true);
				match = true;
			}
		}
		
	}
	return match;
}

bool Board::BetacheckMatch(void) {
	Position pos;
	bool match = false;
	std::stack<Position> newStack;

	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			//4 steps
			if (_checkMatch(i, j, (i + 1), j)
				&& _checkMatch(i, j, (i + 2), j))
			{
				//tiles[i][j].setBlockMatching(true);
				newStack.push({ i, j });
				if (i + 1 < boardHeight)
					newStack.push({ i+1, j });
				if (i + 2 < boardHeight)
					newStack.push({ i + 2, j });
				match = true;
			}

			if (_checkMatch(i, j, i - 1, j)
				&& _checkMatch(i, j, i - 2, j))
			{
				newStack.push({ i, j });
				if (i - 1 >= 0)
					newStack.push({ i-1, j });
				if (i - 2 >= 0)
					newStack.push({ i-2, j });
				match = true;
			}

			if (_checkMatch(i, j, i, j + 1)
				&& _checkMatch(i, j, i, j + 2))
			{
				newStack.push({ i, j });
				if (j + 1 < boardSize)
					newStack.push({ i, j+1 });
				if (j + 2 < boardSize)
					newStack.push({ i, j+2 });
				match = true;
			}

			if (_checkMatch(i, j, i, j - 1)
				&& _checkMatch(i, j, i, j - 2))
			{
				newStack.push({ i, j });
				if (j - 1 >= 0)
					newStack.push({ i, j-1 });
				if (j - 2 >= 0)
					newStack.push({ i, j-2 });
				match = true;
			}
		}
	}
	
	while (!newStack.empty())
	{
		pos = newStack.top();
		newStack.pop();
		tiles[pos.row][pos.column].setBlockMatching(true);
	}
	return match;
}

bool Board::_checkMatchbufferRow(int column, int column2)
{
	if (column2 >= 0 && column2 < BOARD_WIDTH)
	{
		if (bufferRow[column].isBlock() && bufferRow[column2].isBlock())
		{
			if (bufferRow[column].block.color == bufferRow[column2].block.color)
			{
				return true;
			}
		}
	}

	return false;
}

bool Board::checkMatchbufferRow(void) {

	bool match = false;

	for (int j = 0; j < boardWidth; j++)
	{
		//2 steps

		if (_checkMatchbufferRow(j, j + 1)
			&& _checkMatchbufferRow(j, j + 2))
		{
			bufferRow[j].setBlockMatching(true);
			if (j + 1 < BOARD_WIDTH)
				bufferRow[j + 1].setBlockMatching(true);
			if (j + 2 < BOARD_WIDTH)
				bufferRow[j + 2].setBlockMatching(true);
			match = true;
		}

		if (_checkMatchbufferRow(j, j - 1)
			&& _checkMatchbufferRow(j, j - 2))
		{
			bufferRow[j].setBlockMatching(true);
			if (j - 1 >= 0)
				bufferRow[j - 1].setBlockMatching(true);
			if (j - 2 >= 0)
				bufferRow[j - 2].setBlockMatching(true);
			match = true;
		}

	}

	return match;
}

bool Board::checkAllMatches(void) {
	bool matchBoard, matchStack;
	matchBoard = checkMatch();
	matchStack = checkMatchbufferRow();
	return (matchBoard || matchStack);

}

bool Board::isMatch(void) {

	std::stack<Position> tileList;
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			if (tiles[i][j].block.matching)
			{
				tileList.push({ i, j });
				//return true;
			}
		}
	}
	return false;
}

void Board::handleBufferRow() {

	/*
	if ( !isMatch() )
	{
	}
	*/

	if (!_activeBlocks)
	{
		bufferRowTics++;
		if (bufferRowTics > bufferRowTotalTics / bufferRowOffsetTotal)//or >=
		{
			bufferRowOffset++;
			bufferRowTics = 0;
		}

		if (bufferRowOffset >= bufferRowOffsetTotal)
		{
			for (int i = BOARD_HEIGHT - 2; i >= 0; i--)
			{
				for (int j = 0; j < boardWidth; j++)
				{
					tiles[i + 1][j] = tiles[i][j];

					if (i == 0)
					{
						tiles[0][j] = bufferRow[j];
					}
				}
			}
			bufferRowTics = 0;
			bufferRowOffset = 0;
			if (cursor.row < TOP_ROW)
			{
				cursor.row++;
			}
			bufferRowNewbufferRow();
		}
		/*
		if (_stackRaiseForced) {
			++_score;
		}

		_stackRaiseForced = false;
		if (_cursorY <= 10) {
			++_cursorY;
		}
		*/
	}
}

void Board::handleFallingBlocks() {
	
	/*All these act as reverse countdown, from 0 to MAX*/
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{	
			if (tiles[i][j].isBlock())
			{
				if (tiles[i][j].block.state == BlockState::normal)
				{
					
					if (i >= 1)//no need to check the bottom row
					{
						if ( tiles[i - 1][j].isAir() || tiles[i-1][j].block.state == BlockState::floating || tiles[i - 1][j].block.state == BlockState::falling || 
							(tiles[i-1][j].block.state == BlockState::cleared && tiles[i][j].block.stateExtra != BlockExtraState::fromClear)) 
						{	
							tiles[i][j].block.state = BlockState::floating;
							tiles[i][j].floatingCounter = 0;
						}
						//else if ()
					}
				}
				else if (tiles[i][j].block.state == BlockState::floating)
				{
					tiles[i][j].airLock = false;
					//block hovers for a while
					if (tiles[i][j].floatingCounter >= FloatingTime)
					{
						tiles[i][j].block.state = BlockState::falling;
						tiles[i][j].floatingCounter = Tile::DEFAULT_COUNTER_VALUE;
						
					}
					else
						tiles[i][j].floatingCounter++;

				}
				else if (tiles[i][j].block.state == BlockState::falling)
				{
					/*EDIT: no need for counters, falling takes 1 frame strait up*/

					/*If block under is air, or is clear and the block in question is not part of the cascade(block was not on top of a cleared block)
					Allows for trick chains*/
					if (tiles[i - 1][j].isAir() || tiles[i - 1][j].block.state == BlockState::floating || tiles[i - 1][j].block.state == BlockState::falling ||
						(tiles[i - 1][j].block.state == BlockState::cleared && tiles[i][j].block.stateExtra != BlockExtraState::fromClear)) 
					{	
						//Start/Continue fall
						//fall completed
						if (i >= 1)
						{
							//move block place
							tiles[i - 1][j] = tiles[i][j];
							tiles[i][j] = Tile();
						}
					}
					else
					{
						//abord fall
						tiles[i][j].airLock = false;
						tiles[i][j].block.state = BlockState::landed;
					}

				}
				else if (tiles[i][j].block.state == BlockState::landed)
				{
					tiles[i][j].block.state == BlockState::normal;
				}
			}

		}
	}
}

void Board::_swapBlocks(int row, int column, int row2, int column2) {
	Tile interTile;

	interTile = tiles[row][column];
	tiles[row][column] = tiles[row2][column2];
	tiles[row2][column2] = interTile;

}
void Board::handleSwappingBlocks() {
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
		
			if (tiles[i][j].block.state == BlockState::swapping) 
			{

				if (tiles[i][j].swappingCounter >= SwappingTime)
				{
						tiles[i][j].swappingCounter = Tile::DEFAULT_COUNTER_VALUE;						
						tiles[i][j].block.state = BlockState::normal;
						tiles[i][j].airLock = false;
				}
				else
				{
					tiles[i][j].swappingCounter++;
				}

			}
		}
	}
}

void Board::setChainAbove(int row, int col) {
	for (int y = row; y < BOARD_HEIGHT; ++y) {
		Tile& tile = tiles[y][col];
		if (tile.type == block) {
			tile.block.inChain = true;
		}
	}
}

void Board::initTics() {

	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{

		}
	}

}

/*
//seems this gets run at every frame
void Board::tick() {
	if (_state == COUNTDOWN) {
		if (_game->getTime() > COUNTDOWN_MS) {
			_state = RUNNING;
		}
	}
	else if (_state == RUNNING) {
		initTick();
		raiseStack();
		handleGarbageQueue();
		handleBlockTimers();
		handleFalling();
		handleGarbageFalling();
		matchBlocks();
		handleMatchedBlocks();
		handleTriggeredBlocks();

		sendEvents();
	}
	_eventHandler->endTick();
}
*/

void Board::run() {
	//initTimers();
	handleBufferRow();
	checkMatch();

	/*Blocks Falling needs to be done after matches, so that they interact on the next frame*/
	/*Blocks are idle for 1 frame before they can match*/

	//BetacheckMatch();
	
	//display()
}

/********

Created by PlasmaLotus

Last Edited: Nov. 12, 2016

Latest Changes:
Added Beta Game Loop
Created method for swapping blocks
Created method for managing swapping blocks
Created method for managing falling blocks



for (int i = 0; i < boardHeight; i++)
{
	for (int j = 0; j < boardWidth; j++)
	{

	}
}

TODO:
find a way to get input without stopping game loop

for now, just make the block fall without trick swaps
When clearing blocks, make the blocks on top inChain
the blocks should dissapear when cleared, but blocks on top stay since the block is clearing
create more initial boards
*********/