#pragma once

#include "GeneralEnum.h"

#ifndef __Main__
#define __Main__

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

void gotoxy(int x, int y);
double CalcAverageTick(int newtick);
int gameLoop(void);
ControllerCommand getInput();

#endif // !__Main.h__