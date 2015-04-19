// LampServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LampServer.h"

#include "MainFrm.h"
#include "LampServerDoc.h"
#include "LampServerView.h"
#include "DlgLogin.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLampServerApp

BEGIN_MESSAGE_MAP(CLampServerApp, CWinApp)
	//{{AFX_MSG_MAP(CLampServerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
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


	CDlgLogin cdl;
	int res=cdl.DoModal();
	if(res!=IDOK)
		return FALSE;

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CLampServerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLampServerView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CLampServerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CLampServerApp message handlers

