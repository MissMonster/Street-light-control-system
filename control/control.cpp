// control.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DataStructure.h"
#include "control.h"
#include "land.h"
#include "controlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

struct serverset serverinfo;
struct userdata  userinfo;

/////////////////////////////////////////////////////////////////////////////
// CControlApp

BEGIN_MESSAGE_MAP(CControlApp, CWinApp)
	//{{AFX_MSG_MAP(CControlApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlApp construction

CControlApp::CControlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CControlApp object

CControlApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CControlApp initialization

BOOL CControlApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	if(readserverset()!=0)
	{
		return FALSE;
	}

	land landdlg;
	if(landdlg.DoModal()!=IDOK)
	{
		return FALSE;
	}
	
	CControlDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CControlApp::readserverset()
{
	FILE* fp=fopen("serverSet.ini","r");
	if(fp==NULL)
	{
		AfxMessageBox("Œ¥’“µΩ≈‰÷√Œƒº˛!");
		return -1;
	}
	fscanf(fp,"server=%s\nusername=%s\npwd=%s\ndatabase=%s\nport=%d",
		serverinfo.ip,serverinfo.name,serverinfo.password,serverinfo.database,&serverinfo.port);
//	AfxMessageBox(serverinfo.database);
//	AfxMessageBox(serverinfo.ip);
//	AfxMessageBox(serverinfo.name);
//	AfxMessageBox(serverinfo.password);
//	char port[20];
//	sprintf(port,"%d",serverinfo.port);
//	AfxMessageBox(port);
	return 0;
}
