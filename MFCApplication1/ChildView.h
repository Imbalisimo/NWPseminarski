
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "snake.h"
#include "grid.h"
#include "appearingWall.h"
#include "game.h"
#include "WallOptionsDlg.h"

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();
	RECT window_size;
	POINT grid_size;
	game gameObj;
	bool timerFlag=true;
	int timer=1;
// Attributes
public:
	void start();
	void end();
// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

