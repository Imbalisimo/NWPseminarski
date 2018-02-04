
#include "stdafx.h"
#include <map>
#include "grid.h"
#include "node.h"
#include "snake.h"
#include "appearingWall.h"
/*
class appearingWall {
public:
	int length;
	int countdown;
	int countReset;
	std::map<int, node*> occupied;
	appearingWall() {}
	appearingWall(int len, int count) : length(len), countReset(count) {
		countdown = countReset;
	}
	void RdyToappear(grid mreza) {
		node* n;
		do {
			int wallStartNode = rand() % mreza.unoccupiedNodes.size();
			n = mreza.moveIter(wallStartNode);
		} while (n->apple == 1);
		occupied[0] = n;

		int wallDirectionSpread = rand() % 4;
		for (int i = 1;i < length; ++i)
		{
			int wallDirectionSpread = rand() % 4;
			switch (wallDirectionSpread)  //0-UP, 1-RIGHT, 2-DOWN, 3-LEFT
			{
			case 0:
				if (n->up != NULL)
				{
					n->about_to_appear = 1;
					n = n->up;
					break;
				}
			case 1:
				if (n->right != NULL)
				{
					n->about_to_appear = 1;
					n = n->right;
					break;
				}
			case 2:
				if (n->down != NULL)
				{
					n->about_to_appear = 1;
					n = n->down;
					break;
				}
			case 3:
				if (n->left != NULL)
				{
					n->about_to_appear = 1;
					n = n->left;
					break;
				}
			default:
				break;   //ako bude u nekom uzem prostoru velika vjerojatnost da ce zid biti kraci i da se prostire lijevo
						 //(ali nema veze zbog brzine)
			}
			occupied[i] = n;
		}
	}
	void onAppearance(snake zmija)
	{
		for (int i = 0;i < occupied.size();++i)
			if (occupied[i]->snake_wall == 0)
				occupied[i]->snake_wall = 1, occupied[i]->about_to_appear = 0;
			else
				occupied[i]->about_to_appear = 0, occupied.erase(i);
	}

	void wallClear() {
		occupied.empty();
		countdown = countReset;
	}
};*/

appearingWall::appearingWall() {}

void appearingWall::set(int len, int count) {
	length = len;
	countReset = count;
	countdown = countReset;
}

void appearingWall::RdyToappear(grid map) {
	node* n;
	POINT maps;
	do {
		int wallStartNode = rand() % map.unoccupiedNodes.size();
		n = map.moveIter(wallStartNode);
	} while (n->apple == 1);
	occupied[n->coordinates] = n;
	maps = n->coordinates;

	int wallDirectionSpread = rand() % 4;
	for (int i = 1;i < length; ++i)
	{
		int wallDirectionSpread = rand() % 4;
		switch (wallDirectionSpread)  //0-UP, 1-RIGHT, 2-DOWN, 3-LEFT
		{
		case 0:
			--maps.y;
			if (maps.y > 0)
			{
				std::map<POINT, node*>::iterator iter = map.nodes.find(maps);
				n = iter->second;
				n->about_to_appear = 1;
				break;
			}
			++maps.y;
		case 1:
			++maps.x;
			if (maps.x < map.x)
			{
				std::map<POINT, node*>::iterator iter = map.nodes.find(maps);
				n = iter->second;
				n->about_to_appear = 1;
				break;
			}
			--maps.x;
		case 2:
			++maps.y;
			if (n->coordinates.y < map.y)
			{
				std::map<POINT, node*>::iterator iter = map.nodes.find(maps);
				n = iter->second;
				n->about_to_appear = 1;
				break;
			}
			--maps.y;
		case 3:
			--maps.x;
			if (n->coordinates.x > 0)
			{
				std::map<POINT, node*>::iterator iter = map.nodes.find(maps);
				n = iter->second;
				n->about_to_appear = 1;
				break;
			}
			++maps.x;
		default:
			break;   //ako bude u nekom uzem prostoru velika vjerojatnost da ce zid biti kraci i da se prostire lijevo
					 //(ali nema veze zbog brzine)
		}
		occupied[n->coordinates] = n;
	}
}

void appearingWall::onAppearance(snake zmija)
{
	for (std::map<POINT, node*>::iterator iter = occupied.begin();iter != occupied.end();++iter)
	{
		if (iter->second->snake_wall == 0)
			iter->second->snake_wall = 1;
		else
			occupied.erase(iter->first);
		iter->second->about_to_appear = 0;
	}
}

void appearingWall::wallClear() {
	occupied.empty();
	countdown = countReset;
}