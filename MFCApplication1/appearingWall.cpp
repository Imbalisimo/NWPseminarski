
#include "stdafx.h"
#include <map>
#include "grid.h"
#include "node.h"
#include "snake.h"
#include "appearingWall.h"


appearingWall::appearingWall() {}

void appearingWall::set(int len, int count) {
	length = len;
	countReset = count;
	countdown = countReset;
}

void appearingWall::RdyToappear(grid *map, POINT apple) {
	POINT p;
	POINT map_s;
	do {
		int wallStartNode = rand() % map->unoccupiedNodes.size();
		p = map->moveIter(wallStartNode);
	} while (p == apple);
	occupied.push_back(p);
	map_s = p;

	int wallDirectionSpread = rand() % 4;
	for (int i = 1;i < length; ++i)
	{
		int wallDirectionSpread = rand() % 4;
		switch (wallDirectionSpread)  //0-UP, 1-RIGHT, 2-DOWN, 3-LEFT
		{
		case 0:
			--map_s.y;
			if (map_s.y > 0)
				break;
			++map_s.y;
		case 1:
			++map_s.x;
			if (map_s.x < map->x)
				break;
			--map_s.x;
		case 2:
			++map_s.y;
			if (map_s.y < map->y)
				break;
			--map_s.y;
		case 3:
			--map_s.x;
			if (map_s.x > 0)
				break;
			++map_s.x;
		default:
			break;   //ako bude u nekom uzem prostoru velika vjerojatnost da ce zid biti kraci i da se prostire lijevo
					 //(ali nema veze zbog brzine)
		}
		occupied.push_back(p);
	}
}

void appearingWall::onAppearance(snake *snaky)
{
	for (std::list<POINT>::iterator wall_iter = initialize.begin();wall_iter != initialize.end();++wall_iter)
	{
		int flag = 1;
		for (std::list<POINT>::iterator snak_iter = snaky->occupied.begin();snak_iter != snaky->occupied.end();++snak_iter)
		{
			if (*wall_iter == *snak_iter)
				flag = 0;
		}
		if (flag = 1)
			occupied.push_back(*wall_iter);
		else
			flag = 1;
		initialize.remove(*wall_iter);
	}
}

void appearingWall::wallClear() {
	occupied.empty();
	countdown = countReset;
}