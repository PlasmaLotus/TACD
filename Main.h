/*
Created by PlasmaLotus
Updated May 13, 2017
*/

#ifndef __Main__
#define __Main__

#include <iostream>
#include <iomanip>
//#include <conio.h>
#include <time.h>//clock()
#include <Windows.h>//gotoXY
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

//#include <SDL.h>
//#include "Game.h"
void gotoxy(int x, int y);

std::string NumberToString(int Number);
int main(int argc, char * argv[]);

namespace Color {
	enum Code {
		FG_RED = 31,
		FG_GREEN = 32,
		FG_BLUE = 34,
		FG_DEFAULT = 39,
		BG_RED = 41,
		BG_GREEN = 42,
		BG_BLUE = 44,
		BG_DEFAULT = 49
	};
	class Modifier {
		Code code;
	public:
		Modifier(Code pCode) : code(pCode) {}
		friend std::ostream&
			operator<<(std::ostream& os, const Modifier& mod) {
			return os << "\033[" << mod.code << "m";
		}
	};
}


#endif // !__Main.h__