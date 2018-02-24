#include "stdafx.h"
#include "game.h"
#include <string>

void game::start()
{
	const TCHAR* section = _T("Snake");
	const TCHAR* filename = _T(".\\Snake.ini");

	int x, y, wall_size, wall_coundown;
	x = GetPrivateProfileInt(section, _T("Width"), 10, filename);
	y = GetPrivateProfileInt(section, _T("Heigth"), 10, filename);
	wall_size = x + y;
	wall_coundown = GetPrivateProfileInt(section, _T("Countdown"), 10, filename);
	time = GetPrivateProfileInt(section, _T("Speed"), 350, filename);

	CWallOptionsDlg wallOptions;
	wallOptions.x_spaces = x;
	wallOptions.y_spaces = y;
	wallOptions.wall_spaces = wall_size;
	wallOptions.countdown = wall_coundown;
	wallOptions.DoModal();

	x = wallOptions.x_spaces;
	y = wallOptions.y_spaces;
	wall_size = wallOptions.wall_spaces;
	wall_coundown = wallOptions.countdown;

	WritePrivateProfileString(section, _T("Width"), std::to_wstring(x).c_str(), filename);
	WritePrivateProfileString(section, _T("Heigth"), std::to_wstring(y).c_str(), filename);
	WritePrivateProfileString(section, _T("Countdown"), std::to_wstring(wall_coundown).c_str(), filename);

	currentKey = VK_LEFT;
	previousDirection = 0;

	map.set_size(x, y);
	snaky.set(&map);
	wall.set(wall_size, wall_coundown);
	int applePoint = rand() % map.unoccupiedNodes.size();
	apple.x = 0;
	apple.y = 0;
	apple = map.moveIter(applePoint);

	previousDirection = 0;
}

void game::end()
{
	wall.wallClear(&map);
	wall.initialize.clear();
	map.unoccupiedNodes.clear();
}

//NEMA TIMERA, NEMA POZIVANJA START IZ END, TO OSTAVITI U CHILDVIEW

void game::moveTo(UINT key)
{
	currentKey = key;
}

bool game::move()
{
	int success = 1;
	POINT searchingPoint = snaky.occupied.front();
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
		if (searchingPoint.y >= map.y)
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
		if (searchingPoint.x >= map.x)
			success = 0;
		else
			if (previousDirection != VK_LEFT)
				++searchingPoint.x;
		break;
	}

	if (previousDirection != currentKey) {
		previousDirection = currentKey;
	}

	if (wall.countdown < 4)
	{
		if (wall.countdown == -7)
			wall.wallClear(&map);
		if (wall.countdown == 3 && map.unoccupiedNodes.size() > wall.length + map.x && !wall.smallCountreset)
			wall.RdyToappear(&map, apple);
		if (wall.countReset <= 3 && wall.countReset == wall.countdown && map.unoccupiedNodes.size() > wall.length + map.x)
			wall.RdyToappear(&map, apple);
		if (wall.countdown == 0)
			wall.onAppearance(&snaky, &map, apple);
	}
	--wall.countdown;

	//MOVE THEN OCCUPY///////////////
	if (searchingPoint != apple) {
		POINT p = snaky.occupied.back();
		map.unoccupiedNodes[p] = p.y*map.x + p.x;
		snaky.occupied.pop_back();
	}
	else {
		++snaky.length;
		int appleNode = rand() % map.unoccupiedNodes.size();
		apple = map.moveIter(appleNode);
	}
	////////////////////////////////

	//game over or not?
	for (POINT var : snaky.occupied)
		if (var == searchingPoint)
			success = 0;
	for (POINT var : wall.built)
		if (var == searchingPoint)
			success = 0;

	snaky.occupied.push_front(searchingPoint);

	map.unoccupiedNodes.erase(searchingPoint);

	if (snaky.occupied.front() == apple)  //snake goes 2 spaces??
	{
		++snaky.length;
		int appleNode = rand() % map.unoccupiedNodes.size();
		apple = map.moveIter(appleNode);
	}

	//OCCUPY THEN MOVE///////////////////
	/*if (searchingPoint != apple) {
	searchingPoint = snaky.occupied.back();
	map.unoccupiedNodes[searchingPoint] = searchingPoint.y*map.x + searchingPoint.x;
	snaky.occupied.pop_back();
	}
	else {
	++snaky.length;
	int appleNode = rand() % map.unoccupiedNodes.size();
	apple = map.moveIter(appleNode);
	}*/
	////////////////////////////////////

	return success == 1;
}