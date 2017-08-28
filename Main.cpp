/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#include "Main.h"
#include "States\StateManager.h"

void gotoxy(int x, int y)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

int main(int argc, char *argv[]) {
	
	StateManager& sm = StateManager::getInstance();
	sm.run();
	return 0;
}
