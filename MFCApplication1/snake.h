#pragma once

#include "grid.h"

class snake {
public:
	int length, startLength;
	COLORREF color_frame, color_inner;
	std::list<POINT> occupied;
	snake();
	void set(grid *map);
};