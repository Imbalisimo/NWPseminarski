#include "stdafx.h"
#include "game.h"

void game::getColors() 
{
	const TCHAR* filename = _T(".\\Snake.ini");

	int r, g, b;

	TCHAR* section = _T("Snake");
	r = GetPrivateProfileInt(section, _T("FR"), 255, filename);
	g = GetPrivateProfileInt(section, _T("FG"), 255, filename);
	b = GetPrivateProfileInt(section, _T("FB"), 255, filename);
	snaky.color_frame = RGB(r, g, b);

	r = GetPrivateProfileInt(section, _T("IR"), 0, filename);
	g = GetPrivateProfileInt(section, _T("IG"), 0, filename);
	b = GetPrivateProfileInt(section, _T("IB"), 0, filename);
	snaky.color_inner = RGB(r, g, b);

	section = _T("Wall");

	r = GetPrivateProfileInt(section, _T("RR"), 128, filename);
	g = GetPrivateProfileInt(section, _T("RG"), 64, filename);
	b = GetPrivateProfileInt(section, _T("RB"), 0, filename);
	wall.color_rdy = RGB(r, g, b);

	r = GetPrivateProfileInt(section, _T("BR"), 255, filename);
	g = GetPrivateProfileInt(section, _T("BG"), 166, filename);
	b = GetPrivateProfileInt(section, _T("BB"), 77, filename);
	wall.color_built = RGB(r, g, b);

	section = _T("Apple");
	r = GetPrivateProfileInt(section, _T("R"), 255, filename);
	g = GetPrivateProfileInt(section, _T("G"), 0, filename);
	b = GetPrivateProfileInt(section, _T("B"), 0, filename);
	color_apple = RGB(r, g, b);
}

void game::writeColors() 
{
	const TCHAR* filename = _T(".\\Snake.ini");

	int r, g, b;

	TCHAR* section = _T("Snake");

	r = GetRValue(snaky.color_frame);
	g = GetGValue(snaky.color_frame);
	b = GetBValue(snaky.color_frame);
	WritePrivateProfileString(section, _T("FR"), std::to_wstring(r).c_str(), filename);
	WritePrivateProfileString(section, _T("FG"), std::to_wstring(g).c_str(), filename);
	WritePrivateProfileString(section, _T("FB"), std::to_wstring(b).c_str(), filename);

	r = GetRValue(snaky.color_inner);
	g = GetGValue(snaky.color_inner);
	b = GetBValue(snaky.color_inner);
	WritePrivateProfileString(section, _T("IR"), std::to_wstring(r).c_str(), filename);
	WritePrivateProfileString(section, _T("IG"), std::to_wstring(g).c_str(), filename);
	WritePrivateProfileString(section, _T("IB"), std::to_wstring(b).c_str(), filename);

	section = _T("Wall");

	r = GetRValue(wall.color_rdy);
	g = GetGValue(wall.color_rdy);
	b = GetBValue(wall.color_rdy);
	WritePrivateProfileString(section, _T("RR"), std::to_wstring(r).c_str(), filename);
	WritePrivateProfileString(section, _T("RG"), std::to_wstring(g).c_str(), filename);
	WritePrivateProfileString(section, _T("RB"), std::to_wstring(b).c_str(), filename);

	wall.color_built = RGB(r, g, b);
	r = GetRValue(wall.color_built);
	g = GetGValue(wall.color_built);
	b = GetBValue(wall.color_built);
	WritePrivateProfileString(section, _T("BR"), std::to_wstring(r).c_str(), filename);
	WritePrivateProfileString(section, _T("BG"), std::to_wstring(g).c_str(), filename);
	WritePrivateProfileString(section, _T("BB"), std::to_wstring(b).c_str(), filename);

	section = _T("Apple");

	r = GetRValue(color_apple);
	g = GetGValue(color_apple);
	b = GetBValue(color_apple);
	WritePrivateProfileString(section, _T("R"), std::to_wstring(r).c_str(), filename);
	WritePrivateProfileString(section, _T("G"), std::to_wstring(g).c_str(), filename);
	WritePrivateProfileString(section, _T("B"), std::to_wstring(b).c_str(), filename);
}

void game::start()
{
	const TCHAR* filename = _T(".\\Snake.ini");

	getColors();

	int x, y;
	int wall_size, wall_coundown;

	TCHAR* section = _T("Snake");
	snaky.startLength = GetPrivateProfileInt(section, _T("StartLength"), 4, filename);
	WritePrivateProfileString(section, _T("StartLength"), std::to_wstring(snaky.startLength).c_str(), filename);
	time = GetPrivateProfileInt(section, _T("Speed"), 350, filename);
	WritePrivateProfileString(section, _T("Speed"), std::to_wstring(time).c_str(), filename);

	section = _T("Wall");
	x = GetPrivateProfileInt(section, _T("Width"), 10, filename);
	y = GetPrivateProfileInt(section, _T("Heigth"), 10, filename);
	wall_size = x + y;
	wall_coundown = GetPrivateProfileInt(section, _T("Countdown"), 10, filename);
	wall.duration = GetPrivateProfileInt(section, _T("Duration"), 7, filename);
	wall.buildingTime = GetPrivateProfileInt(section, _T("BuildingTime"), 3, filename);

	WritePrivateProfileString(section, _T("BuildingTime"), std::to_wstring(wall.buildingTime).c_str(), filename);
	WritePrivateProfileString(section, _T("Duration"), std::to_wstring(wall.duration).c_str(), filename);

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

	section = _T("Wall");
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
	writeColors();
	wall.wallClear(&map);
	wall.initialize.clear();
	map.unoccupiedNodes.clear();
}


void game::moveTo(UINT key)
{
	currentKey = key;
}

bool game::move()
{
	bool success = true;
	POINT searchingPoint = snaky.occupied.front();
	if (previousDirection + 2 == currentKey || previousDirection - 2 == currentKey)
		currentKey = previousDirection;
	switch (currentKey)
	{
	case VK_UP:
		if (previousDirection != VK_DOWN)
			--searchingPoint.y;

		if (searchingPoint.y < 0)
			success = false;
		break;
	case VK_DOWN:
		if (previousDirection != VK_UP)
			++searchingPoint.y;

		if (searchingPoint.y >= map.y)
			success = false;
		break;
	case VK_LEFT:
		if (previousDirection != VK_RIGHT)
			--searchingPoint.x;

		if (searchingPoint.x < 0)
			success = false;
		break;
	case VK_RIGHT:
		if (previousDirection != VK_LEFT)
			++searchingPoint.x;

		if (searchingPoint.x >= map.x)
			success = false;
		break;
	}

	if (previousDirection != currentKey) {
		previousDirection = currentKey;
	}

	if (wall.countdown < wall.buildingTime+1)
	{
		if (wall.countdown == -wall.duration)
			wall.wallClear(&map);
		if (wall.countdown == wall.buildingTime && map.unoccupiedNodes.size() > wall.length + map.x && !wall.smallCountreset)
			wall.RdyToappear(&map, apple);
		if (wall.countReset <= wall.buildingTime && wall.countReset == wall.countdown && map.unoccupiedNodes.size() > wall.length + map.x)
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
			success = false;
	for (POINT var : wall.built)
		if (var == searchingPoint)
			success = false;

	snaky.occupied.push_front(searchingPoint);

	map.unoccupiedNodes.erase(searchingPoint);
	
	if (snaky.occupied.front() == apple)  //snake goes 2 spaces??
	{
		++snaky.length;
		if (map.unoccupiedNodes.size() != 0)
		{
			int appleNode = rand() % map.unoccupiedNodes.size();
			apple = map.moveIter(appleNode);
		}

	}

	//OCCUPY THEN MOVE///////////////////

	return success;
}

void game::drawApple(CDC* dc, int coefficient_x, int coefficient_y)
{
	CBrush apple_s;
	apple_s.CreateSolidBrush(color_apple);
	dc->SelectObject(apple_s);
	dc->Ellipse(generate_rect(apple, coefficient_x, coefficient_y));
}

void game::drawScore(CDC* dc, CRect window_size)
{
	CString str;
	str.LoadStringW(101);
	str.Append(_T(":"));
	str.Append(std::to_wstring(snaky.length - snaky.startLength).c_str());
	dc->DrawText(str, &window_size, 0);
}