// aboutdlg.cpp : implementation file
//

#include "stdafx.h"
#include "baidumap.h"
#include "aboutdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// aboutdlg dialog


aboutdlg::aboutdlg(CWnd* pParent /*=NULL*/)
	: CDialog(aboutdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(aboutdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void aboutdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(aboutdlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(aboutdlg, CDialog)
	//{{AFX_MSG_MAP(aboutdlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// aboutdlg message handlers
