// googlemapDlg.cpp : implementation file
//

#include "stdafx.h"
#include "googlemap.h"
#include "googlemapDlg.h"
#include "webbrowser2.h"
#include "WebPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWebBrowser2 m_map;

/////////////////////////////////////////////////////////////////////////////
// CGooglemapDlg dialog

CGooglemapDlg::CGooglemapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGooglemapDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGooglemapDlg)
	m_lat = _T("");
	m_long = _T("");
	m_Zoom_Level = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGooglemapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGooglemapDlg)
	DDX_Control(pDX, IDC_EXPLORER1, m_map);
	DDX_Text(pDX, IDC_EDIT1, m_lat);
	DDX_Text(pDX, IDC_EDIT2, m_long);
	DDX_Text(pDX, IDC_EDIT3, m_Zoom_Level);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGooglemapDlg, CDialog)
	//{{AFX_MSG_MAP(CGooglemapDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGooglemapDlg message handlers

BOOL CGooglemapDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_map.Navigate(_T("file:///D:/Google-earth.html"), NULL, NULL, NULL, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGooglemapDlg::OnPaint() 
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
HCURSOR CGooglemapDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CGooglemapDlg::OnOK() 
{
	// TODO: Add extra validation here
	UpdateData(TRUE);  
    CWebPage web;
    web.SetDocument(m_map.GetDocument());  
    CComVariant varResult;  
    //const CString funcName("TansTo");  
	const CString funcName("setlocation"); 
    const CString m_latitude(m_lat);  //传递的参数：纬度  
    const CString m_longtitude(m_long);  //传递的参数：经度   
    const CString m_lev(m_Zoom_Level);  
    web.CallJScript(funcName,m_latitude,m_longtitude,m_lev);  
	//CDialog::OnOK();
}

void CGooglemapDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);  
    CWebPage web;
    web.SetDocument(m_map.GetDocument()); 
    const CString funcName("TansTo");  
    const CString m_latitude("28.184623");//传递的参数：纬度  
    const CString m_longtitude("112.949692");//经度  
    web.CallJScript(funcName,m_latitude,m_longtitude,"16"); 
}
