#pragma once

#include "grid.h"
#include "snake.h"
#include "appearingWall.h"
#include "WallOptionsDlg.h"

class game {
public:
	POINT apple;
	COLORREF color_apple;
	UINT previousDirection, currentKey;
	grid map;
	snake snaky;
	appearingWall wall;
	int time;

	void start();
	void moveTo(UINT key);
	bool move();
	void end();
};