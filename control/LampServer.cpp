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


///////////////////////////////////////////////////////////////////////*获取到当前应用程序所在目录
	TCHAR szAppPath[MAX_PATH];   
	memset(szAppPath,0,MAX_PATH);   
	GetModuleFileName(theApp.m_hInstance,szAppPath,MAX_PATH); //*获取可执行文件的全路径（包括可执行文件的名字）
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
	/*将信息从INI文件中读入程序中的变量.
　　1.所用的WINAPI函数原型为:
	DWORD GetPrivateProfileString(
	LPCTSTR lpAppName,
	LPCTSTR lpKeyName,
	LPCTSTR lpDefaut,
	LPSTR lpReturnedString,
	DWORD nSize,
	LPCTSTR lpFileName
	);
LPCTSTR lpAppName ------- INI文件中的一个字段名

LPCTSTR lpKeyName -------- lpAppName 下的一个键名，也就是里面具体的变量名

LPCTSTR lpString ---------是键值，也就是变量的值， 必须为LPCTSTR或CString类型

LPCTSTR lpFileName --------完整的INI文件路径名

LPCTSTR lpDefaut ----------如果没有其前两个参数值，则将此值赋给变量

LPSTR lpReturnedString --------接收INI文件中的值的CString对象，即接收缓冲区

DWORD nSize ------接收缓冲区的大小
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

