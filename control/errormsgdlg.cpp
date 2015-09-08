// errormsgdlg.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "errormsgdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// errormsgdlg dialog


errormsgdlg::errormsgdlg(CWnd* pParent /*=NULL*/)
	: CDialog(errormsgdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(errormsgdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void errormsgdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(errormsgdlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(errormsgdlg, CDialog)
	//{{AFX_MSG_MAP(errormsgdlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// errormsgdlg message handlers
