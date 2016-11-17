/*
Created by PlasmaLotus
Updated Nov 7, 2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <conio.h>
#include <time.h>//clock()
#include <Windows.h>//sleep
//#include <SDL.h>
//#include "Game.h"
//#include "Main.h"

#include "Block.h"
#include "Board.h"
#include "Tile.h"
#include "GeneralEnum.h"
#include "SFML.h"

#define MAXSAMPLES 100


int tickindex = 0;
int ticksum = 0;
static int ticklist[MAXSAMPLES];

/* need to zero out the ticklist array before starting */
/* average will ramp up until the buffer is full */
/* returns average ticks per frame over the MAXSAMPLES last frames */
void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

double CalcAverageTick(int newtick)
{
	ticksum -= ticklist[tickindex];  /* subtract value falling off */
	ticksum += newtick;              /* add new value */
	ticklist[tickindex] = newtick;   /* save new value so it can be subtracted later */
	if (++tickindex == MAXSAMPLES)    /* inc buffer index */
		tickindex = 0;

	/* return average */
	return((double)ticksum / MAXSAMPLES);
}


ControllerCommand getInput() {
	char char1, char2;

	const int LEFT = 75;
	const int RIGHT = 77;
	const int UP = 72;
	const int DOWN = 80;

	//doesnt stop for input...
	if (_kbhit())
	{

		//scanf("%c", char1);
		char1 = _getch();
		switch (char1)
		{
		case '0':
		case '224':
		{
			char2 = _getch();

			switch (char2)
			{
			case LEFT:	return ControllerCommand::left;
			case RIGHT:	return ControllerCommand::right;
			case UP:	return ControllerCommand::up;
			case DOWN:	return ControllerCommand::down;
			default:	return ControllerCommand::noInput;
			}
		}
		default: return ControllerCommand::noInput;
		}

	}
	else
	{
		return ControllerCommand::noInput;
	}
	//fflush(stdin);

}

int gameLoop(void) {

	Board board;
	ControllerCommand input;
	int frame = 0;
	int second = 0;
	int minute = 0;
	int milisecond = 0;
	int MS_PER_FRAME = 16;//miliseconds per frame
						  //clock_t FPS = 60;
	clock_t lastTime = clock();
	clock_t current = clock();
	clock_t elapsed = current - lastTime;
	while (true)
	{
		/*Manage Time Beta*/
		if (frame == 32767) {
			frame = 0;
		}
		else {
			frame++;
			milisecond++;

			if (milisecond >= 60)
			{
				second++;
				milisecond = 0;
			}

			if (second >= 60)
			{
				minute++;
				second = 0;
			}
		}

		//processInput();

		//current = clock();
		//elapsed = current - lastTime;
		current = clock();
		input = ControllerCommand::noInput;
		if (_kbhit())
		{
			board.handleInput(getInput());
		}

		printf("%d:%d  Frame: %d\n", minute, second, frame);
		printf("Average FPS: %3.2f        \nNB Frames: %3.2f     \nTemps: %d           \nClocks per Sec: %3.2f\n", CalcAverageTick((int)elapsed), (float)elapsed * 60, elapsed, (float)CLOCKS_PER_SEC);
		board.run();
		board.display();
		//lastTime = current;
		elapsed = clock() - current;

		if (MS_PER_FRAME - elapsed > 0)
		{
			fflush(stdout);
			Sleep(MS_PER_FRAME - elapsed);
		}

		//system("cmd /c cls");
		gotoxy(0, 0);
	}

	/*
	double lastTime = getCurrentTime();
	while (true)
	{
	double current = getCurrentTime();
	double elapsed = current - lastTime;
	processInput();
	update(elapsed);
	render();
	lastTime = current;
	}
	*/
}


int main(int argc, char *argv[]) {
	
	/*
	int errorCode;
	errorCode = SDL_Game();
	*/
	
	/*
	char _char;
	Board b1;
	b1.initBoardRandom();
	b1.checkAllMatches();
	b1.displayBoard();
	b1.displaybufferRow();

	_getch();
	return 0;
	*/

	//Main Game loop

	//SFML_Window();
	//SFML_Texture();
	SFML_TestWindow();
	//SpriteTest();
	//gameLoop();
	return 0;
}


/*
TODO: Get input;
*/