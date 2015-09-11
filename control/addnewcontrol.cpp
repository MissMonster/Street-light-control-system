// addnewcontrol.cpp : implementation file
//

#include "stdafx.h"
#include "control.h"
#include "addnewcontrol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// addnewcontrol dialog


addnewcontrol::addnewcontrol(CWnd* pParent /*=NULL*/)
	: CDialog(addnewcontrol::IDD, pParent)
{
	//{{AFX_DATA_INIT(addnewcontrol)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void addnewcontrol::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(addnewcontrol)
	DDX_Control(pDX, IDC_COMBO1, m_controllerAutorun);
	DDX_Control(pDX, IDC_EDIT5, m_streetlightNum);
	DDX_Control(pDX, IDC_EDIT4, m_controllerLatitude);
	DDX_Control(pDX, IDC_EDIT3, m_controllerLongitude);
	DDX_Control(pDX, IDC_EDIT2, m_controllerInfo);
	DDX_Control(pDX, IDC_EDIT1, m_controllerId);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(addnewcontrol, CDialog)
	//{{AFX_MSG_MAP(addnewcontrol)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// addnewcontrol message handlers

void addnewcontrol::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void addnewcontrol::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL addnewcontrol::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_controllerAutorun.AddString("自动");
	m_controllerAutorun.AddString("手动");
	m_controllerAutorun.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
