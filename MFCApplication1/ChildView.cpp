
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChildView.h"
#include <map>
#include <list>
#include <vector>
#include <iterator>
#include "snake.h"
#include "grid.h"
#include "appearingWall.h"
#include "WallOptionsDlg.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRect generate_rect(POINT a, int coefficient_x, int coefficient_y)
{
	CRect rect;
	rect.top = coefficient_y*a.y;
	rect.left = coefficient_x*a.x;
	rect.bottom = rect.top + coefficient_y;
	rect.right = rect.left + coefficient_x;
	return rect;
}

void CChildView::start(grid *map, snake *snaky, appearingWall *wall)
{
	int x, y, wall_size, wall_coundown;
	x = GetPrivateProfileInt(_T("Snake"), _T("Width"), 10, _T("Snake.ini"));
	y = GetPrivateProfileInt(_T("Snake"), _T("Heigth"), 10, _T("Snake.ini"));
	wall_size = x + y;
	wall_coundown = GetPrivateProfileInt(_T("Snake"), _T("Countdown"), 10, _T("Snake.ini"));

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

	WritePrivateProfileString(_T("Snake"), _T("Width"), std::to_wstring(x).c_str(), _T("Snake.ini"));
	WritePrivateProfileString(_T("Snake"), _T("Heigth"), std::to_wstring(y).c_str(), _T("Snake.ini"));
	WritePrivateProfileString(_T("Snake"), _T("Countdown"), std::to_wstring(wall_coundown).c_str(), _T("Snake.ini"));
	
	currentKey = VK_LEFT;
	previousDirection = 0;

	map->set_size(x, y);
	snaky->set(map);
	wall->set(wall_size, wall_coundown);
	int applePoint = rand() % map->unoccupiedNodes.size();
	apple.x = 0;
	apple.y = 0;
	apple = map->moveIter(applePoint);

	previousDirection = 0;

	timer = SetTimer(timer, 350, NULL);
}

void CChildView::end(grid *map, snake *snaky, appearingWall *wall)
{
	KillTimer(timer);
	wall->wallClear(map);
	wall->initialize.clear();
	map->unoccupiedNodes.clear();

	start(map, snaky, wall);
}

// CChildView

CChildView::CChildView() 
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;


	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	GetClientRect(&window_size);
	int ypix = 400, xpix = 400;
	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetViewportExt(window_size.right, window_size.bottom);
	dc.SetWindowExt(xpix, ypix);

	int coefficient_x=xpix/map.x;
	coefficient_x -= coefficient_x / map.x;
	int coefficient_y=ypix/map.y;
	coefficient_y -= coefficient_y / map.y;

	if (wall.countdown < 7)
	{
		CPen wallPen;
		CBrush wall_s;
		if (wall.countdown < 0) 
		{
			wall_s.CreateSolidBrush(RGB(128, 64, 0));
			dc.SelectObject(wall_s);
			wallPen.CreatePen(1, 1, RGB(128, 64, 0));
			dc.SelectObject(wallPen);

			for (POINT var : wall.built)
			{
				dc.Rectangle(generate_rect(var, coefficient_x, coefficient_y));
			}
		}
		else
		{
			wall_s.CreateSolidBrush(RGB(255, 166, 77));
			dc.SelectObject(wall_s);
			wallPen.CreatePen(1, 1, RGB(255, 166, 77));
			dc.SelectObject(wallPen);

			for (POINT var : wall.initialize)
			{
				dc.Rectangle(generate_rect(var, coefficient_x, coefficient_y));
			}
		}
	}

	CBrush innerBrush;
	innerBrush.CreateSolidBrush(RGB(0, 0, 0));
	dc.SelectObject(innerBrush);
	CPen pen;
	pen.CreatePen(PS_NULL, 1, RGB(255, 255, 255));
	dc.SelectObject(pen);

	for(POINT var : snaky.occupied)
	{
		dc.Rectangle(generate_rect(var, coefficient_x, coefficient_y));
	}

	dc.SelectObject(pen);
	CBrush apple_s;
	apple_s.CreateSolidBrush(RGB(255, 0, 0));
	dc.SelectObject(apple_s);
	dc.Ellipse(generate_rect(apple, coefficient_x, coefficient_y));
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	currentKey = nChar;

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
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
		if (wall.countdown == 3 && map.unoccupiedNodes.size() > wall.length+map.x && !wall.smallCountreset)
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

	if (success == 0)
	{
		KillTimer(timer);
		Invalidate();
		end(&map, &snaky, &wall);
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

	Invalidate();

	CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	start(&map, &snaky, &wall);
	return 0;
}