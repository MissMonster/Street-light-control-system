// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


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

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
	m_strShow = _T("");
	m_strMsg = _T("");
	m_uPort = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Text(pDX, IDC_EDIT1, m_strShow);
	DDX_Text(pDX, IDC_EDIT3, m_strMsg);
	DDX_Text(pDX, IDC_EDIT4, m_uPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_CLIENTMSG,OnClientMsg)//////////////////////////////******************************
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	//设置IP以及端口号的默认值****************************
	CIPAddressCtrl * m_Address=(CIPAddressCtrl*)GetDlgItem(IDC_IPADDRESS1); 
//	m_Address->SetAddress(172,25,64,14);
	m_Address->SetAddress(172,25,176,79);
	GetDlgItem(IDC_EDIT4)->SetWindowText(_T("8080"));


	WSADATA wsaData; 
	WORD wVersionRequested = MAKEWORD(2, 0);  
	WSAStartup(wVersionRequested, &wsaData); 
	m_hSocket=socket(AF_INET,SOCK_STREAM,0);//调用socket函数创建套接字  
	WSAAsyncSelect(m_hSocket,this->m_hWnd,WM_CLIENTMSG, FD_CONNECT | FD_READ | FD_WRITE | FD_CLOSE);//利用异步选择模型,自动设置为非阻塞模式 
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(true);   
	BYTE f0,f1,f2,f3; 
	m_ip.GetAddress(f0,f1,f2,f3);
	CString addr; 
	addr.Format("%d.%d.%d.%d", f0, f1, f2, f3);  
	m_addr.sin_family = AF_INET; 
	m_addr.sin_addr.S_un.S_addr = inet_addr(addr.GetBuffer(0));  
	m_addr.sin_port = htons(m_uPort);  
	connect(m_hSocket,(LPSOCKADDR)&m_addr,sizeof(m_addr));//连接服务器 
//	connect(m_hSocket,(SOCKADDR*)&m_addr,sizeof(m_addr));
	UINT tt=WSAGetLastError();  
	switch(tt)  
	{ 
	case 10035:   
		break;  
	default: 
		UpdateData(false); 
		closesocket(this->m_hSocket);   
		this->OnInitDialog();   
		this->OnButton2();  
	} 

}

void CClientDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);  
	m_strShow += "\r\n";  
	m_strShow += m_strMsg; 
	send(m_hSocket,m_strMsg.GetBuffer(0),m_strMsg.GetLength(),0);  
	UINT tt=WSAGetLastError();  
	if(tt!=0)  { 
	m_strShow+="\r\n发送失败!";  } 
	m_strMsg.Empty();  
	UpdateData(FALSE); 
}

void CClientDlg::OnDestroy()
{
	CDialog::OnDestroy();  
	WSAAsyncSelect(m_hSocket, this->m_hWnd, 0, 0);//取消异步选择模式  
	WSACleanup();//关闭套接字，终止连接释放资源
}
long CClientDlg::OnClientMsg(WPARAM wParam, LPARAM lParam) 
{ 
	char buf[1024];  
	int len; 
	switch(lParam)  
	{ 
	case FD_CONNECT:  
		m_strShow = "连接到服务器……";   
		UpdateData(FALSE);    
		return 0;  
	case FD_READ: 
		len = recv(m_hSocket, buf, 1024, 0); 
		buf[len]=NULL; 
		m_strShow += "\r\n";   
		m_strShow += buf;   
		UpdateData(FALSE);   
		return 0;  
	case FD_WRITE:   
		return 0;  
	case FD_CLOSE: 
		m_strShow += "\r\n服务器关闭";   
		closesocket(m_hSocket);   
		UpdateData(FALSE);    
		return 0;  
	default: 
		m_strShow+="\r\n找不到服务器,请确认服务器IP和端口号是否正确";   
		closesocket(m_hSocket);   
		UpdateData(FALSE);    
		return 0;  
	} 
} 

void CClientDlg::OnButton3() 
{
	// TODO: Add your control notification handler code here
	closesocket(m_hSocket);
	
}
