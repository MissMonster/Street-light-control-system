// usercontrol.cpp : implementation file
//

#include "stdafx.h"
#include "LampServer.h"
#include "usercontrol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// usercontrol dialog


usercontrol::usercontrol(CWnd* pParent /*=NULL*/)
	: CDialog(usercontrol::IDD, pParent)
{
	//{{AFX_DATA_INIT(usercontrol)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void usercontrol::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(usercontrol)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(usercontrol, CDialog)
	//{{AFX_MSG_MAP(usercontrol)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// usercontrol message handlers

void usercontrol::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void usercontrol::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}