#pragma once

#include "stdafx.h"
#include <map>
#include "node.h"
#include "POINToperators.h"

class grid {
public:
	int numberOfNodes, x, y;
	std::map<POINT, node*> nodes;
	std::map<POINT, node*> unoccupiedNodes;
	std::map<POINT, node*>::iterator iter;

	grid();
	void set_size(int x, int y);
	node* moveIter(int spaces);

};