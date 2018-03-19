#include "stdafx.h"
#include "grid.h"


grid::grid()
{
}

void grid::set_size(int x, int y)
{
	numberOfNodes = 0;
	this->x = x;
	this->y = y;
	for (int j = 0;j < y;++j) //make all points
	{
		for (int i = 0;i < x;++i)
		{
			++numberOfNodes;
			POINT p;
			p.x = i;
			p.y = j;
			unoccupiedNodes[p] = numberOfNodes;
		}
	}
	iter = unoccupiedNodes.begin();
}

POINT grid::moveIter(int spaces)
{
	iter = unoccupiedNodes.begin();
	for (int i = 0;i < spaces;++i)
		++iter;
	return iter->first;
}