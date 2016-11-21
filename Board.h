/*
Created by PlasmaLotus
Updated Nov 7, 2016
*/

#include <stack>
#include "Block.h"
#include "Tile.h"
#include "GeneralEnum.h"
#include "BoardRandomBoardHandler.h"


#ifndef _Board_
#define _Board_

class Board {

public:
	static const int BOARD_HEIGHT = 11;
	static const int BOARD_WIDTH = 6;
	static const int TOP_ROW = BOARD_HEIGHT - 1;
	//static const BoardDimension = _2D;
	
	Tile tiles[BOARD_HEIGHT][BOARD_WIDTH];
	Tile bufferRow[BOARD_WIDTH];
	//int bufferRowTics;
	
	//struct cursor
	struct Position {
		int row, column;
	};

	Position cursor;

	int boardHeight;
	int boardSize;
	int boardWidth;
	char bufferRowOffset;

	bool chain;
	bool combo;
	bool _activeBlocks;
	bool _stop;

	Board();
	~Board();
	void display();
	void displayBoard();
	void displaybufferRow();
	BlockColor randomColor(void);
	BlockColor randomColor(int nbColor);
	void init_Board(int nbBlocks);
	void initBoardRandom();
	void bufferRowNewbufferRow();
	//void satckNewbufferRow();
	//void initBoardRandom(int[][2]);
	bool swappable(int row, int col);

	bool swapBlock();

	bool moveCursor(ControllerCommand d);

	bool handleInput(ControllerCommand input);

	bool _checkMatch(int row, int column, int row2, int column2);
	bool checkMatch(void);

	bool BetacheckMatch(void);
	bool _checkMatchbufferRow(int column, int column2);

	bool checkMatchbufferRow(void);

	bool checkAllMatches(void);

	bool isMatch(void);

	void handleBufferRow();

	void handleFallingBlocks();

	void _swapBlocks(int row, int column, int row2, int column2);

	void handleSwappingBlocks();

	//void handleBlocks();

	void setChainAbove(int row, int col);

	void initTics();

	void run();
	void run(ControllerCommand input);


private:

	RandomBoardGenerator randomBoardHandler;
	
	//static const char FPS = 60;
	//int boardLevel = 5;
	static const char bufferRowOffsetTotal = 16;
	char bufferRowTics;
	//char bufferRowOffset;
	int bufferRowTotalTics = FPS * 5;
		//6 secs on SHard stage 1
		//2.45 /sec on SHard
		//4.75 secs on vs level 5
		//5secs on LV5 SNES
	
	static const char BlockFlashingTime = 28;//at least //44 at eazy
	static const char BlockClearWaitTime = 15;//at least //25 at eazy
	static const char BlockPopTime = 7;//block start falling at 7th frame //9 at eazy


	//const char swapSpeed = 4;
	//const char swapMidWay = 3;
	
	/*Swap, float, and fall 1 tile takes 10 frames*/

	/*
	All input takes 2 frames to register, and they activage on the next frame
	*/



	/*There are 3 extra frames before falling from a match : Eazy mode*/
	/*Thinking on setting everybody on floating - offset*/
	//static const char FallingTime = 1;//nb of Frames for the block to fall 1 tile // prob 1 frame overall
	/*Same fallTime on eazy, maybe no need for fall counter*/

	/*Animation takes 4 frames, but can be reswapped as early as frame 3*/
	static const char SwappingTime = 4; //want block to be normal at end
	//static const char FallingBufferTime = 10;
	static const char FloatingTime = 5; //or 4 //11 at eazy
	//static const char MatchTime = 0;



	//int bufferRowRaiseSpeed = 2;
	char textbufferRow[BOARD_WIDTH];
	char textBoard[BOARD_HEIGHT][BOARD_WIDTH];

	

	static const char BlockExplosionTics = 4;
	static const char BlockClearingBlink = 28;//on hard 1 speed

	/*In total, Swap, clear, pop and 3tile fall takes slightly more than 1 sec*/



	struct MatchedBlocks {
		std::stack<Position> positionList;
		char matchCounter;
	};

};

#endif
