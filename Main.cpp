/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#include "Main.h"
#include "Game.h"
#include "Block.h"
#include "Board.h"
#include "Tile.h"
#include "GeneralEnum.h"
#include "Game_SFML.h"

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

int main(int argc, char *argv[]) {
	
	Game game;
	game.init();
	game.run();

	//Game().run();
	return 0;
}
