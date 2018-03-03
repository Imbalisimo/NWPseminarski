
#include "stdafx.h"
#include <map>
#include "grid.h"
#include "snake.h"
#include "appearingWall.h"


appearingWall::appearingWall() {}

void appearingWall::set(int len, int count) {
	length = len;
	countReset = count;
	countdown = countReset;
	if (countReset <= 3)
		smallCountreset = true;
	else
		smallCountreset = false;
}

void appearingWall::RdyToappear(grid *map, POINT apple) {
	if (map->unoccupiedNodes.size() > length + map->x && length > 0)
	{
		POINT p;
		POINT map_s;
		do {
			int wallStartNode = rand() % map->unoccupiedNodes.size();
			p = map->moveIter(wallStartNode);
		} while (p == apple);
		initialize.push_back(p);
		map_s = p;

		for (int i = 1;i < length; ++i)
		{
			int wallDirectionSpread = rand() % 4;
			switch (wallDirectionSpread)  //0-UP, 1-RIGHT, 2-DOWN, 3-LEFT
			{
			case 0:
				--map_s.y;
				if (map_s.y >= 0)
					break;
				++map_s.y;
			case 1:
				++map_s.x;
				if (map_s.x <= map->x)
					break;
				--map_s.x;
			case 2:
				++map_s.y;
				if (map_s.y <= map->y)
					break;
				--map_s.y;
			case 3:
				--map_s.x;
				if (map_s.x >= 0)
					break;
				++map_s.x;
			}
			initialize.push_back(map_s);
		}
	}
}

void appearingWall::onAppearance(snake *snaky, grid* map, POINT apple)
{
	for (POINT wall_s : initialize)
	{
		int flag = 1;
		for (POINT snake_s : snaky->occupied)
		{
			if (wall_s == snake_s)
				flag = 0;
		}
		if (wall_s == apple)
			flag = 0;
		if (flag == 1) 
		{
			built.push_back(wall_s);
			map->unoccupiedNodes.erase(wall_s);
		}
	}
	initialize.clear();
}

void appearingWall::wallClear(grid* map) {
	for (POINT var : built)
		map->unoccupiedNodes[var] = var.y*map->x + var.x;
	built.clear();
	countdown = countReset;
}