#include "stdafx.h"
#include <map>
#include "node.h"
#include "grid.h"
/*
class grid {
public:
	int numberOfNodes;
	std::map<int, node*> nodes;
	std::map<int, node*> unoccupiedNodes;
	std::map< int, node*>::iterator iter;

	grid() {}
	grid(int x, int y)
	{
		numberOfNodes = 0;
		node *prev = NULL, *upper = NULL, *nextUpper = NULL;
		for (int j = 0;j < y;++j) //napravi sve nodeove
		{
			upper = nextUpper;
			for (int i = 0;i < x;++i)
			{
				node n;
				if (i == 0)
					nextUpper = &n;

				n.left = prev;

				n.up = upper;
				upper->down = &n;

				n.right = NULL;
				n.down = NULL;

				//gdje se nalazi
				n.space.left = x*(400 / x);
				n.space.top = j*(400 / y);
				n.space.right = (1 + x)*(400 / x);
				n.space.bottom = (1 + j)*(400 / y);

				if (prev != NULL)
					prev->right = &n;
				prev = &n;

				upper = upper->right;

				n.number = ++numberOfNodes;
				nodes[numberOfNodes] = &n;
				unoccupiedNodes[n.number] = &n;
			}
		}
		iter = unoccupiedNodes.begin();
	}
	node* moveIter(int spaces)
	{
		iter = unoccupiedNodes.begin();
		for (int i = 0;i < spaces;++i)
			++iter;
		return iter->second;
	}
};*/

grid::grid()
{
}

void grid::set_size(int x, int y)
{
	numberOfNodes = 0;
	this->x = x;
	this->y = y;
	for (int j = 0;j < y;++j) //napravi sve nodeove
	{
		for (int i = 0;i < x;++i)
		{
			node n;
			n.coordinates.x = i;
			n.coordinates.y = i;

			nodes[n.coordinates] = &n;
			unoccupiedNodes[n.coordinates] = &n;
		}
	}
	iter = unoccupiedNodes.begin();
}

node* grid::moveIter(int spaces)
{
	iter = unoccupiedNodes.begin();
	for (int i = 0;i < spaces;++i)
		++iter;
	return iter->second;
}