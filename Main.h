#pragma once

#include "GeneralEnum.h"

#ifndef __Main.h__
#define __Main.h__


void gotoxy(int x, int y);
double CalcAverageTick(int newtick);
int gameLoop(void);
ControllerCommand getInput();

#endif // !__Main.h__