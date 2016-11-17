#pragma once


#include <SDL.h>

#ifndef _Game_
#define _Game_

int SDL_Game();

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();



#endif // !_Game_

