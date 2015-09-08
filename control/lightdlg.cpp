// lightdlg.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "lightdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// lightdlg dialog


lightdlg::lightdlg(CWnd* pParent /*=NULL*/)
	: CDialog(lightdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(lightdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void lightdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(lightdlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(lightdlg, CDialog)
	//{{AFX_MSG_MAP(lightdlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// lightdlg message handlers
