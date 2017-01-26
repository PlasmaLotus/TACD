/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#include "Main.h"
#include "Board/Game.h"
#include "Board/Block.h"
#include "Board/Board.h"
#include "Board/Tile.h"
#include "Board/GeneralEnum.h"
#include "Board/GameRenderer.h"

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

int main(int argc, char *argv[]) {
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "TACD");
	Game game(window);
	game.init();
	game.run();

	//Game().run();
	return 0;
}
