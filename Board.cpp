/*
Created by PlasmaLotus
Updated Nov 25, 2016
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
isChain(false),
chainCounter(1),
comboCounter(0),
_combo(false),
forceRaise(false),
_activeBlocks(false),
_stop(false),
stopTime(0),
pauseTime(0),
_match(false),
_falling(false),
cursor({ 4,2 }),
boardState(BoardState::Running){
	std::srand(time(NULL));
	initBoardRandom();
	//init_Board(120);
}

Board::~Board(){
}

void Board::reset()
{
	clearAll();
	initBoardRandom();
}

void Board::clearAll() {
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			tiles[i][j] = Tile();
		}
	}
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

/*Display the state of the whole board in the Command Line*/
void Board::display() {
	displayBoard();
	displaybufferRow();
}

/*Displays the state of the board in the Command Line*/
void Board::displayBoard()
{
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
				case pink: textBoard[i][j] = 'K'; break;
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
				case pink: textBoard[i][j] = 'k'; break;
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
	if (isChain)
	{
		printf("Chain: %d\n", chainCounter);
	}
	if (comboCounter > 3)
	{
		printf("Combo: %d\n", comboCounter);
	}
}

/*Displays the state of the bufferRow in the Command Line*/
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
			case pink: textbufferRow[j] = 'K'; break;
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
			case pink: textbufferRow[j] = 'k'; break;
			default: textbufferRow[j] = ' '; break;
			}
		}
	}
	printf("bufferRow: \n ");
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

/*Returns a Random Block Color*/
BlockColor Board::randomColor(void) {
	int defaultNbColor = 5;
	return randomColor(defaultNbColor);
}
/*Returns a Random Block Color*/
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

void Board::initBoardEmpty() {
	for (int i = 0; i < randomBoardHandler.rowInitHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			tiles[i][j].block.state = BlockState::normal;
		}
	}

	for (int j = 0; j < boardWidth; j++)
	{
		//bufferRow[j].block.type = BlockType::block;
		//bufferRow[j].type = BlockType::block;
		bufferRow[j].block.state = BlockState::normal;
		//bufferRow[j].block.color = randomColor(5);
	}

}

/*Initiate the board and buffer Row*/
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

/*Init Board with RandomBoardHandler*/
void Board::initBoardRandom(){
	std::srand(time(NULL));
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
	
		if (tile.isBlock() || tile.isAir())
		{
			if (tile.type == BlockType::block && tile.block.state == BlockState::swapping && tiles[row - 1][col].type == BlockType::air) {
				//if it is swapping and the tile under it would be air
				//prevent from swapping mid air
				return false;
			}

			if (tile.type == BlockType::air && (tiles[row + 1][col].block.state == BlockState::falling || tiles[row + 1][col].block.state == BlockState::swapping || tiles[row + 1][col].block.state == BlockState::floating))
			{
				return false;
			}

			/*
			if (tile.type == BlockType::air && tile.block.state == BlockState::swapping)
			{
				//will fail
				//prevent air from swapping again
				return false;
			}
			*/

			if (tile.block.state == BlockState::normal || tile.block.state == BlockState::falling || tile.block.state == BlockState::swapping )// || tile.block.stateExtra == BlockExtraState::poped)
			{
				return true;
			}

		}
	return false;
}
bool Board::swapBlocks() {
	//cannot swap garbage blocks, matched blocks, falling blocks (unless they are on the right frame....), other swapping blocks
	if (swappable(cursor.row, cursor.column) && swappable(cursor.row, cursor.column+ 1))
	{
		if (tiles[cursor.row][cursor.column].isAir() && tiles[cursor.row][cursor.column + 1].isAir())
		{
			return false;
		}

		if (tiles[cursor.row][cursor.column].isAir())
		{
			tiles[cursor.row][cursor.column].block.state = BlockState::floating;
			//airlock the block under the air one if it is an air as well
			if (tiles[cursor.row - 1][cursor.column].isAir())
			{
				tiles[cursor.row - 1][cursor.column].block.state = BlockState::floating;//set it to floating...
			}
			//airlock the row of blocks to prevent them from swapping
		}
		else if (tiles[cursor.row][cursor.column + 1].isAir())
		{
			tiles[cursor.row][cursor.column+1].block.state = BlockState::floating;
			//airlock the block under the air one if it is an air as well
			if (tiles[cursor.row - 1][cursor.column + 1].isAir())
			{
				tiles[cursor.row - 1][cursor.column + 1].block.state = BlockState::floating;
			}
			
		}
		

		/*
		if (tiles[cursor.row][cursor.column].block.state == BlockState::falling)
		{
			if (tiles[cursor.row][cursor.column + 1].type == BlockType::block && !swappable(cursor.row, cursor.column + 1)){
				/*Cannot be swapped in air unless
				return false;
			}
		}
		else if (tiles[cursor.row][cursor.column + 1].block.state == BlockState::falling)
		{
			if (tiles[cursor.row][cursor.column].type == BlockType::block && !swappable(cursor.row, cursor.column)) {
				//Cannot be swapped in air unless
				return false;
			}
		}
		*/

		/*
			if ((tiles[cursor.row][cursor.column + 1].type == BlockType::block && !swappable(cursor.row, cursor.column + 1)) || (tiles[cursor.row][cursor.column - 1].type == BlockType::block && !swappable(cursor.row, cursor.column - 1))) {
				//Cannot be swapped in air unless 
				return false;
			}
		*/
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
		case Up:
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
		case Down:
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
		case Left:
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
		case Right:
		{
			if (cursor.column < BOARD_WIDTH -2)
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
void Board::addInput(ControllerCommand d) {
	inputs.push(d);
}
bool Board::handleInput() {
	
	while (!inputs.empty())
	{
		ControllerCommand input = inputs.top();
		inputs.pop();
		switch(input)
		{
			case ControllerCommand::Up :
			case ControllerCommand::Down :
			case ControllerCommand::Left :
			case ControllerCommand::Right :
			{
				return moveCursor(input);
			}
			case ControllerCommand::Swap :
				{
					//swap blocks
					swapBlocks();
					break;
				}
			case ControllerCommand::ForceRaise :
				{
					forceRaise = true;//force Raise
					break;
				}
			case ControllerCommand::Pause:
			{
				betaValue++;
			}
			case ControllerCommand::NoInput :
			default: return false;
		}
	}
	return false;
	
}
bool Board::handleInput(ControllerCommand input) {

	switch (input)
	{
		case ControllerCommand::Up:
		case ControllerCommand::Down:
		case ControllerCommand::Left:
		case ControllerCommand::Right:
		{
			return moveCursor(input);
			break;
		}
		case ControllerCommand::Swap:
		{
			//swap blocks
			swapBlocks();
			break;
		}
		case ControllerCommand::ForceRaise:
		{
			forceRaise = true;//force Raise
			break;
		}
		case ControllerCommand::Pause:
		{
			betaValue++;
			break;
		}
		case ControllerCommand::NoInput:
		default: return false;
	}
	return true;

}
/*Verifies if two tiles match*/
bool Board::_checkMatch(int row, int column, int row2, int column2)
{
	//if within bounds
	if (row2 >= 0 && row2 < BOARD_HEIGHT && column2 >= 0 && column2 < BOARD_WIDTH)
	{
		//if both of them are blocks
		if (tiles[row][column].isBlock() && tiles[row2][column2].isBlock())
		{
			//if both block states are normal
			if ((tiles[row][column].block.state == BlockState::normal || tiles[row][column].block.state == BlockState::landed ) && 
				(tiles[row2][column2].block.state == BlockState::normal || tiles[row2][column2].block.state == BlockState::landed))
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

/*Check the whole board to find all matching trios or more*/
bool Board::checkMatch(void) {
	//returns true if a match has been made
	bool match = false;

	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			//bool interMatch = false;
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
				//interMatch = true;
			}
			/*					
			if(_checkMatch(i, j, i - 1, j)
					&& _checkMatch(i, j, i - 2, j) )
			{
				tiles[i][j].setBlockMatching(true);
				if (i - 1 >= 0)
						tiles[i - 1][j].setBlockMatching(true);
				if (i - 2 >= 0)
						tiles[i - 2][j].setBlockMatching(true);
				match = true;
				//interMatch = true;
			}
			*/

			if( _checkMatch(i, j, i, j + 1) 
					&& _checkMatch(i, j, i, j + 2) )
			{
				tiles[i][j].block.setMatching(true);
				if (j + 1 < boardSize)
						tiles[i][j + 1].setBlockMatching(true);
				if (j + 2 < boardSize)
						tiles[i][j + 2].setBlockMatching(true);
				match = true;
				//interMatch = true;
			}
			/*	
			if( _checkMatch(i, j, i, j - 1) 
					&& _checkMatch(i, j, i, j - 2) )
			{
				tiles[i][j].setBlockMatching(true);
				if (j - 1 >= 0)
						tiles[i][j - 1].setBlockMatching(true);
				if (j - 2 >= 0)
						tiles[i][j - 2].setBlockMatching(true);
				match = true;
				//interMatch = true;
			}
			*/

			//if (interMatch)
			if (match)
			{
				isChain = true;
				/*
				if (tiles[i][j].chainNumber >= chainCounter)
				{
					chainCounter = tiles[i][j].chainNumber;
				}
				*/
			}
		}
		
	}

	_match = match;
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

bool Board::blocksOnTopRow(void)
{
	for (int j = 0; j < boardSize; j++)
	{
		if (tiles[TOP_ROW][j].isBlock() || tiles[TOP_ROW][j].isGarbage())
			return true;
	}
	return false;
}
/*Handle the raising of the Stack*/
void Board::handleBufferRow() {

	/*Handle Buffer Row / Handle BufferRow / Handle Raising Blocks*/
	/*TODO: implement forceRaise*/
	/*
	if ( !isMatch() )
	{
	}
	*/

	//if (!_match && !_swap)//!_activeBlocks
	if (boardState = BoardState::Running)
	{
		if (stackRaiseEnabled)
		{
			if (!_stop)
			{
					/*Add pause timer here
						forceRaise should override stoptime*/
				if (!blocksOnTopRow())
				{

					bufferRowTics++;

					if (forceRaise)
					{
						bufferRowTics = 0;
						bufferRowOffset++;
					}
					if (bufferRowTics > bufferRowTotalTics / bufferRowOffsetTotal)//or >=
					{
						bufferRowOffset++;
						bufferRowTics = 0;
					}

					/*swap rows*/
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
						forceRaise = false;//stop force raise
					}

				}
				else
				{
					//make me lose the game
				}
			}
			else
			{
				forceRaise = false;
			}
		}
	}
}

/*Manage the state of all falling and soon to be falling blocks*/
void Board::handleFallingBlocks() {
	/*Handle falling*/
	/*All these act as reverse countdown, from 0 to MAX*/
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			if (tiles[i][j].type == BlockType::block)
			{
				if (tiles[i][j].block.state == BlockState::normal)
				{

					if (i >= 1)//no need to check the bottom row
					{
						if ((tiles[i - 1][j].type == BlockType::air && tiles[i-1][j].block.state != BlockState::swapping) || tiles[i - 1][j].block.state == BlockState::floating || tiles[i - 1][j].block.state == BlockState::falling)//|| (tiles[i-1][j].block.state == BlockState::cleared && tiles[i][j].block.stateExtra != BlockExtraState::fromClear)) 
						{
							tiles[i][j].block.state = BlockState::floating;
							//tiles[i][j].floatingCounter = tiles[i - 1][j].floatingCounter;
							tiles[i][j].floatingCounter = 0;

						}
						//else if ()
					}
				}
				else if (tiles[i][j].block.state == BlockState::floating)
				{
					//tiles[i][j].airLock = false;
					//block hovers for a while
					if (tiles[i][j].floatingCounter > FloatingTime)
					{
						tiles[i][j].block.state = BlockState::falling;
						tiles[i][j].floatingCounter = Tile::DEFAULT_COUNTER_VALUE;
						tiles[i][j].fallingCounter = 0;

					}
					else
						tiles[i][j].floatingCounter++;

				}
				else if (tiles[i][j].block.state == BlockState::falling)//dont fall if there is a block under
				{
					/*EDIT: no need for counters, falling takes 1 frame strait up*/
					/*EDIT EDIT: adding counters again */

					/*If block under is air, or is clear and the block in question is not part of the cascade(block was not on top of a cleared block)
					Allows for trick chains*/
					if (i >= 1)
					{
						if (tiles[i][j].fallingCounter > fallingTime)
						{

							if ((tiles[i - 1][j].type == BlockType::air && tiles[i - 1][j].block.state != BlockState::swapping))
							{
								/*if under is air and isnt swapping*/
								/*Falls through*/
								/*TODO: implement the state from Clear*/
								//move block place
								tiles[i - 1][j] = tiles[i][j];
								//tiles[i][j] = Tile();
								tiles[i][j].type = BlockType::air;
								tiles[i][j].block.state = BlockState::normal;
							}
							if (tiles[i - 1][j].type == BlockType::block && tiles[i - 1][j].block.state == BlockState::swapping)
							{
								/*Stay Falling, try*/
								/*Actually, it needs to land to be matched*/
								tiles[i][j].block.state = BlockState::falling;
							}

							if (tiles[i - 1][j].block.state == BlockState::normal  || tiles[i-1][j].block.state == BlockState::landed || tiles[i - 1][j].block.state == BlockState::swapping)
							{
								/*abord fall*/
								//tiles[i][j].airLock = false;
								tiles[i][j].block.state = BlockState::landed;
							}
							if (tiles[i - 1][j].block.state == BlockState::cleared && tiles[i][j].block.stateExtra != BlockExtraState::fromClear)//skill chain mechanics
							{
								/*yet to be implemenmted*/
							}
						}
						else
						{
							tiles[i][j].fallingCounter++;
						}

					}
					else if (i <= 0)
					{
						tiles[i][j].block.state = BlockState::landed;
					}
				}
				else if (tiles[i][j].block.state == BlockState::landed)
				{
					tiles[i][j].block.state = BlockState::normal;
				}
			}
			else if (tiles[i][j].type == BlockType::air)
			{
				if (tiles[i][j].block.state == BlockState::floating)
				{
					tiles[i][j].block.state = BlockState::falling;
				}
				else if (tiles[i][j].block.state == BlockState::falling)
				{
					tiles[i][j].block.state = BlockState::landed;
				}
				else if (tiles[i][j].block.state == BlockState::landed)
				{
					tiles[i][j].block.state = BlockState::normal;
				}
			}
		}
	}
}

bool Board::garbageBlockCanFall(GarbageBlock &gb) {

}
/*Actually Swap tiles */
void Board::_swapBlocks(int row, int column, int row2, int column2){
	Tile interTile;
	interTile.type = BlockType::block;

	interTile.block = tiles[row][column].block;
	interTile.type = tiles[row][column].type;

	tiles[row][column].block = tiles[row2][column2].block;
	tiles[row][column].type = tiles[row2][column2].type;

	tiles[row2][column2].block = interTile.block;
	tiles[row2][column2].type = interTile.type;

}
/*Manage the swapping blocks' timer*/
void Board::handleSwappingBlocks() {
	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
		
			if (tiles[i][j].block.state == BlockState::swapping) 
			{

				if (tiles[i][j].swappingCounter > SwappingTime)
				{
						tiles[i][j].swappingCounter = Tile::DEFAULT_COUNTER_VALUE;						
						tiles[i][j].block.state = BlockState::normal;
						//tiles[i][j].airLock = false;
				}
				else
				{
					tiles[i][j].swappingCounter++;
				}

			}
		}
	}
}

/*Check the whole board to see if any are matching*/
void Board::handleMatchingBlocks(){
	int popTime = BlockPopTime;

	/*Also handles incrementing chain number*/
	bool chaining = false;
	bool clearing = false;
	int combo = 0;

	for (int i = 0; i < boardHeight; i++) {
		for (int j = 0; j < boardWidth; j++) {
			switch (tiles[i][j].block.state)
			{
			case BlockState::normal:
			{
				if (tiles[i][j].block.state == BlockState::normal && tiles[i][j].block.matching)
				{
					tiles[i][j].block.state = BlockState::matching;
					tiles[i][j].matchingCounter = 0;
					/*
					if (chainCounter < tiles[i][j].chainNumber)
						chainCounter = tiles[i][j].chainNumber;
					*/
					combo++;
					if (tiles[i][j].chain)
					{
						chaining = true;
					}
				}
				break;
			}
			case BlockState::matching:
			{
				if (tiles[i][j].matchingCounter >= BlockFlashingTime)
				{
					tiles[i][j].matchingCounter = Tile::DEFAULT_COUNTER_VALUE;
					tiles[i][j].block.state = BlockState::clearing;
					clearing = true;
					//initClearing(pop)
					tiles[i][j].popCounter = 0;
					tiles[i][j].popCounterFinal = 0;
					tiles[i][j].block.matching = false;

				}
				else
					tiles[i][j].matchingCounter++;
				break;
			}
			case BlockState::clearing:
			{
				tiles[i][j].popCounter--;
				tiles[i][j].popCounterFinal--;
				if (tiles[i][j].popCounter < 0)
				{
					/*Clear the block*/
					//tiles[i][j].type = BlockType::air;
					tiles[i][j].block.stateExtra = BlockExtraState::poped;
					if (tiles[i][j].popCounterFinal < 0)
					{
						tiles[i][j].block.state = BlockState::cleared;
						//tiles[i][j].block.stateExtra = BlockExtraState::extraNormal;

						//setChainAbove(i, j, tiles[i][j].chainNumber);
					}
				}
				break;
			}
			case BlockState::cleared:
			{
				/*TODO: generate Pop mechanics*/
				//tiles[i][j] = Tile();
				setChainAbove(i, j);
				tiles[i][j].type = BlockType::air;
				tiles[i][j].block.state = BlockState::normal;
				tiles[i][j].setBlockMatching(false);
				break;
			}
			}
		
		}
	}
	if (clearing)
	{
		handleClearingBlocks();
	}
	if (chaining)
	{
		chainCounter++;
	}

	comboCounter = combo;
}

/*Manage all clearing blocks' pop timers*/
void Board::handleClearingBlocks() {
	int popTime = BlockPopTime;

	/*Init Popping*/
	/*Start from the top*/
	int chainNumberAll = chainCounter;//Set all Blocks in the match to the same chain number

	
	for (int i = boardHeight - 1; i >= 0; i--) {
		for (int j = 0; j < boardWidth; j++) {
			//***find how many blocks are needed to pop at the same time
			if (tiles[i][j].block.state == BlockState::clearing && tiles[i][j].popCounter == 0)// && tiles[i][j].popCounter == Tile::DEFAULT_POP_VALUE) {
			{
				tiles[i][j].popCounter += BlockClearWaitTime + popTime;
				popTime += BlockPopTime;

				/*
				if (tiles[i][j].chainNumber > chainNumberAll)
				{
					chainNumberAll = tiles[i][j].chainNumber;
				}
				*/
			}
		}
	}
	for (int i = boardHeight - 1; i >= 0; i--) {
		for (int j = 0; j < boardWidth; j++) {

			if (tiles[i][j].block.state == BlockState::clearing && tiles[i][j].popCounterFinal == 0)// && tiles[i][j].popCounter != Tile::DEFAULT_POP_VALUE && tiles[i][j].popCounter == Tile::DEFAULT_POP_VALUE) {
			{
				tiles[i][j].popCounterFinal += BlockClearWaitTime + popTime;
				//tiles[i][j].chainNumber = chainNumberAll;
				//popTime += BlockPopTime;
				//***find how many blocks are needed to pop at the same time
			}
		}
	}

}

/*Set All blocks over the clearing block to have a higher chain if matched*/
void Board::setChainAbove(int row, int col) {
	for (int y = row+1; y < BOARD_HEIGHT; ++y) {
		Tile& tile = tiles[y][col];
		if (tile.type == BlockType::block && tile.block.state == BlockState::normal) {
			tile.block.inChain = true;
			//tile.chainNumber = chain + 1;
			tile.chain = true;
			tile.block.stateExtra = BlockExtraState::fromClear;
			//was trying to set the block preemptively
			//tile.block.state = BlockState::floating;
			//tile.floatingCounter = 0;
			//tile.floatingCounter = -2
		}
		else {
			break;
		}
	}
}

/*Init the state of the Board on every Tic*/
void Board::initTics() {
	
	int matchingChain = 0;//Checks board if There is any falling or clearing blocks
	_match = false;
	_swap = false;
	_stop = false;
	_falling = false;
	//forceRaise = false;
	for (int i = 0; i < boardHeight; i++)
	{
		for (int j = 0; j < boardWidth; j++)
		{
			
			if (!isChain) {
				tiles[i][j].chain = false;
				//tiles[i][j].chainNumber = 1;
			}
			
			if (tiles[i][j].block.state == BlockState::cleared || tiles[i][j].block.state == BlockState::clearing || tiles[i][j].block.state == BlockState::matching)
			{
				_match = true;
			}
			if (tiles[i][j].block.state == BlockState::swapping)
			{
				_swap = true;
			}
			if ( (tiles[i][j].type == BlockType::block || tiles[i][j].type == BlockType::garbage) && ( tiles[i][j].block.state == BlockState::falling || tiles[i][j].block.state == BlockState::landed || tiles[i][j].block.state == BlockState::floating))
			{
				_falling = true;
			}
			
			if (tiles[i][j].type == BlockType::air && tiles[i][j].block.state != BlockState::swapping) {
				tiles[i][j].block.stateExtra = BlockExtraState::extraNormal;
				if (!isChain)
				{
					tiles[i][j].block.state = BlockState::normal;
					tiles[i][j].block.color = BlockColor::none;
				}
			}

			/*
			if (!_match)
			{
				if(tiles[i][j].block.state != BlockState::matching)
				{
					tiles[i][j].setBlockMatching(false);
				}
				//tiles[i][j].airLock = false;//airlock isnt good
				//if()
				//tiles[i][j].block.state = BlockState::normal;//caused problem
			}
			*/

			/*check if any match*/
			switch (tiles[i][j].block.state)
			{
				//case BlockState::matching:
				case BlockState::falling:
				case BlockState::floating:
				case BlockState::clearing:
				case BlockState::cleared:
				case BlockState::matching:
				case BlockState::landed:
				{
					matchingChain++;
					break;
				}
				case BlockState::normal:
				{

					//tiles[i][j].setBlockMatching(false);
					/*
					if (tiles[i][j].block.stateExtra == BlockExtraState::fromClear)
					{
						matchingChain++;
					}
					*/
					if (tiles[i][j].block.stateExtra == BlockExtraState::swappingLeft || tiles[i][j].block.stateExtra == BlockExtraState::swappingRight || tiles[i][j].block.stateExtra == BlockExtraState::poped)
					{
						tiles[i][j].block.stateExtra = BlockExtraState::extraNormal;
						break;
					}
				}
				default: 
					break;
			}


		}
	}
	if (matchingChain <= 0) {
		isChain = false;
	}
	if (_match || _falling)// || _swap)//should not be swap as well
	{
		isChain = true;
	}
	if (!isChain) {
		chainCounter = 1;
		comboCounter = 0;
	}

	if (_match || _swap || _falling)
	{
		_stop = true;
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
void Board::run(ControllerCommand input)
{
	handleInput(input);
	run();
}
void Board::run() {
	initTics();
	
	//handleInput();
	//handleInput(input);
	/*
	while (!inputs.empty())
	{
		inputs.pop();
	}
	*/
	handleSwappingBlocks();
	handleMatchingBlocks();//switch block to matching state
	handleFallingBlocks();//blocks fall
	checkMatch();//find all block that match
	//BetacheckMatch();

	/*Blocks Falling needs to be done after matches, so that they interact on the next frame*/
	/*Blocks are idle for 1 frame before they can match*/
	handleBufferRow();
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

I HATE CODING!!!

Chain doesnt continue if doing basic skill chain
Chain does not continue after 2 ////
 // there is like 1 frame of the chain failing
ie swapping a block under a falling block
Finally added ForceRaise
Added testBoards that are generated from the .pop files

for now, just make the block fall without trick swaps
When clearing blocks, make the blocks on top inChain
the blocks should dissapear when cleared, but blocks on top stay since the block is clearing
create more initial boards
*********/
