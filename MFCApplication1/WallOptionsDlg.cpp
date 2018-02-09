// WallOptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WallOptionsDlg.h"
#include "afxdialogex.h"
#include "resource.h"


// CWallOptionsDlg dialog

IMPLEMENT_DYNAMIC(CWallOptionsDlg, CDialog)

CWallOptionsDlg::CWallOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_DIALOG_SETTINGS, pParent)
	, x_spaces(0)
	, y_spaces(0)
	, wall_spaces(0)
	, countdown(0)
{

}

CWallOptionsDlg::~CWallOptionsDlg()
{
}

void CWallOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDITx, x_spaces);
	DDV_MinMaxUInt(pDX, x_spaces, 7, 100);
	DDX_Text(pDX, IDC_EDITY, y_spaces);
	DDV_MinMaxUInt(pDX, y_spaces, 7, 100);
	DDX_Text(pDX, IDC_EDIT_SIZE, wall_spaces);
	DDV_MinMaxUInt(pDX, wall_spaces, 0, 150);
	DDX_Text(pDX, IDC_EDIT_COUNTDOWN, countdown);
	DDV_MinMaxUInt(pDX, countdown, 0, 10);
	DDX_Control(pDX, IDC_EDIT_COUNTDOWN, enableDisable);
}


BEGIN_MESSAGE_MAP(CWallOptionsDlg, CDialog)
	ON_EN_KILLFOCUS(IDC_EDIT_SIZE, &CWallOptionsDlg::OnEnKillfocusEditSize)
	ON_BN_CLICKED(IDCANCEL, &CWallOptionsDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CWallOptionsDlg message handlers



void CWallOptionsDlg::OnEnKillfocusEditSize()
{
	if (wall_spaces == 0)
		enableDisable.EnableWindow(false);
	else
		enableDisable.EnableWindow(true);
}


void CWallOptionsDlg::OnBnClickedCancel()
{
	exit(0);
	CDialog::OnCancel();
}
