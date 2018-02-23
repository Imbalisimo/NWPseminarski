
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

void CChildView::start()
{
	gameObj.start();
	timer = SetTimer(timer, 350, NULL);
}

void CChildView::end()
{
	KillTimer(timer);
	
	gameObj.end();
	start();

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

	int coefficient_x=xpix/ gameObj.map.x;
	coefficient_x -= coefficient_x / gameObj.map.x;
	int coefficient_y=ypix/ gameObj.map.y;
	coefficient_y -= coefficient_y / gameObj.map.y;
	CString str = _T("SCORE:");
	str.Append(std::to_wstring(gameObj.snaky.length - 4).c_str());
	dc.DrawText(str, &window_size, 0);

	if (gameObj.wall.countdown < 7)
	{
		CPen wallPen;
		CBrush wall_s;
		if (gameObj.wall.countdown < 0)
		{
			wall_s.CreateSolidBrush(RGB(128, 64, 0));
			dc.SelectObject(wall_s);
			wallPen.CreatePen(1, 1, RGB(128, 64, 0));
			dc.SelectObject(wallPen);

			for (POINT var : gameObj.wall.built)
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

			for (POINT var : gameObj.wall.initialize)
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

	for(POINT var : gameObj.snaky.occupied)
	{
		dc.Rectangle(generate_rect(var, coefficient_x, coefficient_y));
	}

	dc.SelectObject(pen);
	CBrush apple_s;
	apple_s.CreateSolidBrush(RGB(255, 0, 0));
	dc.SelectObject(apple_s);
	dc.Ellipse(generate_rect(gameObj.apple, coefficient_x, coefficient_y));
	// Do not call CWnd::OnPaint() for painting messages
}



void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar >= VK_LEFT && nChar <= VK_DOWN)
		gameObj.moveTo(nChar);

	if (nChar == 0x50) //letter P
	{
		if (timerFlag)
			KillTimer(timer);
		else
			timer = SetTimer(timer, 350, NULL);
		timerFlag = !timerFlag;
	}
	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	if (!gameObj.move())
		end();
	
	Invalidate();

	CWnd::OnTimer(nIDEvent);
}


int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	start();
	return 0;
}