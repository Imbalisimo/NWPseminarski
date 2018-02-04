#pragma once
#include <list>
#include "node.h"
#include "grid.h"


class snake {
public:
	int length;
	std::list<node*> occupied;
	snake();
	void set(grid *mreza);
};