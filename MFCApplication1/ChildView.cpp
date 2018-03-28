
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChildView.h"
#include "snake.h"
#include "grid.h"
#include "appearingWall.h"
#include "WallOptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void CChildView::start()
{
	gameObj.start();
	timer = SetTimer(timer, gameObj.time, NULL);
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
	RECT window_size;
	GetClientRect(&window_size);
	int ypix = 400, xpix = 400;
	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetViewportExt(window_size.right, window_size.bottom);
	dc.SetWindowExt(xpix, ypix);

	
	int coefficient_x = xpix / gameObj.map.x;
	int coefficient_y = ypix / gameObj.map.y;

	gameObj.wall.drawWall(&dc, coefficient_x, coefficient_y);

	gameObj.snaky.drawSnake(&dc, coefficient_x, coefficient_y);

	gameObj.drawApple(&dc, coefficient_x, coefficient_y);

	gameObj.drawScore(&dc, window_size);
	
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
			timer = SetTimer(timer, gameObj.time, NULL);
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