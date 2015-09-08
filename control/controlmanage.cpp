// controlmanage.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "controlmanage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// controlmanage dialog


controlmanage::controlmanage(CWnd* pParent /*=NULL*/)
	: CDialog(controlmanage::IDD, pParent)
{
	//{{AFX_DATA_INIT(controlmanage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void controlmanage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(controlmanage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(controlmanage, CDialog)
	//{{AFX_MSG_MAP(controlmanage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// controlmanage message handlers
