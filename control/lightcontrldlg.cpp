// lightcontrldlg.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "lightcontrldlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// lightcontrldlg dialog


lightcontrldlg::lightcontrldlg(CWnd* pParent /*=NULL*/)
	: CDialog(lightcontrldlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(lightcontrldlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void lightcontrldlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(lightcontrldlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(lightcontrldlg, CDialog)
	//{{AFX_MSG_MAP(lightcontrldlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// lightcontrldlg message handlers
