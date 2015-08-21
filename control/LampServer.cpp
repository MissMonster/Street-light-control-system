// LampServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LampServer.h"

#include "DlgLogin.h"
#include "maindlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLampServerApp

BEGIN_MESSAGE_MAP(CLampServerApp, CWinApp)
	//{{AFX_MSG_MAP(CLampServerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLampServerApp construction

CLampServerApp::CLampServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLampServerApp object

CLampServerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLampServerApp initialization

BOOL CLampServerApp::InitInstance()
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


///////////////////////////////////////////////////////////////////////*��ȡ����ǰӦ�ó�������Ŀ¼
	TCHAR szAppPath[MAX_PATH];   
	memset(szAppPath,0,MAX_PATH);   
	GetModuleFileName(theApp.m_hInstance,szAppPath,MAX_PATH); //*��ȡ��ִ���ļ���ȫ·����������ִ���ļ������֣�
	CString exestr2;
	exestr2.Format(_T("%s"),szAppPath); 
	exePath=exestr2.Left(exestr2.ReverseFind('\\')+1);	
/////////////////////////////////////////////////////////////////////*	
	CString strIniPath;
	strIniPath.Format( "%sserverSet.ini" , exePath );
	GetPrivateProfileString( "database" , "server" , "localhost" , m_server.GetBuffer(MAX_PATH) , MAX_PATH , strIniPath );
	GetPrivateProfileString( "database" , "username" , "root" , m_username.GetBuffer(MAX_PATH) , MAX_PATH , strIniPath );
	GetPrivateProfileString( "database" , "pwd" , "" , m_password.GetBuffer(MAX_PATH) , MAX_PATH , strIniPath );
	GetPrivateProfileString( "database" , "database" , "lampmanage" , m_database.GetBuffer(MAX_PATH) , MAX_PATH , strIniPath );
	/*����Ϣ��INI�ļ��ж�������еı���.
����1.���õ�WINAPI����ԭ��Ϊ:
	DWORD GetPrivateProfileString(
	LPCTSTR lpAppName,
	LPCTSTR lpKeyName,
	LPCTSTR lpDefaut,
	LPSTR lpReturnedString,
	DWORD nSize,
	LPCTSTR lpFileName
	);
LPCTSTR lpAppName ------- INI�ļ��е�һ���ֶ���

LPCTSTR lpKeyName -------- lpAppName �µ�һ��������Ҳ�����������ı�����

LPCTSTR lpString ---------�Ǽ�ֵ��Ҳ���Ǳ�����ֵ�� ����ΪLPCTSTR��CString����

LPCTSTR lpFileName --------������INI�ļ�·����

LPCTSTR lpDefaut ----------���û����ǰ��������ֵ���򽫴�ֵ��������

LPSTR lpReturnedString --------����INI�ļ��е�ֵ��CString���󣬼����ջ�����

DWORD nSize ------���ջ������Ĵ�С
*/
///////////////////////////////////////////////////////////////////////////

/*
	CDlgLogin cdl;
	int res=cdl.DoModal();
	if(res!=IDOK)
		return FALSE;

*/
	maindlg dlg;
	dlg.DoModal();
	
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CLampServerApp message handlers

