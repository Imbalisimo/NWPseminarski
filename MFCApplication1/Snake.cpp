#include "stdafx.h"
#include "snake.h"
#include "node.h"
#include "grid.h"

/*
class snake {
public:
	int length;
	std::list<node*> occupied;
	snake() {}
	snake(grid *mreza)
	{
		length = 4;
		node *n = mreza->nodes[mreza->numberOfNodes];
		n->snake_wall = 1;
		occupied.push_back(n);
		mreza->unoccupiedNodes.erase(n->number);

		n = n->right;
		n->snake_wall = 1;
		occupied.push_back(n);
		mreza->unoccupiedNodes.erase(n->number);

		n = n->right;
		n->snake_wall = 1;
		occupied.push_back(n);
		mreza->unoccupiedNodes.erase(n->number);

		n = n->up;
		n->snake_wall = 1;
		occupied.push_back(n);
		mreza->unoccupiedNodes.erase(n->number);
	}
};*/

snake::snake() {}

void snake::set(grid *map)
{
	length = 4;
	POINT maps;
	maps.x = map->x / 2;
	maps.y = map->y / 2;

	node *n;
	for (int i = 0;i < 4;++i)
	{
		n=map->nodes[maps];
		n->snake_wall = 1;
		occupied.push_back(n);
		map->unoccupiedNodes.erase(n->coordinates);
		++maps.x;
	}

	++maps.y;
	n = map->nodes[maps];
	n->snake_wall = 1;
	occupied.push_back(n);
	map->unoccupiedNodes.erase(n->coordinates);
}