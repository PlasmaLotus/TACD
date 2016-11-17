/*
Created by PlasmaLotus
Updated Nov 7, 2016
*/

#ifndef _GeneralBoardEnum_
#define _GeneralBoardEnum_

#define FPS 60
#define TACD_DIRECTORY "Y:/TACD C++/"
//define TACD_DIRECTORY "C:/Users/Lee-Stenio Nazer/panel pop/TACD C++/IMG Files/"


enum BlockType { block, air, garbage };
enum BlockState { clearing, matching, cleared, swapping, floating, falling, landed, nothing, normal };
enum BlockExtraState { swappingLeft, swappingRight, fallingMidRow, swappingMid, extraNormal, fromClear};
enum BlockColor { red, yellow, green, blue, orange, purple, none };
enum BlockExtraColor { ex, null };
enum BoardState { score, vs, singlePlayer, multiPlayer };
enum BoardDimension { _2D, _3D };
enum ControllerCommand { up, down, left, right, a, b, l, r, start, cheat, noInput};

#endif
