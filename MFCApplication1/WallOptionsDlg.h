#pragma once
#include "afxwin.h"


// CWallOptionsDlg dialog

class CWallOptionsDlg : public CDialog
{
	DECLARE_DYNAMIC(CWallOptionsDlg)

public:
	CWallOptionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CWallOptionsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTINGS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	UINT x_spaces;
	UINT y_spaces;
	UINT wall_spaces;
	UINT countdown;
	CEdit enableDisable;
	afx_msg void OnEnKillfocusEditSize();
	afx_msg void OnBnClickedExit();
};
