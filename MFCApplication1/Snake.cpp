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

void snake::drawSnake(CDC* dc, int coefficient_x, int coefficient_y)
{
	CBrush innerBrush;
	innerBrush.CreateSolidBrush(color_inner);
	dc->SelectObject(innerBrush);
	CPen pen;
	pen.CreatePen(PS_NULL, 1, color_frame);
	dc->SelectObject(pen);

	for (POINT var : occupied)
	{
		dc->Rectangle(generate_rect(var, coefficient_x, coefficient_y));
	}
}