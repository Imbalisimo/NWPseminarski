#include "stdafx.h"
#include "snake.h"
#include "node.h"
#include "grid.h"


snake::snake() 
{
}

void snake::set(grid *map)
{
	length = 4;
	POINT startingPoints;
	startingPoints.x = map->x / 2;
	startingPoints.y = map->y / 2;

	for (int i = 0;i < 4;++i)
	{
		occupied.push_back(startingPoints);
		map->unoccupiedNodes.erase(startingPoints);
		++startingPoints.x;
	}

	++startingPoints.y;
	occupied.push_back(startingPoints);
	map->unoccupiedNodes.erase(startingPoints);
}