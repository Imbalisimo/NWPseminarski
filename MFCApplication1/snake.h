#pragma once
#include <list>
#include "grid.h"

class snake {
public:
	int length;
	std::list<POINT> occupied;
	snake();
	void set(grid *map);
	//bool move(grid *map, appearingWall *wall, UINT previousDirection, UINT currentKey, POINT apple);
};