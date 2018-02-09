
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChildView.h"
#include <map>
#include <list>
#include <vector>
#include <iterator>
#include "node.h"
#include "snake.h"
#include "grid.h"
#include "appearingWall.h"

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

// CChildView

CChildView::CChildView() {
}

CChildView::~CChildView()
{
	KillTimer(timer);
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
	int coefficient_y=ypix/map.y;



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
	POINT p = snaky.occupied.front();
	POINT searchingPoint = p;
	if (previousDirection + 2 == currentKey || previousDirection - 2 == currentKey)
		currentKey = previousDirection;
	switch (currentKey)
	{
	case VK_UP:
		if (p.y <= 0)
			success = 0;
		else
			if (previousDirection != VK_DOWN)
				--searchingPoint.y;
		break;
	case VK_DOWN:
		if (p.y >= map.y)
			success = 0;
		else
			if (previousDirection != VK_UP)
				++searchingPoint.y;
		break;
	case VK_LEFT:
		if (p.x <= 0)
			success = 0;
		else
			if (previousDirection != VK_RIGHT)
				--searchingPoint.x;
		break;
	case VK_RIGHT:
		if (p.x >= map.x)
			success = 0;
		else
			if (previousDirection != VK_LEFT)
				++searchingPoint.x;
		break;
	}
	p = searchingPoint;

	if (previousDirection != currentKey) {
		previousDirection = currentKey;
	}

	//DA LI JE UDARILA U ZID ILI SEBE (VARIJABLA P)
	/*if(success==0)
	????????????????
	*/

	snaky.occupied.push_front(p);

	map.unoccupiedNodes.erase(p);
	if (p != apple) {   //da li je pokupila jabuku
		p = snaky.occupied.back();
		map.unoccupiedNodes[p] = p.y*map.x + p.x;
		snaky.occupied.pop_back();
	}
	else {
		++snaky.length;
		int appleNode = rand() % map.unoccupiedNodes.size();
		apple = map.moveIter(appleNode); //MORA POSTOJATI BOLJI NACIN
	}

	if (wall.countdown < 7)
	{
		if (wall.countdown == 3 && map.unoccupiedNodes.size() > 15)
			wall.RdyToappear(&map, apple);
		if (wall.countdown == 0)
			wall.onAppearance(&snaky, &map, apple);
		if (wall.countdown == -6)
			wall.wallClear(&map);
	}
	--wall.countdown;

	Invalidate();

	CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	int x = 15, y = 15, wall_size = 20, wall_coundown = 10;
	//UCITAVANJE IZ FILEA!!!!!!  (kako?)
	map.set_size(x, y);
	snaky.set(&map);
	wall.set(wall_size, wall_coundown);
	int applePoint = rand() % map.unoccupiedNodes.size();
	apple = map.moveIter(applePoint);

	previousDirection = 0;

	timer = SetTimer(timer, 350, NULL);

	return 0;
}
