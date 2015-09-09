// about.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "about.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// about dialog


about::about(CWnd* pParent /*=NULL*/)
	: CDialog(about::IDD, pParent)
{
	//{{AFX_DATA_INIT(about)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void about::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(about)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(about, CDialog)
	//{{AFX_MSG_MAP(about)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// about message handlers

void about::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void about::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}
