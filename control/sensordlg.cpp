// sensordlg.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "sensordlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// sensordlg dialog


sensordlg::sensordlg(CWnd* pParent /*=NULL*/)
	: CDialog(sensordlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(sensordlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void sensordlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(sensordlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(sensordlg, CDialog)
	//{{AFX_MSG_MAP(sensordlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// sensordlg message handlers
