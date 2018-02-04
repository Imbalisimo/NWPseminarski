
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "node.h"
#include "snake.h"
#include "grid.h"
#include "appearingWall.h"

// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();
	RECT window_size;
	POINT grid_size;
	node *apple;
	UINT previousKey;
	grid map;
	snake snaky;
	appearingWall wall;
// Attributes
public:

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
};

