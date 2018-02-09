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
	length = 4;
	POINT startingPoints;
	startingPoints.x = map->x / 2;
	startingPoints.y = map->y / 2;

	for (int i = 0;i < 4;++i)
	{
		++startingPoints.x;
		occupied.push_back(startingPoints);
		map->unoccupiedNodes.erase(startingPoints);
	}

	++startingPoints.y;
	occupied.push_back(startingPoints);
	map->unoccupiedNodes.erase(startingPoints);
}

/*bool snake::move(grid *map, appearingWall *wall, UINT previousDirection, UINT currentKey, POINT apple)
{ 
	int success = 1;
	POINT searchingPoint = occupied.front();
	if (previousDirection + 2 == currentKey || previousDirection - 2 == currentKey)
		currentKey = previousDirection;
	switch (currentKey)
	{
	case VK_UP:
		if (searchingPoint.y <= 0)
			success = 0;
		else
			if (previousDirection != VK_DOWN)
				--searchingPoint.y;
		break;
	case VK_DOWN:
		if (searchingPoint.y >= map->y)
			success = 0;
		else
			if (previousDirection != VK_UP)
				++searchingPoint.y;
		break;
	case VK_LEFT:
		if (searchingPoint.x <= 0)
			success = 0;
		else
			if (previousDirection != VK_RIGHT)
				--searchingPoint.x;
		break;
	case VK_RIGHT:
		if (searchingPoint.x >= map->x)
			success = 0;
		else
			if (previousDirection != VK_LEFT)
				++searchingPoint.x;
		break;
	}

	if (previousDirection != currentKey) {
		previousDirection = currentKey;
	}

	//game over or not?
	for (POINT var : occupied)
		if (var == searchingPoint)
			success = 0;
	for(POINT var : wall->built)
		if (var == searchingPoint)
			success = 0;

	occupied.push_front(searchingPoint);

	map->unoccupiedNodes.erase(searchingPoint);

	if (searchingPoint != apple) {
		searchingPoint = occupied.back();
		map->unoccupiedNodes[searchingPoint] = searchingPoint.y*map->x + searchingPoint.x;
		occupied.pop_back();
	}
	else {
		++length;
		int appleNode = rand() % map->unoccupiedNodes.size();
		apple = map->moveIter(appleNode);
	}
	
	return success == 1;
}*/