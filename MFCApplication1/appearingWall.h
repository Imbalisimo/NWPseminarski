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
	std::map<POINT, node*> occupied;
	appearingWall();
	void set(int len, int count);
	void RdyToappear(grid map);
	void onAppearance(snake snaky);
	void wallClear();
};
