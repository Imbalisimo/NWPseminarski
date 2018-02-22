#pragma once
#include "stdafx.h"
#include "grid.h"
#include "snake.h"
#include "appearingWall.h"
#include "WallOptionsDlg.h"

class game {
public:
	POINT apple;
	UINT previousDirection, currentKey;
	grid map;
	snake snaky;
	appearingWall wall;

	void start();
	void moveTo(UINT key);
	bool move();
	void end();
};