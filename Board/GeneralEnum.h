/*
Created by PlasmaLotus
Updated Dec 25, 2016
*/

#ifndef _GeneralBoardEnum_
#define _GeneralBoardEnum_

#define FPS 60


enum BlockType { block, air, garbage };
enum BlockState { clearing, matching, cleared, swapping, floating, falling, landed, nothing, normal};
enum BlockExtraState { swappingLeft, swappingRight, extraNormal, fromClear, poped};
enum BlockColor { red, yellow, green, blue, orange, purple, none, pink };
enum BlockExtraColor { ex, null };
enum BoardState { score, vs, singlePlayer, multiPlayer };
enum BoardDimension { _2D, _3D };
enum ControllerCommand { Up, Down, Left, Right, Swap, ForceRaise, Start, Cheat, Pause, NoInput};

#endif
