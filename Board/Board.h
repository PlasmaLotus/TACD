/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#include <stack>
#include <list>
#include "Block.h"
#include "Tile.h"
#include "GeneralEnum.h"
#include "BoardRandomBoardHandler.h"
#include "GarbageBlock.h"


#ifndef _Board_
#define _Board_

class Board {

public:
	static const int BOARD_HEIGHT = 12;
	static const int BOARD_WIDTH = 6;
	static const int TOP_ROW = BOARD_HEIGHT - 1;
	//static const BoardDimension = _2D;
	
	Tile tiles[BOARD_HEIGHT][BOARD_WIDTH];
	Tile bufferRow[BOARD_WIDTH];
	//int bufferRowTics;
	
	//struct cursor
	enum BoardState{Countdown, Running, Win, Lose};
	BoardState boardState;
	struct Position {
		int row, column;
		//bool equals(const Position &p1, const Position &p2);
		//bool operator==(const Position p2);
		//bool sort(const Position &p1, const Position &p2);
	};
	Position cursor;

	int topRowHold;

	int boardHeight;
	int boardSize;
	int boardWidth;
	char bufferRowOffset;

	bool forcedRaise;
	bool isChain;
	int chainCounter;
	int comboCounter;
	bool _combo;
	bool _match;
	bool _swap;
	bool _stop;
	bool _falling;

	bool _activeBlocks;

	int stopTime;
	int pauseTime;

	Board();
	~Board();
	void display();
	void displayBoard();
	void displaybufferRow();
	BlockColor randomColor(void);
	BlockColor randomColor(int nbColor);
	void initBoardEmpty();
	void init_Board(int nbBlocks);
	void initBoardRandom();
	void bufferRowNewbufferRow();
	bool swappable(int row, int col);

	bool swapBlocks();

	bool moveCursor(ControllerCommand d);

	bool moveCursorUp();
	bool moveCursorDown();
	bool moveCursorLeft();
	bool moveCursorRight();

	void addInput(ControllerCommand d);

	bool handleInput();
	bool handleInput(ControllerCommand input);

	void forceRaise();

	bool _checkMatch(int row, int column, int row2, int column2);
	bool checkMatch(void);
	bool BetacheckMatch3(void);
	bool BetacheckMatch2(void);
	bool BetacheckMatch(void);
	bool _checkMatchbufferRow(int column, int column2);
	bool checkMatchbufferRow(void);
	bool checkAllMatches(void);
	bool isMatch(void);
	bool blocksOnTopRow(void);
	void handleBufferRow();
	void handleFallingBlocks();
	bool garbageBlockCanFall(GarbageBlock & gb);
	void _swapBlocks(int row, int column, int row2, int column2);
	void handleSwappingBlocks();
	void handleMatchingBlocks();
	void ClearingBlocksInitPop(int popTime);
	void ClearingBlocksInitPopFinal(int popTimeFinal);
	void handleClearingBlocks();
	void setChainAbove(int row, int col, int chain);
	void setChainAbove(int row, int col);

	void initTics();

	void run();
	void run(ControllerCommand input);
	void reset();

	void resetRNG();

	void clearAll();

	std::list <GarbageBlock> garbageQueue;


	bool stackRaiseEnabled = true;
private:

	RandomBoardGenerator randomBoardHandler;

	std::stack <ControllerCommand> inputs;


	
	//static const char FPS = 60;
	//int boardLevel = 5;
	static const int bufferRowOffsetTotal = 16;//Amount of total steps for each bufferRow raise
	int bufferRowTics;//current step of the bufferRow
	//char bufferRowOffset;
	int bufferRowTotalTics = FPS * 5;//Amount of tics total to raise a bufferRow from 0 to 100%
		//6 secs on SHard stage 1
		//2.45 /sec on SHard
		//4.75 secs on vs level 5
		//5secs on LV5 SNES
	
	static const char BlockFlashingTime = 24;//28;//at least //44 at eazy
	static const char BlockClearWaitTime = 15;//at least //25 at eazy
	static const char BlockPopTime = 7;//block start falling at 7th frame //9 at eazy


	//const char swapSpeed = 4;
	//const char swapMidWay = 3;
	
	/*Swap, float, and fall 1 tile takes 10 frames*/

	/*
	All input takes 2 frames to register, and they activate on the next frame
	*/

	char betaValue = 0;

	/*There are 3 extra frames before falling from a match : Eazy mode*/
	/*Thinking on setting everybody on floating - offset*/
	//static const char FallingTime = 1;//nb of Frames for the block to fall 1 tile // prob 1 frame overall
	/*Same fallTime on eazy, maybe no need for fall counter*/

	static const int fallingTime = 0;
	/*Animation takes 4 frames, but can be reswapped as early as frame 3*/
	static const int SwappingTime = 4; //want block to be normal at end
	//static const char FallingBufferTime = 10;
	static const int FloatingTime = 5; // 5 or 4 //11 at eazy
	//static const char MatchTime = 0;



	//int bufferRowRaiseSpeed = 2;
	char textbufferRow[BOARD_WIDTH];
	char textBoard[BOARD_HEIGHT][BOARD_WIDTH];

	static const char BlockExplosionTics = 4;
	static const char BlockClearingBlink = 28;//on hard 1 speed

	/*In total, Swap, clear, pop and 3tile fall takes slightly more than 1 sec*/


};

#endif
