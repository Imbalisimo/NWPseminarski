#pragma once

#include "POINToperators.h"

class grid {
public:
	int numberOfNodes, x, y;
	std::map<POINT, int> unoccupiedNodes;
	std::map<POINT, int>::iterator iter;

	grid();
	void set_size(int x, int y);
	POINT moveIter(int spaces);
};