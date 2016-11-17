/*
Created by PlasmaLotus
Updated Nov 17, 2016
*/

#include "Main.h"
#include "Game.h"
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

	//moved to Game class

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
	return 0;
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

	//SFML_TestWindow();
	Game game;
	game.init();
	//game.test();
	game.test2();

	//SpriteTest();
	//gameLoop();
	_getch();
	return 0;
}


/*
TODO: Get input;
*/