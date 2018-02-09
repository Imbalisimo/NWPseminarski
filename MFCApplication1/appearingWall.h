#pragma once

#include "stdafx.h"
#include <map>
#include "grid.h"
#include "node.h"
#include "snake.h"
#include "POINToperators.h"

class appearingWall {
public:
	int length;
	int countdown;
	int countReset;
	std::list<POINT> built;
	std::list<POINT> initialize;
	appearingWall();
	void set(int len, int count);
	void RdyToappear(grid *map, POINT apple);
	void onAppearance(snake *snaky, grid* map, POINT apple);
	void wallClear(grid* map);
};
