#include "stdafx.h"
#include "snake.h"
#include "grid.h"
#include "appearingWall.h"

snake::snake() 
{
}

void snake::set(grid *map)
{
	occupied.clear();
	length = startLength;
	POINT startingPoints;
	startingPoints.x = map->x / 2;
	startingPoints.y = map->y / 2;

	for (int i = 1;i < startLength;++i)
	{
		++startingPoints.x;
		occupied.push_back(startingPoints);
		map->unoccupiedNodes.erase(startingPoints);
	}

	++startingPoints.y;
	occupied.push_back(startingPoints);
	map->unoccupiedNodes.erase(startingPoints);
}