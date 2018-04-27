#pragma once

#include "grid.h"
#include "snake.h"
#include "appearingWall.h"
#include "WallOptionsDlg.h"
#include "MFCApplication1.h"

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

	void drawApple(CDC* dc, int coefficient_x, int coefficient_y);
	void drawScore(CDC* dc, CRect window_size);
private:
	void getColors();
	void writeColors();
};